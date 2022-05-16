#pragma once
#define MEMTRACE

#include <iostream>
#include "WishList.hpp"
#include "UserList.hpp"


class Menu{
    bool& programRun;

    protected:
    int command;
    bool menuRun;
    WishList& wishes;
    UserList& users;

    public:
    /*** 
     * Konstruktor
     * @param wishes a kívánság lista
     * @param users a felhasználó lista
     * @param pr a főprogram futását irányító bool
     * ***/
    Menu(bool& pr, WishList& wishes, UserList& users): programRun(pr), menuRun(false), command(), wishes(wishes), users(users){}

    virtual void run();

    void createProfile();
    User* signIn();


};