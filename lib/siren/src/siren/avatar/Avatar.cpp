#include <siren/avatar/Avatar.h>
#include <siren/avatar/AvatarLoader.h>
#include <siren/Texture.h>
#include <siren/ResourceManager.h>

namespace siren
{
   /**
    * Cache policy for CalCoreModel objects so that they can be used with the
    * resource management system.
    */
   template<>
   struct siren::CachePolicy<CalCoreModel*>
   {
      static CalCoreModel* copy(CalCoreModel* cacheVal)
      {
         return cacheVal;
      }

      static CalCoreModel* create(const std::string& name)
      {
         return loadCoreModel(name);
      }

      static void destroy(CalCoreModel* val)
      {
         val->destroy();
         delete val;
      }
   };

   /**
    * Cache policy for Avatar objects so that they can be used with the
    * resource management system.
    */
   template<>
   struct siren::CachePolicy<Avatar*>
   {
      static Avatar* copy(Avatar* cacheVal)
      {
         return new Avatar(cacheVal->model()->getCoreModel());
      }

      static Avatar* create(const std::string& name)
      {
         CalCoreModel* core_model =
            ResourceManagerSingleton::instance().get<CalCoreModel*>(name);

         return new Avatar(core_model);
      }

      static void destroy(Avatar* val)
      {
         delete val;
      }
   };

   Avatar::Avatar(CalCoreModel* coremodel)
   {
      //Path
      mPath = "";

      //Drawing options
      mDrawMode = DrawMesh;
      mTexturing = true;
      mShadowColor[0] = mShadowColor[1] = mShadowColor[2] = 0.05f;
      mShadowColor[3] = 0.3f;

      //Animations
      mCurrentAnimIDs.clear();
      mCurrentAnimCycles.clear();

      //Movement
      mDestination.set(0,0,0);
      mMoveSpeed = 0;

      //Mesh data
      mVertices.clear();
      mNormals.clear();
      mTextureCoords.clear();
      mFaces.clear();
      mTextureCoordCounts.clear();
      mFaceCounts.clear();

      //Create new CalModel based on the core model
      if ((coremodel == NULL) || (!mModel.create(coremodel)))
      {
         mModel.destroy();
         std::cerr
            << "Avatar: Failed to create avatar\n"
            << std::endl;
      }

      // attach all meshes to the model
      int meshId;
      for (meshId = 0; meshId < mModel.getCoreModel()->getCoreMeshCount(); meshId++)
      {
         mModel.attachMesh(meshId);
      }

      // set the material set of the whole model
      mModel.setMaterialSet(0);

      mWCS = gmtl::EulerAngleXYZf(0,0,0);
      mCoord.pos() = gmtl::Vec3f(0,0,0);
      mCoord.rot() = gmtl::EulerAngleXYZf(0,0,0);
      mScale = 1.0;

      //Find the amounts of memory we will need for each submesh
      CalRenderer* renderer = new CalRenderer(mModel.getRenderer());

      int meshCount = renderer->getMeshCount();

      //Initialize mVertices, mNormals, mFaces, mTextureCoordCounts sizes for
      //the mesh count with dummy vectors
      std::vector<float*> tempVecF; tempVecF.clear();
      std::vector<int*> tempVecI; tempVecI.clear();
      std::vector<int> tempVec0; tempVec0.clear();

      mVertices.resize(meshCount, tempVecF);
      mNormals.resize(meshCount, tempVecF);
      mFaces.resize(meshCount, tempVecI);
      mTextureCoords.resize(meshCount, tempVecF);
      mTextureCoordCounts.resize(meshCount, tempVec0);
      mFaceCounts.resize(meshCount, tempVec0);

      for (int i=0; i < meshCount; i++)
      {
         int submeshCount = renderer->getSubmeshCount(i);

         //Initialize the data vectors for proper submesh size (with NULL data)
         mVertices[i].resize(submeshCount, NULL);
         mNormals[i].resize(submeshCount, NULL);
         mFaces[i].resize(submeshCount, NULL);
         mTextureCoords[i].resize(submeshCount, NULL);
         mTextureCoordCounts[i].resize(submeshCount, 0);
         mFaceCounts[i].resize(submeshCount, 0);

         for (int j=0; j < submeshCount; j++)
         {
            renderer->selectMeshSubmesh(i, j);

            //Get vertex count (equal numbers of vertices, normals, and texture coords)
            int vertexCount = renderer->getVertexCount();

            //Get face count
            int faceCount = renderer->getFaceCount();

            //Declare all the memory
            mVertices[i][j] = new float[vertexCount * 3];
            mNormals[i][j] = new float[vertexCount * 3];
            mFaces[i][j] = new int[faceCount * 3];

            // set the texture coordinate buffer and state if necessary
            if (renderer->getMapCount() > 0)
            {
               mTextureCoords[i][j] = new float[vertexCount * 2];
            }
            else
            {
               //If there are no texture coords, allocate space for a dummy value
               mTextureCoords[i][j] = new float[1];
            }

         }

      }

      renderer->destroy();
      delete renderer;


      //Load all textures (context specific for multipiping)
      // load all textures and store the opengl texture id in the corresponding map in the material
      for (int materialId = 0; materialId < mModel.getCoreModel()->getCoreMaterialCount(); materialId++)
      {
         // get the core material
         CalCoreMaterial *pCoreMaterial;
         pCoreMaterial = mModel.getCoreModel()->getCoreMaterial(materialId);

         // loop through all maps of the core material
         int mapId;
         for (mapId = 0; mapId < pCoreMaterial->getMapCount(); mapId++)
         {

            // get the filename of the texture
            std::string strFilename;
            strFilename = pCoreMaterial->getMapFilename(mapId);

            // get the texture number from the texture loader
            std::cerr << "Creating texture with name " << (mPath+strFilename) << std::endl;
            Texture* tex = Texture::create(mPath+strFilename);

            // store the texture number in the user data of the map
            pCoreMaterial->setMapUserData(mapId, (Cal::UserData)tex);

         }
      }
   }

