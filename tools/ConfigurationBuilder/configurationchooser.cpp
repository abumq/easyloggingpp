#include "configurationchooser.h"
#include "ui_configurationchooser.h"
#include "easylogging++.h"
ConfigurationChooser::ConfigurationChooser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigurationChooser)
{
    ui->setupUi(this);
    ui->cboLevel->addItems(QStringList() << "ALL" << "DEBUG" << "INFO" << "WARNING" << "ERROR" << "FATAL" << "VERBOSE" << "QA" << "TRACE");
    ui->cboRollOutSizeUnit->addItems(QStringList() << "B" << "KB" << "MB" << "GB");
    QObject::connect(this, SIGNAL(configurationUpdated(QString)), this, SLOT(addCurrentLevelledConfiguration(QString)));
}

ConfigurationChooser::~ConfigurationChooser()
{
    delete ui;
}

easyloggingpp::internal::TypedConfigurations* ConfigurationChooser::getConfiguration(const QString &levelStr)
{
    QMap<QString, easyloggingpp::internal::TypedConfigurations>::iterator it = levelledConfigurations.find(levelStr);
    if (it == levelledConfigurations.end()) {
        return NULL;
    }
    return &*it;
}

const easyloggingpp::Logger *ConfigurationChooser::getLogger(const QString &levelStr) const
{
    QString key = levelStr + QString("-confChooser");
    QMap<QString, easyloggingpp::Logger*>::const_iterator it = levelledLoggers.find(key);
    if (it == levelledLoggers.end()) {
        return NULL;
    }
    return *it;
}

void ConfigurationChooser::updateUI()
{
    QString levelStr = ui->cboLevel->currentText();
    unsigned int level = easyloggingpp::Configurations::Parser::levelFromString(levelStr.toLower().toStdString());
    easyloggingpp::Logger* currLogger = easyloggingpp::Loggers::getLogger(levelStr.append("-confChooser").toStdString());
    ui->chkEnabled->setChecked(easyloggingpp::Loggers::ConfigurationsReader::enabled(currLogger, level));
}

// Proper converted configuration looks like:
QString ConfigurationChooser::convertConfigurationToString() const
{
    QString result = "";
    unsigned int level_ = 0;
    unsigned int configurationType_ = 0;

    for (unsigned int i = 0; i < ui->cboLevel->count(); ++i) {

        unsigned int levelFromCbo = easyloggingpp::Configurations::Parser::levelFromString(ui->cboLevel->itemText(i).toLower().toStdString());
        easyloggingpp::internal::Configuration *c = NULL;
        do {
            c = configurations.get(levelFromCbo, configurationType_);
            configurationType_ = configurationType_ << 1;
            if (configurationType_ == 0) {
                ++configurationType_;
            }
        } while (configurationType_ <= 64);
    }
    return result;
}

void ConfigurationChooser::addCurrentLevelledConfiguration(const QString& levelString)
{
    QString levelStr = levelString;
    if (levelStr == "") levelStr = ui->cboLevel->currentText();
    LINFO << "Adding levelled configuration for [" << levelStr << "]";

    unsigned int level = easyloggingpp::Configurations::Parser::levelFromString(levelStr.toLower().toStdString());
    easyloggingpp::Configurations c;
    c.set(level, easyloggingpp::ConfigurationType::ELPP_Enabled, QuickCast::boolToStr(ui->chkEnabled->checkState() == Qt::Checked));
    c.set(level, easyloggingpp::ConfigurationType::ELPP_ToStandardOutput, QuickCast::boolToStr(ui->chkToStandardOutput->checkState() == Qt::Checked));
    c.set(level, easyloggingpp::ConfigurationType::ELPP_ToFile, QuickCast::boolToStr(ui->chkToFile->checkState() == Qt::Checked));
    easyloggingpp::internal::TypedConfigurations tc = easyloggingpp::internal::TypedConfigurations(c, easyloggingpp::internal::registeredLoggers->constants());
    easyloggingpp::internal::TypedConfigurations* existing = getConfiguration(levelStr);
    if (existing == NULL) {
        levelledConfigurations.insert(levelStr, tc);
    } else {
        levelledConfigurations.remove(levelStr);
        levelledConfigurations.insert(levelStr, tc);
    }
    easyloggingpp::Logger* logger = easyloggingpp::Loggers::getLogger(levelStr.append("-confChooser").toStdString());
    if (!logger->configured()) {
        logger->configure(c);
        levelledLoggers.insert(levelStr, logger);
    } else {
        levelledLoggers.remove(levelStr);
        logger->configure(c);
        levelledLoggers.insert(levelStr, logger);
    }
    updateUI();
}

void ConfigurationChooser::on_cboLevel_currentIndexChanged(const QString&)
{
    if (ui->cboLevel->currentIndex() == 0) {
        ui->chkSetExplicitly->setChecked(true);
        ui->chkSetExplicitly->setEnabled(false);
    } else {
        ui->chkSetExplicitly->setEnabled(true);
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

void ConfigurationChooser::on_spnRollOutSizeValue_valueChanged(int)
{
    emit configurationUpdated(ui->cboLevel->currentText());
}

void ConfigurationChooser::on_cboRollOutSizeUnit_currentIndexChanged(int)
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
    ui->spnRollOutSizeValue->setEnabled(checked);
    ui->cboRollOutSizeUnit->setEnabled(checked);
    emit configurationUpdated(ui->cboLevel->currentText());
}
