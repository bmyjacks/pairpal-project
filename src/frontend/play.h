#ifndef PLAY_H
#define PLAY_H

#include <QWidget>

namespace Ui {
class play;
}

class play : public QWidget
{
    Q_OBJECT

public:
    explicit play(QWidget *parent = nullptr);
    ~play();
signals:
    void back();

private:
    Ui::play *ui;
};

#endif // PLAY_H
