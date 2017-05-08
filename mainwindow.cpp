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


    //设置treewidget每列的宽度为200
    ui->treeWidget->setColumnWidth(0,100);
    ui->treeWidget->setColumnWidth(1,200);
    ui->treeWidget->setColumnWidth(2,200);
    ui->treeWidget->setColumnWidth(3,200);

    qDebug()<<"退出"<<endl;


    //设置treewidget显示风格，默认是没有连线，使用windows风格有连线
    ui->treeWidget->setStyle(QStyleFactory::create ("windows"));
    //默认全部展开
    //ui->treeWidget->expandAll();

    ui->treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    // ui->treeWidget->setStyleSheet("selection-background-color:lightblue;");

    // ui->treeWidget->setDragDropMode(QAbstractItemView::InternalMove);
    //初始化序号值
    index = 1;
    //增加treewidget内容
    QTreeWidgetItem * beiJingItem = AddTreeRoot("bejing","12","备注");
    AddTreeNode(beiJingItem,"haidian","300","备注");
    AddTreeNode(beiJingItem,"chaoYang","450","备注");
    AddTreeNode(beiJingItem,"fengTai","8000","备注");
    QTreeWidgetItem * HeiBeiItem =AddTreeRoot("hebei","100","备注");
    AddTreeNode(HeiBeiItem,"baoDing","5000","备注");
    AddTreeNode(HeiBeiItem,"shiJiaZhuang","6530","备注");


    //连接treewidget的双击和右键菜单槽函数
    connect(ui->treeWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleclicked(QModelIndex)));
    connect(ui->treeWidget,SIGNAL(customContextMenuRequested(const QPoint &)), this,SLOT(onCustomContextMenuRequested(const QPoint &)));
    connect(ui->treeWidget,SIGNAL(itemChanged(QTreeWidgetItem *, int)), this,SLOT(testdrag(QTreeWidgetItem*,int)));



     uModifyText = new ModifyText(this);
     connect(uModifyText,SIGNAL(SignalModifyText(QString )),this,SLOT(SlotModifyText(QString )));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testdrag(QTreeWidgetItem*citem,int clom){


}
void MainWindow::open(){


}
QTreeWidgetItem * MainWindow::AddTreeRoot(QString name,QString value,QString desc)
{

    QTreeWidgetItem * item=new QTreeWidgetItem(QStringList()<<QString::number(index++)<<name<<value<<desc);
    ui->treeWidget->addTopLevelItem(item);

    LayCount(item);

    ui->treeWidget->setCurrentItem(item);
    return item;
}

QTreeWidgetItem * MainWindow::AddTreeNode(QTreeWidgetItem *parent,QString name,QString value,QString desc)
{
    ui->treeWidget->expandItem(parent);
    QString parentindex = parent->text(0);
    parentindex = parentindex+"."+QString::number(parent->childCount()+1);

    QTreeWidgetItem * item=new QTreeWidgetItem(QStringList()<<parentindex<<name<<value<<desc);
    //item->setFlags(item->flags() | Qt::ItemIsEditable);
    parent->addChild(item);

    LayCount(item);
    ui->treeWidget->setCurrentItem(item);
    return item;
}

void MainWindow::on_addroot_clicked()
{
    AddTreeRoot("新根项","1000","备注");

}
void MainWindow::on_add_clicked()
{
    QTreeWidgetItem * item= ui->treeWidget->currentItem();
    if(item!=Q_NULLPTR)
    {
        AddTreeNode(item,"新项","1000","备注");
    }
    else
    {
        AddTreeRoot("新根项","1000","备注");
    }

}
//删除节点
void MainWindow::DeleteTreeItem(QTreeWidgetItem *item){

    if(item==Q_NULLPTR)
    {
        return;
    }

    if(item->parent()==Q_NULLPTR)
    {
        //如果没有父节点就直接删除
        delete ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
    }
    else
    {
        //如果有父节点就要用父节点的takeChild删除节点
        delete item->parent()->takeChild( item->parent()->indexOfChild(item));
    }


}
void MainWindow::on_del_clicked()
{



    DeleteSelected();

}

void MainWindow::on_mod_clicked()
{


   uModifyText->show();

}


