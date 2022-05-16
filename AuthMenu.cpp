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
        if(command >-1 && command < 5){
            switch (command) {
                case 0:
                    wishesMenu();
                    break;
                case 1:
                    friends();
                    break;
                case 2:
                    friendRequests();
                    break;
                case 3:
                    requestFriendship();
                    break;
                case 4:
                    menuRun = false;
                    break;
            }
        }
    }

}

void AuthMenu::wishesMenu() {
    bool subMenu = true;
    while (subMenu){
        std::cout << "Kívánság menü" << std::endl;
        std::cout << "0.Új hozzáadás" << std::endl;
        std::cout << "1.Listázás" << std::endl;
        std::cout << "2.Szerkesztés" << std::endl;
        std::cout << "3.Törlés" << std::endl;
        std::cout << "4.Vissza" << std::endl;

        std:: cin >> command;
        if(command >-1 && command  < 5){
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
        currentUser->listFriends();

        int command2;
        std:: cin >> command2;
        int printed = 0;
        if(command2 == currentUser->getFriends().getLen()){
            subMenu = false;
        } else{
            ///i. barát kávánságainak kilistázása
            for (int j = 0; j < wishes.getWishbyOwner(currentUser->getFriends()[command2]).getLen(); ++j) {
                if(!(wishes.getWishbyOwner(currentUser->getFriends()[command2])[j]->gotTaken())){
                    std::cout<< j <<"."<<wishes.getWishbyOwner(currentUser->getFriends()[command2])[j]->getName()<<std::endl;
                    printed++; ///emiatt nincs külön függvényben
                }
            }
            if(printed > 0){
                int command3;
                std:: cin >> command3;
                ///j. kívánság a currentu giftjeihez adása és a kívánságnál beállít owner
                currentUser->addGift(users.getUserbyUsername(currentUser->getFriends()[command2])->getWishes()[command3]);
                wishes.getWishbyId(users.getUserbyUsername(currentUser->getFriends()[command2])->getWishes()[command3])->setGiver(currentUser->getUsername());
                std::cout << "Sikeres művelet:" << std::endl;
            }
        }
    }
}

void AuthMenu::friendRequests() {
    bool subMenu = true;
    while (subMenu) {
        currentUser->listFriendsRequests();

        int command2;
        std:: cin >> command2;
        int printed = 0;
        if(command2 == currentUser->getFriendRequests().getLen()){
            subMenu = false;
        } else{
            if(currentUser->getFriendRequests().getLen() > 0){
                users.getUserbyUsername(currentUser->getFriendRequests()[command2])->addFriend(currentUser->getUsername());
                currentUser->delFriendRequest(currentUser->getFriendRequests()[command2]);
                currentUser->addFriend(currentUser->getFriendRequests()[command2]);
                std::cout << "Sikeres művelet:" << std::endl;
            }
        }
    }
}

void AuthMenu::requestFriendship(){
    String newRequest;
    std::cin >> newRequest;
    if(users.getUserbyUsername(newRequest) == nullptr || currentUser->getFriends().isIn(newRequest)){
        std::cout << "A művelet sikertelen" << std::endl;
    } else{
        users.getUserbyUsername(newRequest)->addFriendRequest(currentUser->getUsername());
        std::cout << "A művelet sikeres" << std::endl;
    }
}

void AuthMenu::wishesAdd(){
    wishes.addFromConsole(currentUser);
}
void AuthMenu::wishesUpdate(){
    wishes.setNameFromConsole(currentUser);
}

void AuthMenu::wishesList() {
        std::cout << "Kívánságaim:" << std::endl;
        wishes.printWishMenu(currentUser);
}

void AuthMenu::wishesRemove(){
    wishes.deleteFromConsole(currentUser, &users);
}