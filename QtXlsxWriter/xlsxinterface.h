#ifndef XLSXINTERFACE_H
#define XLSXINTERFACE_H

#include <QObject>
#include <QMainWindow>

#include "xlsxdocument.h"
#include "xlsxabstractsheet.h"

#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include "xlsxsheetmodel.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

#include <QFileDialog>
#include <QTableView>

#include <qDebug>

#include <QSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <qmessagebox.h>
QTXLSX_USE_NAMESPACE//必须加上命名空间

class XlsxInterface : public QObject
{
    Q_OBJECT
public:
    explicit XlsxInterface(QObject *parent = 0);


    void InitDataBase();
    //创建测试表1
    void CreateBook1();
    //创建测试表2
    void CreateBook2();
    //创建测试表
    void CreateBookTest();
    //打开excel
    void OpenXlsx();

    void OpenNongyeXlsx();
    void OpenShuiLiXlsx();
    void OpenTuDiXlsx();


    QSqlDatabase db;
signals:

public slots:
};

#endif // XLSXINTERFACE_H
