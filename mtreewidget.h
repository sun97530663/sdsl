#ifndef MTREEWIDGET_H
#define MTREEWIDGET_H
#include <QTreeWidget>
#include <QAction>
#include <QMenu>
#include <QTextEdit>
#include <QStyleFactory>
#include <QLineEdit>
#include <QMenu>
#include <QDebug>
#include <QTreeWidgetItem>
#include <math.h>
#include <QMessageBox>

#include "modifytext.h"
#include "struct.h"
class MTreeWidget : public QTreeWidget
{
      Q_OBJECT
public:
    MTreeWidget(QWidget *parent = 0);
    ~MTreeWidget();

    //增加根节点
    QTreeWidgetItem * AddTreeRoot(QString name,QString value,QString desc);
    //增加普通节点
    QTreeWidgetItem * AddTreeNode(QTreeWidgetItem *parent,QString name,QString value,QString desc);
    //重新排序号
    void onReSort();
    //递归统计和函数
    void onCountNumber(QTreeWidgetItem *item);

    //计算层数
    int LayCount(QTreeWidgetItem *item);

    //删除选中列表
    void DeleteSelected();

    //把选择的TreeItem列表重组成树的结构
    QList<QTreeWidgetItem*> RbuildTree(QList<QTreeWidgetItem*> selectedItemList);

    void SelfBuild(QTreeWidgetItem *item,QList<QTreeWidgetItem*> ItemList,QTreeWidgetItem *newitem = NULL);

    //统计所有根节点
    void CountAllTopNode();
private slots:
    //增加子项
    void on_add_clicked();
    //删除当前选中节点
    void DeleteTreeItem(QTreeWidgetItem *item);
    void on_del_clicked();

    //修改节点
    void on_mod_clicked();
    //增加根节点
    void on_addroot_clicked();
    //双击槽函数
    void doubleclicked(QModelIndex index);
    //编辑完成槽函数
    void finishEdit();
    //右键显示菜单
    void onCustomContextMenuRequested(const QPoint &pos);
    //右键菜单选择
    void onGrpMenuTriggered(QAction *action);

    //统计值
    void on_pushButtoncal_clicked();
    //排序
    void on_pushButtonsort_clicked();
    //测试拖拽
    void testdrag(QTreeWidgetItem*citem,int clom);

    //修改值槽函数
    void SlotModifyText(QString value);

    void on_pushButtonbrother_clicked();

signals:
    //更新顶点信息，给项目总览显示 参数：序号、名称、金额
    void UpdateAllTopNode(QStringList projectindex,QStringList projectname,QStringList projectsum);

private:

    //序号
    int index;
    //临时存储复制内容列表
    QList<COPYITEM> copylist;
    //原始列表
    QList<COPYITEM> copylistOrigin;
    //重组列表
    QList<QTreeWidgetItem*> NewItemList;

    //修改参数界面
    ModifyText *uModifyText;
};

#endif // MTREEWIDGET_H
