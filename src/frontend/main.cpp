#include "dialog.h"
//#include "api/client.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;//zhuchuangkou
    w.show();
    return a.exec();
}
