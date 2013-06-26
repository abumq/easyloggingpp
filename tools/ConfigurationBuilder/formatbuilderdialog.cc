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
    ui->txtFormat->setReadOnly(true);
    updateUi();
    ui->buttonDelTab->setVisible(false);
}

FormatBuilderDialog::~FormatBuilderDialog()
{
    ui->lstOrder->clear();
    delete ui;
}

void FormatBuilderDialog::updateUi() const
{
    QStringList list = ui->txtFormat->text().trimmed().split(" ");
    LOG_VERBOSE(2) << "Updating UI in FormatBuilder, current elements are " << static_cast<QList<QString> >(list);
    Q_FOREACH(QString curr, list) {
        if (curr == qstr(constants->LEVEL_FORMAT_SPECIFIER)) {
            ui->chkLevel->setChecked(true);
        } else if (curr == qstr(constants->DATE_ONLY_FORMAT_SPECIFIER)) {
            ui->grpDateTime->setChecked(true);
            ui->chkDate->setChecked(true);
        } else if (curr == qstr(constants->TIME_ONLY_FORMAT_SPECIFIER)) {
            ui->grpDateTime->setChecked(true);
            ui->chkTime->setChecked(true);
        } else if (curr == qstr(constants->DATE_TIME_FORMAT_SPECIFIER)) {
            ui->grpDateTime->setChecked(true);
            ui->chkDate->setChecked(true);
            ui->chkTime->setChecked(true);
        } else if (curr == qstr(constants->THREAD_ID_FORMAT_SPECIFIER)) {
            ui->chkThreadId->setChecked(true);
        } else if (curr == qstr(constants->LOGGER_ID_FORMAT_SPECIFIER)) {
            ui->chkLoggerId->setChecked(true);
        } else if (curr == qstr(constants->FUNCTION_FORMAT_SPECIFIER)) {
            ui->chkFunction->setChecked(true);
        } else if (curr == qstr(constants->APP_NAME_FORMAT_SPECIFIER)) {
            ui->chkApplicationName->setChecked(true);
        } else if (curr == qstr(constants->HOST_FORMAT_SPECIFIER)) {
            ui->chkHostname->setChecked(true);
        } else if (curr == qstr(constants->USER_FORMAT_SPECIFIER)) {
            ui->chkUsername->setChecked(true);
        } else if (curr == qstr(constants->LOCATION_FORMAT_SPECIFIER)) {
            ui->chkLocation->setChecked(true);
        } else if (curr == qstr(constants->VERBOSE_LEVEL_FORMAT_SPECIFIER)) {
            ui->chkVerboseLevel->setChecked(true);
        } else if (curr == qstr(constants->LOG_MESSAGE_FORMAT_SPECIFIER)) {
            ui->chkLogMessage->setChecked(true);
        } else if (curr == "\\t") {
            ui->lstOrder->insertItem(ui->lstOrder->count(), "\\t");
        }
    }
}

