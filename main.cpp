#include "mainwindow.h"
#include <QApplication>
#include <QElapsedTimer>
#include <QPixmap>
#include <QTimer>
#include "msplashscreen.h"


#include "start.h"

#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    //加载并显示启动画面
    QPixmap pix = QPixmap(":/images/splash.png");
    MSplashScreen *splash = new MSplashScreen(pix,3500);
    splash->setDisabled(true);//禁用用户的输入事件响应
    splash->show();

//    MainWindow w;
//    w.show();
    Start uiStart;
    QTimer::singleShot(3500, &uiStart, SLOT(show()));

    return a.exec();
}
