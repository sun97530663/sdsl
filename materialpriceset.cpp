#include "materialpriceset.h"
#include "ui_materialpriceset.h"

MaterialPriceSet::MaterialPriceSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaterialPriceSet)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    setWindowTitle("材料价格维护");
}

MaterialPriceSet::~MaterialPriceSet()
{
    delete ui;
}
