#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QTextBrowser>
#include <QTextEdit>
#include <QPushButton>

namespace Ui {
class chat;
}

class chat : public QWidget
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = nullptr);
    ~chat();
protected:
    // 重写键盘事件以捕获回车键
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onSendButtonClicked(); // 槽函数，用于处理发送消息




signals:
    void back();

private:
    Ui::chat *ui;
    // 自定义控件指针
    QTextBrowser *messageList; // 显示消息列表
    QTextEdit *inputField;     // 输入框
    QPushButton *sendButton;   // 发送按钮
};

#endif // CHAT_H
