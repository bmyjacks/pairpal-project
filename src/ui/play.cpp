#include "play.h"
#include "ui_play.h"
#include <QPushButton>
play::play(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::play)
{
    ui->setupUi(this);
    connect(ui->back3,&QPushButton::clicked,[=](){
           //发一个信号
      emit this->back();

           });
}

play::~play()
{
    delete ui;
}
