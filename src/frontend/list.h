#ifndef LIST_H
#define LIST_H

#include <QWidget>
#include "chat.h"
#include <QListWidget>
#include <vector>
#include <string>


namespace Ui {
class list;
}

class list : public QWidget
{
    Q_OBJECT

public:
    explicit list(QWidget *parent = nullptr);
    ~list();

    chat *ppage10=NULL;

    // 新增方法
    void updateListWidget(const std::vector<std::string>& items);
    void setBackButtonVisible(bool visible); // 新增方法
    void updateMessage();

signals:
    void back();


private slots:
    // 确保声明了 onListItemClicked
    void onListItemClicked(QListWidgetItem *item);

private:
    Ui::list *ui;
    // QTimer *refreshTimer;

};

#endif // LIST_H
