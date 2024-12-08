#include "list.h"
#include "ui_list.h"
#include "chat.h"
#include <QPushButton>
#include <QToolButton>
#include <QStringList>
#include <QListWidgetItem>
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
//    connect(ui->nameButton,&QToolButton::clicked,[=](){
//        //切换窗口
//        this->hide();//隐藏
//        this->ppage10->show();

//    });

    connect(this->ppage10,&chat::back,[=](){
        this->ppage10->hide();
        this->show();
    });
 // 连接 QListWidget 的 itemClicked 信号到槽函数
    connect(ui->listWidget, &QListWidget::itemClicked, this, &list::onListItemClicked);
    

}

list::~list()
{
    delete ui;
}
void list::updateListWidget(const std::vector<std::string>& items)
{
    ui->listWidget->clear(); // 清空现有的项目
    for (const auto& item : items) {
        ui->listWidget->addItem(QString::fromStdString(item)); // 添加新项目
    }
}

void list::onListItemClicked(QListWidgetItem *item)
{
    // 获取被点击的项目名称
    QString itemName = item->text();

    // 创建 chat 页面实例
    chat *chatPage = new chat();
    chatPage->setWindowTitle(itemName); // 设置窗口标题为项目名称
    chatPage->setChatName(itemName);
    chatPage->show();

    // 设置 chat 页面中的 lb_name 标签
    // chatPage->findChild<QLabel*>("lb_name")->setText(itemName);

    // 隐藏当前 list 页面
//    this->hide();
}