   Avatar::~Avatar()
   {
      //Deallocate all of the memory we took

      //Find the amounts of memory we will need for each submesh
      CalRenderer* renderer = new CalRenderer(mModel.getRenderer());

      int meshCount = renderer->getMeshCount();

      for (int i=0; i < meshCount; i++)
      {
         int submeshCount = renderer->getSubmeshCount(i);
         for (int j=0; j < submeshCount; j++)
         {
            delete [] mVertices[i][j];
            delete [] mNormals[i][j];
            delete [] mTextureCoords[i][j];
            delete [] mFaces[i][j];
         }

      }

      mFaceCounts.clear();
      mTextureCoordCounts.clear();

      //Destroy the renderer
      renderer->destroy();
      delete renderer;

      //Destroy the model instance
      mModel.destroy();
   }

   Avatar*
   Avatar::create(const std::string& name)
   {
      return ResourceManagerSingleton::instance().get<Avatar*>(name);
   }

   /* Set the path where the texture files are.
   ** If using the AvatarFactory class, the factory will set this parameter.
   */
   void Avatar::setPath(const std::string& path)
   {
      mPath = path;

      //Append the slash if it isn't there already
      if (mPath[ mPath.size()-1 ] != '/')
      {
         mPath += "/";
      }

   }

   // Trigger animation cycle
   bool Avatar::triggerAnimationCycle(int id)
   {

      if ((id < 0) || (id >= mModel.getCoreModel()->getCoreAnimationCount()))
      {
         std::cerr
            << "Avatar: Could not start animation cycle number " << id << "\n"
            << std::endl;

         return false;
      }

      //First make sure it isn't already cycling
      std::vector<int>::iterator iter;
      for (iter = mCurrentAnimIDs.begin(); iter != mCurrentAnimIDs.end(); iter++)
      {
         if (*iter == id)
         {
            return true; //If it is already, we're done then
         }
      }

      //Add the animation to the list of cycling animations
      mCurrentAnimIDs.push_back(id);

      //Start the cycling, with full weight and a one second startup interpolation time
      mModel.getMixer()->blendCycle(id, 1.0f, 1.0f);

      return true;
   }

