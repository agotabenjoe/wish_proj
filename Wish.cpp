#pragma once
#define MEMTRACE

#include "Wish.hpp"
#include "ListElement.hpp"
#include "String.hpp"


///Copy konstruktor
///TODO:ennek utánanéz
    Wish::Wish(const Wish& w):ListElement(w){
        name = w.getName();
        giver = w.getGiver();
        owner = w.getOwner();
    }

    /***
     * Getter
     * @return kívánság neve, String
     * ***/
    String Wish::getName() const {
        return name;
    }

    /***
     * Getter
     * @return tulaj felhasználóneve, String
     * ***/
    String Wish::getOwner() const{
        return owner;
    }

    ///TODO: setName

    /***
     * Getter
     * @return ajándékozó felhasználóneve, String
     * ***/
    String Wish::getGiver() const{
        return giver;
    }

    /*** 
     * @param g ajándékozó
     * ***/
    void Wish::setGiver(String g){
        giver = g;
    }

    Wish& Wish::operator=(const Wish& w){
        Wish newW(w);
        return newW;
    }
 
    bool Wish::operator==(const Wish& w){
        if(name == w.getName() && giver == w.getGiver() && owner == w.getOwner())
            return true;
        return false;
    }