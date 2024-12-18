#include "registerpage.h"
#include "ui_registerpage.h"
#include <QPushButton>
#include <QLineEdit>
#include <QStringList>
#include  "ui.h"
#include <string>
#include "self.h"
#include <QDebug>
#include <iostream>



Registerpage::Registerpage(QWidget *parent,self* selfPagePtr) :
    QDialog(parent),
    ui(new Ui::Registerpage),
    selfPage(selfPagePtr)
{
    ui->setupUi(this);
    connect(ui->pbt2,&QPushButton::clicked,[=](){
           //发一个信号
        // 获取名字
        QString name = ui->name->text(); // 直接获取输入框内容
        std::cout << name.toStdString() << std::endl;
        // 获取密码
        QString password = ui->password->text();

        UI::addUser(name.toStdString(), password.toStdString());

        // 初始化性别、年级、学校、学院和标签
        QString grade= ui->grade->currentText();
        QString school= ui->school->currentText();
        QString college= ui->college->currentText();
        QStringList tags;


        UI::addUserTag(name.toStdString(), grade.toStdString());
        UI::addUserTag(name.toStdString(), school.toStdString());
        UI::addUserTag(name.toStdString(), college.toStdString());
        

        // 遍历所有复选框，获取选中状态
        for (int i = 1; i <= 20; ++i) {
            // 动态获取复选框对象
            QCheckBox *checkBox = this->findChild<QCheckBox *>("checkBox_" + QString::number(i));
            if (checkBox && checkBox->isChecked()) {
                // 获取复选框旁边的文字
                tags.append(checkBox->text());
                // 调用 addUserTag 添加标签
                UI::addUserTag(name.toStdString(), checkBox->text().toStdString());
            }
        }
    
        emit userInfoSaved(name, grade, school, college, tags);

        // 如果 selfPage 被正确实例化，调用 updateUserInfo 来更新 Self 页面
        if (selfPage) {
            selfPage->updateUserInfo(name, grade, school, college, tags);
        }

        emit this->back();
           });
}



Registerpage::~Registerpage()
{
    delete ui;
}
