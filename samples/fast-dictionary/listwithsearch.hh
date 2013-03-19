#ifndef LISTWITHSEARCH_HH
#define LISTWITHSEARCH_HH

#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtCore/QList>

class QResizeEvent;
class QListWidgetItem;
template <typename T>
class QFuture;

class ListWithSearch : public QWidget
{
    Q_OBJECT
    
public:
    static int kSearchBarHeight;
    enum kBehaviour { kCaseInsensative, kCaseSensative };

    explicit ListWithSearch(int searchBehaviour_ = kCaseSensative, QWidget *parent = 0);
    virtual ~ListWithSearch();
    void add(const QString& item);
    void resizeEvent(QResizeEvent *);
    void setFocus(void);
    
private slots:
    void on_txtSearchCriteria_textChanged(const QString&);
    void selected(void);

signals:
    void selectionMade(const QString& selection);

private:
    QWidget* parent_;
    QListWidget* list;
    QLineEdit* txtSearchCriteria;
    QList<QListWidgetItem*> items;
    QFuture<void>* future_;
    int searchBehaviour_;

    void setup(QWidget *parent = 0);
    void performSearch(void);

};

#endif // LISTWITHSEARCH_HH