   bool Avatar::triggerAnimationCycle(const std::string& name)
   {
      return triggerAnimationCycle(getAnimID(name));
   }

   // Trigger animation once
   bool Avatar::triggerAnimation(int id)
   {
      if ((id < 0) || (id >= mModel.getCoreModel()->getCoreAnimationCount()))
      {
         std::cerr
            << "Avatar: Could not start animation number " << id << "\n"
            << std::endl;
      }

      //Execute the action just once, with full weight and no delay of execution
      mModel.getMixer()->executeAction(id, 1.0f, 0.0f);

      return true;
   }

   bool Avatar::triggerAnimation( const std::string& name )
   {
      return triggerAnimation(getAnimID(name));
   }

   //Stop an animation, whether it is cyclic or a single execution
   bool Avatar::stopAnimation(int id)
   {
      if ((id < 0) || (id >= mModel.getCoreModel()->getCoreAnimationCount()))
      {
         std::cerr
            << "Avatar: Could not stop animation ID " << id << "\n"
            << std::endl;

         return false;
      }

      //Clear the animation's cycle (set it to weight 0.0) with no delay
      if (!mModel.getMixer()->clearCycle(id, 0.0f))
      {
         return false;
      }

      //Remove it from the list of cyclic animations if it's in the vector
      std::vector<int>::iterator iter;
      for (iter=mCurrentAnimIDs.begin(); iter != mCurrentAnimIDs.end(); iter++)
      {
         if (*iter == id)
         {
            mCurrentAnimIDs.erase(iter);
            break;
         }
      }

      return true;
   }

   bool Avatar::stopAnimation(const std::string& name)
   {
      return stopAnimation(getAnimID(name));
   }

   //Returns false if animation ID doesn't exist or if it isn't running
   bool Avatar::checkAnimation(int id)
   {
      if ((id < 0) || (id >= mModel.getCoreModel()->getCoreAnimationCount()))
      {
         return false;
      }

      //Scan through the list of currently executing animations
      std::vector<int>::iterator iter;
      for (iter = mCurrentAnimIDs.begin(); iter != mCurrentAnimIDs.end(); iter++)
      {
         if (*iter == id )
         {
            return true;
         }
      }

      return false;
   }

   bool Avatar::checkAnimation(const std::string& name)
   {
      return checkAnimation(getAnimID(name));
   }

   //Stop all running animations
   bool Avatar::stopAllAnimations()
   {
      bool status = true;

      //Stop all cyclic animations (if any)
      if (mCurrentAnimIDs.size() > 0)
      {
         std::vector<int>::iterator iter;
         for (iter = mCurrentAnimIDs.begin(); mCurrentAnimIDs.size() > 0; iter = mCurrentAnimIDs.begin())
         {
            if (!stopAnimation((*iter))) status = false;
         }
         mCurrentAnimIDs.clear();
      }

      //Stop all single-action animations
      std::list<CalAnimationAction *>::iterator iter;

      for (iter = model()->getMixer()->m_listAnimationAction.begin();
           iter != model()->getMixer()->m_listAnimationAction.end();
           iter++ )
      {
         (*iter)->destroy();
         delete (*iter);
      }
      model()->getMixer()->m_listAnimationAction.clear();

      return true;
   }

   //Start the avatar moving to a specific position at a given speed (units/sec)
   void Avatar::moveTo(const gmtl::Vec3f& position, float speed)
   {
      mDestination = position;
      mMoveSpeed = speed;
   }

   //Query whether we are carrying out a positional movement
   bool Avatar::isMoving()
   {
      return (mMoveSpeed != 0.0f);
   }

   std::vector<int> Avatar::getCurrentAnimIDs()
   {
      return mCurrentAnimIDs;
   }

