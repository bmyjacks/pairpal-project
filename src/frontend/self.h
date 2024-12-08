#ifndef SELF_H
#define SELF_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include "dialog.h"



namespace Ui {
class self;
}

class self : public QWidget
{
    Q_OBJECT

public:
    explicit self(QWidget *parent = nullptr);
    ~self();

QDialog *ppage20=NULL;
public slots:
    void updateUserInfo(const QString& name,const QString& grade, const QString& school,
                        const QString& college, const QStringList& tags);
signals:
    void back();
private:
    Ui::self *ui;
};

#endif // SELF_H
