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

    ///kommunikál a konzollal és beolvas egy új usert
void UserList::userFromConsole(){
        String newName;
        std::cout << "Adjon meg egy felhasználó nevet:" << std::endl;
        std:: cin >> newName;

        if(getUserbyUsername(newName) == nullptr){
            String newPass;
            std::cout << "Adjon meg egy jelszót:" << std::endl;
            std:: cin >> newPass;
            User* newU;
            newU = new User(newName, newPass);
            add(newU);
            std::cout << "A profil létrejött" << std::endl;
        } else{
            std::cout << "Az adott névvel már létezik felhasználó" << std::endl;
        }
}

///kommunikál a konzollal és beolvas egy új usert
User* UserList::signInFromConsole(){
    String name;
    std::cout << "Adja meg a felhasználó nevét:" << std::endl;
    std:: cin >> name;

   User* currentUser = getUserbyUsername(name);
   if(currentUser != nullptr){
        String pass;
        std::cout << "Adja meg a jelszavát:" << std::endl;
        std:: cin >> pass;
        if(currentUser->getPassword() == pass){
            std::cout << "Sikeres belépés" << std::endl;
        } else{
            std::cout << "Helytelen jelszó" << std::endl;
        }
    } else{
        std::cout << "Helytelen felhasználónév" << std::endl;
    }
    return  currentUser;
}