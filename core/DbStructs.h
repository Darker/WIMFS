#ifndef DBSTRUCTS_H
#define DBSTRUCTS_H

#include <string>

namespace db
{

struct Item
{
  std::string note;
  int count;
};

struct ItemInstance
{
  std::string title;
  std::string note;
  int quantity;
};

}


#endif // DBSTRUCTS_H
