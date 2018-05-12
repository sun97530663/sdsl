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



    //设置分割窗口比例

    ui->splitter->setStretchFactor(1, 1);
    ui->splitter_2->setStretchFactor(0, 1);
    ui->splitter_3->setStretchFactor(1, 1);

    ui->splitter_4->setStretchFactor(0,3);
    ui->splitter_4->setStretchFactor(1,2);


    ui->tableWidgetChangeDE->hide();
    ui->widgetback4->hide();

    isshow =true;


    InitMenu();
    //初始化各个子界面
    InitSubUI();

    //初始化数据库
    InitDataBase();
}

MainWindow::~MainWindow()
{
    delete ui;
}


//初始化菜单设置
void MainWindow::InitMenu()
{

    //在菜单栏项目编辑功能
    QMenu *projectActionMenu = ui->menuBar->addMenu(tr("&项目管理"));

    projectEditAction = new QAction(QIcon(":/images/doc-open"), tr("&项目编辑"), this);
    //projectEditAction->setShortcuts(QKeySequence::Open);
    //openAction->setStatusTip(tr("Open an existing file"));
    connect(projectEditAction, SIGNAL(triggered()), this, SLOT(ProjectEdit()));
    projectActionMenu->addAction(projectEditAction);


    projectSaveAsAction = new QAction(QIcon(":/images/doc-open"), tr("&项目另存为"), this);
    //projectSaveAsAction->setShortcuts(QKeySequence::Open);
    //openAction->setStatusTip(tr("Open an existing file"));
    connect(projectSaveAsAction, SIGNAL(triggered()), this, SLOT(ProjectSaveAs()));
    projectActionMenu->addAction(projectSaveAsAction);


    QMenu *RateActionMenu = ui->menuBar->addMenu(tr("&工程费率"));
    QMenu *MaterialPriceActionMenu = ui->menuBar->addMenu(tr("&材料价格"));
    QMenu *MortarRatioActionMenu = ui->menuBar->addMenu(tr("&砂浆配比"));
    QMenu *ConcreteMixRatioActionMenu = ui->menuBar->addMenu(tr("&砼配合比"));
    QMenu *EquipmentPriceActionMenu = ui->menuBar->addMenu(tr("&设备价格"));
    QMenu *ComputationalFefreshActionMenu = ui->menuBar->addMenu(tr("&计算刷新"));


    QMenu *ReportOutputActionMenu = ui->menuBar->addMenu (tr("&报表输出"));
    QAction *ReportOutputAction = new QAction(QIcon(":/images/doc-open"), tr("&报表输出"), this);//报表输出
    connect(ReportOutputAction, SIGNAL(triggered()), this, SLOT(onReportOutput()));
    ReportOutputActionMenu->addAction(ReportOutputAction);

    QMenu *MaterialPriceMangerActionMenu = ui->menuBar->addMenu(tr("&材料价格编辑"));
    QAction *MaterialPriceSetAction = new QAction(QIcon(":/images/doc-open"), tr("&材料价格材料价格编辑"), this);//材料价格管理
    connect(MaterialPriceSetAction, SIGNAL(triggered()), this, SLOT(onMaterialPriceSet()));
    MaterialPriceMangerActionMenu->addAction(MaterialPriceSetAction);


    QMenu *HelpActionMenu = ui->menuBar->addMenu(tr("&帮助"));



    ui->menuBar->addAction(QString("返回"), this, SLOT(onBackStart()));


}
//初始化各个子界面
void MainWindow::InitSubUI()
{


    //初始化项目总览表
    ui->tableWidgetProjectAll->setColumnCount(3); //设置列数为3
    QStringList header;
    header<<"序号"<<"项目名称"<<"项目金额";
    ui->tableWidgetProjectAll->setHorizontalHeaderLabels(header);
    ui->tableWidgetProjectAll->horizontalHeader()->setStretchLastSection(true); //就是这个地方

    ui->tableWidgetProjectAll->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //隐藏行号
    QHeaderView *headerView = ui->tableWidgetProjectAll->verticalHeader();
    headerView->setHidden(true);
    ui->tableWidgetProjectAll->setColumnWidth(0,50);

    uMaterialPriceSet = new MaterialPriceSet(this);
    uMaterialPriceSet->hide();

    uReportOutput = new ReportOutput(this);
    uReportOutput->hide();

    oAbout = new About;
    oAbout->hide();


    //创建编辑树
    uMTreeWidget = new MTreeWidget();
    //连接更新项目总览的槽函数
    connect(uMTreeWidget,SIGNAL(UpdateAllTopNode(QStringList ,QStringList ,QStringList )),this,SLOT(UpdateProjectAll(QStringList ,QStringList ,QStringList )));

    //统计所有根节点
    uMTreeWidget->CountAllTopNode();
    ui->tabWidgetMainTreeWidget->clear();
    ui->tabWidgetMainTreeWidget->addTab(uMTreeWidget,"工程项目");


}

//初始化数据库
void MainWindow::InitDataBase()
{


    //数据库初始化
    mdatabase = new database;
    mdatabase->databaseInit();


}
//项目编辑槽函数
void MainWindow::ProjectEdit()
{


}
//项目另存为槽函数
void MainWindow::ProjectSaveAs()
{


}

//报表输出
void MainWindow::onReportOutput()
{

    uReportOutput->show();
}
//材料价格编辑槽函数
void MainWindow::onMaterialPriceSet()
{

    uMaterialPriceSet->show();


}
void MainWindow::on_pushButton_clicked()
{
    if(isshow)
    {
        ui->tableWidgetChangeDE->show();
        ui->widgetback4->show();
        isshow = false;
    }
    else
    {
        ui->tableWidgetChangeDE->hide();
        ui->widgetback4->hide();
        isshow = true;
    }
}
//返回起始界面
void MainWindow::onBackStart()
{
    this->hide();
    emit backstart();
}

//更新项目总览表
void MainWindow::UpdateProjectAll(QStringList projectindex,QStringList projectname,QStringList projectsum)
{

    //ui->tableWidgetProjectAll->clear();
    for(int i=0;i<projectindex.size();i++)
    {

        ui->tableWidgetProjectAll->insertRow(i);

        //序号

        ui->tableWidgetProjectAll->setItem(i,0,new QTableWidgetItem (projectindex.at(i)));
        //名称

        ui->tableWidgetProjectAll->setItem(i,1,new QTableWidgetItem (projectname.at(i)));
        //金额

        ui->tableWidgetProjectAll->setItem(i,2,new QTableWidgetItem (projectsum.at(i)));

    }

}
