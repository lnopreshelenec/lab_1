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


// #ifndef LIST_CPP
// #define LIST_CPP
// #include "list.h"
#include <QDebug>


// template class List<Conf*>;
template<class T>
List<T>::List(){
    head = 0;
}

template<class T>
List<T>::List(int var){
    head = 0;
    for(int i = 0;i<(var);++i){
        this->add(0);
    }
}

template<class T>
void List<T>::add(T var)
{
    Element<T> *newi = new Element<T>;
    newi->set_next(0);
    newi->set_data(var);
    newi->set_prev(0);
    Element<T> *curr = head;
    if(curr==0){
        head = newi;
        last = newi;
        return;
    }
    // newi->set_prev(curr);
    while(curr->get_next())
        curr = curr->get_next();

    newi->set_prev(curr);
    curr->set_next(newi);
    // curr->getNext()->set_prev(curr);
    last = newi;
}


template<class T>
void List<T>::print(){
    // Element<T> *curr = head;
    // if(curr == 0){
    //     qDebug()<<"pass"<<endl;
    //     return;
    // }
    // char *c;
    // if  ((type_index (typeid(curr->get_data())).hash_code()==type_index (typeid(c)).hash_code())){
    //     while(curr->get_next()){
    //         printf("data = %s, prev = %p, next = %p\n",curr->get_data(),(void*)curr->get_prev(),(void*)curr->get_next());
    //         curr= curr->get_next();
    //     }
    //     printf("data = %s, prev = %p, next = %p\n",curr->get_data(),(void*)curr->get_prev(),(void*)curr->get_next());

    // }else{
    //     while(curr->get_next()){
    //         qDebug()<<"data = ";
    //         qDebug()<<curr->get_data()<<", ";
    //         qDebug()<<"prev = ";
    //         qDebug()<<(void*)curr->get_prev()<<", ";
    //         qDebug()<<"next = ";
    //         qDebug()<<(void*)curr->get_next()<<"\n";
    //         // printf("data = %d, prev = %p, next = %p\n",curr->getData(),(void*)curr->getPrev(),(void*)curr->getNext());
    //         curr= curr->get_next();
    //     }

    //     qDebug()<<"data = "<<curr->get_data()<<", ";
    //     qDebug()<<"prev = "<<(void*)curr->get_prev()<<", ";
    //     qDebug()<<"next = "<<(void*)curr->get_next()<<"\n";
    // }
    // printf("data = %d, prev = %p, next = %p\n",curr->getData(),(void*)curr->getPrev(),(void*)curr->getNext());
    Element<T> *curr = head;
    if(curr == nullptr){
        qDebug() << "List is empty";
        return;
    }

    qDebug() << "=== List Contents (" << this->len() << " items) ===";
    int index = 0;
    while(curr != nullptr){
        qDebug() << "[" << index++ << "]: " << curr->get_data();
        curr = curr->get_next();
    }
}

template<class T>
Element<T>* List<T>::at(int index){
    Element<T>* curr = head;
    if(curr == 0){
        return curr;
    }
    for(int cur_index = 0;cur_index<(index)&&curr->get_next();cur_index++)
        curr= curr->get_next();
    return curr;

}


template<class T>
int List<T>::remove(int index){
    Element<T>* curr = head;
    if(curr==0){
        return 0;
    }
    if(index==0){
        curr = curr->get_next();
        head->set_next(0);
        delete head;
        head = curr;
        return 1;
    }
    for(int cur_index = 1;cur_index<(index)&&curr->get_next();cur_index++)
        curr= curr->get_next();
    if(curr->get_next()==0){
        return 0;
    }
    Element<T>* next_item = curr->get_next();
    curr->set_next(next_item->get_next());
    next_item->set_next(0);
    delete next_item;
    curr->get_next()->set_prev(curr);
    while(curr->get_next()){curr = curr->get_next();}
    last = curr;
    return 1;
}

template<class T>
void List<T>::setHead(Element<T>* el){
    head = el;
}

template<class T>
List<T>::~List(){
    delete head;
}


template<class T>
Element<T>* List<T>::getHead() const{
    return head;
}


template<class T>
Element<T>* List<T>::getLast() const{
    return last;
}

template<class T>
void List<T>::setLast(Element<T>* el){
    last = el;
}

template<class T>
void List<T>::copy(List<T> &res) const {
    if(res.getHead()!=0){
        delete res.getHead();
        res.setHead(0);
    }
    Element<T>* curr = this->getHead();
    if(curr == 0){
        res.setHead(0);
        return;
    }
    res.add(curr->get_data());
    while(curr->get_next()){
        curr = curr->get_next();
        res.add(curr->get_data());
    }
    return;
}

template<class T>
List<T> List<T>::operator+(const List &l2) const{
    List res;
    if(this->getHead()==0){
        res.setHead(0);
        return res;
    }
    this->copy(res);
    Element<T> * curr = l2.getHead();
    if(curr!=0){
        res.add(curr->get_data());
        while(curr->get_next()){
            curr = curr->get_next();
            res.add(curr->get_data());
        }
    }
    return res;
}

template<class T>
List<T> List<T>::operator+(const T &val){
    add(val);//аргумент это то куда копируем
    List<T> *l = new List<T>;
    this->copy(*l);
    return *l;
}


template<class T>
List<T>::List( const List &l){
    l.copy(*this);//аргумент это то куда копируем
}




template<class T>
List<T>& List<T>::operator =(const List &l){
    l.copy(*this);//аргумент это то куда копируем
    return *this;
}


template <class T>
int List<T>::len()  const{
    if(head==0){
        return 0;
    }
    Element<T> * curr = head;
    int i = 1;
    while(curr->get_next()!=0){
        ++i;
        curr = curr->get_next();
    }
    return i;
}

template <class T>
bool List<T>::operator == (const List<T> &l) const
{

    return len() == l.len();
}

template <class T>
bool List<T>::operator != (const List<T> &l) const
{
    return len() != l.len();
}

// template class Element<Conf*>;
// template class List<Conf*>;
// template class List<Conf*>;

#endif
