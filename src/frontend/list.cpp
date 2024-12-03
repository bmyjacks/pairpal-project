#include "list.h"
#include "ui_list.h"
#include "chat.h"
#include <QPushButton>
#include <QToolButton>
list::list(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::list)
{
    ui->setupUi(this);
    connect(ui->back10,&QPushButton::clicked,[=](){
           //发一个信号
      emit this->back();

           });

    this->ppage10=new chat;//实例学习匹配
    connect(ui->nameButton,&QToolButton::clicked,[=](){
        //切换窗口
        this->hide();//隐藏
        this->ppage10->show();

    });

    connect(this->ppage10,&chat::back,[=](){
        this->ppage10->hide();
        this->show();
    });

}

list::~list()
{
    delete ui;
}
