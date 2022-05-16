#pragma once
#define MEMTRACE

#include "Menu.hpp"

 void Menu::run(){
    menuRun = true;
    while (menuRun){
        std::cout << "Üdvözlő menü" << std::endl;
        std::cout << "0.Új Felhasználó létrehozása" << std::endl;
        std::cout << "1.Bejelentkezés" << std::endl;
        std::cout << "2.Kilépés" << std::endl;

        std:: cin >> command;
        if(command >-1 && command < 3){
            switch (command) {
                case 0:
                    createProfile();
                    break;
                case 1:
                    menuRun = false;
                    break;
                case 2:
                    programRun = false;
                    break;
            }
        }
    }

}

void Menu::createProfile(){

    String newName;
    std::cout << "Adjon meg egy felhasználó nevet:" << std::endl;
    std:: cin >> newName;

    if(userlist.getUserbyUsername(newName) == nullptr){
        String newPass;
        std::cout << "Adjon meg egy jelszót:" << std::endl;
        std:: cin >> newPass;
        User* newU;
        newU = new User(newName, newPass);
        userlist.add(newU);
        std::cout << "A profil létrejött" << std::endl;
    } else{
        std::cout << "Az adott névvel már létezik felhasználó" << std::endl;
    }
}
User* Menu::signIn(){
    String name;
    std::cout << "Adja meg a felhasználó nevét:" << std::endl;
    std:: cin >> name;

    User* currentUser = userlist.getUserbyUsername(name);
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