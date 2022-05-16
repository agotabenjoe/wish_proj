#pragma once
#define MEMTRACE

#include "List.hpp"
#include "ListElement.hpp"
#include "User.hpp"
#include "String.hpp"


class UserList: public List{
    public:
    /*** 
     * Kostruktor: Eltárolja az első User-t a listában
     * @param newUser dinamikusan foglalt listaelem
     * ***/
    UserList(User* newUser):List(newUser){}

    ///Default konstruktor
    UserList():List(){}

    ~UserList(){}

    /***
     * Visszaad egy User-t felhasznáéó név alapján, ha létezik User az adott felhasználónévvel
     * @param Username a keresett User felhasználóneve
     * @return a felhasználónévvel rendelkező User
     * ***/
    User* getUserbyUsername(String Username);

    void userFromConsole();

    User* signInFromConsole();

    void buyGiftFromConsole();

    void addFriendRequestFromConsole();

    void acceptFriendRequestFromConsole();

};