void FormatBuilderDialog::updateFormat() const
{
    QString format;
    for (int i = 0; i < ui->lstOrder->count(); ++i) {
        format.append(ui->lstOrder->item(i)->text() + ((i < ui->lstOrder->count() - 1) ? QString(" ") : QString()));
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
    if (!checked && !ui->chkDate->isChecked()) {
        ui->grpDateTime->setChecked(false);
    }
    QList<QListWidgetItem*> dateOnly = ui->lstOrder->findItems(qstr(constants->DATE_ONLY_FORMAT_SPECIFIER), Qt::MatchCaseSensitive);
    QList<QListWidgetItem*> dateTime = ui->lstOrder->findItems(qstr(constants->DATE_TIME_FORMAT_SPECIFIER), Qt::MatchCaseSensitive);
    QListWidgetItem* item = NULL;
    if (!dateOnly.isEmpty() || !dateTime.isEmpty()) {
        item = dateOnly.isEmpty() ? dateTime.at(0) : dateOnly.at(0);
        if (checked) {
            item->setText(qstr(constants->DATE_TIME_FORMAT_SPECIFIER));
        } else {
            if (ui->chkDate->isChecked()) {
                item->setText(qstr(constants->DATE_ONLY_FORMAT_SPECIFIER));
            }
        }
    } else {
        if (checked) {
            ui->lstOrder->insertItem(ui->lstOrder->count(), qstr(constants->TIME_ONLY_FORMAT_SPECIFIER));
        }
    }
    updateFormat();
}

void FormatBuilderDialog::on_chkDate_toggled(bool checked)
{
    if (!checked && !ui->chkTime->isChecked()) {
        ui->grpDateTime->setChecked(false);
    }
    QList<QListWidgetItem*> timeOnly = ui->lstOrder->findItems(qstr(constants->TIME_ONLY_FORMAT_SPECIFIER), Qt::MatchCaseSensitive);
    QList<QListWidgetItem*> dateTime = ui->lstOrder->findItems(qstr(constants->DATE_TIME_FORMAT_SPECIFIER), Qt::MatchCaseSensitive);
    QListWidgetItem* item = NULL;
    if (!timeOnly.isEmpty() || !dateTime.isEmpty()) {
        item = timeOnly.isEmpty() ? dateTime.at(0) : timeOnly.at(0);
        if (checked) {
            item->setText(qstr(constants->DATE_TIME_FORMAT_SPECIFIER));
        } else {
            if (ui->chkTime->isChecked()) {
                item->setText(qstr(constants->TIME_ONLY_FORMAT_SPECIFIER));
            }
        }
    } else {
        if (checked) {
            ui->lstOrder->insertItem(ui->lstOrder->count(), qstr(constants->DATE_ONLY_FORMAT_SPECIFIER));
        }
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

void FormatBuilderDialog::on_chkVerboseLevel_toggled(bool checked)
{
    addFormat(checked, qstr(constants->VERBOSE_LEVEL_FORMAT_SPECIFIER));
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
    LOG_VERBOSE(1) << "Moving [" << curr->text() << "] up";
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
    LOG_VERBOSE(1) << "Moving [" << curr->text() << "] down";
    ui->lstOrder->insertItem(row + 1, curr);
    ui->lstOrder->setCurrentRow(row + 1);
    updateFormat();
}

void FormatBuilderDialog::on_grpDateTime_toggled(bool checked)
{
    if (!checked) {
        QList<QListWidgetItem*> dateOnly = ui->lstOrder->findItems(qstr(constants->DATE_ONLY_FORMAT_SPECIFIER), Qt::MatchCaseSensitive);
        QList<QListWidgetItem*> timeOnly = ui->lstOrder->findItems(qstr(constants->TIME_ONLY_FORMAT_SPECIFIER), Qt::MatchCaseSensitive);
        QList<QListWidgetItem*> dateTime = ui->lstOrder->findItems(qstr(constants->DATE_TIME_FORMAT_SPECIFIER), Qt::MatchCaseSensitive);
        if (dateOnly.isEmpty() && timeOnly.isEmpty() && dateTime.isEmpty()) {
            return;
        }
        if (!dateOnly.isEmpty()) {
            ui->lstOrder->removeItemWidget(dateOnly.at(0));
            delete dateOnly.at(0);
        }
        if (!timeOnly.isEmpty()) {
            ui->lstOrder->removeItemWidget(timeOnly.at(0));
            delete timeOnly.at(0);
        }
        if (!dateTime.isEmpty()) {
            ui->lstOrder->removeItemWidget(dateTime.at(0));
            delete dateTime.at(0);
        }
    }
    ui->chkDate->setChecked(checked);
    ui->chkTime->setChecked(checked);
}

void FormatBuilderDialog::on_buttonTab_clicked()
{
    ui->lstOrder->insertItem(ui->lstOrder->count(), "\\t");
    updateFormat();
}

void FormatBuilderDialog::on_buttonDelTab_clicked()
{
    int row = ui->lstOrder->currentRow();
    ui->lstOrder->removeItemWidget(ui->lstOrder->selectedItems().at(0));
    delete ui->lstOrder->selectedItems().at(0);
    --row;
    ui->lstOrder->setCurrentRow(row == -1 ? 0 : row);
    updateFormat();
}

void FormatBuilderDialog::on_lstOrder_currentRowChanged(int currentRow)
{
    QListWidgetItem *item = ui->lstOrder->item(currentRow);
    if (item == NULL) {
        return;
    }
    if (item->text() == "\\t") {
        ui->buttonDelTab->setVisible(true);
    } else {
        ui->buttonDelTab->setVisible(false);
    }
}
