#pragma once
#define MEMTRACE

#include <iostream>
#include <sstream>
#include <clocale>

#include "gtest_lite.h"
#include "JSONParser.hpp"
#include "ListElement.hpp"
#include "List.hpp"
#include "UserList.hpp"
#include "WishList.hpp"



/*
Konzolus működés
int main(){
    bool programRun = true;

    JSONParser userFile = JSONParser("userfajl eleresi ut");
    JSONParser wishFile = JSONParser("wishfajl eleresi ut");

    UserList users = userFile.readUserData();
    WishList wishes = wishFile.readWishData();

    User currentUser;

    Menu welcomeMenu = Menu(wishes, users, programRun);

    while(programRun){
        welcomeMenu.run();
        currentUser = welcomeMenu.signIn();
        Menu mainMenu = AuthMenu(wishes, users, programRun, currentUser);
        mainMenu.run();
    }

    userFile.writeUserData(users);
    wishFile.writeWishData(wishes);
*/


///TODO: több felhasználó hozzáadása
///TODO: ostream operator javít

int main(){

    UserList users;  //= userFile.readUserData();
    WishList wishes; //= wishFile.readWishData();

    //regisztráció és ajándékok hozzáadása
    TEST(Regisztralas, regisztralasESAjandekok){
        //Luke
        User* luke = new User("Luke", "jelszo1234");
        users.add(luke);

        Wish* fenykard =  new Wish("fenykard", luke->getUsername());
        wishes.add(fenykard);

        luke->addWish(fenykard->getId());

        Wish* xWing =  new Wish("xWing", luke->getUsername());
        wishes.add(xWing);
        luke->addWish(xWing->getId());

        Wish* robot =  new Wish("robot", luke->getUsername());
        wishes.add(robot);
        luke->addWish(robot->getId());

        Wish* kopeny =  new Wish("kopeny", luke->getUsername());
        wishes.add(kopeny);
        luke->addWish(kopeny->getId());

        EXPECT_EQ(wishes.getWishbyOwner(luke->getUsername())[0]->getId(), fenykard->getId()) << "Luke Fenykard rossz " << std::endl;
        EXPECT_EQ(wishes.getWishbyOwner(luke->getUsername())[1]->getId(), xWing->getId()) << "Luke xWing rossz " << std::endl;
        EXPECT_EQ(wishes.getWishbyOwner(luke->getUsername())[2]->getId(), robot->getId()) << "Luke robot rossz " << std::endl;
        EXPECT_EQ(wishes.getWishbyOwner(luke->getUsername())[3]->getId(), kopeny->getId()) << "Luke kopeny rossz " << std::endl;

        //Obi-Wan
        User* obi = new User("Obi-Wan", "hellothere");
        users.add(obi);

        Wish* fenykard3 =  new Wish("fenykard", obi->getUsername());
        wishes.add(fenykard3);
        obi->addWish(fenykard->getId());

        Wish* gyik =  new Wish("gyik", obi->getUsername());
        wishes.add(gyik);
        obi->addWish(gyik->getId());

        Wish* hajo =  new Wish("hajo", obi->getUsername());
        wishes.add(hajo);
        obi->addWish(hajo->getId());

        Wish* kopeny3 =  new Wish("kopeny", obi->getUsername());
        wishes.add(kopeny3);
        obi->addWish(kopeny3->getId());

        EXPECT_EQ(wishes.getWishbyOwner(obi->getUsername())[0]->getId(), fenykard3->getId()) << "Obi Fenykard rossz " << std::endl;
        EXPECT_EQ(wishes.getWishbyOwner(obi->getUsername())[1]->getId(), gyik->getId()) << "Obi hajo rossz " << std::endl;
        EXPECT_EQ(wishes.getWishbyOwner(obi->getUsername())[2]->getId(), hajo->getId()) << "Obi kopeny rossz " << std::endl;


        //Yoda
        User* yoda = new User("Yoda", "grammardoyoueven");
        users.add(yoda);

        Wish* haziko =  new Wish("haziko", yoda->getUsername());
        wishes.add(haziko);
        obi->addWish(haziko->getId());


        EXPECT_EQ(wishes.getWishbyOwner(yoda->getUsername())[0]->getId(), haziko->getId()) << "Yoda haziko rossz " << std::endl;

        //Han
        User* han = new User("Han", "IShotFirst!");
        users.add(han); //új felhasználó hozzáadás (regisztráció)



        Wish* falcon = new Wish("Falcon", han->getUsername());
        wishes.add(falcon);
        han->addWish(falcon->getId());

        Wish* blaster = new Wish("blaster", han->getUsername());
        wishes.add(blaster);
        han->addWish(blaster->getId());

        Wish* melleny = new Wish("melleny", han->getUsername());
        wishes.add(melleny);
        han->addWish(melleny->getId());


        EXPECT_EQ(wishes.getWishbyOwner(han->getUsername())[0]->getId(), falcon->getId()) << "Han falcon rossz " << std::endl;
        EXPECT_EQ(wishes.getWishbyOwner(han->getUsername())[1]->getId(), blaster->getId()) << "Han blaster rossz " << std::endl;
        EXPECT_EQ(wishes.getWishbyOwner(han->getUsername())[2]->getId(), melleny->getId()) << "Han melleny rossz " << std::endl;



        //Leia
        User* leia = new User("Leia", "alderaan!");
        users.add(leia);

        Wish* hope = new Wish("hope", leia->getUsername());
        wishes.add(hope);
        leia->addWish(hope->getId());

        Wish* blaster2 = new Wish("blaster", leia->getUsername());
        wishes.add(blaster2);
        leia->addWish(blaster2->getId());

        EXPECT_EQ(wishes.getWishbyOwner(leia->getUsername())[0]->getId(), hope->getId()) << "Leia hope rossz " << std::endl;
        EXPECT_EQ(wishes.getWishbyOwner(leia->getUsername())[1]->getId(), blaster2->getId()) << "Leia blaster rossz " << std::endl;


        //Vader
        User* vader = new User("Vader", "hmmmmm");
        users.add(vader); //új felhasználó hozzáadás (regisztráció)

        Wish* halalcsillag = new Wish("Halalcsillag", vader->getUsername());
        wishes.add(halalcsillag);
        vader->addWish(halalcsillag->getId());

        Wish* sisak = new Wish("Sisak", vader->getUsername());
        wishes.add(sisak);
        vader->addWish(sisak->getId());

        Wish* fenykard2 = new Wish("Fenykard", vader->getUsername());
        wishes.add(fenykard2);
        vader->addWish(fenykard2->getId());


        EXPECT_EQ(wishes.getWishbyOwner(vader->getUsername())[0]->getId(), halalcsillag->getId()) << "Vader halalcsillag rossz " << std::endl;
        EXPECT_EQ(wishes.getWishbyOwner(vader->getUsername())[1]->getId(), sisak->getId())<< "Vader sisak rossz " << std::endl;
        EXPECT_EQ(wishes.getWishbyOwner(vader->getUsername())[2]->getId(), fenykard2->getId())<< "Vader fenykard rossz " << std::endl;

        //userFile.writeUserData(users);
        //wishFile.writeWishData(wishes);


    } ENDM



/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/





    //Barát jelölések és elfogadások
    TEST(Baratok, jelolesekEsFogadasok){
        //JSONParser userFile = JSONParser(String("userfajl eleresi ut"));
        //JSONParser wishFile = JSONParser(String("wishfajl eleresi ut"));

        //UserList users = userFile.readUserData();
        //WishList wishes = wishFile.readWishData();

        User* currentUser;

        //Luke
        currentUser = users.getUserbyUsername("Luke");

        currentUser->addFriendRequest("Han");
        currentUser->addFriendRequest("Leia");
        currentUser->addFriendRequest("Vader");

        EXPECT_EQ(currentUser->getFriends().getLen(), 0) << "Luke baratok rossz" << std::endl;

        //Han
        currentUser = users.getUserbyUsername("Han");

        currentUser->addFriend("Luke");
        currentUser->addFriendRequest("Leai");

        EXPECT_EQ(currentUser->getFriends().getLen(), 1) << "Han baratok rossz" << std::endl;
        EXPECT_TRUE(currentUser->getFriends()[0] == String("Luke")) << "Han Luke barat rossz" << std::endl;


        //Leia
        currentUser = users.getUserbyUsername("Leia");

        currentUser->addFriend("Han");
        currentUser->addFriend("Luke");

        EXPECT_EQ(currentUser->getFriends().getLen(), 2) << "Leia baratok rossz" << std::endl;
        EXPECT_TRUE(currentUser->getFriends()[0] == String("Han")) << "Leia Han barat rossz" << std::endl;
        EXPECT_TRUE(currentUser->getFriends()[1] == String("Luke")) << "Leia Luke barat rossz" << std::endl;

        //Vader
        currentUser = users.getUserbyUsername("Vader");

        currentUser->addFriend("Luke");
        currentUser->addFriendRequest("Leia");

        EXPECT_EQ(currentUser->getFriends().getLen(), 1) << "Vader baratok rossz" << std::endl;
        EXPECT_TRUE(currentUser->getFriends()[0] ==  String("Luke")) << "Vader Luke barat rossz" << std::endl;

        //Obi-Wan
        currentUser = users.getUserbyUsername("Obi-Wan");

        currentUser->addFriend("Luke");
        currentUser->addFriend("Leia");
        currentUser->addFriendRequest("Yoda");


        EXPECT_EQ(currentUser->getFriends().getLen(), 2) << "Obi-Wan baratok rossz" << std::endl;
        EXPECT_TRUE(currentUser->getFriends()[0] ==  String("Luke")) << "Obi-Wan Luke barat rossz" << std::endl;
        EXPECT_TRUE(currentUser->getFriends()[1] ==  String("Leia")) << "Obi Leia barat rossz" << std::endl;
        EXPECT_FALSE(currentUser->getFriends()[2] ==  String("Yoda")) << "Obi Yoda barat rossz" << std::endl;

        //Yoda
        currentUser = users.getUserbyUsername("Yoda");

        currentUser->addFriend("Luke");
        currentUser->addFriend("Obi-Wan");

        EXPECT_EQ(currentUser->getFriends().getLen(), 2) << " Yodabaratok rossz" << std::endl;
        EXPECT_TRUE(currentUser->getFriends()[0] ==  String("Luke")) << "Yoda Luke barat rossz" << std::endl;
        EXPECT_TRUE(currentUser->getFriends()[1] ==  String("Obi-Wan")) << "Yoda Obi  barat rossz" << std::endl;


        //userFile.writeUserData(users);
        //wishFile.writeWishData(wishes);


    }ENDM





    //Ajándékok vásárlása
    TEST(Vasrlas, ajdekokVasarlasa){
        //JSONParser userFile = JSONParser(String("userfajl eleresi ut"));
        //JSONParser wishFile = JSONParser(String("wishfajl eleresi ut"));

        //UserList users = userFile.readUserData();
        //WishList wishes = wishFile.readWishData();

        //először az ajándékozó megkapja az ajándék id-jéz
        //az ajándénál beállítjuk az ajándékozót

        User* luke;
        User* han;
        User* leia;
        User* vader;
        User* yoda;
        User* obi;

        luke = users.getUserbyUsername("Luke");
        han = users.getUserbyUsername("Han");
        leia = users.getUserbyUsername("Leia");
        vader = users.getUserbyUsername("Vader");
        yoda = users.getUserbyUsername("Yoda");
        obi = users.getUserbyUsername("Obi-Wan");


        //Luke ajandekoz
        luke->addGift(han->getWishes()[0]);
        wishes.getWishbyOwner("Han")[0]->setGiver("Luke");

        luke->addGift(leia->getWishes()[0]);
        wishes.getWishbyOwner("Leia")[0]->setGiver("Luke");

        luke->addGift(vader->getWishes()[0]);
        wishes.getWishbyOwner("Vader")[0]->setGiver("Luke");

        EXPECT_EQ(luke->getGifts()[0], wishes.getWishbyOwner("Han")[0]->getId()) << "Luke -> Han rossz" << std::endl;
        EXPECT_EQ(luke->getGifts()[1], wishes.getWishbyOwner("Leia")[0]->getId()) << "Luke -> Leia rossz" << std::endl;
        EXPECT_EQ(luke->getGifts()[2], wishes.getWishbyOwner("Vader")[0]->getId()) << "Luke -> Vader rossz" << std::endl;


        //Han ajandekoz
        han->addGift(luke->getWishes()[0]);
        wishes.getWishbyOwner("Luke")[0]->setGiver("Han");

        han->addGift(leia->getWishes()[1]);
        wishes.getWishbyOwner("Leia")[1]->setGiver("Han");


        EXPECT_EQ(han->getGifts()[0], wishes.getWishbyOwner("Luke")[0]->getId()) << "Han -> Luke rossz" << std::endl;
        EXPECT_EQ(han->getGifts()[1], wishes.getWishbyOwner("Leia")[1]->getId()) << "Han -> Leai  rossz" << std::endl;

        //Leia ajandekoz


        leia->addGift(han->getWishes()[1]);
        wishes.getWishbyOwner("Han")[1]->setGiver("Leia");

        leia->addGift(han->getWishes()[2]);
        wishes.getWishbyOwner("Han")[2]->setGiver("Leia");

        leia->addGift(luke->getWishes()[2]);
        wishes.getWishbyOwner("Luke")[2]->setGiver("Leia");


        EXPECT_EQ(leia->getGifts()[0], wishes.getWishbyOwner("Han")[1]->getId()) << "Han -> Leia 1 rossz" << std::endl;
        EXPECT_EQ(leia->getGifts()[1], wishes.getWishbyOwner("Han")[2]->getId()) << "Han -> Leai  2 rossz" << std::endl;

        //Vader ajandekoz
        vader->addGift(luke->getWishes()[3]);
        wishes.getWishbyOwner("Luke")[3]->setGiver("Vader");

        EXPECT_EQ(vader->getGifts()[0], wishes.getWishbyOwner("Luke")[3]->getId()) << "Vader -> Luke  rossz" << std::endl;





        //EXPECT_EQ(vader->getGifts()[0], wishes.getWishbyOwner("Luke")[2]->getId()) << "Vader -> Luke rossz" << std::endl;





        //userFile.writeUserData(users);
        //wishFile.writeWishData(wishes);
    }ENDM


    //Ajándékok törlése
    TEST(Torles, ajendekokTorlese){
        //JSONParser userFile = JSONParser(String("userfajl eleresi ut"));
        //JSONParser wishFile = JSONParser(String("wishfajl eleresi ut"));

        //UserList users = userFile.readUserData();
        //WishList wishes = wishFile.readWishData();


        User* luke;
        User* han;
        User* leia;
        User* vader;
        User* yoda;
        User* obi;

        luke = users.getUserbyUsername("Luke");
        han = users.getUserbyUsername("Han");
        leia = users.getUserbyUsername("Leia");
        vader = users.getUserbyUsername("Vader");
        yoda = users.getUserbyUsername("Yoda");
        obi = users.getUserbyUsername("Obi-Wan");


        //han nem vesz lukenak
        wishes.remove(luke->getWishes()[0]);
        luke->delWish(0);
        han->delGift(0);


        EXPECT_EQ(luke->getWishes().getLen(), 3) << "Han nem vesz Lukenak rossz 1" << std::endl;
        EXPECT_EQ(han->getGifts().getLen(), 1) << "Han nem vesz Lukenak rossz 2" << std::endl;


        //leia nem vesz han-nak
        wishes.remove(han->getWishes()[1]);
        han->delWish(1);
        leia->delGift(1);

        EXPECT_EQ(han->getWishes().getLen(), 2) << "Leia nem vesz Hannak rossz 1" << std::endl;
        EXPECT_EQ(leia->getGifts().getLen(), 2) << "Leia nem vesz Hannak rossz 2" << std::endl;



        //userFile.writeUserData(users);
        //wishFile.writeWishData(wishes);
    }ENDM

    return  0;
}

