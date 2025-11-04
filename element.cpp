#include "element.h"
template<class T>
Element<T>::Element(){}

template<class T>
Element<T>::~Element(){
    if(this){
        if(this->next){
            delete this->next;
        }
    }
}

template<class T>
T Element<T>::get_data() const {
    if(this){
        return data;
    }
    return 0;
}

template<class T>
Element<T>* Element<T>::get_next() const {

    if(this){
        return next;
    }
    return 0;
}


template<class T>
void Element<T>::set_data(T val){

    if(this){
        data = val;
    }
}
template<class T>
void Element<T>::set_next(Element<T>* val){

    if(this){
        next = val;
    }
}


template<class T>
Element<T>* Element<T>::get_prev() const{
    if(this){
        return prev;
    }
    return 0;
}


template<class T>
void Element<T>::set_prev(Element<T>* val){
    if(this){
        prev = val;
    }
}
template class Element<Conf*>;
