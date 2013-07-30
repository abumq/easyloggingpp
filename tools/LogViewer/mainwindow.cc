#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QFile>
#include <QResizeEvent>
#include <QFileDialog>

#include "aboutdialog.hh"
#include "util.hh"
#include "easylogging++.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectSlots();
    logFileInfo = new QLabel();
    ui->toolbar->insertWidget (0, logFileInfo);
    logFile = NULL;
    updateLogFileInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectLogFile()
{
    QFileDialog openDialog(this);
    Util::deletePtr(logFile);
    logFile = new QFile(openDialog.getOpenFileName());
    if (!logFile->open(QIODevice::ReadOnly)) {
        Util::deletePtr(logFile);
    } else {
        ui->txtLogs->setText(logFile->readAll());
    }
    updateLogFileInfo();
}

void MainWindow::exit()
{
    QApplication::exit();
}

void MainWindow::about()
{
    AboutDialog aboutDialog(this);
    aboutDialog.exec();
}

void MainWindow::aboutQt()
{
    QApplication::aboutQt();
}


void MainWindow::connectSlots()
{
    connect(ui->menuSelectLogFile, SIGNAL(triggered()), SLOT(selectLogFile()));
    connect(ui->menuExit, SIGNAL(triggered()), SLOT(exit()));
    connect(ui->menuAbout, SIGNAL(triggered()), SLOT(about()));
    connect(ui->menuAboutQt, SIGNAL(triggered()), SLOT(aboutQt()));
}

void MainWindow::updateLogFileInfo()
{
    if (logFile == NULL) {
        logFileInfo->setText("Please select log file...");
        return;
    }
    logFileInfo->setText(Util::shortFilename(logFile->fileName(), 40));
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    ui->viewer->setGeometry(0, 0, this->geometry().width(), this->geometry().height());
    ui->tabRaw->setGeometry(ui->viewer->geometry());
    ui->txtLogs->setGeometry(ui->tabRaw->geometry());
}
