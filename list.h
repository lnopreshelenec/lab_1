#ifndef LIST_H
#define LIST_H
#include "element.h"
#include "conf.h"

template <class T>
class List
{

public:
    void print();
    ~List();
    List();
    explicit List(int var);
    List(const List<T> &l);
    void copy(List<T> &res) const;
    List<T> operator+(const List<T> &l2) const;
    List<T> operator+(const T &val);
    List& operator=(const List<T> &l2);
    Element<T>* getHead() const;
    void setHead(Element<T>* el);
    Element<T>* getLast() const;
    void setLast(Element<T>* el);

    void add(T var);
    Element<T>* at(int index);
    int remove(int index);

    int len()  const;
    bool operator == (const List<T> &l) const;
    bool operator != (const List<T> &l) const;
private:
    Element<T> *head = 0;
    Element<T> *last = 0;
};



#endif
