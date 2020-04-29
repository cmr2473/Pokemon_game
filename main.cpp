#include <QApplication>
#include "cmr_walk.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);//creates Qapplication object

    walk window; // creates walk object

    window.resize(480,600);
    window.setWindowTitle("Pokemon but worse");
    window.show(); // opens walk window

    return app.exec();
}
