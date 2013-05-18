#ifndef STEREO_H
#define STEREO_H

#include <QObject>
#include <GL/glu.h>

#include <QApplication>
#include <QtOpenGL>
#include <QKeyEvent>
class stereo : public QObject
{

    Q_OBJECT
private:
    GLfloat mConvergence;
    GLfloat mEyeSeparation;
    GLfloat mAspectRatio;
    GLfloat mFOV;
    GLfloat mNearClippingDistance;
    GLfloat mFarClippingDistance;

public:
    stereo (GLfloat Convergence, GLfloat EyeSeparation, GLfloat AspectRatio,GLfloat FOV, GLfloat NearClippingDistance,
                 GLfloat FarClippingDistance);
    void ApplyLeftFrustum();
    void ApplyRightFrustum();
    explicit stereo(QObject *parent = 0);

    
signals:
    
public slots:
    
};

#endif // STEREO_H
