#include <QApplication>

#include "dialog.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Dialog w;  // zhuchuangkou
  w.show();
  return a.exec();
}