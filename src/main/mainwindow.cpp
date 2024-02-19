#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view/scene.h"
#include "view/view.h"

BOARD_NAMESPACE_USE
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_view = std::make_shared<View>(this);
    m_view->setRenderHint(QPainter::Antialiasing);
    m_scene = std::make_shared<Scene>(this);
    m_view->setScene(m_scene.get());

    setCentralWidget(m_view.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}
