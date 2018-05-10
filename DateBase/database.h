#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QMutex>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


class database : public QObject
{

    Q_OBJECT
public:

    explicit database(QObject *parent = 0);

    ~database(void);
    // 系统初始化
    void databaseInit(void);
    // 记录文件关闭
    void databaseClose(void);
    // 记录文件更新
    void databaseUpdate(void);

    // 添加记录
    void AddDataBase(int index, int group, double Axisp1, double Axisp2, double Axisp3,double Axisp4,double Axisp5,double Axisp6\
                            ,double Axisn1, double Axisn2, double Axisn3,double Axisn4,double Axisn5,double Axisn6
                            ,double Uniten);



    //查询数据库
    int SerachDataBase();

    //清空数据库
    bool ClearDataBase();


public:
signals:
    void SendURData();
private:
    // 文件是否创立
    bool IsFileSetup;
    // 系统运行时间
    QDateTime SysStartTime;
    // 预写入指令
    QStringList SysLogStrings;

    int RobotLogKey;
    int SoftWareLogKey;


    QSqlDatabase db;

};



#endif // DATABASE_H
