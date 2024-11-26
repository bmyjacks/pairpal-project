#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QDialog>

namespace Ui {
class Registerpage;
}

class Registerpage : public QDialog
{
    Q_OBJECT

public:
    explicit Registerpage(QWidget *parent = nullptr);
    ~Registerpage();

signals:
    void back();



private:
    Ui::Registerpage *ui;
};

#endif // REGISTERPAGE_H
