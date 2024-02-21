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

void MainWindow::on_actionOpen_triggered(bool checked)
{
}

void MainWindow::on_actionSave_triggered()
{
}

void MainWindow::on_actioncopy_triggered()
{
}

void MainWindow::on_actionPaste_triggered()
{
}

void MainWindow::on_actionCursor_triggered()
{
}

void MainWindow::on_actionPen_triggered()
{
}

void MainWindow::on_actionRect_triggered()
{
}

void MainWindow::on_actionCircle_triggered()
{
}

void MainWindow::on_actionEllipse_triggered()
{
}

void MainWindow::on_actionStar_triggered()
{
}

void MainWindow::on_actionEraser_triggered()
{
}

void MainWindow::on_actionRedo_triggered()
{
}

void MainWindow::on_actionUndo_triggered()
{
}
