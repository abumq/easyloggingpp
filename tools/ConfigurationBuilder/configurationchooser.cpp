#include "configurationchooser.h"
#include "ui_configurationchooser.h"
#include "easylogging++.h"
#include <QFile>
ConfigurationChooser::ConfigurationChooser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigurationChooser)
{
    ui->setupUi(this);
    ui->cboLevel->addItems(QStringList() << "ALL" << "DEBUG" << "INFO" << "WARNING" << "ERROR" << "FATAL" << "VERBOSE" << "QA" << "TRACE");
    ui->cboRollOutSizeUnit->addItems(QStringList() << "B" << "KB" << "MB" << "GB");
    QObject::connect(this, SIGNAL(configurationUpdated(QString)), this, SLOT(addCurrentLevelledConfiguration(QString)));
    addCurrentLevelledConfiguration("ALL");

}

ConfigurationChooser::~ConfigurationChooser()
{
    clearLevelledTypedConfigurations();
    delete ui;
}

easyloggingpp::internal::TypedConfigurations* ConfigurationChooser::getConfiguration(const QString &levelStr) const
{
    QMap<QString, easyloggingpp::internal::TypedConfigurations*>::const_iterator it = levelledTypedConfigurations.find(levelStr);
    if (it == levelledTypedConfigurations.end()) {
        return NULL;
    }
    return *it;
}

void ConfigurationChooser::updateUI()
{
    QString levelStr = ui->cboLevel->currentText();
    unsigned int level = easyloggingpp::Level::convertFromString(levelStr.toLower().toStdString());
    easyloggingpp::internal::TypedConfigurations* currConfig = getConfiguration(levelStr);
    if (currConfig != NULL) {
        ui->chkEnabled->setChecked(easyloggingpp::Loggers::ConfigurationsReader::enabled(currConfig, level));
        ui->chkToStandardOutput->setChecked(easyloggingpp::Loggers::ConfigurationsReader::toStandardOutput(currConfig, level));
        ui->chkToFile->setChecked(easyloggingpp::Loggers::ConfigurationsReader::toFile(currConfig, level));
        ui->txtFilename->setText(QString(easyloggingpp::Loggers::ConfigurationsReader::filename(currConfig, level).c_str()));
        // TODO: Replace level name value with format specifier
        ui->txtFormat->setText(QString(easyloggingpp::Loggers::ConfigurationsReader::logFormat(currConfig, level).c_str()));
        ui->spnRollOutSize->setValue(static_cast<double>(easyloggingpp::Loggers::ConfigurationsReader::logRollOutSize(currConfig, level)));
        int msw = easyloggingpp::Loggers::ConfigurationsReader::millisecondsWidth(currConfig, level);
        switch (msw) {
        case 1:
            msw = 6;
            break;
        case 10:
            msw = 5;
            break;
        case 100:
            msw = 4;
            break;
        case 1000:
            msw = 3;
            break;
        default:
            msw = 3;
        }
        ui->spnMillisecondsWidth->setValue(msw);
        ui->chkPerformanceTracking->setChecked(easyloggingpp::Loggers::ConfigurationsReader::performanceTracking(currConfig, level));
    }
}

