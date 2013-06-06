#ifndef FORMATBUILDERDIALOG_HH
#define FORMATBUILDERDIALOG_HH

#include <QDialog>
namespace Ui {
class FormatBuilderDialog;
}
namespace easyloggingpp {
    namespace internal {
        class Constants;
    }
}

class FormatBuilderDialog : public QDialog
{
    Q_OBJECT
    
public:
    FormatBuilderDialog(QWidget *parent, unsigned int level, const QString& currentFormat);
    virtual ~FormatBuilderDialog();
    QString format(void) const;
    
private slots:
    void on_chkTime_toggled(bool checked);

    void on_chkDate_toggled(bool checked);

    void on_chkLevel_toggled(bool checked);

    void on_chkLoggerId_toggled(bool checked);

    void on_chkThreadId_toggled(bool checked);

    void on_chkApplicationName_toggled(bool checked);

    void on_chkLocation_toggled(bool checked);

    void on_chkFunction_toggled(bool checked);

    void on_chkUsername_toggled(bool checked);

    void on_chkHostname_toggled(bool checked);

    void on_chkLogMessage_toggled(bool checked);

    void on_buttonOrderUp_clicked();

    void on_buttonOrderDown_clicked();

    void on_grpDateTime_toggled(bool checked);

    void on_buttonTab_clicked();

    void on_buttonDelTab_clicked();

    void on_lstOrder_currentRowChanged(int currentRow);

    void on_chkVerboseLevel_toggled(bool checked);

private:
    Ui::FormatBuilderDialog *ui;
    const easyloggingpp::internal::Constants* const constants;

    void updateUi(void) const;
    void updateFormat(void) const;
    QString qstr(const std::string& str) const;
    void addFormat(bool checked, const QString& formatSpecifier);
};

#endif // FORMATBUILDERDIALOG_HH
