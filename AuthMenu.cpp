#pragma once
#define MEMTRACE

#include <iostream>
#include "AuthMenu.hpp"

void AuthMenu::run(){
    menuRun = true;
    while (menuRun){
        std::cout << "Fő menü" << std::endl;
        std::cout << "0.Kívánságlistám" << std::endl;
        std::cout << "1.Barátaim" << std::endl;
        std::cout << "2.Jelölések" << std::endl;
        std::cout << "3.Barát hozzáadás" << std::endl;
        std::cout << "4.Kijelentkezés" << std::endl;

        std:: cin >> command;
        if(command >-1 && command < 4){
            switch (command) {
                case 0:
                    wishes();
                    break;
                case 1:
                    friends();
                    break;
                case 2:
                    friendRequests();
                    break;
                case 3:
                    addFriend();
                    break;
                case 4:
                    menuRun = false;
                    break;
            }
        }
    }

}

void AuthMenu::wishes() {
    bool subMenu = true;
    while (subMenu){
        std::cout << "Kívánságaim" << std::endl;
        std::cout << "0.Új hozzáadás" << std::endl;
        std::cout << "1.Listázás" << std::endl;
        std::cout << "2.Szerkesztés" << std::endl;
        std::cout << "3.Törlés" << std::endl;
        std::cout << "4.Vissza" << std::endl;

        std:: cin >> command;
        if(command >-1 && command < 4){
            switch (command) {
                case 0:
                    wishesAdd();
                    break;
                case 1:
                    wishesList();
                    break;
                case 2:
                    wishesUpdate();
                    break;
                case 3:
                    wishesRemove();
                    break;
                case 4:
                    subMenu = false;
                    break;
            }
        }
    }
}

void AuthMenu::friends() {
    bool subMenu = true;
    while (subMenu){
    std::cout << "Barátaim" << std::endl;
    int i = 0;
    for (; i < currentUser.getFriends().getLen(); ++i) {
        std::cout << i << "." << currentUser.getFriends()[i] << std::endl;
    }
    std::cout << ++i << ".Vissza" << std::endl;

    std:: cin >> command;

        if(command == i){
            subMenu = false;
        } else {
            bool subSubMenu = true;
            while (subSubMenu){
                int j = 0;
            for (; j < wishlist.getWishbyOwner(currentUser.getFriends()[command]).getLen(); ++j) {
                if(!wishlist.getWishbyOwner(currentUser.getFriends()[command])[j]->gotTaken())
                    std::cout << j << "." << wishlist.getWishbyOwner(currentUser.getFriends()[command])[j] << std::endl;
            }
            std::cout << ++j << ".Vissza" << std::endl;
            int command2;
            std::cin >> command2;
            if (command2 == i) {
                subSubMenu = false;
            } else {
                wishlist.getWishbyOwner(currentUser.getFriends()[command])[command2]->setGiver(currentUser.getUsername());
                currentUser.addGift(wishlist.getWishbyOwner(currentUser.getFriends()[command])[command2]->getId());
                std::cout << "Sikeres művelet" << std::endl;

            }
        }

        }


    }
}

void AuthMenu::friendRequests() {}

void AuthMenu::addFriend(){

}

void AuthMenu::wishesAdd(){
    String newName;
    std::cout << "Adjon meg egy új kívánságot:" << std::endl;
    Wish* newW;
    newW = new Wish(newName,currentUser.getUsername());
    wishlist.add(newW);
    std::cout << "Sikeres művelet:" << std::endl;
}
void AuthMenu::wishesUpdate(){
    std:: cin >> command;
    String newName;
    std::cout << "Adjon meg egy új nevet:" << std::endl;
    std:: cin >> newName;
    wishlist.getWishbyId(currentUser.getWishes()[command])->setName(newName);
    std::cout << "Sikeres művelet:" << std::endl;
}

void AuthMenu::wishesList() {
        std::cout << "Kívánságaim" << std::endl;
        for (int i = 0; i < currentUser.getWishes().getLen(); ++i) {
            std::cout << i << "." << wishlist.getWishbyOwner(currentUser.getUsername())[i] << std::endl;
        }
}

void AuthMenu::wishesRemove(){
    std:: cin >> command;
    wishlist.remove(currentUser.getWishes()[command]);
    std::cout << "Sikeres művelet:" << std::endl;
}