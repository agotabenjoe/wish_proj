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
                    menuRun = false;
                    programRun = false;
                    break;
            }
        }
    }

}

void Menu::createProfile(){
    users.userFromConsole();
}
User* Menu::signIn(){
    return users.signInFromConsole();
}