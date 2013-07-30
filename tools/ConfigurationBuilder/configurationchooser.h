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
    static std::string ulongToStr(unsigned long l) { return QString::number(l).toStdString(); }
    static std::string intToStr(int i) { return QString::number(i).toStdString(); }
};

class ConfigurationChooser : public QWidget
{
    Q_OBJECT
    
public:
    explicit ConfigurationChooser(QWidget *parent = 0);
    virtual ~ConfigurationChooser();
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

    void on_cboRollOutSizeUnit_currentIndexChanged(int);

    void on_chkSetExplicitly_toggled(bool checked);

    void on_spnRollOutSize_valueChanged(const QString &arg1);

    void on_buttonBuildFormat_clicked();

    void on_chkPerformanceTracking_toggled(bool checked);

public slots:

    void loadFromFile(const QString& filename_);
private:
    QMap<QString, easyloggingpp::internal::TypedConfigurations*> levelledTypedConfigurations;
    Ui::ConfigurationChooser *ui;
    easyloggingpp::internal::TypedConfigurations *getConfiguration(const QString& levelStr) const;
    void updateUI();
    void clearLevelledTypedConfigurations(void);
signals:
    void configurationUpdated(const QString& levelStr);
};

#endif // CONFIGURATIONCHOOSER_H
