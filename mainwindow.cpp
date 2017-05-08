#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyleFactory>
#include <QLineEdit>
#include <QMenu>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置标题栏
    setWindowTitle("山东省农业综合开发项目造价管理系统");

    //在菜单栏增加打开工程功能
    openAction = new QAction(QIcon(":/images/doc-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    QMenu *file = ui->menuBar->addMenu(tr("&File"));
    file->addAction(openAction);


    //设置分割窗口比例
    ui->splitter_2->setStretchFactor(1, 1);
    ui->splitter_4->setStretchFactor(1, 1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open(){


}
