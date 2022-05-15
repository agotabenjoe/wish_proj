#pragma once
#define MEMTRACE

#include "User.hpp"
#include "ListElement.hpp"
#include "Array.hpp"
#include "String.hpp"

///Copy konstruktors
    User::User(const User& u):ListElement(u){
        userName = u.getUsername(); 
        password = u.getPassword();
        friends = u.getFriends();
        friendRequests = u.getFriendRequests();
        wishes = u.getWishes();
        gift = u.getGifts();
    }
    
    /*** 
     * Getter
     * @return felhasználónév
     * ***/
    String User::getUsername()const{
        return userName;
    }

    /*** 
     * Getter
     * @return barátok tömbje
     * ***/
    Array<String> User::getFriends() const{
        return friends;
    }

    /*** 
     * Getter
     * @return barát kérelemek tömbje
     * ***/
    Array<String> User::getFriendRequests() const{
        return friendRequests;
    }

    /*** 
     * Getter
     * @return kívánságok tömbje
     * ***/
    Array<int> User::getWishes() const{
        return wishes;
    }

    /*** 
     * Getter
     * @return ajándékok tömbje
     * ***/
    Array<int> User::getGifts() const{
        return gift;
    }

    String User::getPassword()const{
        return password;
    }

void User::setUsername(String newUsername){
        userName = newUsername;
    }

void User::sePassword(String newPassword){
        password = newPassword;
    }

    /*** 
     * Hozzáadó
     * @param newFriend új barát felhasználóneve
     * ***/
    void User::addFriend(String newFriend){
        friends.add(newFriend);
    }

    /*** 
     * Hozzáadó
     * @param newRequest új barát kérelem, a kérő felhasználónneve
     * ***/
    void User::addFriendRequest(String newRequest){
        friendRequests.add(newRequest);
    }

    /*** 
     * Hozzáadó
     * @param wishId új kívánság id
     * ***/
    void User::addWish(int wishId){
        wishes.add(wishId);
    }

    /*** 
     * Hozzáadó
     * @param giftId új ajándék id
     * ***/
    void User::addGift(int giftId){
        gift.add(giftId);
    }

    /***
     * Töröl egy Wish-t
     * @param i a törlendő elem indexe a tömben
     * ***/
    void User::delWish(int i){
        wishes.remove(i);
    }

/***
 * Töröl egy Giftet
 * @param i a törlendő elem indexe a tömben
 * ***/
void User::delGift(int i){
    gift.remove(i);
}

/***
 * Töröl egy Giftet id alapján
 * @param i a törlendő elem indexe a tömben
 * ***/
void User::delGiftById(int id){
    for (int i = 0; i < gift.getLen(); ++i) {
        if(gift[i] == id){
            gift.remove(i);
        }
    }
}

    User& User::operator=(const User& u){
        User newU(u);
        return newU;
    }

    bool User::operator==(const User& u){
        if(userName == u.getUsername() && password == u.getPassword() && friends == u.getFriends() &&
            friendRequests == u.getFriendRequests() && wishes == u.getWishes() && gift == u.getGifts())
            return true;
        return false;
    }