void MainWindow::doubleclicked(QModelIndex index){


    //ui->treeWidget->currentItem()->setFlags(ui->treeWidget->currentItem()->flags()& (~Qt::ItemIsEditable));

    //ui->treeWidget->editItem(ui->treeWidget->currentItem());

    int colum = index.column();
    if(colum==0)
        return;
    QTreeWidgetItem *curItem=ui->treeWidget->currentItem();
    // 使用QTextEdit的信号
    QLineEdit *lineEdit=new QLineEdit(this);

    lineEdit->setProperty("colum",colum);

    connect(lineEdit,SIGNAL(editingFinished()),this,SLOT(finishEdit()));
    // 设置widget
    ui->treeWidget->setItemWidget(curItem,colum,lineEdit);
    // 选中项
    ui->treeWidget->setCurrentItem(curItem);
    // 设置默认值
    lineEdit->setText(curItem->text(colum));
    lineEdit->setSelection(0,7);
}

void MainWindow::finishEdit(){

    // 编辑完成后,移除widget,还原树
    QTreeWidgetItem *curItem=ui->treeWidget->currentItem();
    QLineEdit *edit=qobject_cast<QLineEdit*>(sender());
    if(!edit)
        return;
    QString text=edit->text();
    int colum = edit->property("colum").toInt();
    // 移除widget
    ui->treeWidget->removeItemWidget(curItem,colum);
    // 还原值
    curItem->setText(colum,text);

}
void MainWindow::onCustomContextMenuRequested(const QPoint &pos){

    //获取当前被点击的节点
    QTreeWidgetItem* curItem=ui->treeWidget->itemAt(pos);
    //这种情况是右键的位置不在treeItem的范围内，即在空白位置右击
    if(curItem==NULL)
        return;
    //QVariant var = curItem->data(0,Qt::UserRole);
    //if(0 == var)      //data(...)返回的data已经在之前建立节点时用setdata()设置好

    //定义一个右键弹出菜单
    QMenu *popMenu =new QMenu(this);
    connect(popMenu,SIGNAL(triggered(QAction *)),this,SLOT(onGrpMenuTriggered(QAction *)));
    QAction *m_copy = new QAction(tr("复制"),this);
    QAction *m_curt = new QAction(tr("剪切"),this);
    QAction *m_delete = new QAction(tr("删除"),this);
    QAction *m_inertfront = new QAction(tr("此行前插入"),this);
    QAction *m_inertback = new QAction(tr("此行后插入"),this);

    popMenu->addAction(m_copy);
    popMenu->addAction(m_curt);
    popMenu->addAction(m_delete);
    popMenu->addAction(m_inertfront);
    popMenu->addAction(m_inertback);

    popMenu->exec(QCursor::pos());//弹出右键菜单，菜单位置为光标位置


}

