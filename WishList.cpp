#pragma once
#define MEMTRACE

#include "WishList.hpp"
#include "Wish.hpp"
#include "Array.hpp"
#include "String.hpp"
#include "List.hpp"

/***
     * Tulaj felhasználóneve alapján visszaad egy Wish tömöbot, ahol a tulaj összese Wish-e benne van tömben
     * @param owner a tulaj felhasználóneve
     * @return Wish tömb - a tulaj összes kívánsága
     * ***/
    Array<Wish*> WishList::getWishbyOwner(String owner){
        Array<Wish*> ownerWishes;
        Wish* iter = dynamic_cast<Wish*>(elements); //castolás, hogy működjön az őssel
        while (iter != nullptr){
            if(iter->getOwner() == owner){
                ownerWishes.add(iter);
            }
            iter = dynamic_cast<Wish*>(iter->getNext());
        }
        return ownerWishes;
    }

    /***
     * Ajándékozó felhasználóneve alapján visszaad egy Wish tömöbot, ahol az ajándékozó összes ajándéka benne van a tömbben
     * @param owner a tulaj felhasználóneve
     * @return Wish tömb - a tulaj összes kívánsága
     * ***/
    Array<Wish*> WishList::getWishbyGiver(String giver){
        Array<Wish*> giverWishes;
        Wish* iter = dynamic_cast<Wish*>(elements); //castolás, hogy működjön az őssel
        while (iter != nullptr){
            if(iter->getGiver() == giver){
                giverWishes.add(iter);
            }
            iter = dynamic_cast<Wish*>(iter->getNext());
        }
        return giverWishes;
    }