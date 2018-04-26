#include "paint.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //test
    QApplication a(argc, argv);
    paint w;
    w.show();

    return a.exec();
}
