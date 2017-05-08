#ifndef MODIFYTEXT_H
#define MODIFYTEXT_H

#include <QDialog>

namespace Ui {
class ModifyText;
}

class ModifyText : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyText(QWidget *parent = 0);
    ~ModifyText();

protected:
    signals:
    void SignalModifyText(QString value);
private slots:
    void on_pushButtonok_clicked();

    void on_pushButtoncancel_clicked();

private:
    Ui::ModifyText *ui;
};

#endif // MODIFYTEXT_H
