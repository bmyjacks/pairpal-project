#include "sport.h"
#include "ui_sport.h"
#include <QPushButton>
sport::sport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sport)
{
    ui->setupUi(this);
    connect(ui->back2,&QPushButton::clicked,[=](){
           //发一个信号
       emit this->back();

           });
}

sport::~sport()
{
    delete ui;
}
