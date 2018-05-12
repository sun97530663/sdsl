#include "xlsxinterface.h"

XlsxInterface::XlsxInterface(QObject *parent) : QObject(parent)
{
    InitDataBase();
}

//创建测试表1
void XlsxInterface::CreateBook1()
{
    //![Create a xlsx file]
    Document xlsx;

    for (int i=1; i<20; ++i) {
        for (int j=1; j<15; ++j)
            xlsx.write(i, j, QString("R %1 C %2").arg(i).arg(j));
    }
    xlsx.addSheet();
    xlsx.write(2, 2, "Hello Qt Xlsx");
    xlsx.addSheet();
    xlsx.write(3, 3, "This will be deleted...");

    xlsx.addSheet("HiddenSheet");
    xlsx.currentSheet()->setHidden(true);
    xlsx.write("A1", "This sheet is hidden.");

    xlsx.addSheet("VeryHiddenSheet");
    xlsx.sheet("VeryHiddenSheet")->setSheetState(AbstractSheet::SS_VeryHidden);
    xlsx.write("A1", "This sheet is very hidden.");

    xlsx.save();//Default name is "Book1.xlsx"
    //![Create a xlsx file]

    Document xlsx2("Book1.xlsx");
    //![add_copy_move_delete]
    xlsx2.renameSheet("Sheet1", "TheFirstSheet");

    xlsx2.copySheet("TheFirstSheet", "CopyOfTheFirst");

    xlsx2.selectSheet("CopyOfTheFirst");
    xlsx2.write(25, 2, "On the Copy Sheet");

    xlsx2.deleteSheet("Sheet3");

    xlsx2.moveSheet("Sheet2", 0);
    //![add_copy_move_delete]

    //![show_hidden_sheets]
    xlsx2.sheet("HiddenSheet")->setVisible(true);
    xlsx2.sheet("VeryHiddenSheet")->setVisible(true);
    //![show_hidden_sheets]

    xlsx2.saveAs("Book2.xlsx");

}
//创建测试表2
void XlsxInterface::CreateBook2()
{

    QXlsx::Document xlsx;
    //![0]

    //![1]
    QXlsx::Format blue;
    blue.setFontColor(Qt::blue);
    QXlsx::Format red;
    red.setFontColor(Qt::red);
    red.setFontSize(15);
    QXlsx::Format bold;
    bold.setFontBold(true);

    QXlsx::RichString rich;
    rich.addFragment("Hello ", blue);
    rich.addFragment("Qt ", red);
    rich.addFragment("Xlsx", bold);
    xlsx.write("B2", rich);

    xlsx.workbook()->setHtmlToRichStringEnabled(true);
    xlsx.write("B4", "<b>Hello</b> <font color=\"red\">Qt</font> <i>Xlsx</i>");

    xlsx.write("B6", "<font color=\"red\"><b><u><i>Qt Xlsx</i></u></b></font>");

    //![1]

    //![2]
    xlsx.saveAs("Test1.xlsx");
    //![2]

    QXlsx::Document("Test1.xlsx");
    xlsx.saveAs("Test2.xlsx");
}
//创建测试表
void XlsxInterface::CreateBookTest()
{

    Document xlsx;
    //![0]


    //设置第一行行高度
    xlsx.setRowHeight(1, 30.0);
    xlsx.setColumnWidth(16, 9.0);
    xlsx.setColumnWidth(2, 12.5);

    Format borderformat;

    borderformat.setBorderStyle(Format::BorderThin);

    //单元格边框颜色
    for(int r = 4;r<=13;r++)
    {

        for(int c = 1;c<=16;c++)
        {

            xlsx.write(r,c,"",borderformat);
        }
    }
    //写入表头内容
    QXlsx::Format formatheader;
    formatheader.setHorizontalAlignment(Format::AlignHCenter);
    formatheader.setVerticalAlignment(Format::AlignVCenter);
    formatheader.setFontBold(true);
    //formatheader.setFontColor(QColor(Qt::blue));
    formatheader.setFontSize(18);
    formatheader.setFontName("宋体");

    xlsx.setRowFormat(1, formatheader);
    xlsx.write("A1", "项目总概算表及分年度投资概算表",formatheader);
    xlsx.mergeCells("A1:P1", formatheader);



    //靠左格式
    Format formatleftnoborder;
    formatleftnoborder.setFontName("宋体");
    formatleftnoborder.setFontSize(10);
    formatleftnoborder.setHorizontalAlignment(Format::AlignLeft);
    formatleftnoborder.setVerticalAlignment(Format::AlignVCenter);

    //靠右格式
    Format formatrightnoborder;
    formatrightnoborder.setFontName("宋体");
    formatrightnoborder.setFontSize(10);
    formatrightnoborder.setHorizontalAlignment(Format::AlignRight);
    formatrightnoborder.setVerticalAlignment(Format::AlignVCenter);


    //靠左格式
    Format formatleft;
    formatleft.setFontName("宋体");
    formatleft.setFontSize(10);
    formatleft.setHorizontalAlignment(Format::AlignLeft);
    formatleft.setVerticalAlignment(Format::AlignVCenter);
    formatleft.setBorderStyle(Format::BorderThin);
    //靠右格式
    Format formatright;
    formatright.setFontName("宋体");
    formatright.setFontSize(10);
    formatright.setHorizontalAlignment(Format::AlignRight);
    formatright.setVerticalAlignment(Format::AlignVCenter);
    formatright.setBorderStyle(Format::BorderThin);
    //居中格式
    Format formatcenter;
    formatcenter.setFontName("宋体");
    formatcenter.setFontSize(10);
    formatcenter.setHorizontalAlignment(Format::AlignHCenter);
    formatcenter.setVerticalAlignment(Format::AlignVCenter);
    formatcenter.setBorderStyle(Format::BorderThin);

    //工程名称
    xlsx.mergeCells("A3:I3", formatleftnoborder);
    xlsx.write("A3", "工程名称：");

    //单位
    xlsx.write("P3", "单位：万元",formatrightnoborder);

    //序号
    xlsx.mergeCells("A4:A6", formatcenter);
    xlsx.write("A4", "序号");

    //工程费用
    xlsx.mergeCells("B4:B6", formatcenter);
    xlsx.write("B4", "工程费用");

    //
    //项目投资
    xlsx.mergeCells("C4:K4", formatcenter);
    xlsx.write("C4", "项目投资");

    //其中：
    xlsx.mergeCells("L4:O4", formatleft);
    xlsx.write("L4", "其中：");

    //
    xlsx.mergeCells("C5:G5", formatcenter);
    xlsx.write("C5", "工程措施费");

    //
    xlsx.mergeCells("H5:J5", formatcenter);
    xlsx.write("H5", "建设管理费");

    //
    xlsx.mergeCells("K5:K6", formatcenter);
    xlsx.write("K5", "合计");

    //
    xlsx.mergeCells("L5:N5", formatcenter);
    xlsx.write("L5", "财政资金");

    //
    xlsx.mergeCells("P4:P6", formatcenter);
    xlsx.write("P4", "措施费占\n总投资(%)");


    xlsx.write("C6", "工程施工费",formatcenter);

    xlsx.write("O5", " 配套资金",formatcenter);


    //序号
    int index=1;
    for(int i=7;i<=13;i++){

         xlsx.write(i,1, index,formatcenter);
         index++;
    }

    xlsx.write("B7", " 水利措施费",formatleft);
    xlsx.write("B8", " 农业措施费",formatleft);
    xlsx.write("B9", " 林业措施费",formatleft);
    xlsx.write("B10", " 道路措施费",formatleft);
    xlsx.write("B11", " 科技措施费",formatleft);
    xlsx.write("B12", " 其他工作及措施费",formatleft);
    xlsx.write("B13", " 项目总投资",formatleft);

    //xlsx.write("E8", 2);
    //xlsx.mergeCells("E8:F21", mergeformat);
    //![1]
    xlsx.saveAs("项目总概算表及分年度投资概算表.xlsx");
}
//打开
void XlsxInterface::OpenXlsx()
{
    QString filePath = QFileDialog::getOpenFileName(0, "Open xlsx file", QString(), "*.xlsx");
    if (filePath.isEmpty())
        return;
    QSqlQuery query(db);
    Document xlsx(filePath);
    foreach (QString sheetName, xlsx.sheetNames()) {
        Worksheet *sheet = dynamic_cast<Worksheet *>(xlsx.sheet(sheetName));
        if (sheet) {
           // QTableView *view = new QTableView();

//           // connect(view,SIGNAL())
//            view->setModel(new SheetModel(sheet, view));
//            foreach (CellRange range, sheet->mergedCells())
//                view->setSpan(range.firstRow()-1, range.firstColumn()-1, range.rowCount(), range.columnCount());
//            tabWidget.addTab(view, sheetName);

            //SheetModel *sheetmodel = new SheetModel(sheet, view);

            QXlsx::CellRange range;
            range = sheet->dimension();

            int row = range.rowCount();//行
            int clom = range.columnCount();//列

            qDebug()<<row<<clom<<sheetName<<endl;
            for (int i=1; i<=row; i++) {
                QStringList list;
                list.clear();
                for(int j= 1;j<=clom;j++){


                    if (QXlsx::Cell *cell=sheet->cellAt(i, j))
                    {
                        //如果单元格内有数据
                        if(cell->value().type()==QMetaType::UnknownType)
                        {

                            //未知类型

                        }
                        else
                        {

                            qDebug()<<i<<j<<cell->value();
                            //qDebug()<<i<<j<<cell->value()<<cell->cellType()<<cell->format();
                        }

                    }
                    else
                    {
                        //单元格内无数据，为空

                    }

                }

            }

        }
    }

}
//农业
void XlsxInterface::OpenNongyeXlsx()
{
    QString filePath = "./BaseData农业定额.xlsx";
    if (filePath.isEmpty())
        return;
    QSqlQuery query(db);
    Document xlsx(filePath);
    foreach (QString sheetName, xlsx.sheetNames()) {
        Worksheet *sheet = dynamic_cast<Worksheet *>(xlsx.sheet(sheetName));
        if (sheet) {

            QXlsx::CellRange range;
            range = sheet->dimension();

            int row = range.rowCount();//行
            int clom = range.columnCount();//列


             qDebug()<<row<<clom<<sheetName<<endl;
            for (int i=1; i<=row; i++) {


                if(i==1)
                {
                    continue;
                }
                QStringList list;
                list.clear();
                for(int j= 1;j<=clom;j++){


                    if (QXlsx::Cell *cell=sheet->cellAt(i, j))
                    {
                        //如果单元格内有数据
                        if(cell->value().type()==QMetaType::UnknownType)
                        {

                            //未知类型

                        }
                        else
                        {

                            qDebug()<<i<<j<<cell->value();
                            list.append(cell->value().toString());
                            //qDebug()<<i<<j<<cell->value()<<cell->cellType()<<cell->format();
                        }

                    }
                    else
                    {
                        //单元格内无数据，为空
                         list.append("");
                    }

                }

                // 添
                bool ret = false;
                QString sqlLine = QString("insert into NongYeDingE(id,model,dingeno,biaoshi,mingcheng,danwei,dingeliang,danweizhi,danweiming,jixiebianhao,ercixuanze,\demingcheng,shuoming1,shuoming2,shuoming3,shiyongfanwei,gongzuoneirong,danjia,xianjia,jiacha,weijijia,heji,zhushi) values (%1,'%2',%3,'%4','%5','%6',%7,%8,'%9',%10,%11,'%12','%13','%14','%15','%16','%17',%18,%19,%20,%21,%22,'%23')")
                        .arg(list.at(0).toInt())
                        .arg(list.at(1))
                        .arg(list.at(2).toInt())
                        .arg(list.at(3))
                        .arg(list.at(4))
                        .arg(list.at(5))
                        .arg(list.at(6).toDouble())
                        .arg(list.at(7).toInt())
                        .arg(list.at(8))
                        .arg(list.at(9).toInt())
                        .arg(list.at(10).toInt())
                        .arg(list.at(11))
                        .arg(list.at(12))
                        .arg(list.at(13))
                        .arg(list.at(14))
                        .arg(list.at(15))
                        .arg(list.at(16))
                        .arg(list.at(17).toDouble())
                        .arg(list.at(18).toDouble())
                        .arg(list.at(19).toDouble())
                        .arg(list.at(20).toDouble())
                        .arg(list.at(21).toDouble())
                        .arg(list.at(22));

                ret = query.exec(sqlLine);


            }

        }
    }

}
//水利转换
void XlsxInterface::OpenShuiLiXlsx()
{
    QString filePath = "./BaseData水利定额.xlsx";
    if (filePath.isEmpty())
        return;
    QSqlQuery query(db);
    Document xlsx(filePath);
    foreach (QString sheetName, xlsx.sheetNames()) {
        Worksheet *sheet = dynamic_cast<Worksheet *>(xlsx.sheet(sheetName));
        if (sheet) {

            QXlsx::CellRange range;
            range = sheet->dimension();

            int row = range.rowCount();//行
            int clom = range.columnCount();//列


             qDebug()<<row<<clom<<sheetName<<endl;
            for (int i=1; i<=row; i++) {


                if(i==1)
                {
                    continue;
                }
                QStringList list;
                list.clear();
                for(int j= 1;j<=clom;j++){


                    if (QXlsx::Cell *cell=sheet->cellAt(i, j))
                    {
                        //如果单元格内有数据
                        if(cell->value().type()==QMetaType::UnknownType)
                        {

                            //未知类型

                        }
                        else
                        {

                            qDebug()<<i<<j<<cell->value();
                            list.append(cell->value().toString());
                            //qDebug()<<i<<j<<cell->value()<<cell->cellType()<<cell->format();
                        }

                    }
                    else
                    {
                        //单元格内无数据，为空
                         list.append("");
                    }

                }

                // 添
                bool ret = false;
                QString sqlLine = QString("insert into ShuiLiDingE(id,model,dingeno,biaoshi,mingcheng,danwei,dingeliang,danweizhi,danweiming,jixiebianhao,ercixuanze,\demingcheng,shuoming1,shuoming2,shuoming3,shiyongfanwei,gongzuoneirong,danjia,xianjia,jiacha,weijijia,heji) values (%1,'%2',%3,'%4','%5','%6',%7,%8,'%9',%10,%11,'%12','%13','%14','%15','%16','%17',%18,%19,%20,%21,%22)")
                        .arg(list.at(0).toInt())
                        .arg(list.at(1))
                        .arg(list.at(2).toInt())
                        .arg(list.at(3))
                        .arg(list.at(4))
                        .arg(list.at(5))
                        .arg(list.at(6).toDouble())
                        .arg(list.at(7).toInt())
                        .arg(list.at(8))
                        .arg(list.at(9).toInt())
                        .arg(list.at(10).toInt())
                        .arg(list.at(11))
                        .arg(list.at(12))
                        .arg(list.at(13))
                        .arg(list.at(14))
                        .arg(list.at(15))
                        .arg(list.at(16))
                        .arg(list.at(17).toDouble())
                        .arg(list.at(18).toDouble())
                        .arg(list.at(19).toDouble())
                        .arg(list.at(20).toDouble())
                        .arg(list.at(21).toDouble());

                ret = query.exec(sqlLine);


            }

        }
    }

}
//土地
void XlsxInterface::OpenTuDiXlsx()
{
    QString filePath = "./BaseData土地定额.xlsx";
    if (filePath.isEmpty())
        return;
    QSqlQuery query(db);
    Document xlsx(filePath);
    foreach (QString sheetName, xlsx.sheetNames()) {
        Worksheet *sheet = dynamic_cast<Worksheet *>(xlsx.sheet(sheetName));
        if (sheet) {

            QXlsx::CellRange range;
            range = sheet->dimension();

            int row = range.rowCount();//行
            int clom = range.columnCount();//列


             qDebug()<<row<<clom<<sheetName<<endl;
            for (int i=1; i<=row; i++) {


                if(i==1)
                {
                    continue;
                }
                QStringList list;
                list.clear();
                for(int j= 1;j<=clom;j++){


                    if (QXlsx::Cell *cell=sheet->cellAt(i, j))
                    {
                        //如果单元格内有数据
                        if(cell->value().type()==QMetaType::UnknownType)
                        {

                            //未知类型

                        }
                        else
                        {

                            qDebug()<<i<<j<<cell->value();
                            list.append(cell->value().toString());
                            //qDebug()<<i<<j<<cell->value()<<cell->cellType()<<cell->format();
                        }

                    }
                    else
                    {
                        //单元格内无数据，为空
                         list.append("");
                    }

                }

                // 添
                bool ret = false;
                QString sqlLine = QString("insert into TuDiDingE(id,model,dingeno,biaoshi,mingcheng,danwei,dingeliang,danweizhi,danweiming,jixiebianhao,ercixuanze,\demingcheng,shuoming1,shuoming2,shuoming3,shiyongfanwei,gongzuoneirong,danjia,xianjia,jiacha,weijijia,heji) values (%1,'%2',%3,'%4','%5','%6',%7,%8,'%9',%10,%11,'%12','%13','%14','%15','%16','%17',%18,%19,%20,%21,%22)")
                        .arg(list.at(0).toInt())
                        .arg(list.at(1))
                        .arg(list.at(2).toInt())
                        .arg(list.at(3))
                        .arg(list.at(4))
                        .arg(list.at(5))
                        .arg(list.at(6).toDouble())
                        .arg(list.at(7).toInt())
                        .arg(list.at(8))
                        .arg(list.at(9).toInt())
                        .arg(list.at(10).toInt())
                        .arg(list.at(11))
                        .arg(list.at(12))
                        .arg(list.at(13))
                        .arg(list.at(14))
                        .arg(list.at(15))
                        .arg(list.at(16))
                        .arg(list.at(17).toDouble())
                        .arg(list.at(18).toDouble())
                        .arg(list.at(19).toDouble())
                        .arg(list.at(20).toDouble())
                        .arg(list.at(21).toDouble());
                ret = query.exec(sqlLine);


            }

        }
    }

}
void XlsxInterface::InitDataBase()
{
    // 数据记录
    QString FilePathName = "./DataBase.db";
    db = QSqlDatabase::addDatabase("QSQLITE","DataBase");
    db.setDatabaseName(FilePathName);
    if (db.open())
    {
        QSqlQuery query(db);

        //创建农业定额表
        QString sqlLine = QString("select * from NongYeDingE");
        bool isTableExist = query.exec(sqlLine);    //关键的判断
        if(!isTableExist)
        {
            //如果不存在对应的表，则创建

            query.exec("begin");
            query.exec("create table NongYeDingE( "
                       "id             INTEGER PRIMARY KEY,\
                       model          VARCHAR,\
                       dingeno        INTEGER,\
                       biaoshi        VARCHAR,\
                       mingcheng      VARCHAR,\
                       danwei         VARCHAR,\
                       dingeliang     DOUBLE,\
                       danweizhi      INTEGER,\
                       danweiming     VARCHAR,\
                       jixiebianhao   INTEGER,\
                       ercixuanze     INTEGER,\
                       demingcheng    VARCHAR,\
                       shuoming1      VARCHAR,\
                       shuoming2      VARCHAR,\
                       shuoming3      VARCHAR,\
                       shiyongfanwei  VARCHAR,\
                       gongzuoneirong VARCHAR,\
                       danjia         DOUBLE,\
                       xianjia        DOUBLE,\
                       jiacha         DOUBLE,\
                       weijijia       DOUBLE,\
                       heji           DOUBLE,\
                       zhushi         VARCHAR)");
                    query.exec("commit");
            //返回空表
        }
        else
        {
            //对应表已经存在
        }
        //创建水利定额表
        sqlLine = QString("select * from ShuiLiDingE");
        isTableExist = query.exec(sqlLine);    //关键的判断
        if(!isTableExist)
        {
            //如果不存在对应的表，则创建

            query.exec("begin");
            query.exec("create table ShuiLiDingE( "
                       "id             INTEGER PRIMARY KEY,\
                       model          VARCHAR,\
                       dingeno        INTEGER,\
                       biaoshi        VARCHAR,\
                       mingcheng      VARCHAR,\
                       danwei         VARCHAR,\
                       dingeliang     DOUBLE,\
                       danweizhi      INTEGER,\
                       danweiming     VARCHAR,\
                       jixiebianhao   INTEGER,\
                       ercixuanze     INTEGER,\
                       demingcheng    VARCHAR,\
                       shuoming1      VARCHAR,\
                       shuoming2      VARCHAR,\
                       shuoming3      VARCHAR,\
                       shiyongfanwei  VARCHAR,\
                       gongzuoneirong VARCHAR,\
                       danjia         DOUBLE,\
                       xianjia        DOUBLE,\
                       jiacha         DOUBLE,\
                       weijijia       DOUBLE,\
                       heji           DOUBLE,\
                       zhushi         VARCHAR)");
                    query.exec("commit");
            //返回空表
        }
        else
        {
            //对应表已经存在
        }
        //创建土地定额表
        sqlLine = QString("select * from TuDiDingE");
        isTableExist = query.exec(sqlLine);    //关键的判断
        if(!isTableExist)
        {
            //如果不存在对应的表，则创建

            query.exec("begin");
            query.exec("create table TuDiDingE( "
                       "id             INTEGER PRIMARY KEY,\
                       model          VARCHAR,\
                       dingeno        INTEGER,\
                       biaoshi        VARCHAR,\
                       mingcheng      VARCHAR,\
                       danwei         VARCHAR,\
                       dingeliang     DOUBLE,\
                       danweizhi      INTEGER,\
                       danweiming     VARCHAR,\
                       jixiebianhao   INTEGER,\
                       ercixuanze     INTEGER,\
                       demingcheng    VARCHAR,\
                       shuoming1      VARCHAR,\
                       shuoming2      VARCHAR,\
                       shuoming3      VARCHAR,\
                       shiyongfanwei  VARCHAR,\
                       gongzuoneirong VARCHAR,\
                       danjia         DOUBLE,\
                       xianjia        DOUBLE,\
                       jiacha         DOUBLE,\
                       weijijia       DOUBLE,\
                       heji           DOUBLE,\
                       zhushi         VARCHAR)");
                    query.exec("commit");
            //返回空表
        }
        else
        {
            //对应表已经存在
        }
    }
    else
    {

        QSqlError err = db.lastError();

        QMessageBox::about(nullptr, "error", QString("type %1 \n database %2 \n driver %3").arg((int)err.type()).arg(err.databaseText()).arg(err.driverText()));

    }


}
