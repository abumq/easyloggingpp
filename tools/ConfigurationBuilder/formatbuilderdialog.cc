#include "formatbuilderdialog.hh"
#include "ui_formatbuilderdialog.h"
#include <QListWidgetItem>

#include "easylogging++.h"

FormatBuilderDialog::FormatBuilderDialog(QWidget *parent, unsigned int level, const QString& currentFormat) :
    QDialog(parent),
    ui(new Ui::FormatBuilderDialog),
    constants(easyloggingpp::internal::registeredLoggers->constants())
{
    ui->setupUi(this);
    if (level != easyloggingpp::Level::Verbose) {
        ui->chkVerboseLevel->hide();
    } else {
        ui->chkVerboseLevel->show();
    }
    ui->lblLevel->setText(QString("Level: <b>") + QString(easyloggingpp::Level::convertToString(level).c_str()).toUpper() + QString("</b>"));
    ui->txtFormat->setText(currentFormat);
    updateUi();
}

FormatBuilderDialog::~FormatBuilderDialog()
{
    delete ui;
}

void FormatBuilderDialog::updateUi() const
{
    QString curr = ui->txtFormat->text();

}

void FormatBuilderDialog::updateFormat() const
{
    QString format;
    for (int i = 0; i < ui->lstOrder->count(); ++i) {
        format.append(ui->lstOrder->item(i)->text() + QString(" "));
    }
    ui->txtFormat->setText(format);
}

QString FormatBuilderDialog::qstr(const std::string &str) const
{
    return QString(str.c_str());
}

void FormatBuilderDialog::addFormat(bool checked, const QString &formatSpecifier)
{
    QList<QListWidgetItem*> listFormat = ui->lstOrder->findItems(formatSpecifier, Qt::MatchCaseSensitive);
    if (checked) {
        if (listFormat.isEmpty()) {
            ui->lstOrder->insertItem(ui->lstOrder->count(), formatSpecifier);
        }
    } else {
        if (!listFormat.isEmpty()) {
            ui->lstOrder->removeItemWidget(listFormat.at(0));
            delete listFormat.at(0);
        }
    }
    updateFormat();
}

QString FormatBuilderDialog::format() const
{
    return ui->txtFormat->text();
}

void FormatBuilderDialog::on_chkTime_toggled(bool checked)
{
    // FIXME: This needs to be fixed
    QList<QListWidgetItem*> listFormat = ui->lstOrder->findItems(qstr(constants->TIME_ONLY_FORMAT_SPECIFIER), Qt::MatchCaseSensitive);
    QListWidgetItem* item = NULL;
    if (!listFormat.isEmpty()) {
        item = listFormat.at(0);
        if (checked) {
            item->setText(qstr(constants->DATE_TIME_FORMAT_SPECIFIER));

        } else {
            if (ui->chkDate->isChecked()) {
                item->setText(qstr(constants->DATE_ONLY_FORMAT_SPECIFIER));
            }
        }
    } else {
        ui->lstOrder->insertItem(ui->lstOrder->count(), qstr(constants->TIME_ONLY_FORMAT_SPECIFIER));
    }
    updateFormat();
}

void FormatBuilderDialog::on_chkDate_toggled(bool checked)
{
    // FIXME: This needs to be fixed
    QList<QListWidgetItem*> listFormat = ui->lstOrder->findItems(qstr(constants->DATE_ONLY_FORMAT_SPECIFIER), Qt::MatchCaseSensitive);
    QListWidgetItem* item = NULL;
    if (!listFormat.isEmpty()) {
        item = listFormat.at(0);
        if (checked) {
            item->setText(qstr(constants->DATE_TIME_FORMAT_SPECIFIER));

        } else {
            if (ui->chkDate->isChecked()) {
                item->setText(qstr(constants->TIME_ONLY_FORMAT_SPECIFIER));
            }
        }
    } else {
        ui->lstOrder->insertItem(ui->lstOrder->count(), qstr(constants->DATE_ONLY_FORMAT_SPECIFIER));
    }
    updateFormat();
}

void FormatBuilderDialog::on_chkLevel_toggled(bool checked)
{
    addFormat(checked, qstr(constants->LEVEL_FORMAT_SPECIFIER));
}

void FormatBuilderDialog::on_chkLoggerId_toggled(bool checked)
{
    addFormat(checked, qstr(constants->LOGGER_ID_FORMAT_SPECIFIER));
}

void FormatBuilderDialog::on_chkThreadId_toggled(bool checked)
{
    addFormat(checked, qstr(constants->THREAD_ID_FORMAT_SPECIFIER));
}

void FormatBuilderDialog::on_chkApplicationName_toggled(bool checked)
{
    addFormat(checked, qstr(constants->APP_NAME_FORMAT_SPECIFIER));
}

void FormatBuilderDialog::on_chkLocation_toggled(bool checked)
{
    addFormat(checked, qstr(constants->LOCATION_FORMAT_SPECIFIER));
}

void FormatBuilderDialog::on_chkFunction_toggled(bool checked)
{
    addFormat(checked, qstr(constants->FUNCTION_FORMAT_SPECIFIER));
}

void FormatBuilderDialog::on_chkUsername_toggled(bool checked)
{
    addFormat(checked, qstr(constants->USER_FORMAT_SPECIFIER));
}

void FormatBuilderDialog::on_chkHostname_toggled(bool checked)
{
    addFormat(checked, qstr(constants->HOST_FORMAT_SPECIFIER));
}

void FormatBuilderDialog::on_chkLogMessage_toggled(bool checked)
{
    addFormat(checked, qstr(constants->LOG_MESSAGE_FORMAT_SPECIFIER));
}

void FormatBuilderDialog::on_buttonOrderUp_clicked()
{
    if (ui->lstOrder->selectedItems().isEmpty()) {
        return;
    }
    int row = ui->lstOrder->currentRow();
    if (row == 0) {
        return;
    }
    QListWidgetItem* curr = ui->lstOrder->takeItem(row);
    ui->lstOrder->insertItem(row - 1, curr);
    ui->lstOrder->setCurrentRow(row - 1);
    updateFormat();
}

void FormatBuilderDialog::on_buttonOrderDown_clicked()
{
    if (ui->lstOrder->selectedItems().isEmpty()) {
        return;
    }
    int row = ui->lstOrder->currentRow();
    if (row == ui->lstOrder->count()) {
        return;
    }
    QListWidgetItem* curr = ui->lstOrder->takeItem(row);
    ui->lstOrder->insertItem(row + 1, curr);
    ui->lstOrder->setCurrentRow(row + 1);
    updateFormat();
}
