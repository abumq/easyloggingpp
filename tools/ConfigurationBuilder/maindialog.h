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
    void initializeTree(void);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainDialog *ui;
    FileSelector* fileSelector;
    ConfigurationChooser* configurationChooser;
    QList<QTreeWidgetItem*> treeWidgetItems;
};

#endif // MAINDIALOG_H
