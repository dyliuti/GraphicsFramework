#include "mainwindow.h"
#include "view/canvasGL.h"
#include "view/canvasGLSync2.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    //    CanvasGL canvas;
    //    canvas.show();

    CanvasGLSync2 syncCanvas;
    syncCanvas.show();
    //    MainWindow w;
    //    w.show();
    return a.exec();
}
