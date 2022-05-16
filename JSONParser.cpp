#pragma once
#define MEMTRACE

#include <iostream>
#include <sstream>
#include <fstream>
#include "UserList.hpp"
#include "WishList.hpp"
#include "JSONParser.hpp"

using namespace std;
using std::ifstream;


UserList JSONParser::readUserData() {

    ///Ha nem létezik létrejön
    file = fopen(fileName.c_str(),"r");
    if(!file){
        fclose(file);
        file = fopen(fileName.c_str(), "w");
        fclose(file);
    }

    file = fopen(fileName.c_str(),"r");

    enum state{
        reading,
        newuser,
        waiforusername,
        username,
        waitforpassword,
        password,
        friends,
        friendsmiddle,
        newfriend,
        friendrequests,
        friendrequestsmiddle,
        newfriendrequests,
        wish,
        newwish,
        gift,
        newgift
    }state;

    UserList users;
    User* newUser;

    String uname;
    String pass;
    String nFriend;
    String request;
    String nWish;
    String nGift;

    int len =  0;

    char ch;
    state = reading;
    while ((ch = fgetc(file)) != EOF){
        switch (state) {
            case reading:
                if(ch == '{')
                    state = newuser;
                break;
            case newuser:
                    newUser = new User;
                    users.add(newUser);
                    state = waiforusername;
                break;
            case waiforusername:
                uname = "";
                if(ch == ':')
                    state = username;
                break;
            case username:
                if(ch == ','){
                    newUser->setUsername(uname);
                    state = waitforpassword;
                }
                else {
                    if(ch != '\"')
                        if(ch != ' ')
                            uname = uname + ch;
                }
                break;
            case waitforpassword:
                pass = "";
                if(ch == ':')
                    state = password;
                break;
            case password:
                if(ch == ','){
                    newUser->sePassword(pass);
                    state = friends;
                }
                else {
                    if(ch != '\"')
                        if(ch != ' ')
                            pass = pass + ch;
                }
                break;
            case friends:
                len = 0;
                nFriend = "";
                if(ch == ','  || ch== '[')
                    state = newfriend;
                if(ch == ']')
                    state = friendrequests;
                break;
            case friendsmiddle:
                nFriend = "";
                if(ch == '"')
                    state=newfriend;
                break;
            case newfriend:
                if( ch == ']'){
                    if(len>0){
                        newUser->addFriend(nFriend);
                    }
                    state = friendrequests;
                } else
                if(ch == ','){
                    if(len>0){
                        newUser->addFriend(nFriend);
                    }
                    state = friendsmiddle;
                }
                else {
                    if(ch != '\"'){
                        if(ch != ' '){
                            len++;
                            nFriend = nFriend + ch;
                        }
                    }
                }
                break;
            case friendrequests:
                len = 0;
                request = "";
                if(ch == ','  || ch== '[')
                    state = newfriendrequests;
                else if(ch == ']')
                    state = wish;
                break;
            case friendrequestsmiddle:
                request = "";
                if(ch == '"')
                    state=newfriendrequests;
                break;
            case newfriendrequests:
                if( ch == ']'){
                    if(len>0){
                        newUser->addFriendRequest(request);
                    }
                    state = wish;
                }
                if(ch == ','){
                    if(len>0){
                        newUser->addFriendRequest(request);
                    }
                    state = friendrequestsmiddle;
                }
                else {
                    if(ch != '\"')
                        if(ch != ' '){
                            len++;
                            request = request + ch;
                        }
                }
                break;
            case wish:
                len = 0;
                nWish = "";
                if(ch == ','  || ch== '[')
                    state = newwish;
                else if(ch == ']')
                    state = gift;
                break;
            case newwish:
                if( ch == ']'){
                    if(len>0){
                        stringstream tmp;
                        tmp << nWish;
                        int w;
                        tmp >> w;
                        newUser->addWish((w));
                    }
                    state = gift;
                }
                if(ch == ','){
                    if(len>0){
                        stringstream tmp;
                        tmp << nWish;
                        int w;
                        tmp >> w;
                        newUser->addWish((w));
                    }
                    len = 0;
                    nWish = "";
                    state = newwish;
                }
                else {
                    if(ch != '\"')
                        if(ch != ' '){
                            len++;
                            nWish = nWish + ch;
                        }

                }
                break;
            case gift:
                len = 0;
                nGift = "";
                if(ch == ','  || ch== '[')
                    state = newgift;
                else if(ch == ']')
                    state = reading;
                break;
            case newgift:
                if( ch == ']'){
                    if(len >0){
                        stringstream tmp;
                        tmp << nGift;
                        int g;
                        tmp >> g;
                        newUser->addGift((g));
                    }
                    state = reading;
                }
                if(ch == ','){
                    if(len >0){
                        stringstream tmp;
                        tmp << nGift;
                        int g;
                        tmp >> g;
                        newUser->addGift((g));
                    }
                    len = 0;
                    nGift = "";
                    state = newgift;
                }
                else {
                    if(ch != '\"')
                        if(ch != ' '){
                            len++;
                            nGift = nGift + ch;
                        }

                }
                break;
        }


    }

    fclose(file);
    return users;
}

