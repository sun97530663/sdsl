#include "database.h"
#include <QMessageBox>

bool IsFileFail = false;
QMutex mutex;

database::database(QObject *parent) :
    QObject(parent)
{
    IsFileSetup = false;

    RobotLogKey = 0;
    SoftWareLogKey = 0;
    SysLogStrings.clear();


}
database::~database(void)
{
}
void database::databaseInit()
{

    //建立数据库存放目录
    QFileInfo datalog("./DataLog");
    if(datalog.exists()){

        //已存在,不处理
    }
    else{

        //如果不存在则建立DataLog目录
        QDir *temp = new QDir;
        bool ok = temp->mkdir("./DataLog");
        if(!ok)
            return;
    }
    if ((!IsFileSetup) && (!IsFileFail))
    {
        QDateTime tm;
        tm = QDateTime::currentDateTime();
        // 数据记录
        QString FilePathName = ".\\DataLog\\";
        FilePathName.append("DataBaseLog.db");
        QFile mFile(FilePathName);
        if(mFile.exists())
        {


            if(QSqlDatabase::contains("database"))
                db = QSqlDatabase::database("database");
            else
                db = QSqlDatabase::addDatabase("QSQLITE","database");

            db.setDatabaseName(FilePathName);
            if (db.open())
            {

                IsFileSetup = true;
            }
            else
            {
                IsFileFail = true;
                QSqlError err = db.lastError();
            }

        }else{
            //如果文件不存在建立表
            db = QSqlDatabase::addDatabase("QSQLITE","database");
            db.setDatabaseName(FilePathName);
            if (db.open())
            {
                QSqlQuery query(db);
                bool w = false;
                w= query.exec("begin");


                QString sqlline ="create table DataBaseLog(id integer primary key,myindex integer,GroupNum integer"\
                        ",AxisP1 real, AxisP2 real, AxisP3 real, AxisP4 real, AxisP5 real, AxisP6 real"\
                        ",AxisN1 real, AxisN2 real, AxisN3 real, AxisN4 real, AxisN5 real, AxisN6 real"\
                        ",UniteN real)";
                w = query.exec(sqlline);

                qDebug()<<w<<endl;
                w = query.exec("commit");
                SysStartTime = QDateTime::currentDateTime();
                IsFileSetup = true;
                SysLogStrings.clear();
            }
            else
            {
                IsFileFail = true;
                QSqlError err = db.lastError();
                QMessageBox::about(nullptr, "error", QString("type %1 \n database %2 \n driver %3").arg((int)err.type()).arg(err.databaseText()).arg(err.driverText()));
            }

        }

    }
    else if (IsFileSetup)
    {
    }
}
void database::databaseClose(void)
{
    if (IsFileSetup)
    {
    }
}

// 添加记录
void database::AddDataBase(int index, int group, double Axisp1, double Axisp2, double Axisp3,double Axisp4,double Axisp5,double Axisp6\
                           ,double Axisn1, double Axisn2, double Axisn3,double Axisn4,double Axisn5,double Axisn6
                           ,double Uniten){


    if (IsFileSetup)
    {
        mutex.lock();// 上锁

        SoftWareLogKey++;

        QString sqlLine = QString("insert into DataBaseLog values (%1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13, %14, %15, %16)")\
                .arg(SoftWareLogKey).arg(index).arg(group)\
                .arg(Axisp1).arg(Axisp2).arg(Axisp3).arg(Axisp4).arg(Axisp5).arg(Axisp6)\
                .arg(Axisn1).arg(Axisn2).arg(Axisn3).arg(Axisn4).arg(Axisn5).arg(Axisn6)\
                .arg(Uniten);

        SysLogStrings.append(sqlLine);
        mutex.unlock();//解锁
    }

}

//查询数据库
int database::SerachDataBase(){




    //查询对应表是否存在
    QSqlQuery query(db);
    QString sqlLine = QString("select * from DataBaseLog");
    bool isTableExist = query.exec(sqlLine);    //关键的判断
    if(!isTableExist)
    {
        //如果不存在对应的表
        qDebug() << "table does not exist";

        return 1;

    }
    else
    {
        //对应表存在

        sqlLine =  QString("select * from DataBaseLog");
        //获取当前编号
        bool IsInsert = query.exec(sqlLine);

        int tid = 0;
        int tindex = 0;
        int tgroup = 0;


        while(query.next())
        {
            tid = query.value(0).toInt();
            tindex = query.value(1).toInt();
            tgroup = query.value(2).toInt();

        }
        return 0;
    }
}
//清空数据库
bool database::ClearDataBase(){

    if (IsFileSetup)
    {
        // 进入临界区
        mutex.lock();
        QSqlQuery query(db);

        QString sqlLine =  QString("delete from DataBaseLog");
        //
        bool Isdelete = false;
        Isdelete = query.exec(sqlLine);

        if(Isdelete){
            SoftWareLogKey = 0;
        }

        mutex.unlock();
        return Isdelete;
    }

}
