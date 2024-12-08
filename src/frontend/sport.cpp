#include "sport.h"
#include "ui_sport.h"
#include <QPushButton>
#include "ui.h"
#include "list.h"
sport::sport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sport)
{
    ui->setupUi(this);
    connect(ui->back2,&QPushButton::clicked,[=](){
           //发一个信号
        // 获取 eattime 和 eatplace 的内容
        QString sporttime = ui->sporttime->text();  // 获取 eattime 输入框的内容
        QString sportplace = ui->sportplace->text(); // 获取 eatplace 输入框的内容

        // 获取 eatitem ComboBox 中选择的内容
        QString sportitem = ui->sportitem->currentText(); // 获取 ComboBox 当前选择的项

        // 使用全局变量 currentUsername
        UI::addUserTag(UI::currentUsername, sporttime.toStdString());
        UI::addUserTag(UI::currentUsername, sportplace.toStdString());
        UI::addUserTag(UI::currentUsername, sportitem.toStdString());

       emit this->back();

           });
    connect(ui->sportpair, &QPushButton::clicked, [=]() {
        std::vector<std::string> pairs = UI::getPair(UI::currentUsername);

        // 假设你有一个 list 界面的实例
        list *listPage = new list();
        listPage->updateListWidget(pairs);
        listPage->show();
    });
}

sport::~sport()
{
    delete ui;
}
