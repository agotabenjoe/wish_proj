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

    cout<<"1"<<endl;
    ///Ha nem létezik létrejön
    file = fopen(fileName.c_str(),"r");
    if(!file){
        cout<<"2"<<endl;
        fclose(file);
        file = fopen(fileName.c_str(), "w");
        fclose(file);
    }

    file = fopen(fileName.c_str(),"r");
    cout<<"3"<<endl;

    bool beenEOF = false;

    enum state{
        reading,
        newuser,
        waiforusername,
        username,
        waitforpassword,
        password,
        friends,
        newfriend,
        friendrequests,
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

    char ch;

    state = reading;
    while ((ch = fgetc(file)) != EOF){
        /*if(file.eof()){
            beenEOF = true;
        }
        file >> ch;
        //cout<<ch;*/



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
                    state = waitforpassword;
                    ///TODO: setUsername
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
                    state = friends;
                    ///TODO: setPassword
                }
                else {
                    if(ch != '\"')
                        if(ch != ' ')
                            pass = pass + ch;
                }
                break;
            case friends:
                nFriend = "";
                if(ch == ','  || ch== '[')
                    state = newfriend;
                else if(ch == ']')
                    state = friendrequests;
                break;
            case newfriend:
                if(ch == ','){
                    newUser->addFriend(nFriend);
                    state = friends;
                }
                else {
                    if(ch != '\"')
                        if(ch != ' ')
                            nFriend = nFriend + ch;
                }
                break;
            case friendrequests:
                request = "";
                if(ch == ','  || ch== '[')
                    state = newfriendrequests;
                else if(ch == ']')
                    state = wish;
                break;
            case newfriendrequests:
                if(ch == ','){
                    newUser->addFriendRequest(request);
                    state = friendrequests;
                }
                else {
                    if(ch != '\"')
                        if(ch != ' ')
                            request = request + ch;
                }
                break;
            case wish:
                nWish = "";
                if(ch == ','  || ch== '[')
                    state = newwish;
                else if(ch == ']')
                    state = gift;
                break;
            case newwish:
                if(ch == ','){
                    stringstream tmp;
                    tmp << nWish;
                    int w;
                    tmp >> w;
                    newUser->addWish((w));
                    state = wish;
                }
                else {
                    if(ch != '\"')
                        if(ch != ' ')
                            nWish = nWish + ch;
                }
                break;
            case gift:
                nGift = "";
                if(ch == ','  || ch== '[')
                    state = newgift;
                else if(ch == ']')
                    state = reading;
                break;
            case newgift:
                if(ch == ','){
                    stringstream tmp;
                    tmp << nGift;
                    int g;
                    tmp >> g;
                    newUser->addGift((g));
                    state = gift;
                }
                else {
                    if(ch != '\"')
                        if(ch != ' ')
                            nGift = nGift + ch;
                }
                break;
        }
        
    }

    fclose(file);
    return users;
}