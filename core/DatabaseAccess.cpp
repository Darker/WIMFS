#include "DatabaseAccess.h"

#include <sqlite3++/Database.h>
#include <sqlite3++/Statement.h>

using namespace sqlitepp;

struct DatabaseAccess::Statements
{
  Statement<StrUnowned, StrUnowned, int> getAllItemInstances{R"SQL(
            SELECT title, note, quantity FROM items_instances
      )SQL"};
  Statement<QString, QString, int> getAllItems{R"SQL(
            SELECT weight FROM items
      )SQL"};
  Statement<> insertItem{R"SQL(
            INSERT INTO items (weight) values (?)
      )SQL"};
  Statement<double, int, sqlitepp::StrUnowned> readstmt{R"SQL(
          SELECT data, int_num, key FROM test WHERE key = ?
          )SQL"};

};


DatabaseAccess::DatabaseAccess(QObject *parent)
  : QObject{parent}
  , stmt{new Statements()}
{

}

DatabaseAccess::~DatabaseAccess()
{
  stmt.reset(nullptr);
}

void DatabaseAccess::initDB(const QString& dbPath)
{
  database.reset(new Database());
  //static_assert(sizeof(decltype(*(dbPath.data()))) == sizeof(QChar), "Cannot convert qstring to db path");
  QByteArray ba = dbPath.toLocal8Bit();
  database->open(ba.constData());
  database->exec(R"SQL(
        -- Create table for the data
        CREATE TABLE IF NOT EXISTS "items_instances" (
          "item_instance_id" INTEGER PRIMARY KEY,
          "item_id" INTEGER NOT NULL,
          "location_id" INTEGER NOT NULL,
          "title" TEXT,
          "note" TEXT,
          "created" DATETIME,
          "updated" DATETIME,
          "quantity" INT NOT NULL DEFAULT 0,
          "quantity_type" SMALLINT
        )
  )SQL");
  database->exec(R"SQL(
        CREATE TABLE IF NOT EXISTS "items" (
          "item_id" INTEGER PRIMARY KEY,
          "weight" INTEGER
        )
  )SQL");
  database->exec(R"SQL(
        CREATE TABLE IF NOT EXISTS "item_labels" (
          "label_id" INTEGER PRIMARY KEY,
          "language" TEXT,
          "name" TEXT,
          "description" TEXT
        );
  )SQL");

  database->exec(R"SQL(
        CREATE TABLE IF NOT EXISTS "locations" (
          "location_id" INTEGER PRIMARY KEY,
          "location_type_id" INTEGER,
          "name" TEXT,
          "description" TEXT
        );
  )SQL");

  stmt->getAllItems.Init(database.get());
  stmt->getAllItemInstances.Init(database.get());
}

QList<db::ItemInstance> DatabaseAccess::fetchItemInstances()
{
  QList<db::ItemInstance> items;
//  double readDouble;
//  int readInt;
//  std::string readStr;
//  stmt->readstmt.execute(
//    [&readDouble, &readInt, &readStr](double rdbl, int rint, sqlitepp::StrUnowned rstr)
//    {
//      readDouble = rdbl;
//      readInt = rint;
//      readStr = rstr.data();
//      //readDouble = std::get<0>(tpl);
//      //readInt = std::get<1>(tpl);
//      //readStr = std::get<2>(tpl).data();
//      return false;
//    },
//    "test_name"
//  );
  const auto rowCB = [&items](StrUnowned title, StrUnowned note, int value) {
    items.append(db::ItemInstance{std::string{title.data()}, std::string{note.data()}, value});
    return true;
  };
  stmt->getAllItemInstances.execute(rowCB);

  return items;
}
