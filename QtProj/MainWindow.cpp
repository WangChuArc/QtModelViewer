#include "stdafx.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    pGLWidget = new ModelGLWidget(this);
    setCentralWidget(pGLWidget);
    connect();
}

void MainWindow::connect()
{
    QObject::connect(ui.pActOpenModel, &QAction::triggered, this, &MainWindow::openModel);
    QObject::connect(this, &MainWindow::loadModelFromDiskFinished, pGLWidget, &ModelGLWidget::loadModel);
}

void MainWindow::openModel()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open model", global::modelPath.c_str(), "Models (*.obj)");
    if (fileName.isEmpty()) return;
    QTextCodec* codec = QTextCodec::codecForName("gb2312");
    std::string str(codec->fromUnicode(fileName).data());
    Data::Model::add_model(str);
    pGLWidget->loadModel();
}
