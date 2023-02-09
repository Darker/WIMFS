#ifndef IDTOINDEXMAP_H
#define IDTOINDEXMAP_H

#include <QModelIndex>

struct IdToIndex
{
  // Id of a database row
  size_t id;
  // QModelIndex of a view row
  QModelIndex index;
};

#endif // IDTOINDEXMAP_H
