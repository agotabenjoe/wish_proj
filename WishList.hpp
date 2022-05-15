#pragma once
#define MEMTRACE

#include "List.hpp"
#include "ListElement.hpp"
#include "Wish.hpp"
#include "Array.hpp"

class WishList: public List{
    public:
    /*** 
     * Kostruktor: Eltárolja az első Wish-t a listában
     * @param newWish dinamikusan foglalt listaelem
     * ***/
    WishList(Wish* newWish):List(newWish){}

    ///Default konstruktor
    WishList():List(){}

    ~WishList(){}

    /***
     * Tulaj felhasználóneve alapján visszaad egy Wish tömöbot, ahol a tulaj összese Wish-e benne van tömben
     * @param owner a tulaj felhasználóneve
     * @return Wish tömb - a tulaj összes kívánsága
     * ***/
    Array<Wish*> getWishbyOwner(String owner);

    /***
     * Ajándékozó felhasználóneve alapján visszaad egy Wish tömöbot, ahol az ajándékozó összes ajándéka benne van a tömbben
     * @param owner a tulaj felhasználóneve
     * @return Wish tömb - a tulaj összes kívánsága
     * ***/
    Array<Wish*> getWishbyGiver(String giver);


};