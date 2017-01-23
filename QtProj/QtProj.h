#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtProj.h"

class QtProj : public QMainWindow
{
    Q_OBJECT

public:
    QtProj(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtProjClass ui;
};
