#include "Song.h"
#pragma warning (disable:4996)

Song::Song(const char* name, int hours, int minutes, int seconds, const char* genre, const char* filename)
    : duration(hours, minutes, seconds), content() 
{
    setName(name);
    setGenre(genre);
    setContent(filename);
}

Song::Song() = default;

void Song::modifyContent(int k)
{
    this->content.transformEachKthBitToOne(k);
}

void Song::mixContent(const Song& other)
{
    this->content.mixContent(other.content);
}

void Song::print() const
{
    std::cout << name << ":" << std::endl;
    duration.serialize(std::cout);

    if (genre.hasGenre((GenreType)(1 << 0))) std::cout << "Rock ";
    if (genre.hasGenre((GenreType)(1 << 1))) std::cout << "Pop ";
    if (genre.hasGenre((GenreType)(1 << 2))) std::cout << "Hip-hop ";
    if (genre.hasGenre((GenreType)(1 << 3))) std::cout << "Electronic ";
    if (genre.hasGenre((GenreType)(1 << 4))) std::cout << "Jazz ";
    std::cout << std::endl;
}

void Song::save(const char* filename) const
{
    if (!filename)
    {
        std::cerr << "Error: Invalid file name:" << filename << std::endl;
        return;
    }

    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to create file." << filename << std::endl;
        return;
    }

    file.write((const char*)&name, sizeof(name));
    content.save(filename);

    file.close();
}

const char* Song::getName() const
{
    return name;
}

int Song::getDuration() const
{
    return duration.getSecondsFromMidnight();
}

const Content& Song::getContent() const
{
    return this->content;
}

const Genre& Song::getGenre() const
{
    return this->genre;
}

void Song::setGenre(const char* genre)
{
    if (!genre)
        return;

    while (*genre)
    {
        this->genre.addGenre(*genre);
        genre++;
    }
}

void Song::setName(const char* name)
{
    if (!name)
    {
        std::cerr << "Error: Invalid name." << std::endl;
        return;
    }

    strcpy(this->name, name);
    this->name[strlen(name)] = '\0';
}

void Song::setContent(const Content& content)
{
    this->content = content;
}

void Song::setContent(const char* filename)
{
    if (!filename)
    {
        std::cerr << "Error: Invalid file name:" << filename << std::endl;
        return;
    }
    content.readContent(filename);
}

void Song::setTime(const Time& time)
{
    this->duration = time;
}