#include "mtreewidget.h"

MTreeWidget::MTreeWidget(QWidget *parent)
{

    resize(QSize(700,400));

    //设置头名称
    setHeaderLabels(QStringList()<<"序号"<<"名称"<<"价格"<<"备注");
    //设置头对齐
    for(int i=0;i<=3;i++)
    {
        headerItem()->setTextAlignment(i,Qt::AlignHCenter);
    }
    //设置treewidget每列的宽度
    setColumnWidth(0,100);
    setColumnWidth(1,200);
    setColumnWidth(2,200);
    setColumnWidth(3,200);
    //设置treewidget显示风格，默认是没有连线，使用windows风格有连线
    setStyle(QStyleFactory::create ("windows"));
    //默认全部展开
    //expandAll();

    setSelectionMode(QAbstractItemView::ExtendedSelection);
    // setStyleSheet("selection-background-color:lightblue;");

    // setDragDropMode(QAbstractItemView::InternalMove);
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
    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleclicked(QModelIndex)));
    connect(this,SIGNAL(customContextMenuRequested(const QPoint &)), this,SLOT(onCustomContextMenuRequested(const QPoint &)));
    connect(this,SIGNAL(itemChanged(QTreeWidgetItem *, int)), this,SLOT(testdrag(QTreeWidgetItem*,int)));
    setFocusPolicy(Qt::ClickFocus);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setStyleSheet(QString::fromUtf8("\n"
                                    "\n"
                                    "QTreeWidget::item {\n"
                                    "border: 1px solid gray;\n"
                                    "border-right-color: transparent;\n"
                                    "\n"
                                    "\n"
                                    "}\n"
                                    "\n"
                                    "\n"
                                    "QTreeWidget{\n"
                                    "\n"
                                    "border-radius:0px;\n"
                                    "selection-color: rgb(85, 255, 127);\n"
                                    "background-color:white;/*\346\225\264\344\270\252\350\241\250\346\240\274\347\232\204\350\203\214\346\231\257\350\211\262\357\274\214\350\277\231\351\207\214\344\270\272\347\231\275\350\211\262*/\n"
                                    "border:1px solid #E0DDDC;/*\350\276\271\346\241\206\344\270\2721\345\203\217\347\264\240\357\274\214\347\201\260\350\211\262*/\n"
                                    "}\n"
                                    "QTreeView::item:selected\n"
                                    "{   \n"
                                    "     \n"
                                    "	background-color: rgb(85, 255, 255);\n"
                                    "     color: rgba(0,0,0,255);\n"
                                    "}\n"
                                    "/*\350\277\231\351\207\214\346\230\257\350\241\250\346\240\274\350\241\250\345\244\264\346\240\267\345\274\217*/\n"
                                    "QHeaderView::section{\n"
                                    "background-color:white;/*\350\203\214\346\231\257\350\211\262 \347\231\275\350\211\262*/\n"
                                    "border:0px solid #E0DDDC;/*\345\205\210\346\212\212\350\276\271\346\241\206\345\256\275\345\272\246\350\256\276\344"
                                    "\270\2720\357\274\214\345\215\263\351\232\220\350\227\217\346\211\200\346\234\211\350\241\250\345\244\264\350\276\271\346\241\206*/\n"
                                    "border-bottom:1px solid #E0DDDC;/*\347\204\266\345\220\216\345\217\252\346\230\276\347\244\272\344\270\213\350\276\271\346\241\206\357\274\214\345\233\240\344\270\272\344\270\212\350\276\271\346\241\206\345\222\214\345\267\246\345\217\263\350\276\271\346\241\206\346\230\257\346\225\264\344\270\252Table\347\232\204\350\276\271\346\241\206\357\274\214\351\203\275\346\230\276\347\244\272\344\274\232\346\234\2112px\347\232\204\350\276\271\346\241\206\345\256\275\345\272\246*/\n"
                                    "\n"
                                    "border-left:1px solid #E0DDDC;\n"
                                    "height:20px;/*\350\241\250\345\244\264\351\253\230\345\272\246*/\n"
                                    "}\n"
                                    "\n"
                                    "\n"
                                    "QScrollBar:vertical\n"
                                    "{\n"
                                    "    width:8px;\n"
                                    "    background:rgba(0,0,0,0%);\n"
                                    "    margin:0px,0px,0px,0px;\n"
                                    "    padding-top:9px;   /* \347\225\231\345\207\2729px\347\273\231\344\270\212\351\235\242\345\222\214\344\270\213\351\235\242\347\232\204\347\256\255\345\244\264*/\n"
                                    ""
                                    "    padding-bottom:9px;\n"
                                    "}\n"
                                    "QScrollBar::handle:vertical\n"
                                    "{\n"
                                    "    width:8px;\n"
                                    "    background:rgba(0,0,0,25%);\n"
                                    "    border-radius:4px;   /* \346\273\232\345\212\250\346\235\241\344\270\244\347\253\257\345\217\230\346\210\220\346\244\255\345\234\206*/\n"
                                    "    min-height:20;\n"
                                    "}\n"
                                    "QScrollBar::handle:vertical:hover\n"
                                    "{\n"
                                    "    width:8px;\n"
                                    "    background:rgba(0,0,0,50%);   /* \351\274\240\346\240\207\346\224\276\345\210\260\346\273\232\345\212\250\346\235\241\344\270\212\347\232\204\346\227\266\345\200\231\357\274\214\351\242\234\350\211\262\345\217\230\346\267\261*/\n"
                                    "    border-radius:4px;\n"
                                    "    min-height:20;\n"
                                    "}\n"
                                    "QScrollBar::add-line:vertical\n"
                                    "{\n"
                                    "    height:9px;width:8px;\n"
                                    "	border-image: url(:/image/arrow_down.png);\n"
                                    "    subcontrol-position:bottom;\n"
                                    "}\n"
                                    "QScrollBar::sub-line:vertical\n"
                                    "{\n"
                                    "    height:9px;width:8px;\n"
                                    "    border-image:url(:/image/arrow_up.png);\n"
                                    "    subcontrol-position:top;\n"
                                    "}\n"
                                    "QScrollBar::add-line:vertical:hover\n"
                                    "{\n"
                                    "    heig"
                                    "ht:9px;width:8px;\n"
                                    "    border-image:url(:/image/arrow_down.png);\n"
                                    "    subcontrol-position:bottom;\n"
                                    "}\n"
                                    "QScrollBar::sub-line:vertical:hover\n"
                                    "{\n"
                                    "    height:9px;width:8px;\n"
                                    "    border-image:url(:/image/arrow_up.png);\n"
                                    "    subcontrol-position:top;\n"
                                    "}\n"
                                    "\n"
                                    "QScrollBar::add-page:vertical  \n"
                                    "{\n"
                                    "    background:rgba(0,0,0,10%);\n"
                                    "    \n"
                                    "}\n"
                                    "\n"
                                    "QScrollBar::sub-page:vertical{\n"
                                    "\n"
                                    "	background:rgba(0,0,0,10%);\n"
                                    "}\n"
                                    "\n"
                                    "QScrollBar:horizontal\n"
                                    "{\n"
                                    "    height:8px;\n"
                                    "    background:rgba(0,0,0,0%);\n"
                                    "    margin:0px,0px,0px,0px;\n"
                                    "    padding-left:9px;   /* \347\225\231\345\207\2729px\347\273\231\344\270\212\351\235\242\345\222\214\344\270\213\351\235\242\347\232\204\347\256\255\345\244\264*/\n"
                                    "    padding-right:9px;\n"
                                    "}\n"
                                    "QScrollBar::handle:horizontal\n"
                                    "{\n"
                                    "    height:8px;\n"
                                    "    background:rgba(0,0,0,25%);\n"
                                    "    border-radius:4px;   /* \346\273\232\345\212\250\346\235\241\344\270\244\347\253\257\345\217\230\346\210\220\346\244\255\345\234\206*/\n"
                                    " "
                                    "   min-width:20;\n"
                                    "}\n"
                                    "\n"
                                    "QScrollBar::handle:horizontal:hover\n"
                                    "{\n"
                                    "    height:8px;\n"
                                    "    background:rgba(0,0,0,50%);   /* \351\274\240\346\240\207\346\224\276\345\210\260\346\273\232\345\212\250\346\235\241\344\270\212\347\232\204\346\227\266\345\200\231\357\274\214\351\242\234\350\211\262\345\217\230\346\267\261*/\n"
                                    "    border-radius:4px;\n"
                                    "    min-width:20;\n"
                                    "}\n"
                                    "QScrollBar::add-page:horizontal  \n"
                                    "{\n"
                                    "    background:rgba(0,0,0,10%);\n"
                                    "    \n"
                                    "}\n"
                                    "\n"
                                    "QScrollBar::sub-page:horizontal{\n"
                                    "\n"
                                    "	background:rgba(0,0,0,10%);\n"
                                    "}\n"
                                    "QScrollBar::add-line:horizontal\n"
                                    "{\n"
                                    "    height:8px;width:9px;\n"
                                    "    border-image:url(:/image/arrow_right.png);\n"
                                    "    subcontrol-position:right;\n"
                                    "}\n"
                                    "QScrollBar::sub-line:horizontal\n"
                                    "{\n"
                                    "    height:8px;width:9px;\n"
                                    "    border-image:url(:/image/arrow_left.png);\n"
                                    "    subcontrol-position:left;\n"
                                    "}\n"
                                    "QScrollBar::add-line:horizontal:hover\n"
                                    "{\n"
                                    "    height:8px;width:9px;\n"
                                    "    border-image:url(:/image/arrow_right.png);\n"
                                    ""
                                    "    subcontrol-position:right;\n"
                                    "}\n"
                                    "QScrollBar::sub-line:horizontal:hover\n"
                                    "{\n"
                                    "    height:8px;width:9px;\n"
                                    "    border-image:url(:/image/arrow_left.png);\n"
                                    "    subcontrol-position:left;\n"
                                    "}"));


    uModifyText = new ModifyText(this);
    connect(uModifyText,SIGNAL(SignalModifyText(QString )),this,SLOT(SlotModifyText(QString )));


}
MTreeWidget::~MTreeWidget()
{

}


