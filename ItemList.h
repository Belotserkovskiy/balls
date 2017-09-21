#ifndef BALLSLIST_H
#define BALLSLIST_H

#include <abstractitem.h>

#include <list>
#include <mutex>

class ItemList
{
    std::list< AbstractItem*> m_itemsList;
    int m_count = 0;
    std::mutex m_mutex;
public:
    ItemList();

    int addItem( AbstractItem *item);
    void deleteItem( AbstractItem *item);
    void clear();
    int count();

    void lock();
    void unlock();
    std::list< AbstractItem*>::iterator begin();
    std::list< AbstractItem*>::iterator end();

};

#endif // BALLSLIST_H
