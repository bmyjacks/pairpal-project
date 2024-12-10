#include "play.h"
#include "ui_play.h"
#include <QPushButton>
#include "ui.h"
#include "list.h" 
play::play(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::play)
{
    ui->setupUi(this);
    connect(ui->back3,&QPushButton::clicked,[=](){
          
        
      emit this->back();

           });
    // 添加新的连接到 playpair 按钮的槽函数
    connect(ui->playpair, &QPushButton::clicked, [=]() {
        // 获取 eattime 和 eatplace 的内容
        QString playtime = ui->playtime->text();  // 获取 eattime 输入框的内容
        QString playplace = ui->playplace->text(); // 获取 eatplace 输入框的内容

        // 获取 eatitem ComboBox 中选择的内容
        QString playitem = ui->playitem->currentText(); // 获取 ComboBox 当前选择的项

        // 使用全局变量 currentUsername
        UI::addUserTag(UI::currentUsername, playtime.toStdString());
        UI::addUserTag(UI::currentUsername, playplace.toStdString());
        UI::addUserTag(UI::currentUsername, playitem.toStdString());


        
        // 调用 getPair 函数
        std::vector<std::string> pairs = UI::getPair(UI::currentUsername);
        
        // 假设你有一个 list 界面的实例
        list *listPage = new list();
        listPage->updateListWidget(pairs);
        listPage->show();
    });

}

play::~play()
{
    delete ui;
}
