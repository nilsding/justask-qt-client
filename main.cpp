#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow foo;
    foo.show();
    return app.exec();
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
