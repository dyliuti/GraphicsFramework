#include "mainwindow.h"
#include "boarddefine.h"
#include "ui_mainwindow.h"
#include "view/scene.h"
#include "view/view.h"
#include <QDebug>

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

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onActionOpenTriggered);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onActionSaveTriggered);
    connect(ui->actioncopy, &QAction::triggered, this, &MainWindow::onActionCopyTriggered);
    connect(ui->actionpaster, &QAction::triggered, this, &MainWindow::onActionPasteTriggered);
    connect(ui->actionCursor, &QAction::triggered, this, &MainWindow::onActionCursorTriggered);
    connect(ui->actionPen, &QAction::triggered, this, &MainWindow::onActionPenTriggered);
    connect(ui->actionRect, &QAction::triggered, this, &MainWindow::onActionRectTriggered);
    connect(ui->actionCircle, &QAction::triggered, this, &MainWindow::onActionCircleTriggered);
    connect(ui->actionEllipse, &QAction::triggered, this, &MainWindow::onActionEllipseTriggered);
    connect(ui->actionStar, &QAction::triggered, this, &MainWindow::onActionStarTriggered);
    connect(ui->actionEraser, &QAction::triggered, this, &MainWindow::onActionEraserTriggered);
    connect(ui->actionredo, &QAction::triggered, this, &MainWindow::onActionRedoTriggered);
    connect(ui->actionundo, &QAction::triggered, this, &MainWindow::onActionUndoTriggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onActionOpenTriggered(bool checked)
{
    qInfo() << "111111: " << __FUNCTION__;
}

void MainWindow::onActionSaveTriggered()
{
}

void MainWindow::onActionCopyTriggered()
{
}

void MainWindow::onActionPasteTriggered()
{
}

void MainWindow::onActionCursorTriggered()
{
    m_view->setCursor(Qt::ArrowCursor);
    setActiveToolImage(ToolType::Cursor);
    statusBar()->showMessage("Current tool is Select");
    m_scene->getStateMachine()->switchState(StateType::Select);
}

void MainWindow::onActionPenTriggered()
{
    m_view->setCursor(Qt::ArrowCursor);
    setActiveToolImage(ToolType::Pen);
    statusBar()->showMessage("Current tool is Pen");
    m_scene->getStateMachine()->switchState(StateType::Pen);
}

void MainWindow::onActionRectTriggered()
{
    m_view->setCursor(Qt::ArrowCursor);
    setActiveToolImage(ToolType::Rect);
    statusBar()->showMessage("Current tool is Rectangle");
    const auto& stateMachine = m_scene->getStateMachine();
    if (!stateMachine->isCureentSelectType()) {
        stateMachine->switchState(StateType::Rect);
    }
}

void MainWindow::onActionCircleTriggered()
{
    m_view->setCursor(Qt::ArrowCursor);
    setActiveToolImage(ToolType::Cirle);
    statusBar()->showMessage("Current tool is Cirle");
    m_scene->getStateMachine()->switchState(StateType::Cirle);
}

void MainWindow::onActionEllipseTriggered()
{
    m_view->setCursor(Qt::ArrowCursor);
    setActiveToolImage(ToolType::Ellipse);
    statusBar()->showMessage("Current tool is Ellipse");
    m_scene->getStateMachine()->switchState(StateType::Ellipse);
}

void MainWindow::onActionStarTriggered()
{
    m_view->setCursor(Qt::ArrowCursor);
    setActiveToolImage(ToolType::Star);
    statusBar()->showMessage("Current tool is Star");
    m_scene->getStateMachine()->switchState(StateType::Star);
}

void MainWindow::onActionEraserTriggered()
{
    m_view->setCursor(Qt::ArrowCursor);
    setActiveToolImage(ToolType::Eraser);
    statusBar()->showMessage("Current tool is Eraser");
    m_scene->getStateMachine()->switchState(StateType::Eraser);
}

void MainWindow::onActionRedoTriggered()
{
}

void MainWindow::onActionUndoTriggered()
{
}

void MainWindow::setActiveToolImage(ToolType type)
{
    ui->actionCursor->setIcon(QIcon(type == ToolType::Cursor ? ":/resource/graph/cursor_active.png" : ":/resource/graph/cursor.png"));
    ui->actionPen->setIcon(QIcon(type == ToolType::Pen ? ":/resource/graph/pen_active.png" : ":/resource/graph/pen.png"));
    ui->actionRect->setIcon(QIcon(type == ToolType::Rect ? ":/resource/graph/rectangle1_active.png" : ":/resource/graph/rectangle1.png"));
    ui->actionCircle->setIcon(QIcon(type == ToolType::Cirle ? ":/resource/graph/circle_active.png" : ":/resource/graph/circle.png"));
    ui->actionStar->setIcon(QIcon(type == ToolType::Star ? ":/resource/graph/star_active.png" : ":/resource/graph/star.png"));
    ui->actionEraser->setIcon(QIcon(type == ToolType::Eraser ? ":/resource/graph/eraser_active.png" : ":/resource/graph/eraser.png"));
}
