#ifndef CONFIGURATIONCHOOSER_H
#define CONFIGURATIONCHOOSER_H

#include <QWidget>
#include <QMap>
#include "easylogging++.h"

namespace Ui {
class ConfigurationChooser;
}

class QuickCast : private easyloggingpp::internal::StaticClass {
public:
    static std::string boolToStr(bool b) { return b ? "true" : "false"; }
    static QString configFromIntType(unsigned int config) {
        switch (config) {
        case easyloggingpp::ConfigurationType::ELPP_Enabled:
            return "ENABLED";
            break;
        case easyloggingpp::ConfigurationType::ELPP_Filename:
            return "FILENAME";
            break;
        case easyloggingpp::ConfigurationType::ELPP_Format:
            return "FORMAT";
            break;
        case easyloggingpp::ConfigurationType::ELPP_ToFile:
            return "TO_FILE";
            break;
        case easyloggingpp::ConfigurationType::ELPP_ToStandardOutput:
            return "TO_STANDARD_OUTPUT";
            break;
        case easyloggingpp::ConfigurationType::ELPP_MillisecondsWidth:
            return "MILLISECONDS_WIDTH";
            break;
        case easyloggingpp::ConfigurationType::ELPP_PerformanceTracking:
            return "PERFORMANCE_TRACKING";
            break;
        case easyloggingpp::ConfigurationType::ELPP_RollOutSize:
            return "ROLL_OUT_SIZE";
            break;
        }
    }
};

class ConfigurationChooser : public QWidget
{
    Q_OBJECT
    
public:
    explicit ConfigurationChooser(QWidget *parent = 0);
    ~ConfigurationChooser();
    QString convertConfigurationToString() const;
    
private slots:
    void addCurrentLevelledConfiguration(const QString& levelString = "ALL");

    void on_cboLevel_currentIndexChanged(const QString&);

    void on_chkEnabled_toggled(bool);

    void on_chkToFile_toggled(bool);

    void on_chkToStandardOutput_toggled(bool);

    void on_txtFormat_editingFinished();

    void on_txtFilename_editingFinished();

    void on_spnMillisecondsWidth_valueChanged(int);

    void on_spnRollOutSizeValue_valueChanged(int);

    void on_cboRollOutSizeUnit_currentIndexChanged(int);

    void on_chkSetExplicitly_toggled(bool checked);

private:
    QMap<QString, easyloggingpp::Configurations> levelledConfigurations;
    QMap<QString, easyloggingpp::internal::TypedConfigurations> levelledTypedConfigurations;
    QMap<QString, easyloggingpp::Logger*> levelledLoggers;
    Ui::ConfigurationChooser *ui;
    easyloggingpp::internal::TypedConfigurations *getConfiguration(const QString& levelStr);
    const easyloggingpp::Logger* getLogger(const QString& levelStr) const;
    void updateUI();

signals:
    void configurationUpdated(const QString& levelStr);
};

#endif // CONFIGURATIONCHOOSER_H
