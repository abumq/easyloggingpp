#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QWidget>

namespace Ui {
class FileSelector;
}

class FileSelector : public QWidget
{
    Q_OBJECT
    
public:
    explicit FileSelector(QWidget *parent = 0);
    ~FileSelector();
    QString filename(void) const;
    void resize(int w);
    void openForSaving(void);
protected:
    static const unsigned int kDefaultHeight = 41;
private slots:
    void on_pushButton_2_clicked();

signals:
    void fileOpened(const QString&);

private:
    Ui::FileSelector *ui;
};

#endif // FILESELECTOR_H
