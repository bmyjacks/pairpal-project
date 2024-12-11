#include "eat.h"
#include "ui_eat.h"
#include <QPushButton>
#include "ui.h"
#include "list.h"
#include "pairpal.h"
eat::eat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::eat)
    
{
    ui->setupUi(this);
    connect(ui->back4,&QPushButton::clicked,[=](){
          
        
      emit this->back();

           });
    connect(ui->eatpair, &QPushButton::clicked, [=]() {
        
        // 获取 eattime 和 eatplace 的内容
        QString eattime = ui->eattime->text();  // 获取 eattime 输入框的内容
        QString eatplace = ui->eatplace->text(); // 获取 eatplace 输入框的内容
        QString eatitem = ui->eatitem->currentText(); // 获取 ComboBox 当前选择的项

        // 使用全局变量 currentUsername
        UI::addUserTag(UI::currentUsername, eattime.toStdString());
        UI::addUserTag(UI::currentUsername, eatplace.toStdString());
        UI::addUserTag(UI::currentUsername, eatitem.toStdString());

        
        std::vector<std::string> pairs = UI::getPair(UI::currentUsername);

        
        list *listPage = new list();
        listPage->updateListWidget(pairs);
        listPage->setBackButtonVisible(false); // 隐藏 back10 按钮
        listPage->show();
         
    });
}

eat::~eat()
{
    delete ui;
}
