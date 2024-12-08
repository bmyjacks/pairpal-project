#include "eat.h"
#include "ui_eat.h"
#include <QPushButton>
#include "ui.h"
#include "list.h"
eat::eat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::eat)
{
    ui->setupUi(this);
    connect(ui->back4,&QPushButton::clicked,[=](){
           //发一个信号
        // 获取 eattime 和 eatplace 的内容
        QString eattime = ui->eattime->text();  // 获取 eattime 输入框的内容
        QString eatplace = ui->eatplace->text(); // 获取 eatplace 输入框的内容

        // 获取 eatitem ComboBox 中选择的内容
        QString eatitem = ui->eatitem->currentText(); // 获取 ComboBox 当前选择的项

        // 使用全局变量 currentUsername
        UI::addUserTag(UI::currentUsername, eattime.toStdString());
        UI::addUserTag(UI::currentUsername, eatplace.toStdString());
        UI::addUserTag(UI::currentUsername, eatitem.toStdString());

      emit this->back();

           });
    connect(ui->eatpair, &QPushButton::clicked, [=]() {
        std::vector<std::string> pairs = UI::getPair(UI::currentUsername);

        // 假设你有一个 list 界面的实例
        list *listPage = new list(this);
        listPage->updateListWidget(pairs);
        listPage->show();
    });
}

eat::~eat()
{
    delete ui;
}
