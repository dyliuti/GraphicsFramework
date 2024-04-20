#include "mainwindow.h"

#include <QApplication>
#include "view/canvasGL.h"
#include "view/canvasGLSync.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

//    CanvasGL canvas;
//    canvas.show();

    CanvasGLSync syncCanvas;
    syncCanvas.show();
//    MainWindow w;
//    w.show();
    return a.exec();
}
