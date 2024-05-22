#pragma once
#include "Song.h"

enum class SortBy
{
    name, 
    duration
};

enum class SearchBy
{
    genre,
    name
};

class Playlist
{
private:
    Song songs[MAX_SONGS];
    unsigned songCount = 0;

public:
    Playlist();
    const Song* getSongs() const;
    const unsigned getSongsCount() const;
    int getSongIndexByName(const char* name) const;

    void add(const Song& song);
    void add(const char* name, int hours, int minutes, int seconds, const char* genre, const char* filename); 
    void print() const;
    void sortBy(const SortBy& sort);
    Playlist find(SearchBy searchBy, const char* query) const;
    void mix(const char* song1, const char* song2);
    void mix(const char* song1, int k);
    void save(const char* songName, const char* filename) const;

private:
    Playlist find(const char* query, bool (*condition)(const Song&, const char*)) const;
    void sortBy(bool(*isLess)(const Song& s1, const Song& s2));
};