   bool Avatar::update(float deltaTime)
   {

      if (!updateAnimations(deltaTime))
      {
         return false;
      }

      if (!updateMesh(deltaTime))
      {
         return false;
      }

      if (!updateMove(deltaTime))
      {
         return false;
      }

      return true;
   }

   // Update the skeleton for animations
   bool Avatar::updateAnimations(float deltaTime)
   {
      mModel.getMixer()->updateAnimation(deltaTime);
      mModel.getMixer()->updateSkeleton();

      return true;
   }

   // Update the mesh after the skeleton has been set for the frame
   bool Avatar::updateMesh(float deltaTime)
   {
      mModel.getPhysique()->update();
      mModel.getSpringSystem()->update(deltaTime);

      CalRenderer* renderer = new CalRenderer(mModel.getRenderer());

      //Get the mesh data for all meshes and submeshes
      int meshCount = renderer->getMeshCount();

      // get all meshes of the model
      int meshId;
      for (meshId = 0; meshId < meshCount; meshId++)
      {
         int submeshId, submeshCount;

         submeshCount = renderer->getSubmeshCount(meshId);

         // get all submeshes of the mesh
         for (submeshId = 0; submeshId < submeshCount; submeshId++)
         {

            // select mesh and submesh and grab all the data
            if (renderer->selectMeshSubmesh(meshId, submeshId))
            {

               // get the transformed vertices of the submesh
               renderer->getVertices(mVertices[meshId][submeshId]);

               // get the transformed normals of the submesh
               renderer->getNormals(mNormals[meshId][submeshId]);

               // get the texture coordinates of the submesh
               mTextureCoordCounts[meshId][submeshId] = renderer->getTextureCoordinates(0, mTextureCoords[meshId][submeshId]);

               // get the faces of the submesh
               mFaceCounts[meshId][submeshId] = renderer->getFaces(mFaces[meshId][submeshId]);
            }
            else
            {
               std::cerr
                  << "Avatar: Attempting to update for an invalid submesh (this is bad)\n"
                  << std::endl;
            }

         }
      }

      renderer->destroy();
      delete renderer;

      return true;

   }

   //Just update the positional movement (delta is in seconds)
   bool Avatar::updateMove(float deltaTime)
   {
      //If we have no speed then we aren't moving
      if (!isMoving())
      {
         return true;
      }

      //Check to see if we are already there
      if (mCoord.getPos() == mDestination)
      {
         mMoveSpeed = 0;
         return true;
      }

      //Rotate the avatar to face the destination
      gmtl::Vec3f pathVec = mDestination - mCoord.getPos();;

      gmtl::Vec3f direction = pathVec;
      gmtl::normalize(direction);

      //If this will be close to a 180-degree rotation,
      //Make 2 different rotations about the Y-axis.
      gmtl::Quatf tempRot;
      if (gmtl::length( gmtl::Vec3f(0,0,-1) - direction) < 0.15)
      {
         gmtl::Quatf rot1 = gmtl::makeRot<gmtl::Quatf>(gmtl::Vec3f(0,0,1), gmtl::Vec3f(1,0,0));
         gmtl::Quatf rot2 = gmtl::makeRot<gmtl::Quatf>(gmtl::Vec3f(1,0,0), direction);
         tempRot = rot1 * rot2;
      }
      else
      {
         tempRot = gmtl::makeRot<gmtl::Quatf>(gmtl::Vec3f(0,0,1), direction);
      }

      gmtl::Matrix44f newRotation = gmtl::make<gmtl::Matrix44f>(tempRot);

      mCoord.mRot = gmtl::make<gmtl::EulerAngleXYZf>(newRotation);

      //Check to see if we within completion of the destination
      if (gmtl::length(pathVec) <= (mMoveSpeed * deltaTime))
      {
         //Move to destination
         mCoord.pos() = mDestination;

         //Set speed to 0
         mMoveSpeed = 0;
      }
      else
      {
         //Then we are not within finishing distance
         //Move the max distance
         mCoord.pos() += (direction * (mMoveSpeed * deltaTime));

      }

      return true;
   }


