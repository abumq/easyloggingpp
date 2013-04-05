#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "easylogging++.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    LINFO << "Test";
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
