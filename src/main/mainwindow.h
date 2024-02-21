#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "board_global.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

BOARD_NAMESPACE_BEGIN
class View;
class Scene;
BOARD_NAMESPACE_END

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered(bool checked);

private:
    Ui::MainWindow* ui;
    std::shared_ptr<Board::View> m_view;
    std::shared_ptr<Board::Scene> m_scene;
};
#endif // MAINWINDOW_H
