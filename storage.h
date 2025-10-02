#ifndef STORAGE_H
#define STORAGE_H

#include <QList>

template <typename T>
class Storage
{
private:
    QList<T> list;
public:
    Storage();
    T GetItem(const int& index);
    int FindItem(const T& value);
    void AddItem(const T& value);
    void RemoveItem(const int& index);
    void UpdateItem(const T& value, const int& index);
    unsigned GetSize();
};

template <typename T>
Storage<T>::Storage()
{

}

template <typename T>
T Storage<T>::GetItem(const int& index)
{
    return this->list.value(index);
}

template <typename T>
int Storage<T>::FindItem(const T& value)
{
    return this->list.indexOf(value);
}

template <typename T>
void Storage<T>::AddItem(const T& value)
{
    this->list.push_back(value);
}

template <typename T>
void Storage<T>::RemoveItem(const int& index)
{
    this->list.removeAt(index);
}

template <typename T>
void Storage<T>::UpdateItem(const T& value, const int& index)
{
    this->list.replace(index, value);
}

template <typename T>
unsigned Storage<T>::GetSize()
{
    return this->list.size();
}

#endif // STORAGE_H
