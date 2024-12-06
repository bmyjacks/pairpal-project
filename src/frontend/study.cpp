#include "study.h"
#include "ui_study.h"
#include <QPushButton>
#include "ui.h"
#include "list.h"
study::study(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::study)
{
    ui->setupUi(this);
    connect(ui->back1,&QPushButton::clicked,[=](){
           //发一个信号
        // 获取 eattime 和 eatplace 的内容
        QString studytime = ui->studytime->text();  // 获取 eattime 输入框的内容
        QString studyplace = ui->studyplace->text(); // 获取 eatplace 输入框的内容

        // 获取 eatitem ComboBox 中选择的内容
        QString studyitem = ui->studyitem->currentText(); // 获取 ComboBox 当前选择的项

        // 使用全局变量 currentUsername
        UI::addUserTag(UI::currentUsername, studytime.toStdString());
        UI::addUserTag(UI::currentUsername, studyplace.toStdString());
        UI::addUserTag(UI::currentUsername, studyitem.toStdString());

        emit this->back();

           });
        connect(ui->studypair, &QPushButton::clicked, [=]() {
        std::vector<std::string> pairs = UI::getPair(UI::currentUsername);

        // 假设你有一个 list 界面的实例
        list *listPage = new list(this);
        listPage->updateListWidget(pairs);
        listPage->show();
    });
}

study::~study()
{
    delete ui;
}
