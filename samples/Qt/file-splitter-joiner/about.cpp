#include "about.h"
#include "ui_about.h"
#include <QMessageBox>
#include "easylogging++.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About) {
    ui->setupUi(this);
    ui->el_info->setText(QString(el::VersionInfo::formattedInfo().c_str()));
}

About::~About() {
    delete ui;
}

void About::on_pushButton_clicked() {
    QMessageBox aboutQt;
    aboutQt.aboutQt(this);
}
