#pragma once
#define MEMTRACE
#include <fstream>
#include "UserList.hpp"
#include "WishList.hpp"

class JSONParser{
    std::fstream file;
    String fileName;

    public:
    /*** 
     * Konstruktor: megnyit egy fájlt a megadott elérési útból
     * @param path elérési út
     * ***/
    JSONParser(String path):fileName(path){}
    /*** 
     * Destruktor: bezárja a megnyitott fájlt
     * ***/
    ~JSONParser();

    JSONParser(const JSONParser& j);

    /*** 
     * A JSONParser-nek megadott fájlból beolvas egy UserList-et
     * @return UserList-et ad vissza, benne a felhasználók adataival
     * ***/
    UserList readUserData() const; //pointer-foglalás

    /*** 
     * A JSONParser-nek megadott fájlból beolvas egy WishList-et
     * @return WishList-et ad vissza, benne a felhasználók adataival
     * ***/
    WishList readWishData() const; //pointer-foglalás

    /*** 
     * A JSONParser-nek megadott fájlba kiír egy UserList-et
     * @param users a kiírandó UserList
     * ***/
    void writeUserData(UserList& users);

    /*** 
     * A JSONParser-nek megadott fájlba kiír egy WishList-et
     * @param wishes a kiírandó WishList
     * ***/
    void writeWishData(WishList& wishes);
};