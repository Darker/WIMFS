#ifndef QT_DB_CONVERSIONS_H
#define QT_DB_CONVERSIONS_H
#include <sqlite3++/traits/ReadTraits.h>
#include <QString>

namespace sqlitepp {

template<>
struct ReadTraits<QString>
{
  static QString ReadFromStatement(RawStatement::ReadHelper& reader)
  {
    StrUnowned chars = reader.ReadString();
    return QString(chars.data());
  }
};

}


#endif // QT_DB_CONVERSIONS_H