void MainWindow::onGrpMenuTriggered(QAction *action){

    QString Text = action->text();

    if(Text=="复制"){

        QList<QTreeWidgetItem*> selectedItemList = ui->treeWidget->selectedItems();
//        copylistOrigin.clear();
//        for(int i=0;i<selectedItemList.count();i++){

//            COPYITEM item;
//            item.TreeItem = selectedItemList[i];
//            item.IsDelete = false;//复制，不删除
//            copylistOrigin.append(item);

//        }
        //重新构建
        QList<QTreeWidgetItem*> itemlist = RbuildTree(selectedItemList);
        copylist.clear();
        for(int i=0;i<itemlist.count();i++){

            COPYITEM item;
            item.TreeItem = itemlist[i];
            item.IsDelete = false;//复制，不删除
            copylist.append(item);

        }
    }

    if(Text=="剪切"){

        QList<QTreeWidgetItem*> selectedItemList = ui->treeWidget->selectedItems();
        copylistOrigin.clear();
        for(int i=0;i<selectedItemList.count();i++){

            COPYITEM item;
            item.TreeItem = selectedItemList[i];
            item.IsDelete = true;//复制，不删除
            copylistOrigin.append(item);

        }
        //重构
        QList<QTreeWidgetItem*> itemlist = RbuildTree(selectedItemList);
        copylist.clear();
        for(int i=0;i<itemlist.count();i++){

            COPYITEM item;
            item.TreeItem = itemlist[i];
            item.IsDelete = true;//剪贴，要删除
            copylist.append(item);

        }
    }

    if(Text=="删除"){
        DeleteSelected();
    }


    if(Text=="此行前插入"){

        QTreeWidgetItem * currentItem = ui->treeWidget->currentItem();
        if(currentItem==Q_NULLPTR)
        {
            return;
        }
        if(copylist.size()==0){
            //如果粘贴板为空则新建空行

            QString index = "null";
            QString name = "null";
            QString value = "0";
            QString desc = "null";
            QTreeWidgetItem *newitem = new QTreeWidgetItem(QStringList()<<index<<name<<value<<desc);
            if(currentItem->parent()==Q_NULLPTR)
            {
                //如果没有父节点
                ui->treeWidget->insertTopLevelItem(ui->treeWidget->indexOfTopLevelItem(currentItem),newitem);

                LayCount(newitem);

            }
            else
            {
                //如果有父节点
                currentItem->parent()->insertChild(currentItem->parent()->indexOfChild(currentItem),newitem);


                LayCount(newitem);
            }
            ui->treeWidget->setCurrentItem(newitem);
        }

        for(int i=0;i<copylist.size();i++){


            QString index = copylist.at(i).TreeItem->text(0);
            QString name = copylist.at(i).TreeItem->text(1);
            QString value = copylist.at(i).TreeItem->text(2);
            QString desc = copylist.at(i).TreeItem->text(3);

            //QTreeWidgetItem *newitem = new QTreeWidgetItem(QStringList()<<index<<name<<value<<desc);

             QTreeWidgetItem *newitem = copylist.at(i).TreeItem;
            if(currentItem->parent()==Q_NULLPTR)
            {
                //如果没有父节点
                ui->treeWidget->insertTopLevelItem(ui->treeWidget->indexOfTopLevelItem(currentItem),newitem);

                LayCount(newitem);

            }
            else
            {
                //如果有父节点
                currentItem->parent()->insertChild(currentItem->parent()->indexOfChild(currentItem),newitem);

                LayCount(newitem);
            }
            ui->treeWidget->setCurrentItem(newitem);

        }

        //删除原始列表
        for(int i=0;i<copylistOrigin.size();i++){

            if(copylistOrigin.at(i).IsDelete==true){
                //如果是剪切操作，则复制完信息后删除原item
                DeleteTreeItem(copylistOrigin.at(i).TreeItem);
                //删除后从复制列表中移除，否则会下次粘贴出错
                copylistOrigin.removeAt(i);
                i--;
            }
        }
        //插入后重新排序
        onReSort();
        ui->treeWidget->expandAll();


    }

    if(Text=="此行后插入"){

        QTreeWidgetItem * currentItem = ui->treeWidget->currentItem();
        if(currentItem==Q_NULLPTR)
        {
            return;
        }
        if(copylist.size()==0){
            //如果粘贴板为空则新建空行
            QString index = "null";
            QString name = "null";
            QString value = "0";
            QString desc = "null";
            QTreeWidgetItem *newitem = new QTreeWidgetItem(QStringList()<<index<<name<<value<<desc);

            if(currentItem->parent()==Q_NULLPTR)
            {
                //如果没有父节点
                ui->treeWidget->insertTopLevelItem(ui->treeWidget->indexOfTopLevelItem(currentItem)+1,newitem);

                LayCount(newitem);

            }
            else
            {
                //如果有父节点
                currentItem->parent()->insertChild(currentItem->parent()->indexOfChild(currentItem)+1,newitem);

                LayCount(newitem);
            }
            ui->treeWidget->setCurrentItem(newitem);
        }

        for(int i=0;i<copylist.size();i++){


            QString index = copylist.at(i).TreeItem->text(0);
            QString name = copylist.at(i).TreeItem->text(1);
            QString value = copylist.at(i).TreeItem->text(2);
            QString desc = copylist.at(i).TreeItem->text(3);


            //QTreeWidgetItem *newitem = new QTreeWidgetItem(QStringList()<<index<<name<<value<<desc);
            QTreeWidgetItem *newitem = copylist.at(i).TreeItem;
            if(currentItem->parent()==Q_NULLPTR)
            {
                //如果没有父节点
                ui->treeWidget->insertTopLevelItem(ui->treeWidget->indexOfTopLevelItem(currentItem)+1,newitem);


                LayCount(newitem);
            }
            else
            {
                //如果有父节点
                currentItem->parent()->insertChild(currentItem->parent()->indexOfChild(currentItem)+1,newitem);


                LayCount(newitem);
            }
            ui->treeWidget->setCurrentItem(newitem);
            currentItem = newitem;

        }

        //删除原始列表
        for(int i=0;i<copylistOrigin.size();i++){

            if(copylistOrigin.at(i).IsDelete==true){
                //如果是剪切操作，则复制完信息后删除原item
                DeleteTreeItem(copylistOrigin.at(i).TreeItem);
                //删除后从复制列表中移除，否则会下次粘贴出错
                copylistOrigin.removeAt(i);
                i--;
            }
        }
        //插入后重新排序
        onReSort();
        ui->treeWidget->expandAll();

    }

}
//重新排序号函数
void MainWindow::onReSort(){

    index =1;
    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it) {
        //do something like



        QTreeWidgetItem * phItem = (*it)->parent();    //获取当前item的父item
        if(!phItem)
        {   // 说明是根节点
            (*it)->setText(0,QString::number(index++));
        }
        else{

            QString parentindex = phItem->text(0);
            parentindex = parentindex+"."+QString::number(phItem->indexOfChild((*it))+1);
            (*it)->setText(0,parentindex);

        }
        ++it;
    }

}
//递归统计和函数
void MainWindow::onCountNumber(QTreeWidgetItem *item){


    int count = 0;
    for(int index=0;index<item->childCount();index++){

        if(item->child(index)->childCount()>0){
            onCountNumber(item->child(index));
        }
        count += item->child(index)->text(2).toInt();

    }
    item->setText(2,QString::number(count));

}
//计算值
void MainWindow::on_pushButtoncal_clicked()
{


    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it) {
        //获取当前item的父item
        QTreeWidgetItem * phItem = (*it)->parent();
        if(!phItem)
        {
            // 说明是根节点
            onCountNumber((*it));
        }
        ++it;
    }
}

