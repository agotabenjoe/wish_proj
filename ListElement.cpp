#pragma once
#define MEMTRACE

#include "ListElement.hpp"

int ListElement::newUid = 0;

///Copy konstruktor
ListElement::ListElement(const ListElement& l){
    uid = l.getId();
    next = l.getNext();
}

    /***
     * Getter
     * @return a listában a következő elemre mutató pointer
     * ***/
    ListElement* ListElement::getNext() const {
        return next;
    }
    
    /***
     * Getter
     * @return a lista elem egyedi azonosítója
     * ***/
    int ListElement::getId() const {
        return uid;
    }

    /***
     * Setter: Beállít egy új következő listaelemet
     * @param newNext az új következő listaelemre mutató pointer
     * ***/
    void ListElement::setNext(ListElement* newNext){
        next = newNext;
    }

/***
* Setter: Beállít új idt
* @param i új id
* ***/
void ListElement::setId(int i){
    uid = i;
}
