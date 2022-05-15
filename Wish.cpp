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

    bool Wish::gotTaken() const{
        return isTaken;
    }

void Wish::setName(String n){
    name = n;
}



/***
 * Getter
 * @return ajándékozó felhasználóneve, String
 * ***/
String Wish::getGiver() const{
    if(!isTaken){
        throw "not taken";
    }
    return giver;
}

    /*** 
     * @param g ajándékozó
     * ***/
    void Wish::setGiver(String g){
        giver = g;
        isTaken = true;
    }

/***
 * @param o owner
 * ***/
void Wish::setOwner(String o){
    owner = o;
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