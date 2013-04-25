#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

class QLabel;
class QFile;
class QResizeEvent;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void selectLogFile(void);
    void exit(void);
    void about(void);
    void aboutQt(void);

private:
    Ui::MainWindow *ui;
    QLabel* logFileInfo;
    QFile* logFile;

    void connectSlots(void);
    void updateLogFileInfo(void);

    virtual void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_HH
