#ifndef REPORTOUTPUT_H
#define REPORTOUTPUT_H

#include <QWidget>
#include "QtXlsxWriter/xlsxinterface.h"
namespace Ui {
class ReportOutput;
}

class ReportOutput : public QWidget
{
    Q_OBJECT

public:
    explicit ReportOutput(QWidget *parent = 0);
    ~ReportOutput();

private slots:
    void on_pushButtonExport_clicked();


    void on_pushButtonOpen_clicked();

private:
    Ui::ReportOutput *ui;

    //表格测试
    XlsxInterface interface;

};

#endif // REPORTOUTPUT_H