WishList JSONParser::readWishData()  {
    //Ha nem létezik létrejön
    file = fopen(fileName.c_str(),"r");
    if(!file){
        fclose(file);
        file = fopen(fileName.c_str(), "w");
        fclose(file);
    }

    file = fopen(fileName.c_str(),"r");


    enum state{
        reading,
        nwish,
        name,
        owner,
        giver,
        waitforname,
        waitforowner,
        waitforgiver,
        waitforname2,
        waitforowner2,
        waitforgiver2
    }state;

    WishList wishes;
    Wish* newWish;

    String n;
    String o;
    String g;
    int gLen = 0;

    char ch;
    state = reading;
    while ((ch = fgetc(file)) != EOF){

        switch (state) {
            case reading:
                if(ch == '{')
                    state = nwish;
                break;
            case nwish:
                newWish = new Wish;
                wishes.add(newWish);
                state = waitforname2;
                break;
            case waitforname2:
                if(ch == ':')
                    state = waitforname;
                break;
            case waitforname:
                n = "";
                if(ch == '"')
                    state = name;
                break;
            case name:
                if(ch == '"'){
                    newWish->setName(n);
                    state = waitforowner2;
                } else{
                    n = n + ch;
                }
                break;
            case waitforowner2:
                if(ch == ':')
                    state = waitforowner;
                break;
            case waitforowner:
                o = "";
                if(ch == '"')
                    state = owner;
                break;
            case owner:
                if(ch == '"'){
                    newWish->setOwner(o);
                    state = waitforgiver2;
                } else{
                    o = o + ch;
                }
                break;
            case waitforgiver2:
                if(ch == ':')
                    state = waitforgiver;
                break;
            case waitforgiver:
                g = "";
                gLen = 0;
                if(ch == '"')
                    state = giver;
                break;
            case giver:
                if(ch == '"'){
                    if(gLen > 0){
                        newWish->setGiver(g);
                    }
                    state = reading;
                } else{
                    gLen = gLen +1;
                    g = g + ch;
                }
                break;
        }
    }

    fclose(file);
    return wishes;
}

void JSONParser::writeUserData(UserList &users) {
    file = fopen(fileName.c_str(), "w");

    fprintf(file, "[\n");
    for (int i = 0; i < users.getLen()+1; ++i) {
        fprintf(file,"{\n\"username\": \"%s\",\n \"password\": \"%s\",\n", dynamic_cast<User*>(users[i])->getUsername().c_str(), dynamic_cast<User*>(users[i])->getPassword().c_str());

       fprintf(file,"\"friends\":[");
        for (int j = 0; j < dynamic_cast<User*>(users[i])->getFriends().getLen(); ++j) {
            if((dynamic_cast<User*>(users[i])->getFriends().getLen() - 1 )== j){
                fprintf(file,"\"%s\"", dynamic_cast<User*>(users[i])->getFriends()[j].c_str());
            }else{
                fprintf(file,"\"%s\", ", dynamic_cast<User*>(users[i])->getFriends()[j].c_str());
            }
        }
        fprintf(file,"]\n");

        fprintf(file,"\"friendrequests\":[");
        for (int j = 0; j < dynamic_cast<User*>(users[i])->getFriendRequests().getLen(); ++j) {
            if((dynamic_cast<User*>(users[i])->getFriendRequests().getLen() - 1 )== j){
                fprintf(file,"\"%s\"", dynamic_cast<User*>(users[i])->getFriendRequests()[j].c_str());
            }else{
                fprintf(file,"\"%s\", ", dynamic_cast<User*>(users[i])->getFriendRequests()[j].c_str());
            }
        }
        fprintf(file,"]\n");

        fprintf(file,"\"wish\":[");
        for (int j = 0; j < dynamic_cast<User*>(users[i])->getWishes().getLen(); ++j) {
            if((dynamic_cast<User*>(users[i])->getWishes().getLen() - 1 )== j){
                fprintf(file,"%d", dynamic_cast<User*>(users[i])->getWishes()[j]);
            }else{
                fprintf(file,"%d, ", dynamic_cast<User*>(users[i])->getWishes()[j]);
            }
        }
        fprintf(file,"]\n");

        fprintf(file,"\"gift\":[");
        for (int j = 0; j < dynamic_cast<User*>(users[i])->getGifts().getLen(); ++j) {
            if((dynamic_cast<User*>(users[i])->getGifts().getLen() - 1 )== j){
                fprintf(file,"%d", dynamic_cast<User*>(users[i])->getGifts()[j]);
            }else{
                fprintf(file,"%d, ", dynamic_cast<User*>(users[i])->getGifts()[j]);
            }
        }
        fprintf(file,"]\n");

        fprintf(file, "},\n");
    }
    fprintf(file, "]");
    fclose(file);
}

void JSONParser::writeWishData(WishList &wishes){
    file = fopen(fileName.c_str(), "w");

    fprintf(file, "[\n");

    for (int i = 0; i < wishes.getLen()+1; ++i) {
        if(dynamic_cast<Wish*>(wishes[i])->gotTaken()){
            fprintf(file,"{\n\"name\":\"%s\",\n\"owner\":\"%s\",\n\"giver\":\"%s\"\n},\n",  dynamic_cast<Wish*>(wishes[i])->getName().c_str(),dynamic_cast<Wish*>(wishes[i])->getOwner().c_str(),dynamic_cast<Wish*>(wishes[i])->getGiver().c_str());
        }else{
            fprintf(file,"{\n\"name\":\"%s\",\n\"owner\":\"%s\",\n\"giver\":\"\"\n},\n",  dynamic_cast<Wish*>(wishes[i])->getName().c_str(),dynamic_cast<Wish*>(wishes[i])->getOwner().c_str());
        }
    }
    fprintf(file, "]");
    fclose(file);

}