#include "modifytext.h"
#include "ui_modifytext.h"

ModifyText::ModifyText(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyText)
{
    ui->setupUi(this);
}

ModifyText::~ModifyText()
{
    delete ui;
}

void ModifyText::on_pushButtonok_clicked()
{
    emit SignalModifyText(ui->lineEdit->text());
    this->close();
}

void ModifyText::on_pushButtoncancel_clicked()
{
    this->close();
}
