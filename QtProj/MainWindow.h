#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtProj.h"
#include "MainWindowUI.h"
#include "ModelGLWidget.h"
#include <QFileDialog>
#include "global.h"
#include "Data.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef MainWindow MyType;
    typedef Ui::MainWindowUI UiType;
    MainWindow(QWidget * parent = Q_NULLPTR);

signals:
    void loadModelFromDiskFinished();

private:
    UiType ui;
    ModelGLWidget* pGLWidget;
    void connect();
    void openModel();
};
