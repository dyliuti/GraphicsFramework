#include "fileutil.h"
#include "mainwindow.h"
#include "previewglwidget.h"
#include "resource.h"
#include <QApplication>
#include <QDebug>
#include <opengl/texture.h>
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);
    Resource::registerResource();

    PreviewGLWidget glWidget;
    glWidget.setTexturePath(":/model/model/facemodel.png");
    glWidget.show();

    //    MainWindow w;
    //    w.show();
    return a.exec();
}
