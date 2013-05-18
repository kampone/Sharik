#include <QApplication>
#include "light.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    light w;
    w.showFullScreen();
    
    return a.exec();
}
