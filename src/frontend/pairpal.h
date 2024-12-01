#ifndef PAIRPAL_H
#define PAIRPAL_H

#include <QMainWindow>

#include "eat.h"
#include "play.h"
#include "self.h"
#include "sport.h"
#include "study.h"

namespace Ui {
class pairpal;
}

class pairpal : public QMainWindow {
  Q_OBJECT

 public:
  explicit pairpal(QWidget *parent = nullptr);
  ~pairpal();

  study *ppage4 = NULL;
  sport *ppage5 = NULL;
  play *ppage6 = NULL;
  eat *ppage7 = NULL;
  self *ppage8 = NULL;

 private:
  Ui::pairpal *ui;
};

#endif  // PAIRPAL_H
