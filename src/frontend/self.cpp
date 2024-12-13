#include "self.h"

#include <ui.h>

#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include <iostream>
#include <unordered_set>

#include "dialog.h"
#include "ui_self.h"

self::self(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::self)
{
    ui->setupUi(this);
    connect(ui->back5,&QPushButton::clicked,[=](){
           //发一个信号
       emit this->back();

           });
    connect(ui->back13, &QPushButton::clicked, [=]() {
        emit closeAll();  // 发出关闭所有页面的信号
    });
//    this->ppage20=new Dialog;//实例学习匹配
//    connect(ui->back13,&QPushButton::clicked,[=](){
//        //切换窗口
//        this->hide();//隐藏
//        this->ppage20->show();

//    });
}

self::~self()
{
    delete ui;
}

void self::updateUserInfo(const QString &name, const QString &grade, const QString &school,
                           const QString &college, const QStringList &tags)
{
    // 在UI上显示注册页面的信息
    ui->namelabel->setText(name);         // 显示姓名
    ui->gradelabel->setText(grade);       // 显示年级
    ui->schoollabel->setText(school);     // 显示学校
    ui->collegelabel->setText(college);   // 显示学院

    userTags = tags;
    // 如果你有标签显示框，可以将 tags 连接成一个字符串
    ui->tagslabel->setText(tags.join(", ")); // 显示标签
}

void self::showUserInfo() {
  const auto userTags = UI::getUserTags(UI::currentUsername);

  const std::unordered_set<std::string> grades = {"大一", "大二", "大三", "大四", "研一", "研二"};
  const std::unordered_set<std::string> schools = {"SME", "SSE", "SDS", "HSS", "MES", "MUS"};
  const std::unordered_set<std::string> colleges = {"逸夫书院", "学勤书院", "思廷书院", "祥波书院", "道扬书院", "厚含书院", "第七书院"};

  std::string grade;
  std::string school;
  std::string college;
  QStringList otherTags;

  for (const auto &tag : userTags) {
    if (grades.contains(tag)) {
      grade = tag;
    } else if (schools.contains(tag)) {
      school = tag;
    } else if (colleges.contains(tag)) {
      college = tag;
    } else {
      otherTags.append(QString::fromStdString(tag));
    }
  }

  updateUserInfo(UI::currentUsername.data(), grade.data(), school.data(), college.data(), otherTags);
}