void MTreeWidget::testdrag(QTreeWidgetItem*citem,int clom){


}

QTreeWidgetItem * MTreeWidget::AddTreeRoot(QString name,QString value,QString desc)
{

    QTreeWidgetItem * item=new QTreeWidgetItem(QStringList()<<QString::number(index++)<<name<<value<<desc);
    addTopLevelItem(item);

    LayCount(item);

    setCurrentItem(item);
    return item;
}

QTreeWidgetItem * MTreeWidget::AddTreeNode(QTreeWidgetItem *parent,QString name,QString value,QString desc)
{
    expandItem(parent);
    QString parentindex = parent->text(0);
    parentindex = parentindex+"."+QString::number(parent->childCount()+1);

    QTreeWidgetItem * item=new QTreeWidgetItem(QStringList()<<parentindex<<name<<value<<desc);
    //item->setFlags(item->flags() | Qt::ItemIsEditable);
    parent->addChild(item);

    LayCount(item);
    setCurrentItem(item);
    return item;
}


//删除节点
void MTreeWidget::DeleteTreeItem(QTreeWidgetItem *item){

    if(item==Q_NULLPTR)
    {
        return;
    }

    if(item->parent()==Q_NULLPTR)
    {
        //如果没有父节点就直接删除
        delete takeTopLevelItem(indexOfTopLevelItem(item));
    }
    else
    {
        //如果有父节点就要用父节点的takeChild删除节点
        delete item->parent()->takeChild( item->parent()->indexOfChild(item));
    }


}



