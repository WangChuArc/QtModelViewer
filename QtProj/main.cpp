#include "stdafx.h"
#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <QMessageBox>
#include <QString>

void init();

int main(int argc, char *argv[])
{
   
    QApplication a(argc, argv);
    init();
    MainWindow w;
    w.show();
    return a.exec();
}

void init()
{
    // setup format
    QSurfaceFormat fmt;
    fmt.setVersion(4, 3);
    fmt.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);
    fmt.setRenderableType(QSurfaceFormat::RenderableType::OpenGL);
    QSurfaceFormat::setDefaultFormat(fmt);
}