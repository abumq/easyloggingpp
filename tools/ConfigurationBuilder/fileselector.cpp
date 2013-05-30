#include "fileselector.h"
#include "ui_fileselector.h"

FileSelector::FileSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSelector)
{
    ui->setupUi(this);
}

FileSelector::~FileSelector()
{
    delete ui;
}

QString FileSelector::filename(void) const
{
    return ui->lineEdit->text();
}

void FileSelector::resize(int w)
{
    ui->horizontalLayoutWidget->setGeometry(0, 0, w, kDefaultHeight);
}
