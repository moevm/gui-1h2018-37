#include "paint.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//last test1
    QApplication a(argc, argv);
    paint w;
    w.show();

    return a.exec();
}
