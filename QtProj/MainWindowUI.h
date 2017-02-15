#pragma once
#ifndef _MAIN_WINDOW_UI_H_
#define _MAIN_WINDOW_UI_H_

#include "ui_QtProj.h"
#include "Presenter.h"
#include "ModelGLWidget.h"

namespace Ui
{
    class MainWindowUI : public QtProjClass
    {
    public:
        typedef QtProjClass BaseType;
        typedef MainWindowUI MyType;

        QAction* pActOpenModel;
        QMenu* pMenu;
        QHBoxLayout* pLayout;
        void setupUi(QMainWindow *pMainWindow);

    signals:
        void mainWndSetupUiFined();
    };
}


#endif //_MAIN_WINDOW_UI_H_
