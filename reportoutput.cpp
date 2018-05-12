#include "reportoutput.h"
#include "ui_reportoutput.h"

ReportOutput::ReportOutput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportOutput)
{
    ui->setupUi(this);


    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    setWindowTitle("报表输出");

    QListWidgetItem *item1 = new QListWidgetItem("项目总概算表及分年度投资概算表", ui->listWidgetExport);
    item1->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
    item1->setCheckState(Qt::Unchecked);

    ui->listWidgetExport->addItem(item1);




}

ReportOutput::~ReportOutput()
{
    delete ui;
}

void ReportOutput::on_pushButtonExport_clicked()
{
    interface.CreateBookTest();
}

void ReportOutput::on_pushButtonOpen_clicked()
{
    //interface.OpenXlsx();

    interface.OpenNongyeXlsx();
    interface.OpenShuiLiXlsx();
    interface.OpenTuDiXlsx();
}