void MainWindow::on_pushButtonsort_clicked()
{
    onReSort();
}
//计算层数
int MainWindow::LayCount(QTreeWidgetItem *item){

    int Count = 1;
    QTreeWidgetItem *phItem = item->parent();
    while(phItem)
    {
        Count++;
        phItem = phItem->parent();
    }

    switch (Count) {
    case 1:
    {

        //根节点字体加粗
        QFont font;
        font.setBold(true);
        item->setFont(0,font);
        item->setFont(1,font);
        item->setFont(2,font);
        item->setFont(3,font);

        //设置根节点为红色
        item->setTextColor(0,QColor(250, 128, 114));
        item->setTextColor(1,QColor(250, 128, 114));
        item->setTextColor(2,QColor(250, 128, 114));
        item->setTextColor(3,QColor(250, 128, 114));
        item->setTextAlignment(1,Qt::AlignHCenter);
        item->setTextAlignment(2,Qt::AlignHCenter);
        item->setTextAlignment(3,Qt::AlignHCenter);
    }
        break;
    case 2:
    {

        //第二级,蓝色
        item->setTextColor(0,QColor(0, 206, 209));
        item->setTextColor(1,QColor(0, 206, 209));
        item->setTextColor(2,QColor(0, 206, 209));
        item->setTextColor(3,QColor(0, 206, 209));
        item->setTextAlignment(1,Qt::AlignHCenter);
        item->setTextAlignment(2,Qt::AlignHCenter);
        item->setTextAlignment(3,Qt::AlignHCenter);
    }
        break;
    case 3:
    {
        //第三级,黑色
        item->setTextColor(0,QColor(105, 105, 105));
        item->setTextColor(1,QColor(105, 105, 105));
        item->setTextColor(2,QColor(105, 105, 105));
        item->setTextColor(3,QColor(105, 105, 105));
        item->setTextAlignment(1,Qt::AlignHCenter);
        item->setTextAlignment(2,Qt::AlignHCenter);
        item->setTextAlignment(3,Qt::AlignHCenter);

    }
        break;
    case 4:
    {

        //第四级,橙色
        item->setTextColor(0,QColor(255, 140, 0));
        item->setTextColor(1,QColor(255, 140, 0));
        item->setTextColor(2,QColor(255, 140, 0));
        item->setTextColor(3,QColor(255, 140, 0));
        item->setTextAlignment(1,Qt::AlignHCenter);
        item->setTextAlignment(2,Qt::AlignHCenter);
        item->setTextAlignment(3,Qt::AlignHCenter);
    }
        break;
    default:
    {

        //其他,橙色
        item->setTextColor(0,QColor(255, 140, 0));
        item->setTextColor(1,QColor(255, 140, 0));
        item->setTextColor(2,QColor(255, 140, 0));
        item->setTextColor(3,QColor(255, 140, 0));
        item->setTextAlignment(1,Qt::AlignHCenter);
        item->setTextAlignment(2,Qt::AlignHCenter);
        item->setTextAlignment(3,Qt::AlignHCenter);
    }
        break;
    }


    if(item->childCount()>0){

        for(int i=0;i<item->childCount();i++){

             LayCount(item->child(i));
        }

    }
    return Count;

}
//删除当前选中
void MainWindow::DeleteSelected(){

    QList<QTreeWidgetItem*> selectedItemList = ui->treeWidget->selectedItems();

    QString num ="";
    for(int i=0;i<selectedItemList.size();i++){
        num+=selectedItemList.at(i)->text(0)+" ";
    }
    QString message = QString("是否删除项 %1 ?").arg(num);
    QMessageBox messagebox(QMessageBox::Warning,"删除",message,QMessageBox::Yes|QMessageBox::No,this);
    if (messagebox.exec()==QMessageBox::Yes)
    {
        for(int i=0;i<selectedItemList.count();i++){

            //如果要删除的在复制列表里则从复制列表里移除
            for(int j=0;j<copylist.size();j++){

                if(copylist.at(j).TreeItem==selectedItemList[i]){
                    copylist.removeAt(j);
                }
            }
            DeleteTreeItem(selectedItemList[i]);


        }
        //删除后重新排序
        onReSort();
    }
    else
    {
        qDebug()<<"clicked no\n";
    }
}

