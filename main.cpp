#pragma once
#define MEMTRACE
#define MODE 2
///1 - menüvezérelt működés
///2 - teszt futtatása
///3 - fájlkezelés teszt

#include <iostream>
#include <sstream>
#include <clocale>

#include "gtest_lite.h"
#include "JSONParser.hpp"
#include "ListElement.hpp"
#include "List.hpp"
#include "UserList.hpp"
#include "WishList.hpp"


#if MODE == 1

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
}

#endif

#if MODE == 2
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
 * Teszteli, hogy két felhasználó barát-e
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

/***
 * Teszteli, hogy egy felhasználó ajándékoz-e egy másiknak
 * @param users a UserList referenciája
 * @param users a UserList referenciája
 * @param giver az ajándékozó user username-e
 * @param wisher az ajándékozott user username-e
 * ***/
void giftingTest(UserList& users, WishList& wishes, char const *giver, char const *wisher){
    Array<Wish*> wisherWishes =  wishes.getWishbyOwner(wisher);

    int idx = 0;
    while (wisherWishes[idx]->gotTaken()){
        idx++;
    }

    User* gU = users.getUserbyUsername(giver);
    User* wU = users.getUserbyUsername(wisher);

    gU->addGift(wisherWishes[idx]->getId());
    wisherWishes[idx]->setGiver(giver);

    EXPECT_EQ(gU->getGifts()[ gU->getGifts().getLen()-1], wU->getWishes()[idx]) << giver << " " << wisher << "rossz" << std::endl;
}

/***
 * Teszteli, hogy egy felhasználó törli az egyik kívánságát
 * @param users a UserList referenciája
 * @param users a UserList referenciája
 * @param giver az ajándékozó user username-e
 * @param wisher az a törlő user username-e
 * ***/
void delGiftTest(UserList& users, WishList& wishes, char const *wisher, int idx){
    User* wU = users.getUserbyUsername(wisher);
    int id =  wU->getWishes()[idx];
    wU->delWish(idx);

    Wish* wishToDel = wishes.getWishbyId(id);

    ///Csak akkor fut le ha már valaki veszi a kívánónak
    if(wishToDel->gotTaken()){
        String giver =  wishToDel->getGiver();
        User* gU = users.getUserbyUsername(giver);
        gU->delGiftById(id);
        EXPECT_FALSE(gU->getGifts().isIn(id)) << giver <<"-"<< wisher << "rossz 2" << std::endl;
    }
    wishes.remove(id);
    EXPECT_FALSE(wU->getWishes().isIn(id)) << wisher << "rossz 1" << std::endl;
}

