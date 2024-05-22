#pragma once

#include <cstdint>

enum class GenreType : char
{
    r = (1 << 0),
    p = (1 << 1),
    h = (1 << 2),
    e = (1 << 3),
    j = (1 << 4)
};

class Genre 
{
private:
    char genreCode = 0;

public:
    Genre();
    Genre(char ch);
    Genre(const GenreType& type);
    void addGenre(const GenreType& type);
    void addGenre(char ch);
    bool hasGenre(const GenreType& type) const;
    bool hasGenre(char ch) const;
};
