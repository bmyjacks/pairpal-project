#include "pairpal.h"

#include <QPushButton>

#include "eat.h"
#include "play.h"
#include "self.h"
#include "sport.h"
#include "study.h"
#include "ui_pairpal.h"
pairpal::pairpal(QWidget *parent) : QMainWindow(parent), ui(new Ui::pairpal) {
  ui->setupUi(this);
  this->ppage4 = new study;  // 实例学习匹配
  connect(ui->studyButton, &QPushButton::clicked, [=]() {
    // 切换窗口
    this->hide();  // 隐藏
    this->ppage4->show();
  });

  connect(this->ppage4, &study::back, [=]() {
    this->ppage4->hide();
    this->show();
  });

  this->ppage5 = new sport;  // 实例学习匹配
  connect(ui->sportButton, &QPushButton::clicked, [=]() {
    // 切换窗口
    this->hide();  // 隐藏
    this->ppage5->show();
  });

  connect(this->ppage5, &sport::back, [=]() {
    this->ppage5->hide();
    this->show();
  });

  this->ppage6 = new play;  // 实例学习匹配
  connect(ui->playButton, &QPushButton::clicked, [=]() {
    // 切换窗口
    this->hide();  // 隐藏
    this->ppage6->show();
  });

  connect(this->ppage6, &play::back, [=]() {
    this->ppage6->hide();
    this->show();
  });

  this->ppage7 = new eat;  // 实例学习匹配
  connect(ui->eatButton, &QPushButton::clicked, [=]() {
    // 切换窗口
    this->hide();  // 隐藏
    this->ppage7->show();
  });

  connect(this->ppage7, &eat::back, [=]() {
    this->ppage7->hide();
    this->show();
  });

  this->ppage8 = new self;  // 实例学习匹配
  connect(ui->selfButton, &QPushButton::clicked, [=]() {
    // 切换窗口
    this->hide();  // 隐藏
    this->ppage8->show();
  });

  connect(this->ppage8, &self::back,[=](){
        this->ppage8->hide();
        this->show();
    });
}

pairpal::~pairpal()
{
    delete ui;
}