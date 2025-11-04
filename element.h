#ifndef ELEMENT_H
#define ELEMENT_H
#include "conf.h"

template <class T>
class Element
{
public:
    Element();
    T get_data() const;
    void set_data(T val);
    Element* get_next() const;
    Element* get_prev() const;
    void set_next(Element* val);
    void set_prev(Element* val);
    ~Element();
private:
    T data;
    Element<T> *next = 0;
    Element<T> *prev = 0;
};

#endif // ELEMENT_H
