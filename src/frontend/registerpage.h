#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QDialog>
// #include "self.h"

class self;  // 前向声明

namespace Ui {
class Registerpage;
}

class Registerpage : public QDialog
{
    Q_OBJECT

public:
    explicit Registerpage(QWidget *parent = nullptr,self* page=nullptr);
    void onButtonClicked();
    ~Registerpage();
    // 将 selfPage 指针声明为类成员
    void setSelfPage(self* page) {
        selfPage = page;
    }

signals:
    void back();


    void userInfoSaved(const QString& name, const QString& grade, const QString& school,
                        const QString& college, const QStringList& tags);

private:
    self* selfPage;  // 指向 Self 页面类的指针

    Ui::Registerpage *ui;
};

#endif // REGISTERPAGE_H
