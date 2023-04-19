#include "mainwindow.h"
#include "qstylehelper.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    // this function uses new Qt >= 5.15 win32 dark titlebar environment
    QStyleHelper::setTitleBarDarkColor();

    QApplication a(argc, argv);
    MainWindow w;

    // For a nice black window
    w.setAttribute(Qt::WA_TranslucentBackground);

    // initialize the instance and set desired look you want, also you can set any custom QPalette for dark and light scheme separately
    QStyleHelper::instance().setDarkPalette().setWidgetStyle("fusion").setAutoChangePalette(true);

    w.show();

    return a.exec();
}
