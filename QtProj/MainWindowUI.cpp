#include "stdafx.h"
#include "MainWindowUI.h"


void Ui::MainWindowUI::setupUi(QMainWindow *pMainWindow)
{
    this->BaseType::setupUi(pMainWindow);
    pMenu = menuBar->addMenu("File");
    pActOpenModel = new QAction("OpenModel", pMainWindow);
    pMenu->addAction(pActOpenModel);
}