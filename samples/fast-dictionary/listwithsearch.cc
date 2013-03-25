#include "listwithsearch.hh"
#include "easylogging++.h"
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrentRun>
#include <QDebug>

int ListWithSearch::kSearchBarHeight = 22;

ListWithSearch::ListWithSearch(int searchBehaviour_, QWidget *parent) :
    QWidget(parent),
    parent_(parent),
    searchBehaviour_(searchBehaviour_)
{
    setup(parent);
    future_ = new QFuture<void>;
}


void ListWithSearch::setup(QWidget *parent)
{
    setObjectName(QString::fromUtf8("ListWithSearch"));
    resize(400, 300);
    list = new QListWidget(parent);
    list->setObjectName(QString::fromUtf8("list"));
    list->setGeometry(QRect(20, 60, 256, 192));
    txtSearchCriteria = new QLineEdit(parent);
    txtSearchCriteria->setObjectName(QString::fromUtf8("txtSearchCriteria"));
    txtSearchCriteria->setGeometry(QRect(20, 20, 251, 25));
    connect(txtSearchCriteria, SIGNAL(textChanged(QString)), this, SLOT(on_txtSearchCriteria_textChanged(QString)));
    connect(txtSearchCriteria, SIGNAL(returnPressed()), this, SLOT(selected()));
}

void ListWithSearch::resizeEvent(QResizeEvent*)
{
    txtSearchCriteria->setGeometry (0, 0, width(), kSearchBarHeight);
    list->setGeometry(0, txtSearchCriteria->height(), width(), height() - txtSearchCriteria->height());
}

void ListWithSearch::setFocus()
{
    txtSearchCriteria->setFocus();
}

ListWithSearch::~ListWithSearch()
{
    LTRACE << "Cleaning memory";
    for (int i = items.count() - 1; i >= 0; --i) {
        delete items.at(i);
    }
    list->clear();
    delete future_;
    delete list;
    delete txtSearchCriteria;
    LTRACE << "Memory cleaned from list";
}

void ListWithSearch::add(const QString &item)
{
    QListWidgetItem* widgetItem = new QListWidgetItem(item, list);
    items.push_back(widgetItem);
    list->insertItem(0, widgetItem);
}

void ListWithSearch::on_txtSearchCriteria_textChanged(const QString&)
{
    if (future_->isRunning()) {
        future_->cancel();
    } else {
        *future_ = QtConcurrent::run(this, &ListWithSearch::performSearch);
    }
}

void ListWithSearch::selected(void)
{
    if (list->count() != 0) {
        emit selectionMade(list->item(0)->text());
    }
}

void ListWithSearch::performSearch(void)
{
    LTRACE << "Performing search...[" << txtSearchCriteria->text()<< "]";
    PDEBUG << "Cleaning list...";
    while (list->count()) {
        list->takeItem(0);
    }
    PDEBUG << "List cleaned!";
    if (txtSearchCriteria->text() == "") {
        for (int i = items.count() - 1; i >= 0; --i) {
            QListWidgetItem* widgetItem = items.at(i);
            list->insertItem(0, widgetItem);
        }
    } else {
        for (int i = 0; i < items.count(); ++i) {
            if (items.at(i)->text().startsWith(txtSearchCriteria->text(), searchBehaviour_ == kCaseSensative ?
                                               Qt::CaseSensitive : Qt::CaseInsensitive)) {
                list->insertItem(i, items.at(i));
            }
        }
    }
}
