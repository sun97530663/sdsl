#ifndef MATERIALPRICESET_H
#define MATERIALPRICESET_H

#include <QWidget>

namespace Ui {
class MaterialPriceSet;
}

class MaterialPriceSet : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialPriceSet(QWidget *parent = 0);
    ~MaterialPriceSet();

private:
    Ui::MaterialPriceSet *ui;
};

#endif // MATERIALPRICESET_H