void MainWindow::on_pushButtonbrother_clicked()
{

    QTreeWidgetItem * item= ui->treeWidget->currentItem();
    if(item==Q_NULLPTR)
        return;


    QTreeWidgetItem * phItem = item->parent();
    if(!phItem)
    {
        // 说明是根节点
         AddTreeRoot("新根项","1000","备注");
    }
    else{


        AddTreeNode(phItem,"新项","1000","备注");
    }


}

//修改值槽函数
void MainWindow::SlotModifyText(QString value){


    QTreeWidgetItem * currentItem = ui->treeWidget->currentItem();

    if(currentItem==Q_NULLPTR)
    {
        return;
    }

    currentItem->setText(2,value);


}
//把复制列表重组成树的结构
QList<QTreeWidgetItem*> MainWindow::RbuildTree(QList<QTreeWidgetItem*> ItemList){




    NewItemList.clear();
    for(int i=0;i<ItemList.size();i++){

        if(ItemList.contains(ItemList.at(i)->parent())){

            //如果有父项在列表中则忽略本条继续下一条
             continue;
        }
        else{

            //列表里没有父对象

            SelfBuild( ItemList.at(i),ItemList);

        }

    }
    return NewItemList;
}

void MainWindow::SelfBuild(QTreeWidgetItem *item,QList<QTreeWidgetItem*> ItemList,QTreeWidgetItem *newitem){


    if(ItemList.contains(item->parent())){

        //如果有父项
        for(int j=0;j<ItemList.size();j++){

            if(ItemList.at(j)->parent()==item){

                QString index = ItemList.at(j)->text(0);
                QString name = ItemList.at(j)->text(1);
                QString value = ItemList.at(j)->text(2);
                QString desc = ItemList.at(j)->text(3);
                QTreeWidgetItem *newchilditem = new QTreeWidgetItem(QStringList()<<index<<name<<value<<desc);
                newitem->addChild(newchilditem);


                //递归
                SelfBuild(ItemList.at(j),ItemList,newchilditem);
            }
        }
    }
    else{

        //没有父项
        QString index = item->text(0);
        QString name = item->text(1);
        QString value = item->text(2);
        QString desc = item->text(3);
        QTreeWidgetItem *newitem = new QTreeWidgetItem(QStringList()<<index<<name<<value<<desc);
        NewItemList.append(newitem);
        for(int j=0;j<ItemList.size();j++){

            if(ItemList.at(j)->parent()==item){

                QString index = ItemList.at(j)->text(0);
                QString name = ItemList.at(j)->text(1);
                QString value = ItemList.at(j)->text(2);
                QString desc = ItemList.at(j)->text(3);
                QTreeWidgetItem *newchilditem = new QTreeWidgetItem(QStringList()<<index<<name<<value<<desc);
                newitem->addChild(newchilditem);



                //递归
                SelfBuild(ItemList.at(j),ItemList,newchilditem);
            }
        }
    }


}
