#include <QApplication>
#include "light.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    light w;
    w.resize(800,800);
    w.show();

    return a.exec();
}
