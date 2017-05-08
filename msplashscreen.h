/*
 *
 *
 * 闪屏功能模块
 *
 *
 */

#ifndef MSPLASHSCREEN_H
#define MSPLASHSCREEN_H

#include <QSplashScreen>
#include <QPixmap>
#include <QProgressBar>
#include <QList>
#include <QtGlobal>

class MSplashScreen: public QSplashScreen
{
     Q_OBJECT

public:
     MSplashScreen(QPixmap& pixmap,int time);
     ~MSplashScreen();

private:
     //进度条
     QProgressBar *ProgressBar;
     //随机数列表
     QList<int> numbersList;
     //启动界面停留的时间
     int elapseTime;
     //图片
     QPixmap mpixmap;

private:
     void setProgress();
     void generateAscendRandomNumber();

private slots:
     void slotUpdateProgress();
};


#endif // MSPLASHSCREEN_H
