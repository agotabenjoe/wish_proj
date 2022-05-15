#pragma once
#define MEMTRACE
#include "User.hpp"
#include "Menu.hpp"

class AuthMenu: public Menu{
    User& currentUser;

    public:
    /*** 
     * Konstruktor
     * @param wishes a kívánság lista
     * @param users a felhasználó lista
     * @param pr a főprogram futását irányító bool
     * @param cUser a bejelentkezett felhasználó
     * ***/
    AuthMenu(WishList& wishes, UserList& users, bool& pr, User& cUser):Menu(pr, wishes, users), currentUser(cUser){}

    void run();

    void wishes();

    void friends();

    void friendRequests();

    void addFriend();

    void signOut();


    void wishesAdd();

    void wishesList();

    void wishesUpdate();

    void wishesRemove();
};