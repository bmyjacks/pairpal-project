#include "dialog.h"

#include <QPushButton>

#include "pairpal.h"
#include "registerpage.h"  //头文件
#include "ui_dialog.h"
Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
  // 注册页面
  this->ppage2 = new Registerpage;  // 实例窗口二
  connect(ui->btnRegister, &QPushButton::clicked, [=]() {
    // 切换窗口
    this->hide();  // 隐藏
    this->ppage2->show();
  });

  connect(this->ppage2, &Registerpage::back, [=]() {
    this->ppage2->hide();
    this->show();
  });

  // 主页面
  this->ppage3 = new pairpal;
}

Dialog::~Dialog() { delete ui; }

void Dialog::on_btnLogin_clicked() {
  if (ui->txtUserName->text() == tr("dabao") &&
      ui->txtPassWord->text() == tr("123456")) {
    this->hide();  // 隐藏
    this->ppage3->show();

  } else {
    // QMessageBox::warning(this,tr("Warning"),tr("UserName or PassWord
    // Error!"),QMessageBox::Yes);
    QMessageBox msgBox;
    msgBox.setText("用户名或密码输入错误，请重新输入！");
    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        msgBox.exec();
    }

}



