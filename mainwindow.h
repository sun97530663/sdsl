#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QSplitter>
#include <QTextEdit>

#include <QTreeWidgetItem>
#include "struct.h"

#include <math.h>
#include <QMessageBox>
#include "modifytext.h"
#include "materialpriceset.h"
#include "reportoutput.h"
#include "about.h"
#include "mtreewidget.h"
#include "DateBase/database.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    //初始化各个子界面
    void InitSubUI();
    //初始化菜单设置
    void InitMenu();
    //初始化数据库
    void InitDataBase();
public
    slots:
    //项目编辑槽函数
    void ProjectEdit();
    //项目另存为槽函数
    void ProjectSaveAs();
    //报表输出
    void onReportOutput();
    //材料价格编辑槽函数
    void onMaterialPriceSet();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;


    MaterialPriceSet *uMaterialPriceSet;//材料价格编辑界面
    ReportOutput *uReportOutput;//报表输出界面

    About *oAbout;

    QAction *projectEditAction;//项目编辑
    QAction *projectSaveAsAction;//项目另存为

    QAction *ReportOutputAction;//报表输出

    QAction *MaterialPriceSetAction;//材料价格管理


    MTreeWidget * uMTreeWidget;
    bool isshow;

    database *mdatabase;

};

#endif // MAINWINDOW_H
