#include "qq03.h"
#include "ui_qq03.h"

qq03::qq03(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qq03)
{
    ui->setupUi(this);
}

qq03::~qq03()
{
    delete ui;
}
