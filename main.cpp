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
///Konzolos működés
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

/***
 * User hozzáadása a UserListhez
 * @param u a UserList referenciája
 * @param name az új user neve
 * @param pass az új user jelszava
 * ***/
void addUser(UserList& u, char const *name, char const* pass){
    User* newUser = new User(String(name), String(pass));
    u.add(newUser);
}

/***
 * Wish hozzáadása a WishListhez
 * @param u a UserList referenciája
 * @param w a WishList referenciája
 * @param pass az új user jelszava
 * ***/
void addWish(UserList& u, WishList& w, char const *userName, String  wishName){
    Wish* newWish =  new Wish(wishName, userName);
    u.getUserbyUsername(userName)->addWish(newWish->getId());
    w.add(newWish);
}

/***
 * A user hozzáadás és wish hozzáadás sikerességének tesztelése
 * @param u a UserList referenciája
 * @param w a WishList referenciája
 * @param userName az új user neve
 * @param pass az új user jelszava
 * @param userWishes a kívánságok neveinek tömbje
 * ***/
void userAndWishTest(UserList& users, WishList& wishes,char const *userName, char const* pass, Array<String> userWishes){
    addUser(users, userName, pass);
    for (int i = 0; i < userWishes.getLen(); ++i) {
        addWish(users, wishes, userName, userWishes[i]);
        EXPECT_EQ(wishes.getWishbyOwner(userName)[i]->getId(), users.getUserbyUsername(userName)->getWishes()[i]) << userName <<" "<< userWishes[i] <<"rossz " << std::endl;
    }
}

///TODO:majd refactorolni kell és belerakni az arrayba mint tagfüggvény és templatesíteni kell
/***
 * Ellenőrzi, hogy egy String benne van- egy String tömben
 * @param a a tömb
 * @param str a String
 * ***/
bool isIn(Array<String> a, String str){
    for (int i = 0; i < a.getLen(); ++i) {
        if(a[i] == str){
            return true;
        }
    }
    return false;
}

/***
 * Teszteli, hogy két felhasználó barát e
 * @param users a UserList referenciája
 * @param requester a jelölő user username-e
 * @param accepter a fogadó user username-e
 * ***/
void friendTest(UserList& users,char const *requester, char const *accepter){

    User* rU = users.getUserbyUsername(requester);
    User* aU = users.getUserbyUsername(accepter);

    aU->addFriendRequest(requester);
    aU->addFriend(requester);
    rU->addFriend(accepter);

    EXPECT_TRUE(isIn(aU->getFriends(),requester)) << accepter << " " << requester << " barat rossz" << std::endl;
    EXPECT_TRUE(isIn(rU->getFriends(),accepter)) << requester << " " <<accepter << " barat rossz" << std::endl;
}

void giftingTest(UserList& users, WishList& wishes, char const *giver, char const *wisher){
    //keresse meg azt a wisht, amit még nem vesz senki és ajándékozza oda azt és teszteljen arra
    Array<Wish*> wisherWishes =  wishes.getWishbyOwner("Vader");

    bool foundUntaken = false;
    int idx = 0;
    while (wisherWishes[idx]->gotTaken()){
        idx++;
    }
    //ekkor meg van az első, aminek még nincs ajándékozva

    User* gU = users.getUserbyUsername(giver);
    User* wU = users.getUserbyUsername(wisher);

    gU->addGift(wisherWishes[idx]->getId());
    wisherWishes[idx]->setGiver(giver);

    ///TODO:tesztelés
    EXPECT_EQ(luke->getGifts()[0], wishes.getWishbyOwner("Han")[0]->getId()) << "Luke -> Han rossz" << std::endl;
}

int main(){

    UserList users;  //= userFile.readUserData();
    WishList wishes; //= wishFile.readWishData();

    //regisztráció és ajándékok hozzáadása
    TEST(Regisztralas, regisztralasESAjandekok){

        //Luke
        Array<String> lukeWish;
        lukeWish.add("fenykard");
        lukeWish.add("xWing");
        lukeWish.add("kopeny");
        lukeWish.add("robot");
        userAndWishTest(users, wishes,"Luke", "jelszo1234", lukeWish);


        //Obi-Wan
        Array<String> obiWish;
        obiWish.add("fenykard");
        obiWish.add("gyik");
        obiWish.add("hajo");
        obiWish.add("kopeny");
        userAndWishTest(users, wishes,"Obi-Wan", "hellothere", obiWish);

        //Yoda
        Array<String> yodaWish;
        yodaWish.add("haziko");
        userAndWishTest(users, wishes,"Yoda", "grammardoyoueven", yodaWish);

        //Han
        Array<String> hanWish;
        hanWish.add("Falcon");
        hanWish.add("blaster");
        hanWish.add("melleny");
        userAndWishTest(users, wishes,"Han", "IShotFirst", hanWish);

        //Leia
        Array<String> leiaWish;
        leiaWish.add("hope");
        leiaWish.add("blaster");
        userAndWishTest(users, wishes,"Leia", "alderaan", leiaWish);

        //Vader
        Array<String> vaderWish;
        vaderWish.add("Halalcsillag");
        vaderWish.add("sisak");
        vaderWish.add("fenykard");
        userAndWishTest(users, wishes,"Vader", "ahmmhmh", vaderWish);

        //userFile.writeUserData(users);
        //wishFile.writeWishData(wishes);
    } ENDM

    //Barát jelölések és elfogadások
    TEST(Baratok, jelolesekEsFogadasok){
        //JSONParser userFile = JSONParser(String("userfajl eleresi ut"));
        //JSONParser wishFile = JSONParser(String("wishfajl eleresi ut"));

        //UserList users = userFile.readUserData();
        //WishList wishes = wishFile.readWishData();

        ///Luke-Han-Leia-Obi-Yoda-Vader
        friendTest(users, "Luke", "Han");
        friendTest(users, "Luke", "Leia");
        friendTest(users, "Luke", "Obi-Wan");
        friendTest(users, "Luke", "Yoda");
        friendTest(users, "Luke", "Vader");

        ///Han-Leia
        friendTest(users, "Han", "Leia");

        ///Obi--Leia-Yoda
        friendTest(users, "Obi-Wan", "Leia");
        friendTest(users, "Obi-Wan", "Yoda");

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

        //Obi-Wan ajándékoz
        obi->addGift(yoda->getWishes()[0]);
        wishes.getWishbyOwner("Yoda")[0]->setGiver("Obi-Wan");

        EXPECT_EQ(obi->getGifts()[0], wishes.getWishbyOwner("Yoda")[0]->getId()) << "Obi -> Yoda  rossz" << std::endl;

        //Obi-Wan ajándékoz
        yoda->addGift(obi->getWishes()[1]);
        wishes.getWishbyOwner("Obi-Wan")[1]->setGiver("Yoda");

        EXPECT_EQ(yoda->getGifts()[0], wishes.getWishbyOwner("Obi-Wan")[1]->getId()) << "Yoda -> obi  rossz" << std::endl;


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


