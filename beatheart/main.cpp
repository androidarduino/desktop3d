#include <QtGui>
#include "widget.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    HeartBeat w;
    w.show();
    return app.exec();
}