void ConfigurationChooser::loadFromFile(const QString &filename_)
{
    clearLevelledTypedConfigurations();
    easyloggingpp::Configurations c(filename_.toStdString());

    easyloggingpp::internal::TypedConfigurations tc(c, easyloggingpp::internal::registeredLoggers->constants());
    easyloggingpp::Configurations cLevel;
    unsigned int l = 0;
    do {
        cLevel.set(l, easyloggingpp::ConfigurationType::Enabled, QuickCast::boolToStr(easyloggingpp::Loggers::ConfigurationsReader::enabled(&tc, l)));
        cLevel.set(l, easyloggingpp::ConfigurationType::ToStandardOutput, QuickCast::boolToStr(easyloggingpp::Loggers::ConfigurationsReader::toStandardOutput(&tc, l)));
        cLevel.set(l, easyloggingpp::ConfigurationType::ToFile, QuickCast::boolToStr(easyloggingpp::Loggers::ConfigurationsReader::toFile(&tc, l)));
        cLevel.set(l, easyloggingpp::ConfigurationType::Filename, easyloggingpp::Loggers::ConfigurationsReader::filename(&tc, l));
        cLevel.set(l, easyloggingpp::ConfigurationType::Format, easyloggingpp::Loggers::ConfigurationsReader::logFormat(&tc, l));
        cLevel.set(l, easyloggingpp::ConfigurationType::RollOutSize, QuickCast::ulongToStr(easyloggingpp::Loggers::ConfigurationsReader::logRollOutSize(&tc, l)));
        cLevel.set(l, easyloggingpp::ConfigurationType::MillisecondsWidth, QuickCast::intToStr(easyloggingpp::Loggers::ConfigurationsReader::millisecondsWidth(&tc, l)));
        cLevel.set(l, easyloggingpp::ConfigurationType::PerformanceTracking, QuickCast::boolToStr(easyloggingpp::Loggers::ConfigurationsReader::performanceTracking(&tc, l)));
        easyloggingpp::internal::TypedConfigurations *tcLevel = new easyloggingpp::internal::TypedConfigurations(c, easyloggingpp::internal::registeredLoggers->constants());
        levelledTypedConfigurations.insert(QString(easyloggingpp::Level::convertToString(l).c_str()).toUpper(), tcLevel);
        l = l << 1;
        if (l == 0) {
            ++l;
        }
        cLevel.clear();
    } while (l <= easyloggingpp::Level::kMaxValid);
    updateUI();
}

void ConfigurationChooser::clearLevelledTypedConfigurations()
{
    Q_FOREACH(QString key, levelledTypedConfigurations.keys()) {
        delete *levelledTypedConfigurations.find(key);
    }
    levelledTypedConfigurations.clear();
}

QString ConfigurationChooser::convertConfigurationToString() const
{
    QString result = "";
    std::stringstream resultList;

    for (int i = 0; i < ui->cboLevel->count(); ++i) {
        QString levelStr = ui->cboLevel->itemText(i);
        unsigned int level = easyloggingpp::Level::convertFromString(levelStr.toLower().toStdString());
        easyloggingpp::internal::TypedConfigurations* existingTypedConfigurations = getConfiguration(levelStr);
        if (existingTypedConfigurations == NULL) {
            continue;
        }
        easyloggingpp::Configurations* c = const_cast<easyloggingpp::Configurations*>(&existingTypedConfigurations->configurations());
        easyloggingpp::Configurations* allC = const_cast<easyloggingpp::Configurations*>(&getConfiguration("ALL")->configurations());
        easyloggingpp::internal::Configuration* currConf = NULL;

        int currIterCount = 0;
        for (unsigned int ci = 0; ci < c->count(); ++ci) {
            currConf = c->at(ci);
            if (currConf->level() != level) {
                continue;
            }
            if (currConf->type() == easyloggingpp::ConfigurationType::RollOutSize &&
                    easyloggingpp::Loggers::ConfigurationsReader::logRollOutSize(existingTypedConfigurations, level) == 0) {
                continue;
            }
            easyloggingpp::internal::Configuration* confInAll = allC->get(easyloggingpp::Level::All, currConf->type());
            if (currConf->level() != easyloggingpp::Level::All && confInAll != NULL && currConf->value() == confInAll->value()) {
                continue;
            }
            if (currIterCount == 0) {
                resultList << "*" << levelStr.toStdString() << ":\n";
            }
            resultList << "    " << easyloggingpp::ConfigurationType::convertToString(currConf->type()).c_str() << "    :    " << currConf->value().c_str() << "\n";
            ++currIterCount;
        }
    }
    return QString(resultList.str().c_str());
}

