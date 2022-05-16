#pragma once
#define MEMTRACE

#include "ListElement.hpp"
#include "Array.hpp"
#include "String.hpp"
//majd mindig csekkolni kell, hogy érvényesek e még a wishek
//a tömbök felszabadítása nem a User class felelőssége!!! az Array destruktorban lesz majd megcsinálva, ugyanígy a stringekkel sem csinálnia semmit
class User: public ListElement{
    String userName; 
    String password;
    Array<String> friends;
    Array<String> friendRequests;
    Array<int> wishes;
    Array<int> gift;

    public:
    /***
     * Konstruktor: beolvasáshoz
     * @param name a User felhasználóneve
     * @param password a User jelszava
     * @param newNext a listában a következő elemre mutató pointer
     * ***/
    User(ListElement* newNext,String name, String pass, Array<String> f, Array<String> fr, Array<int> w, Array<int> g)
        :ListElement(newNext), userName(name), password(pass), friends(f), friendRequests(fr), wishes(w), gift(g){}

    /***
     * Konstruktor: az új userek hozzáadásához
     * @param name a User felhasználóneve
     * @param password a User jelszava
     * @param newNext a listában a következő elemre mutató pointer
     * ***/
    User(String name, String pass):ListElement(nullptr), userName(name), password(pass){}

    ///Default konstruktor
    User():ListElement(nullptr),userName(), password(), friends(), friendRequests(), wishes(), gift(){}

    ///Copy konstruktor
    User(const User& u);
    
    /*** 
     * Getter
     * @return felhasználónév
     * ***/
    String getUsername()const;

     /*** 
     * Getter
     * @return jelszó
     * ***/
    String getPassword()const;

    /*** 
     * Getter
     * @return barátok tömbje
     * ***/
    Array<String> getFriends() const;

    /*** 
     * Getter
     * @return barát kérelemek tömbje
     * ***/
    Array<String> getFriendRequests() const;

    /*** 
     * Getter
     * @return kívánságok tömbje
     * ***/
    Array<int> getWishes() const;

    /*** 
     * Getter
     * @return ajándékok tömbje
     * ***/
    Array<int> getGifts() const;

    void setUsername(String newUsername);

    void sePassword(String newPassword);

    void delFriendRequest(String toDel);

    /*** 
     * Hozzáadó
     * @param newFriend új barát felhasználóneve
     * ***/
    void addFriend(String newFriend);

    /*** 
     * Hozzáadó
     * @param newRequest új barát kérelem, a kérő felhasználónneve
     * ***/
    void addFriendRequest(String newRequest);

    /*** 
     * Hozzáadó
     * @param wishId új kívánság id
     * ***/
    void addWish(int wishId);

    /*** 
     * Hozzáadóxwxw
     * @param giftId új ajándék id
     * ***/
    void addGift(int giftId);

    /***xw
     * Töröl egy Wish-t
     * @param i a törlendő elem indexe a tömben
     * ***/
    void delWish(int i);

    /***xw
     * Töröl egy Wish-t
     * @param i a törlendő elem indexe a tömben
     * ***/
    void delGift(int i);

    /***
    * Töröl egy Giftet id alapján
    * @param i a törlendő elem indexe a tömben
    * ***/
    void delGiftById(int id);

    void delWishById(int toDel);

    User& operator=(const User& u);

    bool operator==(const User& u);
};