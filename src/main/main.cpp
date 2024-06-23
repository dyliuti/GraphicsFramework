#include "mainwindow.h"
#include "view/canvasGL.h"
#include "view/canvasGLSync.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    CanvasGL canvas;
    canvas.show();

//    CanvasGLSync syncCanvas;
//    syncCanvas.show();
    //    MainWindow w;
    //    w.show();
    return a.exec();
}
