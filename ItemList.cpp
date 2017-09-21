#include "ItemList.h"

ItemList::ItemList()
{

}

int ItemList::addItem(AbstractItem *item)
{
    std::lock_guard<std::mutex> _lock(m_mutex);
    item->setParentList( this);
    m_itemsList.push_back( item);
    ++m_count;
    return 0;
}

void ItemList::deleteItem(AbstractItem *item)
{
    std::lock_guard<std::mutex> _lock(m_mutex);
    m_itemsList.remove( item);
}

void ItemList::clear()
{
    std::lock_guard<std::mutex> _lock(m_mutex);
    for( auto &item : m_itemsList)
        delete item;
    m_itemsList.clear();
}

int ItemList::count()
{
    return m_count;
}

void ItemList::lock()
{
    m_mutex.lock();
}

void ItemList::unlock()
{
    m_mutex.unlock();
}

std::list< AbstractItem*>::iterator ItemList::begin()
{
    return m_itemsList.begin();
}

std::list< AbstractItem*>::iterator ItemList::end()
{
    return m_itemsList.end();
}
