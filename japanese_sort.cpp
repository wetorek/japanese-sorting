// Bartłomiej Mzyk- zadanie 2- część praktyczna
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

inline bool twoLetters (string s1, string s2, int iteratorS1, int iteratorS2, bool marker1, bool marker2);
inline bool twoDigits (string s1, string s2, int iteratorS1, int iteratorS2, bool marker1, bool marker2);

inline bool comparison (string s1, string s2, int counter1, int counter2, bool marker1, bool marker2)    // marker1 i marker2 patrzą czy wcześniej były dominujące zera w obu stringach
{
    if (counter1 == s1.length() && counter2 == s2.length())       // end of two strings
        return marker1;
    if (isalpha(s1[counter1]) && isalpha(s2[counter2])){                   // two letters
        return twoLetters(s1, s2, counter1, counter2, marker1, marker2);
    }
    else if (counter1 == s1.length())     // only one has ended
        return true;
    else if (counter2 == s2.length())
        return false;
    else if ( isalpha(s1[counter1]))
        return false;
    else if ( isalpha(s2[counter2]))
        return true;                           // two Digits
    else {
        return twoDigits(s1, s2, counter1, counter2, marker1, marker2);
    }
}
inline bool twoLetters (string s1, string s2, int iteratorS1, int iteratorS2, bool marker1, bool marker2)
{
    int j1 = iteratorS1;
    int j2 = iteratorS2;
    string substring1;
    string substring2;
    while ( j1 < s1.length() && isalpha(s1[j1])) {     // create a substring
        substring1 += s1[j1];
        j1++;
    }
    while ( j2 < s2.length() && isalpha(s2[j2])){
        substring2 += s2[j2];
        j2++;
    }

    if (substring1 < substring2)
        return true;
    else if (substring1 > substring2 )
        return false;
    else
        return comparison(s1, s2, j1,j2, marker1, marker2);
}
inline bool twoDigits (string s1, string s2, int iteratorS1, int iteratorS2, bool marker1, bool marker2)
{
    int zero1Counter = 0;
    int zero2Counter = 0;
    int i2 = iteratorS1;
    int j2 = iteratorS2;
    while (iteratorS1 < s1.length() && s1[iteratorS1++] == '0' )    // liczę zera z przodu
        zero1Counter++;
    while (iteratorS2 < s2.length() && s2[iteratorS2++] == '0' )
        zero2Counter++;

    string substring1;
    string substring2;
    iteratorS1 = i2;
    iteratorS2 = j2;
    while (iteratorS1 < s1.length() && !isalpha(s1[iteratorS1]))   // tworzę stringa bez zer z przodu, same cyfry
        substring1 += s1[iteratorS1++];
    while (iteratorS2 < s2.length() && !isalpha(s2[iteratorS2]))
        substring2 += s2[iteratorS2++];
    substring1 = substring1.substr(zero1Counter, substring1.length());
    substring2 = substring2.substr(zero2Counter, substring2.length());

    if (substring1.length() < substring2.length())
        return true;
    if (substring1.length() == substring2.length())         // kiedy nasze ciągi bez zer z przodu są równej długości
    {
        if (substring1 < substring2)
            return true;
        else if (substring1 > substring2)
            return false;
        else{
            if (zero1Counter > zero2Counter)      // w zależności od zer sprawdzam markery
                if (!marker2)
                    return comparison(s1, s2, iteratorS1, iteratorS2, true, false);
                else
                    return comparison(s1, s2, iteratorS1, iteratorS2, marker1, marker2);
            else if (zero1Counter < zero2Counter)
                if (!marker1)
                    return comparison(s1, s2, iteratorS1, iteratorS2, false, true);
                else
                    return comparison(s1, s2, iteratorS1, iteratorS2, marker1, marker2);
            else
                return comparison(s1, s2, iteratorS1, iteratorS2, marker1, marker2);
        }
    }
    else
        return false;

}

bool compareString ( string s1, string s2)
{
    return comparison(s1,s2,0,0, false, false );
}
int main()
{
    vector < string > dane;
    string linia = "";
    while ( getline (cin, linia))
    {
        dane.push_back (linia);
    }
    sort (dane.begin(), dane.end(), compareString);
    for ( int i = 0; i < (int) dane.size(); i++)
        cout << dane.at(i) << endl;

    return 0;
}
