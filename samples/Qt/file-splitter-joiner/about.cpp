#include "about.h"
#include "ui_about.h"
#include <QMessageBox>

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About) {
    ui->setupUi(this);
}

About::~About() {
    delete ui;
}

void About::on_pushButton_clicked() {
    QMessageBox aboutQt;
    aboutQt.aboutQt(this);
}