void MTreeWidget::doubleclicked(QModelIndex index){


    //currentItem()->setFlags(currentItem()->flags()& (~Qt::ItemIsEditable));

    //editItem(currentItem());

    int colum = index.column();
    if(colum==0)
        return;
    QTreeWidgetItem *curItem=currentItem();
    // 使用QTextEdit的信号
    QLineEdit *lineEdit=new QLineEdit(this);

    lineEdit->setProperty("colum",colum);

    connect(lineEdit,SIGNAL(editingFinished()),this,SLOT(finishEdit()));
    // 设置widget
    setItemWidget(curItem,colum,lineEdit);
    // 选中项
    setCurrentItem(curItem);
    // 设置默认值
    lineEdit->setText(curItem->text(colum));
    lineEdit->setSelection(0,7);
}

void MTreeWidget::finishEdit(){

    // 编辑完成后,移除widget,还原树
    QTreeWidgetItem *curItem=currentItem();
    QLineEdit *edit=qobject_cast<QLineEdit*>(sender());
    if(!edit)
        return;
    QString text=edit->text();
    int colum = edit->property("colum").toInt();
    // 移除widget
    removeItemWidget(curItem,colum);
    // 还原值
    curItem->setText(colum,text);

}
void MTreeWidget::onCustomContextMenuRequested(const QPoint &pos){

    //获取当前被点击的节点
    QTreeWidgetItem* curItem=itemAt(pos);
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

void MTreeWidget::onGrpMenuTriggered(QAction *action){

    QString Text = action->text();

    if(Text=="复制"){

        QList<QTreeWidgetItem*> selectedItemList = selectedItems();
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

        QList<QTreeWidgetItem*> selectedItemList = selectedItems();
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

        QTreeWidgetItem * currentItem = this->currentItem();
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
                insertTopLevelItem(indexOfTopLevelItem(currentItem),newitem);

                LayCount(newitem);

            }
            else
            {
                //如果有父节点
                currentItem->parent()->insertChild(currentItem->parent()->indexOfChild(currentItem),newitem);


                LayCount(newitem);
            }
            setCurrentItem(newitem);
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
                insertTopLevelItem(indexOfTopLevelItem(currentItem),newitem);

                LayCount(newitem);

            }
            else
            {
                //如果有父节点
                currentItem->parent()->insertChild(currentItem->parent()->indexOfChild(currentItem),newitem);

                LayCount(newitem);
            }
            setCurrentItem(newitem);

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
        expandAll();


    }

    if(Text=="此行后插入"){

        QTreeWidgetItem * currentItem = this->currentItem();
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
                insertTopLevelItem(indexOfTopLevelItem(currentItem)+1,newitem);

                LayCount(newitem);

            }
            else
            {
                //如果有父节点
                currentItem->parent()->insertChild(currentItem->parent()->indexOfChild(currentItem)+1,newitem);

                LayCount(newitem);
            }
            setCurrentItem(newitem);
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
                insertTopLevelItem(indexOfTopLevelItem(currentItem)+1,newitem);


                LayCount(newitem);
            }
            else
            {
                //如果有父节点
                currentItem->parent()->insertChild(currentItem->parent()->indexOfChild(currentItem)+1,newitem);


                LayCount(newitem);
            }
            setCurrentItem(newitem);
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
        expandAll();

    }

}
//重新排序号函数
void MTreeWidget::onReSort(){

    index =1;
    QTreeWidgetItemIterator it(this);
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
void MTreeWidget::onCountNumber(QTreeWidgetItem *item){


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
void MTreeWidget::on_pushButtoncal_clicked()
{


    QTreeWidgetItemIterator it(this);
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

void MTreeWidget::on_pushButtonsort_clicked()
{
    onReSort();
}
//计算层数
int MTreeWidget::LayCount(QTreeWidgetItem *item){

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
void MTreeWidget::DeleteSelected(){

    QList<QTreeWidgetItem*> selectedItemList = selectedItems();

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


//把复制列表重组成树的结构
QList<QTreeWidgetItem*> MTreeWidget::RbuildTree(QList<QTreeWidgetItem*> ItemList){




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

void MTreeWidget::SelfBuild(QTreeWidgetItem *item,QList<QTreeWidgetItem*> ItemList,QTreeWidgetItem *newitem){


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

//增加根节点
void MTreeWidget::on_addroot_clicked()
{
    AddTreeRoot("新根项","1000","备注");

}
//增加下级
void MTreeWidget::on_add_clicked()
{
    QTreeWidgetItem * item= currentItem();
    if(item!=Q_NULLPTR)
    {
        AddTreeNode(item,"新项","1000","备注");
    }
    else
    {
        AddTreeRoot("新根项","1000","备注");
    }

}
//增加同级节点
void MTreeWidget::on_pushButtonbrother_clicked()
{

    QTreeWidgetItem * item= currentItem();
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
void MTreeWidget::SlotModifyText(QString value){


    QTreeWidgetItem * currentItem = this->currentItem();

    if(currentItem==Q_NULLPTR)
    {
        return;
    }

    currentItem->setText(2,value);


}

//删除
void MTreeWidget::on_del_clicked()
{



    DeleteSelected();

}
//修改
void MTreeWidget::on_mod_clicked()
{


    uModifyText->show();

}