   bool Avatar::render(DrawMode mode)
   {
      if ((mode == DrawMesh) || (mode == DrawShadow) || (mode == DrawMeshForceTex))
      {
         return renderMesh(mode);
      }
      else if (mode == DrawSkeleton)
      {
         return renderSkeleton();
      }
      else
      {
         return false;
      }
   }

   bool Avatar::render()
   {
      return render(mDrawMode);
   }

   //Render out the avatar mesh
   bool Avatar::renderMesh(DrawMode mode)
   {
      //Push everything - Matrix, GL State machine, Client state
      glPushMatrix();

      //Set up position/rotation/scaling
      setGLTransform();

      //Draw the mesh
      drawGLMesh(mode);

      glPopMatrix();

      return true;

   }

   bool Avatar::renderSkeleton()
   {
      //Set up position/rotation/scaling
      glPushMatrix();

      setGLTransform();

      //Draw the skeleton lines/points
      drawGLSkeleton();

      glPopMatrix();

      return true;
   }

   void Avatar::setTexture( bool enable )
   {
      mTexturing = enable;
   }


   void Avatar::setDrawMode( DrawMode mode )
   {
      mDrawMode = mode;
   }

   bool Avatar::setLOD(float level)
   {
      mModel.setLodLevel(level);
      return true;
   }

   void Avatar::setShadowColor(float red, float green, float blue, float alpha)
   {
      if      (red > 1.0) mShadowColor[0] = 1.0;
      else if (red < 0.0) mShadowColor[0] = 0.0;
      else                mShadowColor[0] = red;

      if      (green > 1.0) mShadowColor[1] = 1.0;
      else if (green < 0.0) mShadowColor[1] = 0.0;
      else                  mShadowColor[1] = green;

      if      (blue > 1.0) mShadowColor[2] = 1.0;
      else if (blue < 0.0) mShadowColor[2] = 0.0;
      else                 mShadowColor[2] = blue;

      if      (alpha > 1.0) mShadowColor[3] = 1.0;
      else if (alpha < 0.0) mShadowColor[3] = 0.0;
      else                  mShadowColor[3] = alpha;
   }

   /*
   **  Position/Rotation/Scaling settings
   */

   void Avatar::setPos(const gmtl::Vec3f& xyz)
   {
      mCoord.mPos = xyz;
   }

   void Avatar::setRot(const gmtl::Quatf& rot)
   {

      //Convert the quat to xyz eulers
      gmtl::Matrix44f rot_matrix;
      gmtl::identity(rot_matrix);

      gmtl::set(rot_matrix, rot);
      gmtl::set(mCoord.rot(), rot_matrix);

   }

   void Avatar::setRot(const gmtl::EulerAngleXYZf& xyz)
   {
      mCoord.rot() = xyz;
   }

   void Avatar::setScale(float scale)
   {
      mScale = scale;
   }

   const gmtl::EulerAngleXYZf& Avatar::getRotXYZ() const
   {
      return mCoord.getRot();
   }

   const gmtl::Vec3f& Avatar::getPos() const
   {
      return mCoord.getPos();
   }

   gmtl::Quatf Avatar::getRotQuat() const
   {
      return gmtl::makeRot<gmtl::Quatf>(mCoord.getRot());
   }

   float Avatar::getScale()
   {
      return mScale;
   }

   void Avatar::setWCS(const gmtl::EulerAngleXYZf& xyz_degs)
   {
      mWCS = xyz_degs;
   }

   CalBone* Avatar::getBone(const std::string& boneName)
   {

      int boneId = mModel.getCoreModel()->getBoneId(boneName);

      //Make sure the bone exists
      if (boneId == -1)
      {
         return NULL;
      }

      return model()->getSkeleton()->getBone(boneId);
   }

   int Avatar::getAnimID(const std::string& animName)
   {
      return mModel.getCoreModel()->getAnimId(animName);
   }

   CalModel* Avatar::model()
   {
      return &mModel;
   }


