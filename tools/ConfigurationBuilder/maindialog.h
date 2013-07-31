#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QList>
namespace Ui {
class MainDialog;
}
class FileSelector;
class ConfigurationChooser;
class QTreeWidgetItem;

class MainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();
private slots:
    void on_pushButton_clicked();

    void on_buttonSave_clicked();

private:
    Ui::MainDialog *ui;
    FileSelector* fileSelector;
    ConfigurationChooser* configurationChooser;
};

#endif // MAINDIALOG_H
