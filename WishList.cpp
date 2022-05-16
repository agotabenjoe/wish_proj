#pragma once
#define MEMTRACE

#include "WishList.hpp"
#include "Wish.hpp"
#include "Array.hpp"
#include "String.hpp"
#include "List.hpp"
#include "User.hpp"

/***
     * Tulaj felhasználóneve alapján visszaad egy Wish tömöbot, ahol a tulaj összese Wish-e benne van tömben
     * @param owner a tulaj felhasználóneve
     * @return Wish tömb - a tulaj összes kívánsága
     * ***/
    Array<Wish*> WishList::getWishbyOwner(String owner){
        Array<Wish*> ownerWishes;
        Wish* iter = dynamic_cast<Wish*>(elements); ///castolás, hogy működjön az őssel
        while (iter != nullptr){
            if(iter->getOwner() == owner){
                ownerWishes.add(iter);
            }
            iter = dynamic_cast<Wish*>(iter->getNext());
        }
        return ownerWishes;
    }

/***
 * Id alapján visszad egy wisht
 * @param int a keresett elem idje
 * @return keresett wish
 * ***/
Wish* WishList::getWishbyId(int id){
    Wish* wishById;
    Wish* iter = dynamic_cast<Wish*>(elements); ///castolás, hogy működjön az őssel
    while (iter->getId() != id){
        iter = dynamic_cast<Wish*>(iter->getNext());
    }
    wishById = iter;
    return wishById;
}

    /***
     * Ajándékozó felhasználóneve alapján visszaad egy Wish tömöbot, ahol az ajándékozó összes ajándéka benne van a tömbben
     * @param owner a tulaj felhasználóneve
     * @return Wish tömb - a tulaj összes kívánsága
     * ***/
    Array<Wish*> WishList::getWishbyGiver(String giver){
        Array<Wish*> giverWishes;
        Wish* iter = dynamic_cast<Wish*>(elements); ///castolás, hogy működjön az őssel
        while (iter != nullptr){
            if(iter->getGiver() == giver){
                giverWishes.add(iter);
            }
            iter = dynamic_cast<Wish*>(iter->getNext());
        }
        return giverWishes;
    }

///******a menü miatt kellenek:

///Ki listázza egy user wisheit mint menüelemeket
void WishList::printWishMenu(User* u){
    int l = u->getWishes().getLen();
    for (int i = 0; i < l; ++i) {
      std::cout << i << "." << getWishbyOwner(u->getUsername())[i]->getName() << std::endl;
    }

}

void WishList::setNameFromConsole(User* u){
    int command;
    std::cout << "Melyik kívánságit kívánja szerkeszteni?" << std::endl;
    std:: cin >> command;
    if(command < u->getWishes().getLen()){
        String newName;
        std::cout << "Adjon meg egy új nevet:" << std::endl;
        std:: cin >> newName;
        getWishbyId(u->getWishes()[command])->setName(newName);
        std::cout << "Sikeres művelet:" << std::endl;
    } else{
        std::cout << "Sikertelen művelet:" << std::endl;
    }
}

void WishList::deleteFromConsole(User* u,UserList* users){
    int command;
    std::cout << "Melyik kívánságit kívánja törölni?" << std::endl;
    std:: cin >> command;
    if(command < u->getWishes().getLen()){
        if(getWishbyId(u->getWishes()[command])->gotTaken()){ ///Itt töröljük ha valaki ajándékozza
            users->getUserbyUsername(getWishbyId(u->getWishes()[command])->getGiver())->delWishById(u->getWishes()[command]);
        }
        remove(u->getWishes()[command]);
        u->delWish(command);
        std::cout << "Sikeres művelet:" << std::endl;
    } else{
        std::cout << "Sikertelen művelet:" << std::endl;
    }
}

void WishList::addFromConsole(User* u){
    std::cout << "Adja meg az új kívánságot" << std::endl;
    String newName;
    std:: cin >> newName;
    Wish* newW;
    newW = new Wish (newName, u->getUsername());
    add(newW);
    u->addWish(newW->getId());
    std::cout << "Sikeres művelet" << std::endl;
}