#include "ui/registerpage.h"

#include <QPushButton>
Registerpage::Registerpage(QWidget *parent)
    : QDialog(parent), ui(new Ui::Registerpage) {
  ui->setupUi(this);
  connect(ui->pbt2, &QPushButton::clicked, [=]() {
    // 发一个信号
    emit this->back();
  });
}

Registerpage::~Registerpage() { delete ui;
}
