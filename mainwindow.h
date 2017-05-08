#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QSplitter>
#include <QTextEdit>

#include <QTreeWidgetItem>
#include "struct.h"

#include <math.h>
#include <QMessageBox>
#include "modifytext.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



public
    slots:
    void open();
private:
    Ui::MainWindow *ui;

    QAction *openAction;

};

#endif // MAINWINDOW_H
