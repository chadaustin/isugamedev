#ifndef SIREN_AVATAR_H
#define SIREN_AVATAR_H

#include <iostream>
#include <map>

#include <gmtl/Vec.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Coord.h>
#include <gmtl/Quat.h>
#include <gmtl/Generate.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <cal3d/cal3d.h>

namespace siren
{
   class Avatar
   {
   public:
      Avatar(CalCoreModel* coremodel);
      ~Avatar();

      static Avatar* create(const std::string& name);

      //Draw modes
      enum DrawMode { DrawMesh, DrawSkeleton, DrawShadow, DrawMeshForceTex };

      //Set the path for texture loading
      void setPath(const std::string& path);

      //Execute an animation once
      bool triggerAnimation(int id);
      bool triggerAnimation(const std::string& name);

      //Start an animation cycling
      bool triggerAnimationCycle(int id);
      bool triggerAnimationCycle(const std::string& name);

      //Stop an animation that is currently executing
      bool stopAnimation(int id);
      bool stopAnimation(const std::string& name);

      //Test whether an animation is currently executing
      bool checkAnimation(int id);
      bool checkAnimation(const std::string& name);

      //Stop all running animations
      bool stopAllAnimations();

      //Start the avatar moving to a specific position at a given speed (units/sec)
      void moveTo(const gmtl::Vec3f& position, float speed);
      //Query whether we are carrying out a positional movement
      bool isMoving();

      //Get the last animation started
      std::vector<int> getCurrentAnimIDs();

      //Force the avatar to update its own animation AND mesh data
      //deltaTime is in seconds
      bool update(float deltaTime);

      //The next 3 update functions are necessary in order to combine manual
      //   bone movement with loaded animations. Call updateAnimations first,
      //   set any manual bones, then update the mesh. UpdateMove can be called
      //   optionally if we are moving (with moveTo)

      //Just update the animation data
      bool updateAnimations(float deltaTime);
      //Just update the mesh data
      bool updateMesh(float deltaTime);
      //Just update the positional movement
      bool updateMove(float deltaTime);

      //Draw the avatar using OpenGL commands (based on draw mode)
      bool render(DrawMode mode);
      bool render();

      //Draw the avatar's full mesh using OpenGL commands
      bool renderMesh(DrawMode mode);

      //Draw the avatar's skeleton using OpenGL commands
      bool renderSkeleton();

      //Turn texturing on or off
      void setTexture(bool enable);

      //Set to draw the mesh or the skeleton when the render function
      void setDrawMode(DrawMode mode);

      //Set the model's level of detail factor
      bool setLOD(float level);

      //Set the color and transparency value of the
      void setShadowColor(float red, float green, float blue, float alpha);

      //Position/Rotation/Scaling
      void setPos(const gmtl::Vec3f& xyz);
      void setRot(const gmtl::Quatf& rot);
      void setRot(const gmtl::EulerAngleXYZf& xyz);
      void setScale(float scale);

      const gmtl::EulerAngleXYZf& getRotXYZ() const;
      const gmtl::Vec3f& getPos() const;
      gmtl::Quatf getRotQuat() const;
      float getScale();

      void setWCS(const gmtl::EulerAngleXYZf& xyz_degs);

      //Bone definitions
      CalBone* getBone(const std::string& boneName);

      //Animation defintions
      int getAnimID(const std::string& animName);

      //Access to Cal3D model object
      CalModel* model();

   protected:
      void setGLTransform();
      void drawGLMesh(DrawMode mode);
      void drawGLSkeleton();
      gmtl::Matrix44f transformMat(const gmtl::Matrix44f& origMat);

      CalModel mModel;

      std::string mPath;

      DrawMode mDrawMode;
      bool mTexturing;
      float mShadowColor[4];
      std::vector<int> mCurrentAnimIDs;

      //Position, rotation and scaling
      gmtl::EulerAngleXYZf mWCS; //Strictly meant for switching to a different coordinate system
      gmtl::CoordVec3EulerAngleXYZf mCoord;
      float mScale;

      //Currently executing animations
      std::vector<int> mCurrentAnimCycles;

      //Movement data
      gmtl::Vec3f mDestination;
      float mMoveSpeed;

      //Mesh data
      std::vector < std::vector <float*> > mVertices;
      std::vector < std::vector <float*> > mNormals;
      std::vector < std::vector <float*> > mTextureCoords;
      std::vector < std::vector <int*> > mFaces;
      std::vector < std::vector <int> > mTextureCoordCounts;
      std::vector < std::vector <int> > mFaceCounts;
   };
}

#endif
