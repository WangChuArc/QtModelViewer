#pragma once
#ifndef _QTPROG_DEBUG_H_
#define _QTPROG_DEBUG_H_

#include <QOpenGLDebugLogger>
#include <QMessageBox>

namespace QtProgDebug
{
    // 不能处理重载，不要用
    template<typename TR, typename ...TArgs>
    inline auto static_aop_OGLDebug(TR(f)(TArgs...) )
    {
        return [f](TArgs ...args)
        {
            QOpenGLDebugLogger logger;
            logger.initialize();
            auto rt = f(forward<TArgs>(args)...);
            auto msgList = logger.loggedMessages();
            for (auto msg : msgList)
            {
                QMessageBox::about(nullptr, "log", msg.message());
            }
            return rt;
        };
    };

#define static_aop_OGLDebug_before \
    {\
        QOpenGLDebugLogger logger;\
        logger.initialize();
        // invoke your function here
#define static_aop_OGLDebug_after \
        auto msgList = logger.loggedMessages();\
        for (auto msg : msgList)\
        {\
            QMessageBox::about(nullptr, "log", msg.message());\
        }\
    }
}

#endif // !_QTPROG_DEBUG_H_

