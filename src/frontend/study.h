#ifndef STUDY_H
#define STUDY_H

#include <QWidget>

namespace Ui {
class study;
}

class study : public QWidget
{
    Q_OBJECT

public:
    explicit study(QWidget *parent = nullptr);
    ~study();
signals:
    void back();

private:
    Ui::study *ui;
};

#endif // STUDY_H
