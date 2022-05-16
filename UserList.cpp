#pragma once
#define MEMTRACE
 
#include "List.hpp"
#include "UserList.hpp"
#include "User.hpp"
#include "String.hpp"

    /***
     * Visszaad egy User-t felhasznáéó név alapján, ha létezik User az adott felhasználónévvel
     * @param Username a keresett User felhasználóneve
     * @return a felhasználónévvel rendelkező User
     * ***/
    User* UserList::getUserbyUsername(String Username){
        User* iter = dynamic_cast<User*>(elements); //castolás, hogy működjön az őssel
        while (iter!=nullptr){
            if(iter->getUsername() == Username){
                return iter;
            }
            iter = dynamic_cast<User*>(iter->getNext());
        }
        return  iter;
    }