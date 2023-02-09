#ifndef ITEMINSTANCEMODEL_H
#define ITEMINSTANCEMODEL_H

#include <QAbstractListModel>

class ItemInstanceModel : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit ItemInstanceModel(QObject *parent = nullptr);

  // Header:
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  // Fetch data dynamically:
  //bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

//  bool canFetchMore(const QModelIndex &parent) const override;
//  void fetchMore(const QModelIndex &parent) override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
public slots:
  void rowsAdded(std::size_t count);
private:
};

#endif // ITEMINSTANCEMODEL_H
