#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Playlist.h"
#include "Genre.h"

using namespace std;

int main() 
{
    Playlist p;
    p.add("Song 2", 0, 1, 55, "rp", "song2.dat");
    p.add("Song 1", 0, 1, 5, "p", "song1.dat");
    p.add("Song 3", 0, 2, 56, "je", "song3.dat");

    std::cout << "Playlist:" << endl;
    p.print();
    std::cout << endl;

    p.sortBy(SortBy::name);
    std::cout << "Sorted by name:" << endl;
    p.print();
    std::cout << endl;

    std::cout << "Searching for Song 1:" << endl;
    p.find(SearchBy::name, "Song 1");
    std::cout << endl;

    std::cout << "Searching for genre 'p':" << endl;
    Playlist popSongs = p.find(SearchBy::genre, "p");
    std::cout << endl;

    p.mix("Song 3", 3);
    std::cout << "Saving modified Song 3:" << endl;
    p.save("Song 3", "song5.dat");
    std::cout << endl;

    std::cout << "Mixing Song 1 with Song 2:" << endl;
    p.mix("Song 1", "Song 2");
    std::cout << endl;

    std::cout << "Saving modified Song 1:" << endl;
    p.save("Song 1", "song4.dat");
    std::cout << endl;

    return 0;
}
