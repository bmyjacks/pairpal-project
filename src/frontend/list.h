#ifndef LIST_H
#define LIST_H

#include <QWidget>
#include "chat.h"
//#include <QListWidget>

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

signals:
    void back();

private:
    Ui::list *ui;

};

#endif // LIST_H
