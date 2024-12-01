#ifndef SPORT_H
#define SPORT_H

#include <QWidget>

namespace Ui {
class sport;
}

class sport : public QWidget {
  Q_OBJECT

 public:
  explicit sport(QWidget *parent = nullptr);
  ~sport();

 signals:
  void back();

 private:
  Ui::sport *ui;
};

#endif  // SPORT_H
