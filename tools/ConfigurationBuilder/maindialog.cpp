#include "maindialog.h"
#include "ui_maindialog.h"
#include "fileselector.h"
#include "configurationchooser.h"
#include <QFile>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    fileSelector = new FileSelector(this);
    configurationChooser = new ConfigurationChooser(this);
    fileSelector->resize(841);
    fileSelector->move(((std::max(width(), fileSelector->width()) - std::min(width(), fileSelector->width())) / 2),
                       height() - fileSelector->height());
    QObject::connect(fileSelector, SIGNAL(fileOpened(QString)), configurationChooser, SLOT(loadFromFile(QString)));
}

MainDialog::~MainDialog()
{
    delete ui;
    delete fileSelector;
    delete configurationChooser;
}

void MainDialog::on_pushButton_clicked()
{
    LOG(INFO) << "Building...";
    ui->txtConfigurations->setText(configurationChooser->convertConfigurationToString());
}

void MainDialog::on_buttonSave_clicked()
{
    on_pushButton_clicked();
    QString configurationToSave = ui->txtConfigurations->toPlainText();
    fileSelector->openForSaving();
    if (fileSelector->filename().isEmpty()) {
        return;
    }
    LOG(INFO) << "Saving configuration file";
    QFile f(fileSelector->filename());
    if (f.open(QIODevice::WriteOnly)) {
        f.write (QByteArray(configurationToSave.toStdString ().c_str()));
        f.close();
    } else {
        LOG(ERROR) << "Unable to write to file [" << fileSelector->filename() << "]. Please make sure it is writable.";
    }
}
