#include "study.h"
#include "ui_study.h"
#include <QPushButton>
study::study(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::study)
{
    ui->setupUi(this);
    connect(ui->back1,&QPushButton::clicked,[=](){
           //发一个信号
        emit this->back();

           });
}

study::~study()
{
    delete ui;
}
