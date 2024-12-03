#ifndef SELF_H
#define SELF_H

#include <QWidget>

namespace Ui {
class self;
}

class self : public QWidget
{
    Q_OBJECT

public:
    explicit self(QWidget *parent = nullptr);
    ~self();
signals:
    void back();
private:
    Ui::self *ui;
};

#endif // SELF_H
