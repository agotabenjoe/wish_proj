#pragma once
#define MEMTRACE

#include <cstddef>

#include "ListElement.hpp"

class List{
    int len;
    
    protected:
    ListElement* elements;

    public:
    /*** 
     * Kostruktor: Eltárolja az első listaelemet
     * @param newElement dinamikusan foglalt listaelem
     * ***/
    List(ListElement* newElement):len(1), elements(newElement){}

    ///Default konstruktor
    List():len(0), elements(nullptr){}

    /*** 
     * Destruktor
     * ***/
    virtual ~List();
    
    /*** 
     * Hozzádja a dinamikusan foglalat elemet a listához
     * @param newElement dinamikusan foglalt listaelem
     * ***/
    void add(ListElement* newElement);//végén a pointer mutatsson a new elementre


    /*** 
     * Töröl egy listaelemet azonosító alapján
     * @param id a törölendő elem azonosítója
     * ***/
    virtual void remove(int id);

    int getLen();

     /*** 
     * 0.tól kezdődő konstans indexelő operátor
     * @param idx index
     * ***/
    ListElement* operator[](int idx) const;

    /*** 
     * 0.tól kezdődő indexelő operátor
     * @param i index
     * ***/
    ListElement* operator[](int idx);

};