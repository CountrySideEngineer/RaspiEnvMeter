#include "craspienvmeterview.h"
#include "util/util.h"

/**
 * @brief Constructor of CRaspiEnvMeterView class
 * @param parent    Pointer to parental QWidget object which holds this object.
 */
CRaspiEnvMeterView::CRaspiEnvMeterView(QWidget* parent)
    : QAbstractItemView(parent)
    , model_row_index_(-1)
    , item_view_(nullptr)
{}

/**
 * @brief Destructor.
 */
CRaspiEnvMeterView::~CRaspiEnvMeterView()
{
    Util::SAFE_RELEASE_DATA(&(this->item_view_));
}


/**
 * @brief Returns the rectangle on the viewport occupied by the item at index.
 *        If the index is not visible or explicitly hidden, the returned rectangle is invalid.
 * @param index Index of view (this variable is not in use).
 * @return  The rectangle on the viewport occupied by the item at index.
 */
QRect CRaspiEnvMeterView::visualRect(const QModelIndex &index) const
{
    Q_UNUSED(index)

    return QRect(0, 0, 100, 100);
}

/**
 * @brief Scroll the view if necessary to ensure that the item at index is visible.
 * @param index Index of model.
 * @param hint  Hint.
 * @attention   Nothing to do in this class, method.
 */
void CRaspiEnvMeterView::scrollTo(const QModelIndex &index, ScrollHint hint)
{
    Q_UNUSED(index)
    Q_UNUSED(hint)
}

/**
 * @brief Returns the model index of the item at the viewport coordinates point.
 * @param point Index of the item at the viewport coordinates point.
 * @return  The model index of the item.
 * @attention   Nothing to do in this class, method.
 */
QModelIndex CRaspiEnvMeterView::indexAt(const QPoint &point) const
{
    Q_UNUSED(point)

    return QModelIndex();
}

QModelIndex CRaspiEnvMeterView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(cursorAction)
    Q_UNUSED(modifiers)

    return QModelIndex();
}

/**
 * @brief Returns the horizontal offset of the view.
 * @return The horizontal offset of the view.
 */
int CRaspiEnvMeterView::horizontalOffset() const
{
    return 0;
}

/**
 * @brief Returns the vertical offset of the view.
 * @return The vertical offset of the view.
 */
int CRaspiEnvMeterView::verticalOffset() const
{
    return 0;
}

/**
 * @brief Returns true if the item referred to by the given index is hidden in the view,
 *        otherwise returns false.
 * @param index Index of the item.
 * @return  True if the item referred to by the given index is hidden in the view, otherwise returns false.
 */
bool CRaspiEnvMeterView::isIndexHidden(const QModelIndex &index) const
{
    Q_UNUSED(index)

    return false;
}

/**
 * @brief Applies the selection flags to the items in or touched by the rectangle, rect.
 * @param rect  Reference of QRect object.
 * @param command   Command of flags.
 * @attention   Nothing to do in this function.
 */
void CRaspiEnvMeterView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{
    Q_UNUSED(rect)
    Q_UNUSED(command)
    QString sampleStirng = tr("ssss");
}

/**
 * @brief Returs the region from the viewport of the items in the given selection.
 * @param selection Reference of QItemSelection object which represents the area of selection.
 * @return  The region from the viewport of the items in the given selection.
 */
QRegion CRaspiEnvMeterView::visualRegionForSelection(const QItemSelection &selection) const
{
    Q_UNUSED(selection)

    return QRegion();
}

/**
 * @brief This slot is called when items with the given roles are changed in the model.
 *        The changed items are those from topLeft to bottomRight inclusive.
 *        If just one item is changed topLeft == bottomRight.
 * @param topLeft   Index of model top left.
 * @param bottomRight   Index of model bottom right.
 * @param roles Role of data change.
 */
void CRaspiEnvMeterView::dataChanged(const QModelIndex &topLeft,
                                     const QModelIndex &bottomRight,
                                     const QVector<int> &roles)
{
    assert(nullptr != this->model());
    assert(nullptr != this->item_view_);

    Q_UNUSED(bottomRight)
    Q_UNUSED(roles)

    int index = topLeft.row();
    if (this->model_row_index_ == index) {
        //Wrtie code here to update view.
        this->item_view_->setText(this->model()->data(topLeft).toString());
    } else {
        //Nothing todo.
    }
}
