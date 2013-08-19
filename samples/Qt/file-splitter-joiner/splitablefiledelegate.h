#ifndef SPLITABLEFILEDELEGATE_H
#define SPLITABLEFILEDELEGATE_H

#include <QItemDelegate>
class SplitterWidget;

class SplitableFileDelegate : public QItemDelegate {
    Q_OBJECT
public:
    SplitableFileDelegate(SplitterWidget *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    SplitterWidget* parent;
};
#endif // SPLITABLEFILEDELEGATE_H
