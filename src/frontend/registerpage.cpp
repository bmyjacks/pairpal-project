#include "registerpage.h"
#include "ui_registerpage.h"
#include <QPushButton>
#include <QLineEdit>


Registerpage::Registerpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registerpage) {
    ui->setupUi(this);
    connect(ui->pbt2,&QPushButton::clicked,[=](){
           //发一个信号
        QLineEdit *lineEdit = ui->name;
        if (lineEdit) {
            QString content = lineEdit->text(); // 获取输入框内
        }


        emit this->back();
           });
}



Registerpage::~Registerpage()
{
    delete ui;
}