int main(){



    ///regisztráció és ajándékok hozzáadása
    TEST(Regisztralas, regisztralasESAjandekok){
            JSONParser userFile("example.json");
            UserList users; //= userFile.readUserData();

            //JSONParser wishFile("wishes.json");
            WishList wishes; //= wishFile.readWishData();


        ///Luke
        Array<String> lukeWish;
        lukeWish.add("fenykard");
        lukeWish.add("xWing");
        lukeWish.add("kopeny");
        lukeWish.add("robot");
        userAndWishTest(users, wishes,"Luke", "jelszo1234", lukeWish);


        ///Obi-Wan
        Array<String> obiWish;
        obiWish.add("fenykard");
        obiWish.add("gyik");
        obiWish.add("hajo");
        obiWish.add("kopeny");
        userAndWishTest(users, wishes,"Obi-Wan", "hellothere", obiWish);

        ///Yoda
        Array<String> yodaWish;
        yodaWish.add("haziko");
        userAndWishTest(users, wishes,"Yoda", "grammardoyoueven", yodaWish);

        ///Han
        Array<String> hanWish;
        hanWish.add("Falcon");
        hanWish.add("blaster");
        hanWish.add("melleny");
        userAndWishTest(users, wishes,"Han", "IShotFirst", hanWish);

        ///Leia
        Array<String> leiaWish;
        leiaWish.add("hope");
        leiaWish.add("blaster");
        userAndWishTest(users, wishes,"Leia", "alderaan", leiaWish);

        ///Vader
        Array<String> vaderWish;
        vaderWish.add("Halalcsillag");
        vaderWish.add("sisak");
        vaderWish.add("fenykard");
        userAndWishTest(users, wishes,"Vader", "ahmmhmh", vaderWish);

            userFile.writeUserData(users);
            //wishFile.writeWishData(wishes);


    } ENDM

       ///Barát jelölések és elfogadások
       TEST(Baratok, jelolesekEsFogadasok){
           //JSONParser userFile = JSONParser(String("userfajl eleresi ut"));
           //JSONParser wishFile = JSONParser(String("wishfajl eleresi ut"));

           //UserList users = userFile.readUserData();
           //WishList wishes = wishFile.readWishData();
              JSONParser userFile("example.json");
               UserList users = userFile.readUserData();

               JSONParser wishFile("wishes.json");
               WishList wishes  = wishFile.readWishData();

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

               userFile.writeUserData(users);
               //wishFile.writeWishData(wishes);
       }ENDM
/*
      ///Ajándékok vásárlása
       TEST(Vasrlas, ajdekokVasarlasa){
           //JSONParser userFile = JSONParser(String("userfajl eleresi ut"));
           //JSONParser wishFile = JSONParser(String("wishfajl eleresi ut"));

           //UserList users = userFile.readUserData();
           //WishList wishes = wishFile.readWishData();

           ///Luke
           giftingTest(users, wishes, "Luke", "Han");
           giftingTest(users, wishes, "Luke", "Leia");
           giftingTest(users, wishes, "Luke", "Vader");

           ///Han
           giftingTest(users, wishes, "Han", "Leia");
           giftingTest(users, wishes, "Han", "Luke");

           ///Leia
           giftingTest(users, wishes, "Leia", "Han");
           giftingTest(users, wishes, "Leia", "Han");
           giftingTest(users, wishes, "Leia", "Luke");

           ///Vader
           giftingTest(users, wishes, "Vader", "Luke");

           ///Obi-Wan
           giftingTest(users, wishes, "Obi-Wan", "Yoda");

           ///Yoda
           giftingTest(users, wishes, "Yoda", "Obi-Wan");

           //userFile.writeUserData(users);
           //wishFile.writeWishData(wishes);
               userFile.writeUserData(users);

           }ENDM

       //Ajándékok törlése
       TEST(Torles, ajendekokTorlese){
           //JSONParser userFile = JSONParser(String("userfajl eleresi ut"));
           //JSONParser wishFile = JSONParser(String("wishfajl eleresi ut"));

           //UserList users = userFile.readUserData();
           //WishList wishes = wishFile.readWishData();

           ///Luke nem kér Vadertől
           delGiftTest(users, wishes, "Luke",0);

           ///Luke nem kér Hantól
           delGiftTest(users, wishes, "Luke", 0);

           ///Obi-Wan nem kér Yoda-tól
           delGiftTest(users, wishes, "Obi-Wan", 0);

           ///Leia nem kér Han-tól
           delGiftTest(users, wishes, "Leia", 1);

           ///Vader nem kér Luke-tól
           delGiftTest(users, wishes, "Vader", 0);

           ///Vader nem kér egyet
           delGiftTest(users, wishes, "Vader", 0);

           ///Vader nem kér egyet
           delGiftTest(users, wishes, "Vader", 0);

           //userFile.writeUserData(users);
           //wishFile.writeWishData(wishes);
       }ENDM
   */


    return  0;
}
#endif


#if MODE == 3
int main(){
    JSONParser wishFile("wishes.json");
    WishList wishes = wishFile.readWishData();

    std::cout << wishes.getWishbyId(0)->gotTaken() << std::endl;
    std::cout << wishes.getWishbyId(0)->getName()<< std::endl;
    std::cout << wishes.getWishbyId(0)->getOwner() << std::endl;
    std::cout << wishes.getWishbyId(0)->getGiver()<< std::endl;

    std::cout << wishes.getWishbyId(1)->gotTaken() << std::endl;
    std::cout << wishes.getWishbyId(1)->getName()<< std::endl;
    std::cout << wishes.getWishbyId(1)->getOwner() << std::endl;
    std::cout << wishes.getWishbyId(1)->getGiver()<< std::endl;

    std::cout << wishes.getWishbyId(2)->gotTaken() << std::endl;
    std::cout << wishes.getWishbyId(2)->getName()<< std::endl;
    std::cout << wishes.getWishbyId(2)->getOwner() << std::endl;
    //std::cout << wishes.getWishbyId(2)->getGiver()<< std::endl;



    return 0;
}

#endif