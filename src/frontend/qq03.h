#ifndef QQ03_H
#define QQ03_H

#include <QWidget>

namespace Ui {
class qq03;
}

class qq03 : public QWidget
{
    Q_OBJECT

public:
    explicit qq03(QWidget *parent = nullptr);
    ~qq03();

private:
    Ui::qq03 *ui;
};

#endif // QQ03_H
