/////////////////////////////////////////////////////////////////////////////
#ifndef _QUAKENAV_H_
#define _QUAKENAV_H_

class QuakeNav
{
public:
    QuakeNav();
    virtual ~QuakeNav() {;}
    
    // get the eye position
    virtual const Vec3<float>& getTrans();
    
    // set translation
    virtual void setTrans(const Vec3<float>& trans);    
    
    // set translation
    virtual void setTrans(const float& x, const float& y, const float& z);    
    
    //set rotation
    virtual void setRot(const Matrix4f& trans);
    
    //set rotation
    virtual void setRot(const float& rad, const float& x, const float& y, const float& z);
    
    // modify the matrix such that x mouse offset will
    // translate trackball in the Y axis.
    // give - the y mouse current and previous positions
    // result - matrix is offset by the delta
    virtual void applyXtrans( const float& delta );
    
    // modify the matrix such that y mouse offset will
    // translate trackball in the Y axis.
    // give - the y mouse current and previous positions
    // result - matrix is offset by the delta
    virtual void applyYtrans( const float& delta );
    
    // modify the matrix such that y mouse offset will
    // translate trackball in the Z axis.
    // give - the y mouse current and previous positions
    // result - matrix is offset by the delta
    virtual void applyZtrans( const float& delta );
    
    // modify the matrix such that x,y mouse offset will
    // translate trackball in the XY plane.
    // give - the x,y mouse current and previous positions
    // result - matrix is offset by the deltas
    virtual void applyXYtrans( const float& xdelta, const float& ydelta );
    
    // modify the matrix such that x,y mouse offset will
    // translate trackball in the XZ plane.
    // give - the x,y mouse current and previous positions
    // result - matrix is offset by the deltas
    virtual void applyXZtrans( const float& xdelta, const float& zdelta );
    
    // modify the matrix such that y mouse offset will
    // rotate trackball about the X axis
    // give - the y mouse current and previous positions
    // result - matrix is offset by the delta
    virtual void applyXrot( const float& delta );
    
    // modify the matrix such that x mouse offset will
    // rotate trackball about the Y axis
    // give - the x mouse current and previous positions
    // result - matrix is offset by the delta
    virtual void applyYrot( const float& delta );
    
    // modify the matrix such that x mouse offset will
    // rotate trackball about the Z axis
    // give - the x mouse current and previous positions
    // result - matrix is offset by the delta
    virtual void applyZrot( const float& delta );
    
    // modify the matrix such that x,y mouse offsets will
    // rotate by the derived-class-defined method.
    // give - the x,y mouse current and previous positions
    // result - matrix is offset by the deltas
    virtual void applyGeneralRot( const float& xdelta, const float& ydelta );

    void getMatrix( Matrix4f& mat ) const { mat = mLookAtMatrix; }
    const Matrix4f& matrix() const { return mLookAtMatrix; }
    
protected:
   Matrix4f mLookAtMatrix;
    void _recalcMatrix();

    float       pitch, yaw;
    Vec3<float> eye, up, direction;
};

inline void QuakeNav::_recalcMatrix()
{
    // update the lookat matrix...
   Matrix4f mat1( Matrix4f::identity() );
   mat1.makeRot( pitch, Vec3<float>( 1,0,0 ) );
   Matrix4f mat2( Matrix4f::identity() );
   mat2.makeRot( yaw, Vec3<float>( 0,1,0 ) );
   
   Matrix4f mat3( Matrix4f::identity() );
   mat3.makeTrans( -eye );
  
   Matrix4f rot = mat1 * mat2;
   mLookAtMatrix = rot * mat3;
   rot.invert( rot );
   
   direction = rot * Vec3<float>(0,0,-1);

   //cout<<pitch<<" "<<yaw<<" "<<eye[0]<<" "<<eye[1]<<" "<<eye[2]<<"\n"<<flush;
}

// get the eye position
inline const Vec3<float>& QuakeNav::getTrans()
{
    return eye;
}

// Set the eye position
inline void QuakeNav::setTrans( const float& x, const float& y, const float& z )
{
    eye.set( x, y, z );
    _recalcMatrix();
}    

//set rotation
inline void QuakeNav::setRot( const Matrix4f& rotation )
{
   Matrix4f mat( rotation );
   Vec3<float> vec;
   mLookAtMatrix.getTrans( vec );
   mat.setTrans( vec );
   mLookAtMatrix = mat;
}

// set the translation of the scene
inline void QuakeNav::setRot( const float& rad, const float& x, const float& y, 
			    const float& z)
{
   Matrix4f mat( Matrix4f::identity() );
   mat.makeRot( rad, Vec3<float>( x, y, z ) );
   Vec3<float> vec;
   mLookAtMatrix.getTrans( vec );
   mat.setTrans( vec );
   mLookAtMatrix = mat;
   
   //cout<<rad<<" "<<x<<" "<<y<<" "<<z<<" "<<pitch<<" "<<yaw<<"\n"<<flush;
   //assert( false );
}

// Set the eye position
inline void QuakeNav::setTrans( const Vec3<float>& i )
{
    eye = i;
    _recalcMatrix(); //TODO: make this more efficient.
}

#endif
