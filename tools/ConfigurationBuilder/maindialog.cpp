#include "maindialog.h"
#include "ui_maindialog.h"
#include "fileselector.h"
#include "configurationchooser.h"

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
    configurationChooser->loadFromFile("/home/majid/projects/EasyLoggingPP/test/test_conf.conf");
}

MainDialog::~MainDialog()
{
    delete ui;
    delete fileSelector;
    delete configurationChooser;
}

void MainDialog::on_pushButton_clicked()
{
    ui->txtConfigurations->setText(configurationChooser->convertConfigurationToString());
}
