#include "stereo.h"
const GLfloat pi=3.1415926535897932384626433832795;

//stereo::stereo(QObject *parent) :
//    QObject(parent){
//}

stereo::stereo (GLfloat Convergence, GLfloat EyeSeparation, GLfloat AspectRatio,
                  GLfloat FOV, GLfloat NearClippingDistance, GLfloat FarClippingDistance,QObject *parent):
     QObject(parent),
     mConvergence(Convergence),
     mEyeSeparation(EyeSeparation),
     mAspectRatio(AspectRatio),
     mFOV(FOV * pi / 180.0f),
     mNearClippingDistance(NearClippingDistance),
     mFarClippingDistance(FarClippingDistance)
{
}



  void stereo::ApplyLeftFrustum()

  {
      GLfloat top, bottom, left, right;
      top     = mNearClippingDistance * tan(mFOV/2);
      bottom  = -top;
      GLfloat a = mAspectRatio * tan(mFOV/2) * mConvergence;
      GLfloat b = a - mEyeSeparation/2;
      GLfloat c = a + mEyeSeparation/2;
      left    = -b * mNearClippingDistance/mConvergence;
      right   =  c * mNearClippingDistance/mConvergence;

      // Set the Projection Matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glFrustum(left, right, bottom, top,
                mNearClippingDistance, mFarClippingDistance);

      // Displace the world to right
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(mEyeSeparation/2, 0.0f, 0.0f);
  }
  void stereo::ApplyRightFrustum()
  {
      GLfloat top, bottom, left, right;
      top     = mNearClippingDistance * tan(mFOV/2);
      bottom  = -top;
      GLfloat a = mAspectRatio * tan(mFOV/2) * mConvergence;
      GLfloat b = a - mEyeSeparation/2;
      GLfloat c = a + mEyeSeparation/2;

      left    =  -c * mNearClippingDistance/mConvergence;
      right   =   b * mNearClippingDistance/mConvergence;

      // Set the Projection Matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glFrustum(left, right, bottom, top,
                mNearClippingDistance, mFarClippingDistance);

      // Displace the world to left
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(-mEyeSeparation/2, 0.0f, 0.0f);
  }