void ConfigurationChooser::addCurrentLevelledConfiguration(const QString& levelString)
{
    QString levelStr = levelString;
    if (levelStr == "") levelStr = ui->cboLevel->currentText();
    LINFO << "Adding levelled configuration for [" << levelStr << "]";

    unsigned int level = easyloggingpp::Level::convertFromString(levelStr.toLower().toStdString());
    easyloggingpp::Configurations c;
    c.set(level, easyloggingpp::ConfigurationType::Enabled, QuickCast::boolToStr(ui->chkEnabled->checkState() == Qt::Checked), true);
    c.set(level, easyloggingpp::ConfigurationType::ToStandardOutput, QuickCast::boolToStr(ui->chkToStandardOutput->checkState() == Qt::Checked), true);
    c.set(level, easyloggingpp::ConfigurationType::ToFile, QuickCast::boolToStr(ui->chkToFile->checkState() == Qt::Checked), true);
    c.set(level, easyloggingpp::ConfigurationType::Filename, ui->txtFilename->text().toStdString(), true);
    c.set(level, easyloggingpp::ConfigurationType::Format, ui->txtFormat->text().toStdString(), true);
    c.set(level, easyloggingpp::ConfigurationType::PerformanceTracking, QuickCast::boolToStr(ui->chkPerformanceTracking->checkState() == Qt::Checked), true);
    c.set(level, easyloggingpp::ConfigurationType::RollOutSize, QString::number(ui->spnRollOutSize->value()).toStdString());
    c.set(level, easyloggingpp::ConfigurationType::MillisecondsWidth, QuickCast::intToStr(ui->spnMillisecondsWidth->value()));

    easyloggingpp::internal::TypedConfigurations *tc = new easyloggingpp::internal::TypedConfigurations(c, easyloggingpp::internal::registeredLoggers->constants());
    if (getConfiguration(levelStr) == NULL) {
        levelledTypedConfigurations.insert(levelStr, tc);
    } else {
        levelledTypedConfigurations.remove(levelStr);
        levelledTypedConfigurations.insert(levelStr, tc);
    }
    updateUI();
}

void ConfigurationChooser::on_cboLevel_currentIndexChanged(const QString&)
{
    if (ui->cboLevel->currentIndex() == 0) {
        ui->chkSetExplicitly->setEnabled(false);
        ui->chkSetExplicitly->setChecked(true);
    } else {
        ui->chkSetExplicitly->setEnabled(true);
        ui->chkSetExplicitly->setChecked(getConfiguration(ui->cboLevel->currentText()) != NULL);
    }
    updateUI();
}

void ConfigurationChooser::on_chkEnabled_toggled(bool)
{
    emit configurationUpdated(ui->cboLevel->currentText());
}

void ConfigurationChooser::on_chkToFile_toggled(bool)
{
    emit configurationUpdated(ui->cboLevel->currentText());
}

void ConfigurationChooser::on_chkToStandardOutput_toggled(bool)
{
    emit configurationUpdated(ui->cboLevel->currentText());
}

void ConfigurationChooser::on_txtFormat_editingFinished()
{
    emit configurationUpdated(ui->cboLevel->currentText());
}

void ConfigurationChooser::on_txtFilename_editingFinished()
{
    emit configurationUpdated(ui->cboLevel->currentText());
}

void ConfigurationChooser::on_spnMillisecondsWidth_valueChanged(int)
{
    emit configurationUpdated(ui->cboLevel->currentText());
}
void ConfigurationChooser::on_cboRollOutSizeUnit_currentIndexChanged(int)
{
    emit configurationUpdated(ui->cboLevel->currentText());
}

void ConfigurationChooser::on_spnRollOutSize_valueChanged(const QString&)
{
    emit configurationUpdated(ui->cboLevel->currentText());
}

void ConfigurationChooser::on_chkSetExplicitly_toggled(bool checked)
{
    ui->chkEnabled->setEnabled(checked);
    ui->chkToFile->setEnabled(checked);
    ui->chkToStandardOutput->setEnabled(checked);
    ui->chkPerformanceTracking->setEnabled(checked);
    ui->txtFilename->setEnabled(checked);
    ui->txtFormat->setEnabled(checked);
    ui->spnMillisecondsWidth->setEnabled(checked);
    ui->spnRollOutSize->setEnabled(checked);
    ui->cboRollOutSizeUnit->setEnabled(checked);
    if (!checked) {
        // Remove all the configurations since user does not want to configure for this level
        QString levelStr = ui->cboLevel->currentText();
        easyloggingpp::internal::TypedConfigurations* existingTypedConfigurations = getConfiguration(levelStr);
        if (existingTypedConfigurations != NULL) {
            delete existingTypedConfigurations;
            existingTypedConfigurations = NULL;
            levelledTypedConfigurations.remove(levelStr);
        }
    } else {
        emit configurationUpdated(ui->cboLevel->currentText());
    }
}
