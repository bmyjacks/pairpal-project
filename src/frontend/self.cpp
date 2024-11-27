#include "self.h"

#include <QPushButton>

#include "ui_self.h"
self::self(QWidget *parent) : QWidget(parent), ui(new Ui::self) {
  ui->setupUi(this);
  connect(ui->back5, &QPushButton::clicked, [=]() {
    // 发一个信号
    emit this->back();
  });
}

self::~self() { delete ui;
}