#include "start.h"
#include "ui_start.h"

Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);

    uiMainWindow = new MainWindow();
    uiMainWindow->hide();
}

Start::~Start()
{
    delete ui;
}

void Start::on_btnOpen_clicked()
{

    this->hide();
    uiMainWindow->show();
}
