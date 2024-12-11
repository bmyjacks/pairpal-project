#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>
// #include "registerpage.h"//yemianer
// #include "pairpal.h"//zhuyemian
// #include "self.h"
class Registerpage;  // 前向声明
class pairpal;
class self;

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    Registerpage *ppage2=NULL;//用来保存页面二对象地址
    pairpal *ppage3=NULL;//保存主页面
private slots:
    void on_btnLogin_clicked();
//    void logout();


private:
//    void resetSessionData()；
    Ui::Dialog *ui;

};
#endif // DIALOG_H
