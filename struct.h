#ifndef STRUCT_H
#define STRUCT_H
#include <QString>
#include <QTreeWidgetItem>
//复制粘贴等操作临时存储结构体
typedef struct{

    QTreeWidgetItem * TreeItem;
    bool IsDelete;//来自剪贴和复制的区别标志

}COPYITEM;
#endif // STRUCT_H
