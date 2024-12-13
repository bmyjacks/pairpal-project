#include "list.h"
#include "ui_list.h"
#include "chat.h"
#include <QPushButton>
#include <QToolButton>
#include <QStringList>
#include <QListWidgetItem>
#include <QTimer>
#include <QSet>
#include "ui.h"  // 添加这一行
#include <algorithm> 

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

    connect(this->ppage10,&chat::back,[=](){
        this->ppage10->hide();
        this->show();
    });
 // 连接 QListWidget 的 itemClicked 信号到槽函数
    connect(ui->listWidget, &QListWidget::itemClicked, this, &list::onListItemClicked);
    
    // // 创建并启动定时器，定期刷新列表
    // refreshTimer = new QTimer(this);
    // connect(refreshTimer, &QTimer::timeout, [this]() {
    //     std::vector<std::string> users;
    
    //     // 获取发送的消息
    //     std::vector<std::string> sentMessages = UI::getSentMessages(UI::currentUsername);
    //     // 获取接收的消息
    //     std::vector<std::string> receivedMessages = UI::getReceivedMessages(UI::currentUsername);
        
    //     // 从发送消息中提取接收者
    //     for (const auto& msg : sentMessages) {
    //         // 消息格式为: "From: xxx\nTo: yyy\nMessage: zzz"
    //         size_t pos = msg.find("To: ");
    //         if (pos != std::string::npos) {
    //             std::string user = msg.substr(pos + 4);
    //             pos = user.find("\n");
    //             if (pos != std::string::npos) {
    //                 user = user.substr(0, pos);
    //                 users.push_back(user);
    //             }
    //         }
    //     }
    //     // 从接收消息中提取发送者
    //     for (const auto& msg : receivedMessages) {
    //         // 消息格式为: "From: xxx\nTo: yyy\nMessage: zzz"
    //         size_t pos = msg.find("From: ");
    //         if (pos != std::string::npos) {
    //             std::string user = msg.substr(pos + 6);
    //             pos = user.find("\n");
    //             if (pos != std::string::npos) {
    //                 user = user.substr(0, pos);
    //                 users.push_back(user);
    //             }
    //         }
    //     }
        
    //     // 去重
    //     std::sort(users.begin(), users.end());
    //     users.erase(std::unique(users.begin(), users.end()), users.end());
        
    //     // 更新列表
    //     updateListWidget(users);
    // });
    // refreshTimer->start(2000); // 每2秒刷新一次

}

list::~list()
{
    // if (refreshTimer) {
    //     refreshTimer->stop();
    //     delete refreshTimer;
    // }
    delete ui;
}
void list::updateListWidget(const std::vector<std::string>& items)
{

    // // 保存当前选中的项
    // QString currentSelected;
    // if (ui->listWidget->currentItem()) {
    //     currentSelected = ui->listWidget->currentItem()->text();
    // }

    ui->listWidget->clear(); // 清空现有的项目
    
    for (const auto& item : items) {
        ui->listWidget->addItem(QString::fromStdString(item)); // 添加新项目
    }
    // // 恢复选中状态
    // if (!currentSelected.isEmpty()) {
    //     auto items = ui->listWidget->findItems(currentSelected, Qt::MatchExactly);
    //     if (!items.isEmpty()) {
    //         ui->listWidget->setCurrentItem(items.first());
    //     }
    // }

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
    
    // // 保持当前选中状态
    // ui->listWidget->setCurrentItem(item);
    chatPage->receiveMessages();
    // 隐藏当前 list 页面
//    this->hide();
}

void list::setBackButtonVisible(bool visible)
{
    ui->back10->setVisible(visible);
}