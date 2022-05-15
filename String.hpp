#pragma once
#define MEMTRACE

#include <iostream>

class String
{
    char *pData; ///< pointer az adatra
    size_t len;  ///< hossz lezáró nulla nélkül
public:
    /// Kiírunk egy Stringet (debug célokra)
    /// Ezt a tagfüggvényt elkészítettük, hogy használja a hibák felderítéséhez.
    /// Igény szerint módosítható
    /// @param txt - nullával lezárt szövegre mutató pointer.
    ///              Ezt a szöveget írjuk ki a debug információ előtt.
    void printDbg(const char *txt = "") const
    {
        std::cout << txt << "[" << len << "], "
                  << (pData ? pData : "(NULL)") << '|' << std::endl;
    }

    void clearPdata()
    {
        delete[] pData;
    }

    void newPdata(size_t i)
    {
        pData = new char[i];
    }

    /// Az első két feladatot előre megoldottuk, de lehet, hogy nem jól.
    /// Az üres sztring reprezentációja nem szerencsés, mert így NULL pointerré
    /// konvertál a c_str(), ami külön kezelést igényel a későbbiekben.
    /// Ezt a teszt program sem fogadja el.
    /// Gondolja végig, és változtassa meg!
    /// Két lehetőség van:
    ///     a) nem NULL pointert tárol, hanem ténylegesen üres sztringet.
    ///     b) NULL-t tárol, de a c_str() üres sztringet ad vissza helyette
    /// Bármelyik megoldás jó, mert ez az osztály belügye.

    /// Paraméter nélküli konstruktor:
    String() : pData(0), len(0) {}

    /// Sztring hosszát adja vissza.
    /// @return sztring tényleges hossza (lezáró nulla nélkül).
    size_t size() const { return len; }

    /// C-sztringet ad vissza
    /// @return pointer a tárolt, vagy azzal azonos tartalmú nullával lezárt sztring-re.
    const char *c_str() const
    {
        if (len == 0)
        {
            return "";
        }
        else
        {
            return pData;
        }
    }
    /// Itt folytassa a tagfüggvények deklarációit a feladatoknak megfelelően.
    /// ...
    void setLen(int newLen)
    {
        len = newLen;
    }

    char* getPdata() const {
        return pData;
    }

    String(const char c);

    String(const char *c);

    String(const String &the_other);

    ~String();

    String &operator=(const String &the_other);

    String operator+(const String &rhs) const;

    String operator+(const char rhs) const;

    char &operator[](const size_t i);

    const char &operator[](const size_t i) const;

    bool operator==(const String &rhs) const;

    bool operator!=(const String &rhs) const;
    
}; /// Itt az osztály deklarációjának vége

String operator+(char c, const String &rhs);
/// Ide kerülnek a globális operátorok deklarációi.
/// ...
std::ostream& operator<<(std::ostream& os, String const& rhs);