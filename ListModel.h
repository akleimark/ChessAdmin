#ifndef LISTMODEL_H
#define LISTMODEL_H

#include "MVC.h"

template <class T>
class ListModel : public Model
{
    public:
    ListModel<T>() {}
        virtual ~ListModel() {}
        void add(const T& item) { container.insert(item); }
        virtual void getAll();
        unsigned int getSize() const { return container.size(); }
        typename std::set<T>::const_iterator cbegin() const {return container.cbegin(); }
        typename std::set<T>::const_iterator cend() const {return container.cend(); }        
        T atIndex(const unsigned int &index) const;

    protected:
        std::set<T> container;
};

template <typename T>
T ListModel<T>::atIndex(const unsigned int &index) const
{
    typename std::set<T>::const_iterator it;

    unsigned int currentIndex = 0;
    for(it = container.begin(); it != container.end(); ++it)
    {
        if(currentIndex++ == index)
        {
            return *it;
        }
    }
    throw std::out_of_range("Felaktigt index.");
}

#endif // LISTMODEL_H
