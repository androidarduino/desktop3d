#include <QtGui>
#include "widget.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Earth earth;
    earth.show();
    return app.exec();
}
