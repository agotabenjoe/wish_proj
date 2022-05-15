#pragma once
#define MEMTRACE

#include <cstddef>
#include <iostream>
#include "List.hpp"
#include "ListElement.hpp"

 /*** 
     * Destruktor
     * ***/
     List::~List(){
     //std::cout<< "called";
         ListElement* iter = elements;
         while (iter != nullptr){
             std::cout<< "called";
             ListElement* next = iter->getNext();
             delete iter;
             iter = next;
         }
    }
    
    /*** 
     * Hozzádja a dinamikusan foglalat elemet a listához
     * @param newElement dinamikusan foglalt listaelem
     * ***/
    void List::add(ListElement* newElement){
        if (elements == nullptr) {
            elements = newElement;
        } else {
            ListElement* iter = elements;
            while (iter->getNext() != nullptr){
             iter = iter->getNext();
            }
            iter->setNext(newElement);
            len++;
        }
    }

    /*** 
     * Töröl egy listaelemet azonosító alapján
     * @param id a törölendő elem azonosítója
     * ***/
    void List::remove(int id){
         if(id==elements->getId()){
            ListElement* tmp = elements->getNext();
            delete elements;
            elements = tmp;
        }else{
             ListElement* before;
             ListElement* iter = elements;
             while (iter->getId() != id){
                 before = iter;
                 iter = iter->getNext();
             }
             before->setNext(iter->getNext());
             delete iter;
         }
    }

     /*** 
     * 0.tól kezdődő konstans indexelő operátor
     * @param idx index
     * ***/
    ListElement* List::operator[](int idx) const{
        if(idx > len || idx < 0)
            throw "out of range";
        ListElement* iter = elements;
        for (size_t i = 0; i != idx; i++){
            iter = iter->getNext();
        }
        return iter;
    }

    /*** 
     * 0.tól kezdődő indexelő operátor
     * @param idx index
     * ***/
    ListElement* List::operator[](int idx){
        if(idx > len || idx < 0)
            throw "out of range";
        ListElement* iter = elements;
        for (size_t i = 0; i != idx; i++){
            iter = iter->getNext();
        }
        return iter;
    }