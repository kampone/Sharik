#include "light.h"
#include <QGLWidget>
#include "stereo.h"

const GLfloat pi=3.1415926535897932384626433832795, k=pi/180;
const GLuint np=36;
const GLfloat R=0.3f;
const GLfloat step=pi/np;

light::light(QWidget *parent) :
    QGLWidget(parent),
    m_x(0.0f),
    m_y(0.0f),
    m_dx(0.0f),
    m_dy(0.0f)
{

  m_qObj = gluNewQuadric();

}

void light::initializeGL()
{

   GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
   GLfloat mat_shininess[]={50.0};
   GLfloat light_position[]={1.0,1.0,-1.0,0.0};
   GLfloat white_light[]={1.0,1.0,1.0,1.0};

   glClearColor(0.0,0.0,0.0,0.0);
   //glShadeModel(GL_FLAT);
   glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
   glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);


   glLightfv(GL_LIGHT0,GL_POSITION,light_position);
   glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
   glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_TEXTURE_2D);


    genTextures();

   //падрыхтоўка стэка матрыц трансфармацыі
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glPushMatrix();
}
void light::genTextures() // функция genTexture() класса Scene3D, создаёт текстуры
{
   // загрузка изображений
   QImage image1; // создаём объекты класса QImage (изображения)
   image1.load("4.jpg"); // загружаем изображение в переменную image1
   image1=QGLWidget::convertToGLFormat(image1); // конвертируем изображение в формат для работы с OpenGL
   image2.load("fon.jpg");
   image2=QGLWidget::convertToGLFormat(image2);
   glGenTextures(2, textureID); // создаём два имени и записываем их в массив
   // создаём и связываем текстурные объекты с состоянием текстуры
   // 1-ый текстурный объект
   glBindTexture(GL_TEXTURE_2D, textureID[0]); // создаём и связываем 1-oй текстурный объект с последующим состоянием текстуры
   glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)image1.width(), (GLsizei)image1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image1.bits()); // связываем текстурный объект с изображением
   glEnable(GL_DEPTH_TEST);
   //glEnable(GL_LIGHTING);
   //glEnable(GL_LIGHT0);
   glEnable(GL_NORMALIZE);
   glEnable(GL_COLOR_MATERIAL);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // задана линейная фильтрация вблизи
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // задана линейная фильтрация вдали
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // при фильтрации игнорируются тексели, выходящие за границу текстуры для s координаты
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // при фильтрации игнорируются тексели, выходящие за границу текстуры для t координаты
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // цвет текселя полностью замещает цвет фрагмента фигуры

    glBindTexture(GL_TEXTURE_2D, textureID[1]); // создаём и связываем 2-oй текстурный объект с последующим состоянием текстуры
      glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)image2.width(), (GLsizei)image2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image2.bits()); // связываем текстурный объект с изображением
     glEnable(GL_DEPTH_TEST);
      //glEnable(GL_LIGHTING);
      //glEnable(GL_LIGHT0);
      glEnable(GL_NORMALIZE);
      glEnable(GL_COLOR_MATERIAL);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // задана линейная фильтрация вблизи
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // задана линейная фильтрация вдали
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // при фильтрации игнорируются тексели, выходящие за границу текстуры для s координаты
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // при фильтрации игнорируются тексели, выходящие за границу текстуры для t координаты
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // цвет текселя полностью замещает цвет фрагмента фигуры
}
void light::drawBackGround(){
 /*  glBindTexture(GL_TEXTURE_2D, textureID[1]); // создаём и связываем 2-oй текстурный объект с последующим состоянием текстуры
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)image2.width(), (GLsizei)image2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image2.bits()); // связываем текстурный объект с изображением
   glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // задана линейная фильтрация вблизи
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // задана линейная фильтрация вдали
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // при фильтрации игнорируются тексели, выходящие за границу текстуры для s координаты
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // при фильтрации игнорируются тексели, выходящие за границу текстуры для t координаты
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // цвет текселя полностью замещает цвет фрагмента фигуры

  */glBegin (GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f (-1, 1,R);


        glTexCoord2f(1.0f, 0.0f);
        glVertex3f (1, 1,R);


        glTexCoord2f(1.0f, 1.0f);
        glVertex3f (1, -1,R);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f (-1, -1,R);

 glEnd();

/*   glBindTexture(GL_TEXTURE_2D, textureID[0]); // создаём и связываем 2-oй текстурный объект с последующим состоянием текстуры
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)image2.width(), (GLsizei)image2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image2.bits()); // связываем текстурный объект с изображением
   glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // задана линейная фильтрация вблизи
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // задана линейная фильтрация вдали
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // при фильтрации игнорируются тексели, выходящие за границу текстуры для s координаты
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // при фильтрации игнорируются тексели, выходящие за границу текстуры для t координаты
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // цвет текселя полностью замещает цвет фрагмента фигуры
*/
}

void light::paintGL()
{

   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


   stereo cam(  2000.0f,5005.0f,1.3333f, 45.0f,-10*R,200.0f);   // Far Clipping Distance

   cam.ApplyLeftFrustum();
   glColorMask(true, false, false, false);
   glLoadIdentity();
   glBindTexture(GL_TEXTURE_2D, textureID[1]);
   drawBackGround();

   glPopMatrix();
   GLfloat tempMatrix[16];
   glGetFloatv(GL_MODELVIEW_MATRIX,tempMatrix);
   glLoadIdentity();
   GLfloat angle=(sqrt(m_dy*m_dy+m_dx*m_dx)*180.0)/(pi*R);
   glRotatef(angle,m_dy,-m_dx,0.0f);
   glMultMatrixf(tempMatrix);
   glGetFloatv(GL_MODELVIEW_MATRIX,tempMatrix);
   glPushMatrix();
   glLoadIdentity();
   m_x+=m_dx;
   m_y+=m_dy;
   glTranslatef(m_x,m_y,0.0f);
   glMultMatrixf(tempMatrix);
   glBindTexture(GL_TEXTURE_2D, textureID[0]);
   gluQuadricTexture(m_qObj,1);
   gluSphere(m_qObj,R,100,100);

   glClear(GL_DEPTH_BUFFER_BIT) ;

   cam.ApplyRightFrustum();
   glColorMask(false, true, true, false);

   glLoadIdentity();

   glBindTexture(GL_TEXTURE_2D, textureID[1]);
   drawBackGround();
   glPopMatrix();
   glGetFloatv(GL_MODELVIEW_MATRIX,tempMatrix);
   glLoadIdentity();
   glRotatef(angle,m_dy,-m_dx,0.0f);
   glMultMatrixf(tempMatrix);
   glGetFloatv(GL_MODELVIEW_MATRIX,tempMatrix);
   glPushMatrix();
   glLoadIdentity();
   glTranslatef(m_x,m_y,0.0f);
   glMultMatrixf(tempMatrix);
   glBindTexture(GL_TEXTURE_2D, textureID[0]);
   gluQuadricTexture(m_qObj,1);
   gluSphere(m_qObj,R,100,100);
   //drawAxis();

   glColorMask(true, true, true, true);


 //  drawAxis();
   glFlush();
}




void light::drawAxis() // построить оси координат
{
   glLineWidth(5.0f); // устанавливаю ширину линии приближённо в пикселях
   // до вызова команды ширина равна 1 пикселю по умолчанию


   glBegin(GL_LINES); // построение линии
      glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
      glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
   glEnd();

   //QColor halfGreen(0, 128, 0, 255);
   //qglColor(halfGreen);
   glBegin(GL_LINES);
      // ось y зеленого цвета
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glVertex3f( 0.0f, -1.0f,  0.0f);

      //glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
      // ось z синего цвета
      glVertex3f( 0.0f,  0.0f,  1.0f);
      glVertex3f( 0.0f,  0.0f, -1.0f);
   glEnd();
}

void light::mousePressEvent(QMouseEvent *pe) {
    m_ptPosition = pe->pos();
}

void light::mouseMoveEvent(QMouseEvent *pe) {
    m_dy=-2 * (GLfloat)(pe->y() - m_ptPosition.y()) / height();
    m_dx=+2 * (GLfloat)(pe->x() - m_ptPosition.x()) / width();
    m_ptPosition = pe->pos();
    updateGL();
}

void light::resizeGL(int w, int h)
{
   glViewport(0,0,(GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //if (w<=h)
   //  glOrtho(-1.5,1.5,-0.5*(GLfloat)h/(GLfloat)w,0.5*(GLfloat)h/(GLfloat)w,-10.0,10.0);
   //else
   //GLfloat left=-100,right=100,bottom=-100,top=100,near=-10.0,far=40.0;
   //glOrtho(-1.5*(GLfloat)w/(GLfloat)h,1.5*(GLfloat)w/(GLfloat)h,-1.5,1.5,-10.0,10.0);
   //glFrustum(left, right, bottom, top, near, far);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

  /*  glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //GLfloat left=-0.2,right=0.2,bottom=-0.1125,top=0.1125,near=1.0,far=50.0;
    GLfloat left=-(GLint)w/2,right=(GLint)w,bottom=-(GLint)h,top=(GLint)h,near=1.0,far=50.0;
    //GLfloat left=-16.5,right=16.5,bottom=-10,top=10,near=50.0,far=4000.0;
    glFrustum(left, right, bottom, top, near, far);*/

}

void light::keyPressEvent(QKeyEvent *pe){

    switch(pe->key()){

    case Qt::Key_Escape:
        QApplication::exit();
        break;
    case Qt::Key_W:
        m_dx= 0.0f;
        m_dy=+0.01f;
        break;
    case Qt::Key_S:
        m_dx= 0.0f;
        m_dy=-0.01f;
        break;
    case Qt::Key_A:
        m_dx=-0.01;
        m_dy= 0.0f;
        break;
    case Qt::Key_D:
        m_dx=+0.01;
        m_dy= 0.0f;
        break;
    case Qt::Key_Space:
        defaultScene();
        break;
    default:
        QWidget::keyPressEvent(pe);
    }
    updateGL();

}

void light::defaultScene() // наблюдение сцены по умолчанию
{
   glPopMatrix();
   glLoadIdentity();
   glPushMatrix();
   m_x=0.0f;
   m_y=0.0f;
   m_dx=0.0f;
   m_dy=0.0f;
}

