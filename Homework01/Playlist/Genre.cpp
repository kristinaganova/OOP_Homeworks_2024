#include "Genre.h"
#include <iostream>

Genre::Genre() = default;

Genre::Genre(char ch) : genreCode(ch) {}

Genre::Genre(const GenreType& type) : genreCode((char)(type)) {}

void Genre::addGenre(const GenreType& type)
{
    genreCode |= (char)(type);
}

void Genre::addGenre(char ch)
{
    switch (ch)
    {
    case 'r': addGenre(GenreType::r); break;
    case 'p': addGenre(GenreType::p); break;
    case 'h': addGenre(GenreType::h); break;
    case 'e': addGenre(GenreType::e); break;
    case 'j': addGenre(GenreType::j); break;
    default:
        std::cerr << "Error: Invalid genre character '" << ch << "'" << std::endl;
    }
}

bool Genre::hasGenre(const GenreType& type) const
{
    return (genreCode & (char)(type)) != 0;
}

bool Genre::hasGenre(char ch) const
{
    switch (ch)
    {
    case 'r': return hasGenre(GenreType::r);
    case 'p': return hasGenre(GenreType::p);
    case 'h': return hasGenre(GenreType::h);
    case 'e': return hasGenre(GenreType::e);
    case 'j': return hasGenre(GenreType::j);
    default:
        std::cerr << "Error: Invalid genre character '" << ch << "'" << std::endl;
        return false;
    }
}