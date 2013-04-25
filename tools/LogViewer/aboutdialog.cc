#include "aboutdialog.hh"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    connect(ui->buttonClose, SIGNAL(clicked()), SLOT(close()));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
