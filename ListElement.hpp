#pragma once
#define MEMTRACE
///TODO: másoló konstruktor, pointerrel megy?

class ListElement{
    int uid;
    static int newUid;
    ListElement* next; 

    public:
    /***
     * Konstruktor
     * @param newNext a listában a következő elemre mutató pointer
     *  ***/
    ListElement(ListElement* newNext):next(newNext){
        uid = newUid;
        newUid++;
    }

    ///Copy konstruktor
    ListElement(const ListElement& l);

    ///Copy konstruktor a leszármazottaknak
    ListElement(int id, ListElement* nxt);

    /***
     * Destruktor 
     * ***/
    virtual ~ListElement(){};

    /***
     * Getter
     * @return a listában a következő elemre mutató pointer
     * ***/
    ListElement* getNext() const ;
    
    /***
     * Getter
     * @return a lista elem egyedi azonosítója
     * ***/
    int getId() const ;

    /***
     * Setter: Beállít egy új következő listaelemet
     * @param newNext az új következő listaelemre mutató pointer
     * ***/
    void setNext(ListElement* newNext);

    
};