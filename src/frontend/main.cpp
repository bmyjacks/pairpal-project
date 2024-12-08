#include <QApplication>

#include "dialog.h"
#include "ui.h"

int main(int argc, char *argv[]) {
  UI::UI();
  QApplication a(argc, argv);
  Dialog w;  // zhuchuangkou
  w.show();
  return a.exec();
}