   void Avatar::setGLTransform()
   {
      //Move
      glTranslatef(mCoord.mPos[0], mCoord.mPos[1], mCoord.mPos[2]);

      //Rotate
      glRotatef(gmtl::Math::rad2Deg(mCoord.mRot[0]), 1,0,0);
      glRotatef(gmtl::Math::rad2Deg(mCoord.mRot[1]), 0,1,0);
      glRotatef(gmtl::Math::rad2Deg(mCoord.mRot[2]), 0,0,1);

      //Adjust for WCS
      glRotatef(gmtl::Math::rad2Deg(mWCS[0]), 1,0,0);
      glRotatef(gmtl::Math::rad2Deg(mWCS[1]), 0,1,0);
      glRotatef(gmtl::Math::rad2Deg(mWCS[2]), 0,0,1);

      //Scale uniformly
      glScalef(mScale, mScale, mScale);
   }

   void Avatar::drawGLMesh(DrawMode mode)
   {
      glPushAttrib(GL_ALL_ATTRIB_BITS);

      //Note that Irix differs from the OpenGL standard with this little gem.
      //Thank them for the sloppy ifdef coding you see here.
#ifdef GL_CLIENT_ALL_ATTRIB_BITS
      glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
#else
      glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
#endif

      // get the renderer of the model
      CalRenderer *pCalRenderer = new CalRenderer(mModel.getRenderer());

      // begin the rendering loop
      if (!pCalRenderer->beginRendering())
      {
         return;
      }

      // we will use vertex arrays, so enable them
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);

      // get the number of meshes
      int meshCount;
      meshCount = pCalRenderer->getMeshCount();

