#include "msplashscreen.h"

#include <QLabel>

#include <QTime>
#include <QTimer>
MSplashScreen::MSplashScreen(QPixmap& pixmap,int time) :
    QSplashScreen(pixmap),
    elapseTime(time),mpixmap(pixmap)
{
   ProgressBar = new QProgressBar(this);
   //设置进度条的位置
    ProgressBar->setGeometry(0,pixmap.height()-50,pixmap.width(),30);
    //设置进度条的样式
    ProgressBar->setStyleSheet("QProgressBar {color:black;font:30px;text-align:center; }QProgressBar::chunk {background-color: rgb(202, 165, 14);}");
    //设置进度条的样式
    ProgressBar->setRange(0, 100);
    //设置进度条的当前进度
    ProgressBar->setValue(0);




    //软件名称
    QLabel *label = new QLabel(this);
    //文字颜色
    label->move(130,0);

    //文字颜色
    QPalette palette;
    QBrush brush(QColor(255, 170, 0, 255));
    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
    label->setPalette(palette);

    //字体，微软雅黑
    QFont font;
    font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
    font.setPointSize(12);//字号大小
    label->setFont(font);
    label->setText("山东省农业综合开发项目造价管理系统");

    //制作单位
    QLabel *labelc = new QLabel(this);
    //文字颜色
    labelc->move(mpixmap.width()-200,mpixmap.height()-20);
    //文字颜色
    labelc->setPalette(palette);

    //字体，微软雅黑
    QFont fontc;
    fontc.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
    fontc.setPointSize(9);//字号大小
    labelc->setFont(fontc);
    labelc->setText("山东国地水利土地勘察设计有限公司");

    generateAscendRandomNumber();
    setProgress();


}

MSplashScreen::~MSplashScreen()
{

}

void MSplashScreen::setProgress()
{
    int tempTime=elapseTime/100;
    for(int i=0;i<100;i++)
    {
       QTimer::singleShot(i*tempTime, this, SLOT(slotUpdateProgress()));
    }
    QTimer::singleShot(elapseTime, this, SLOT(close()));
}

void MSplashScreen::slotUpdateProgress()
{
    static int num=0;
    ProgressBar->setValue(numbersList[num]);
    num++;
}

void MSplashScreen::generateAscendRandomNumber()
{
    int i;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //生成100个大小在[0,100]之间的随机数
    for(i=0;i<100;i++)
    {
        numbersList.append(qrand()%101);
    }
    //递增排序
    qSort(numbersList.begin(),numbersList.end());
}
