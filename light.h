#ifndef LIGHT_H
#define LIGHT_H
#include <GL/glu.h>
#include <QGLWidget>
#include <QApplication>
#include <QtOpenGL>
#include <QKeyEvent>


class light : public QGLWidget
{
    Q_OBJECT
public:

    explicit light(QWidget *parent = 0);

protected:
    void genTextures();
   void drawAxis();
   virtual void initializeGL();
   virtual void resizeGL(int nWidth, int nHeight);
   virtual void paintGL();
   virtual void keyPressEvent(QKeyEvent *);
   virtual void mousePressEvent(QMouseEvent *pe);
   virtual void mouseMoveEvent(QMouseEvent *pe);
   void defaultScene();
   void drawBackGround();
private:
    GLUquadricObj* m_qObj;
    GLfloat m_x;
    GLfloat m_y;
    GLfloat m_dx;
    GLfloat m_dy;
    QPoint m_ptPosition;
    QImage image1;
    QImage image2;
    GLuint textureID[2];
signals:

public slots:

};
#endif // LIGHT_H
