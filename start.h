#ifndef START_H
#define START_H

#include <QWidget>
#include "mainwindow.h"
namespace Ui {
class Start;
}

class Start : public QWidget
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = 0);
    ~Start();

private slots:
    void on_btnOpen_clicked();

private:
    Ui::Start *ui;
    MainWindow *uiMainWindow;
};

#endif // START_H
