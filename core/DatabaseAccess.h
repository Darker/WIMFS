#ifndef DATABASEACCESS_H
#define DATABASEACCESS_H

#include "DbStructs.h"

#include <QObject>

namespace sqlitepp
{
  class Database;
}

class DatabaseAccess : public QObject
{
  Q_OBJECT
public:
  explicit DatabaseAccess(QObject *parent = nullptr);

  virtual ~DatabaseAccess();
signals:
  void itemChanged(std::int64_t);
  void rowsAdded(int);
public slots:
  void initDB(const QString& dbPath);
  QList<db::ItemInstance> fetchItemInstances();

private:
  struct Statements;
  std::unique_ptr<Statements> stmt;

  std::unique_ptr<sqlitepp::Database> database;
};

#endif // DATABASEACCESS_H
