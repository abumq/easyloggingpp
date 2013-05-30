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
    easyloggingpp::Configurations configurations;
    QMap<QString, easyloggingpp::internal::TypedConfigurations> levelledConfigurations;
    QMap<QString, easyloggingpp::Logger*> levelledLoggers;
    Ui::ConfigurationChooser *ui;
    easyloggingpp::internal::TypedConfigurations *getConfiguration(const QString& levelStr);
    const easyloggingpp::Logger* getLogger(const QString& levelStr) const;
    void updateUI();

signals:
    void configurationUpdated(const QString& levelStr);
};

#endif // CONFIGURATIONCHOOSER_H
