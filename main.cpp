#include "mainwindow.h"
#include <QApplication>
#include <QElapsedTimer>
#include <QPixmap>
#include <QTimer>
#include "msplashscreen.h"

#include "mtreewidget.h"
#include <QFile>

#include "CrashModule/ccrashstack.h"
long __stdcall   callback(_EXCEPTION_POINTERS*   excp)
{
    CCrashStack crashStack(excp);
    QString sCrashInfo = crashStack.GetExceptionInfo();
    QString sFileName = "testcrash.dmp";

    QFile file(sFileName);
    if (file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        file.write(sCrashInfo.toUtf8());
        file.close();
    }

    qDebug()<<"Error:\n"<<sCrashInfo;
    //MessageBox(0,L"Error",L"error",MB_OK);
    QMessageBox msgBox;
    msgBox.setText(QString::fromUtf8("亲，我死了，重新启动下吧！"));
    msgBox.exec();

    return   EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SetUnhandledExceptionFilter(callback);//注冊异常捕获函数

    //加载并显示启动画面
    QPixmap pix = QPixmap(":/images/splash.png");


    MSplashScreen *splash = new MSplashScreen(pix,3500);
    splash->setDisabled(true);//禁用用户的输入事件响应
    splash->show();
    MainWindow w;
    QTimer::singleShot(3500, &w, SLOT(show()));

    MTreeWidget * uMTreeWidget = new MTreeWidget;
    uMTreeWidget->show();


    //hometest
    return a.exec();
}
