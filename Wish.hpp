#pragma once
#define MEMTRACE

#include <iostream>

#include "ListElement.hpp"
#include "String.hpp"

class Wish: public ListElement{
    String name;
    String owner;
    String giver;

    public:
    /***
     * Konstruktor
     * @param name a kívánság neve
     * @param owner a kívánság tulaja, a kívánó felhasználóneve
     * @param giver az ajándékozó felhasználóneve
     * @param newNext a listában a következő elemre mutató pointer
     * ***/
    Wish(String n, String o, String g, ListElement* newNext):ListElement(newNext), name(n),owner(o),giver(g){}

    /***
     * Konstruktor: új wish hozzáadásához
     * @param name a kívánság neve
     * @param owner a kívánság tulaja, a kívánó felhasználónever
     * ***/
    Wish(String n, String o):ListElement(NULL), name(n),owner(o){}

    ///Copy konstruktor
    Wish(const Wish& w);

    /***
     * Getter
     * @return kívánság neve, String
     * ***/
    String getName() const;

    /***
     * Getter
     * @return tulaj felhasználóneve, String
     * ***/
    String getOwner() const;

    /***
     * Getter
     * @return ajándékozó felhasználóneve, String
     * ***/
    String getGiver() const;

    /*** 
     * @param g ajándékozó
     * ***/
    void setGiver(String g);

    Wish& operator=(const Wish& w);
 
    bool operator==(const Wish& w);

    std::ostream operator<<(const Wish& w) const;
};