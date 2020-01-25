#ifndef CRASPIENVMETERVIEW_H
#define CRASPIENVMETERVIEW_H

#include <QObject>
#include <QAbstractItemView>
#include <QLabel>

class CRaspiEnvMeterView : public QAbstractItemView
{
    Q_OBJECT

public:
    explicit CRaspiEnvMeterView(QWidget* parent = nullptr);
    virtual ~CRaspiEnvMeterView() override;

    QRect visualRect(const QModelIndex &index) const override;
    void scrollTo(const QModelIndex &index, ScrollHint hint) override;
    QModelIndex indexAt(const QPoint &point) const override;

    void SetModelRowIndex(int value) { this->model_row_index_ = value; }
    int GetModelrowIndex() { return this->model_row_index_; }
    void SetModelColIndex(int value) { this->model_col_index_ = value; }
    int GetModelColIndex() { return this->model_col_index_; }

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
    int model_col_index_;

    QLabel* item_view_;
};

#endif // CRASPIENVMETERVIEW_H