      // render all meshes of the model
      int meshId;
      for (meshId = 0; meshId < meshCount; meshId++)
      {

         // get the number of submeshes
         int submeshCount;
         submeshCount = pCalRenderer->getSubmeshCount(meshId);

         // render all submeshes of the mesh
         int submeshId;
         for (submeshId = 0; submeshId < submeshCount; submeshId++)
         {
            // select mesh and submesh for further data access
            if (pCalRenderer->selectMeshSubmesh(meshId, submeshId))
            {

               unsigned char meshColor[4];
               GLfloat materialColor[4];

               // set the material ambient color
               pCalRenderer->getAmbientColor(&meshColor[0]);
               materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
               glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);

               // set the material diffuse color
               pCalRenderer->getDiffuseColor(&meshColor[0]);
               materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
               glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);

               // set the material specular color
               pCalRenderer->getSpecularColor(&meshColor[0]);
               materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
               glMaterialfv(GL_FRONT, GL_SPECULAR, materialColor);

               // set the material shininess factor
               float shininess = 50.0;
   //            shininess = pCalRenderer->getShininess();
               glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

               // set the vertex and normal buffers
               glVertexPointer(3, GL_FLOAT, 0, mVertices[meshId][submeshId]);
               glNormalPointer(GL_FLOAT, 0, mNormals[meshId][submeshId]);

               bool useTexture = false;

               if (mode == DrawShadow)
               {
                  // to draw shadows
                  glEnable(GL_BLEND);
                  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                  // specify shadow color to dark black and blending rate
                  glColor4f(mShadowColor[0], mShadowColor[1], mShadowColor[2], mShadowColor[3]);
                  glDisable(GL_LIGHTING);
               }
               else
               {
                  // set the texture coordinate buffer and state if necessary
                  if((pCalRenderer->getMapCount() > 0) && (mTextureCoordCounts[meshId][submeshId] > 0))
                  {

                     //Attempt to retrieve the texture ID
                     Texture* tex = (Texture*)pCalRenderer->getMapUserData(0);

                     //If we are in texture forcing mode...
                     if (mode == DrawMeshForceTex)
                     {
                        //Make a call to the loader telling it to make sure the texture is there!
   //                     mFactory->TextureLoader()->enforceTexture((int)pCalRenderer->getMapUserData(0));
                     }
   //                std::cout << "DrawGLMesh: context: " << vrj::GlDrawManager::instance()->getCurrentContext() << ": got texture ID for " << (int)pCalRenderer->getMapUserData(0) << " as " << texID << "\n" << std::flush;

                     useTexture = true;
                     glEnable(GL_TEXTURE_2D);
                     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                     glEnable(GL_COLOR_MATERIAL);

                     tex->bind();
   //                  glBindTexture(GL_TEXTURE_2D, texID);
                     glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

                     // set the texture coordinate buffer
                     glTexCoordPointer(2, GL_FLOAT, 0, mTextureCoords[meshId][submeshId]);
                     glColor3f(1.0f, 1.0f, 1.0f);

                  }
               }

               // draw the submesh
               glDrawElements(GL_TRIANGLES, mFaceCounts[meshId][submeshId] * 3, GL_UNSIGNED_INT, mFaces[meshId][submeshId]);

               // disable the texture coordinate state if necessary
               if (useTexture)
               {
                  glDisable(GL_COLOR_MATERIAL);
                  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                  glDisable(GL_TEXTURE_2D);
               }
            }
         }
      }

      // clear vertex array state
      glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);

      // end the rendering
      pCalRenderer->endRendering();
      //delete the copy of the renderer
      pCalRenderer->destroy();
      delete pCalRenderer;

      glPopAttrib();
      glPopClientAttrib();

   }


   void Avatar::drawGLSkeleton()
   {
      //Pushing client attributes that we will change
      glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);

      glDisable(GL_LIGHTING);
      // draw the bone lines
      float lines[1024][2][3];
      int nrLines;
      nrLines =  mModel.getSkeleton()->getBoneLines(&lines[0][0][0]);

      glLineWidth(3.0f);
      glColor3f(1.0f, 1.0f, 1.0f);
      glBegin(GL_LINES);
         int currLine;
         for (currLine = 0; currLine < nrLines; currLine++)
         {
            glVertex3f(lines[currLine][0][0], lines[currLine][0][1], lines[currLine][0][2]);
            glVertex3f(lines[currLine][1][0], lines[currLine][1][1], lines[currLine][1][2]);
         }
      glEnd();
      glLineWidth(1.0f);

      // draw the bone points
      float points[1024][3];
      int nrPoints;
      nrPoints =  mModel.getSkeleton()->getBonePoints(&points[0][0]);

      glPointSize(4.0f);
      glBegin(GL_POINTS);
         glColor3f(1.0f, 0.0f, 0.0f);
         int currPoint;
         for (currPoint = 0; currPoint < nrPoints; currPoint++)
         {
            glVertex3f(points[currPoint][0], points[currPoint][1], points[currPoint][2]);
         }
      glEnd();
      glPointSize(1.0f);


      glPopAttrib();
   }

   gmtl::Matrix44f Avatar::transformMat(const gmtl::Matrix44f& origMat)
   {
      //Transform the original matrix to the avatar's local Juggler coordinate space
      //Note that if you want to submit this matrix to Cal3D calls, you must still
      //perform the transformation to Cal3D coordinates.

      //Move
      gmtl::Matrix44f transMat = gmtl::makeTrans<gmtl::Matrix44f>(
                                 gmtl::Vec3f(-mCoord.mPos[0],
                                             -mCoord.mPos[1],
                                             -mCoord.mPos[2]));

      //Rotate
      gmtl::EulerAngleXYZf tempRot = mCoord.mRot;
      tempRot[0] = -tempRot[0];
      tempRot[1] = -tempRot[1];
      tempRot[2] = -tempRot[2];
      gmtl::Matrix44f rotMat = gmtl::makeRot<gmtl::Matrix44f>(tempRot);

      //Scale uniformly
      gmtl::Matrix44f scaleMat;

      if (getScale() == 0.0)
      {
         scaleMat = gmtl::makeScale<gmtl::Matrix44f>(0.0f);
      }
      else
      {
         scaleMat = gmtl::makeScale<gmtl::Matrix44f>(1.0f / getScale());
      }

      return transMat * rotMat * scaleMat * origMat;
   }
}
