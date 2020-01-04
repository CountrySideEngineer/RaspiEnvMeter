#ifndef CRASPIENVMETERVIEW_H
#define CRASPIENVMETERVIEW_H

#include <QObject>
#include <QAbstractItemView>
#include <QLabel>

class CRaspiEnvMeterView : public QAbstractItemView
{
public:
    explicit CRaspiEnvMeterView(QWidget* parent = nullptr);

    QRect visualRect(const QModelIndex &index) const override;
    void scrollTo(const QModelIndex &index, ScrollHint hint) override;
    QModelIndex indexAt(const QPoint &point) const override;

protected slots:
    void dataChanged(const QModelIndex &topLeft,
                     const QModelIndex &bottomRight,
                     const QVector<int> &roles = QVector<int>()) override;

protected:
    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
    int horizontalOffset() const override;
    int verticalOffset() const override;
    bool isIndexHidden(const QModelIndex &index) const override;
    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) override;
    QRegion visualRegionForSelection(const QItemSelection &selection) const override;

protected:
    int model_row_index_;

    QLabel* item_view_;
};

#endif // CRASPIENVMETERVIEW_H
