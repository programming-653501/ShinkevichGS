#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/fonts/dserase.ttf");

    QDir data("data");
    if (!data.exists())
	data.mkpath(".");

    MainWindow w;
    w.show();

    return a.exec();
}
