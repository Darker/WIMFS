#include "ItemInstanceModel.h"

ItemInstanceModel::ItemInstanceModel(QObject *parent)
  : QAbstractListModel(parent)
{

}

QVariant ItemInstanceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
      switch (section) {
      case 0:
          return QString("title");
      case 1:
          return QString("note");
      case 2:
          return QString("quantity");
      }
  }
  return QVariant();
}

int ItemInstanceModel::rowCount(const QModelIndex &parent) const
{
  // For list models only the root node (an invalid parent) should return the list's size. For all
  // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
  if (parent.isValid())
    return 0;
  return 2;
  // FIXME: Implement me!
}

int ItemInstanceModel::columnCount(const QModelIndex& parent) const
{
  if (parent.isValid())
    return 0;
  return 3;
  // FIXME: Implement me!
}
//bool ItemInstanceModel::hasChildren(const QModelIndex &parent) const
//{
//  // FIXME: Implement me!
//}

//bool ItemInstanceModel::canFetchMore(const QModelIndex &parent) const
//{
//  // FIXME: Implement me!
//  return false;
//}

//void ItemInstanceModel::fetchMore(const QModelIndex &parent)
//{
//  // FIXME: Implement me!
//}

QVariant ItemInstanceModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  int row = index.row();
  int col = index.column();

  switch (role) {
    case Qt::DisplayRole:
        return QString("Row%1, Column%2")
                .arg(row + 1)
                .arg(col +1);
//    case Qt::FontRole:
//        break;
//    case Qt::BackgroundRole:
//        break;
//    case Qt::TextAlignmentRole:
//        break;
    case Qt::CheckStateRole:
        if (col > 1) // add a checkbox to cell(1,0)
            return Qt::Checked;
        break;
  }
  return QVariant();
}

void ItemInstanceModel::rowsAdded(std::size_t count)
{
  auto root = createIndex(0,0).parent();
  // Get number of rows
  int lastRow = rowCount(root) - 1;
  // we identify the top left cell
  QModelIndex first = createIndex(lastRow,0);
  QModelIndex last = createIndex(lastRow + count,0);
  // emit a signal to make the view reread identified data
  emit dataChanged(first, last, {Qt::DisplayRole, Qt::DecorationRole});
}
