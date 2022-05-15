#pragma once
#define MEMTRACE

#include "memtrace.h"

template<typename T> 
class Array{
    T* elements;
    int len;

    public:
    ///Konstruktor
    Array(int size):len(size){
        this->elements = new T [size];
    }

    ///Default konstruktor
    Array():elements(nullptr),len(0){};

     Array(T* e,int size):elements(e),len(size){};

   ///Destruktor
    ~Array(){
      delete[] elements;
    }

    ///Copy konstruktor
    Array(const Array<T>& a){
        len = a.getLen();
        elements = new T [len];
        for (int i = 0; i < len; i++){
            elements[i] = a[i];
        }
    }

    /***
     * Getter
     * @return a dinamikus tömb hossza
     *  ***/
    int getLen() const {
        return len;
    }

    /*** 
     * Hozzáad egy új elemet a tömbvégéhez
     * @param newElement új elem
     * ***/
    void add(T newElement){
        len++;
        T* placeHolder = new T [len];
        for (int i = 0; i < len-1; ++i){
            placeHolder[i] = elements[i];
        }
        delete[] elements;
        elements = placeHolder;
        elements[len-1] = newElement;
    }

    /***
     * Töröl egy elemet a tömbböl, nem marad üres hely a tömb shiftelődik és rövidebb lesz
     * @param idx törlendő elem indexe
     * ***/
    void remove(int idx){
        ///Először beshiftelünk a trölöni kívánt elem helyére
        for (int i = 0; i < len; ++i) {
            if(idx<i){
                elements[i-1] = elements[i];
            }
        }
        ///Létrehozzuk az új kisebb tömböt és beleírjuk az elshiftelt tömböt, amiben már nincs benn a törölt elem
        len = len-1;
        T* tmp = new T [len];
        for (int i = 0; i < len; ++i){
            tmp[i] = elements[i];
        }
        delete[] elements;
        elements = tmp;

        ///elem indexének helyére shiftelés ezután jön az utolsó elem levágása
       /* int j = 0;
        for (int i = 0; i < len; i++){
            if(idx != j){
                tmp[i] = elements[j];
                j++;
            }else{
                j++;
                tmp[i] = elements[j];
                
            }
        }
        delete[] elements;
        elements = tmp;*/
    }

    /***
    * Ellenőrzi, hogy egy String benne van- egy String tömben
    * @param a a tömb
    * @param str a String
    * ***/
    bool isIn(T e){
        for (int i = 0; i < getLen(); ++i) {
            if((*this)[i] == e){
                return true;
            }
        }
        return false;
    }


     /***
     * Konstans indexelő operátor
     * ***/
    T operator[](int i) const{
        return elements[i];
    }
   
    /***
     *  Indexelő operátor
     * ***/
    T& operator[](int i){
        return elements[i];
    }

    Array<T>& operator=(const Array<T>& a){
        Array<T> newA(a);
        *this = newA;
        return *this;
    }

    bool operator==(const Array<T>& a){
        if(len != a.getLen())
            return false;

        for (int i = 0; i < len; i++){
            if((*this)[i] != a[i])
                return false;
        }
        return true;
    }
};