#include <QApplication>
#include "cmr_walk.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    walk window;

    window.resize(480,600);
    window.setWindowTitle("Pokemon but worse");
    window.show();

    return app.exec();
}
