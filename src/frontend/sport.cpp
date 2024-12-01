#include "sport.h"

#include <QPushButton>

#include "ui_sport.h"
sport::sport(QWidget *parent) : QWidget(parent), ui(new Ui::sport) {
  ui->setupUi(this);
  connect(ui->back2, &QPushButton::clicked, [=]() {
    // 发一个信号
    emit this->back();
  });
}

sport::~sport() { delete ui;
}
