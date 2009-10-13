#include <QtGui/QApplication>
#include "weatherwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WeatherWindow w;
    //w.updatePicture();
    w.show();
    //WeatherInfo info;
    //info.update("Changchun","zh-cn");
    return a.exec();
}
