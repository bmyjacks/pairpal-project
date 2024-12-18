#include "chat.h"
#include "ui_chat.h"
#include <QPushButton>
#include <QDebug>
#include <QKeyEvent>
#include "ui.h" 
chat::chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    // 使用 findChild 查找 UI 中的控件
    messageList = findChild<QTextBrowser *>("messageList"); // 显示消息列表
    inputField = findChild<QTextEdit *>("inputField");      // 输入框
    sendButton = findChild<QPushButton *>("sendButton");    // 发送按钮
    lb_name = findChild<QLabel *>("lb_name"); // 查找 lb_name

    // 检查控件是否找到
    if (!messageList || !inputField || !sendButton) {
        qDebug() << "Failed to find UI components!";
        if (!messageList) qDebug() << "messageList not found!";
        if (!inputField) qDebug() << "inputField not found!";
        if (!sendButton) qDebug() << "sendButton not found!";
        return; // 避免程序继续运行导致崩溃
    }

    // 连接信号和槽
    bool sendButtonConnected = connect(sendButton, &QPushButton::clicked, this, &chat::onSendButtonClicked);

    qDebug() << "sendButton connected:" << sendButtonConnected;
}

chat::~chat()
{
    delete ui;
}

void chat::setChatName(const QString &name)
{
    ui->lb_name->setText(name);
}

void chat::onSendButtonClicked()
{
    QString message = inputField->toPlainText().trimmed();

    if (!message.isEmpty()) {
        // 发送消息
        QString recipient = lb_name->text(); // 假设 lb_name 是接收者
        QString currentUser = QString::fromStdString(UI::currentUsername);
        if (UI::sendMessage(currentUser.toStdString(), recipient.toStdString(), message.toStdString())) {
            // 将消息添加到消息显示区域
            messageList->append("我: " + message);

            // 清空输入框
            inputField->clear();
            
            // 自动滚动到最新消息
            messageList->moveCursor(QTextCursor::End);
        } else {
            qDebug() << "Failed to send message!";
        }
    }
    

}
void chat::receiveMessages() {

    // 清空现有消息
    messageList->clear();
    // 创建一个向量来存储所有消息，以便我们可以按正确顺序显示
    std::vector<QString> allMessages;

   // 获取当前聊天对象的用户名
    QString chatPartner = lb_name->text();
    QString currentUser = QString::fromStdString(UI::currentUsername);

    // 获取发送的消息
    std::vector<std::string> sentMessages = UI::getSentMessages(UI::currentUsername);
    for (const auto& msg : sentMessages) {
        QString qMsg = QString::fromStdString(msg);
        // 解析消息格式
        QStringList parts = qMsg.split("\n");
        if (parts.size() == 3) {
            QString to = parts[1].mid(4); // "To: " 后的内容
            QString message = parts[2].mid(9).trimmed(); // "Message: " 后的内容，去除空格
            // 只显示发给当前聊天对象的消息
            if (to == chatPartner) {
            //QString message = parts[2].mid(9); // "Message: " 后的内容
            //messageList->append("我 -> " + to + ": " + message);
            allMessages.push_back("我: " + message);
            }
        }
    
    }

    // QString sender = lb_name->text(); // 假设 lb_name 是对方的名字
    // std::vector<std::string> receivedMessages = UI::getReceivedMessages(UI::currentUsername);
    // for (const auto& recvMsg : receivedMessages) {
    //     // 过滤掉自己发送的消息，只显示对方发来的消息
    //     if (recvMsg.find(sender.toStdString()) != std::string::npos) {
    //         messageList->append("对方: " + QString::fromStdString(recvMsg));
    //     }
    // }
     // 获取接收到的消息
    std::vector<std::string> receivedMessages = UI::getReceivedMessages(UI::currentUsername);
    for (const auto& msg : receivedMessages) {
        QString qMsg = QString::fromStdString(msg);
        // 解析消息格式
        QStringList parts = qMsg.split("\n");
        if (parts.size() == 3) {
            QString from = parts[0].mid(6).trimmed(); // "From: " 后的内容，去除空格
            QString message = parts[2].mid(9).trimmed(); // "Message: " 后的内容，去除空格
            if (from == chatPartner) {
            // QString message = parts[2].mid(9); // "Message: " 后的内容
            // //messageList->append(from + ": " + message);
            allMessages.push_back(from + ": " + message);
            
            }
        }
    }
    // 按时间顺序显示所有消息
    for (const auto& message : allMessages) {
        messageList->append(message);
    }

    messageList->moveCursor(QTextCursor::End);
}

// 捕获键盘事件（用于检测按下回车键）
void chat::keyPressEvent(QKeyEvent *event)
{
    // 检查是否在输入框中按下了回车键
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        if (inputField->hasFocus()) { // 确保焦点在 inputField
            onSendButtonClicked();   // 调用发送消息槽函数
            return;                  // 防止默认行为
        }
    }

    // 调用父类的 keyPressEvent 处理其他按键
    QWidget::keyPressEvent(event);
}