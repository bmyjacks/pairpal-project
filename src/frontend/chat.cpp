#include "chat.h"
#include "ui_chat.h"
#include <QPushButton>
#include <QDebug>
#include <QKeyEvent>
chat::chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    connect(ui->back11,&QPushButton::clicked,[=](){
           //发一个信号
      emit this->back();

           });
    // 使用 findChild 查找 UI 中的控件
    messageList = findChild<QTextBrowser *>("messageList"); // 显示消息列表
    inputField = findChild<QTextEdit *>("inputField");      // 输入框
    sendButton = findChild<QPushButton *>("sendButton");    // 发送按钮

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
void chat::onSendButtonClicked()
{
    // 获取输入框的文本
    QString message = inputField->toPlainText().trimmed(); // QTextEdit 使用 toPlainText

    if (!message.isEmpty()) {
        // 将消息添加到消息显示区域（QTextBrowser）
        messageList->append("我: " + message);

        // 清空输入框
        inputField->clear();

//        // 模拟接收一条消息
//        messageList->append("对方: 收到 -> " + message);

        // 自动滚动到最新消息
        messageList->moveCursor(QTextCursor::End);
    }
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

