#include "eat.h"
#include "ui_eat.h"
#include <QPushButton>
eat::eat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::eat)
{
    ui->setupUi(this);
    connect(ui->back4,&QPushButton::clicked,[=](){
           //发一个信号
      emit this->back();

           });
}

eat::~eat()
{
    delete ui;
}