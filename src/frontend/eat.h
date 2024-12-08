#ifndef EAT_H
#define EAT_H

#include <QWidget>

namespace Ui {
class eat;
}

class eat : public QWidget
{
    Q_OBJECT

public:
    explicit eat(QWidget *parent = nullptr);
    ~eat();
signals:
    void back();

private:
    Ui::eat *ui;
};

#endif // EAT_H
