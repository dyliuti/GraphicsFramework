#include "mainwindow.h"

#include <QApplication>
#include "view/canvasGL.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    CanvasGL canvas;
    canvas.show();
//    MainWindow w;
//    w.show();
    return a.exec();
}
