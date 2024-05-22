#include "Playlist.h"
namespace
{
    bool compareNames(const Song& s1, const Song& s2)
    {
        return strcmp(s1.getName(), s2.getName()) < 0;
    }

    bool compareDuration(const Song& s1, const Song& s2)
    {
        return s1.getDuration() < s2.getDuration();
    }
}

Playlist::Playlist() = default;

const Song* Playlist::getSongs() const
{
    return this->songs;
}

const unsigned Playlist::getSongsCount() const
{
    return this->songCount;
}

int Playlist::getSongIndexByName(const char* name) const
{
    if (!name)
    {
        std::cerr << "Error: Invalid name." << std::endl;
        return -1;
    }
    for (int i = 0; i < songCount; i++)
    {
        if (strcmp(songs[i].getName(), name) == 0)
            return i;
    }
    std::cout << "Not found" << std::endl;
    return -1;
}

void Playlist::add(const Song& song)
{
    if (songCount < MAX_SONGS)
    {
        songs[songCount++] = song;
    }
    else
        std::cerr << "Error: Maximum number of songs reached." << std::endl;
}

void Playlist::add(const char* name, int hours, int minutes, int seconds, const char* genre, const char* filename)
{
    if (!filename)
    {
        std::cout << "Error: Invalid file name" << std::endl;
        return;
    }
    if (songCount < MAX_SONGS) 
    {
        songs[songCount++] = Song(name, hours, minutes, seconds, genre, filename);
    }
    else 
        std::cerr << "Error: Maximum number of songs reached." << std::endl;
}

void Playlist::print() const 
{
    find("all", [](const Song& song, const char* name) -> bool{return true;});
}

void Playlist::sortBy(bool(*isLess)(const Song& s1, const Song& s2))
{
    for (int i = 0; i < songCount; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < songCount; j++)
        {
            if (isLess(songs[j], songs[minIndex]))
                minIndex = j;

        }
        if (i != minIndex)
            std::swap(songs[i], songs[minIndex]);
    }
}

void Playlist::sortBy(const SortBy& sort)
{
    switch (sort)
    {    
    case SortBy::name: sortBy(compareNames); break;
    case SortBy::duration: sortBy(compareDuration); break;
    default:
    {
        std::cout << "Error: Invalid sorting value";
        break;
    }
    }
}

Playlist Playlist::find(SearchBy searchBy, const char* query) const
{
    Playlist result;
    if(!query)
    {
        std::cerr << "Error: Invalid query:" << std::endl;
        return Playlist();
    }

    switch (searchBy)
    {
    case SearchBy::name:
        result = find(query, [](const Song& song, const char* name)
            { return strcmp(song.getName(), name) == 0; });

        break;
    case SearchBy::genre:
    {
        result = find(query, [](const Song& song, const char* genre)
            {
                while (*genre)
                {
                    if (!song.getGenre().hasGenre(*genre))
                        return false;
                    genre++;
                }
                return true;
            }
        );
        break;
    }
    default: std::cout << "Invalid searching value!" << std::endl; break;
    }

    return result;
}

Playlist Playlist::find(const char* query, bool (*condition)(const Song&, const char*)) const
{
    if (!query)
    {
        std::cerr << "Error: Invalid query." << std::endl;
        return Playlist();
    }

    Playlist result;
    for (int i = 0; i < songCount; i++)
    {
        if (condition(songs[i], query))
        {
            songs[i].print(); //for just using it like a void 
            result.add(songs[i]);
        }
    }

    return result;
}

void Playlist::mix(const char* song1, const char* song2)
{
    if (!song1 || !song2)
    {
        std::cerr << "Error: Invalid song name." << std::endl;
        return;
    }

    int index1 = getSongIndexByName(song1);
    int index2 = getSongIndexByName(song2);
    
    if (index1 != -1 && index2 != -1) 
    {
        songs[index1].mixContent(songs[index2]);
    }
    else 
        std::cerr << "Error: One or both songs not found." << std::endl;
}

void Playlist::mix(const char* song, int k)
{
    if (!song)
    {
        std::cerr << "Error: Invalid song name." << std::endl;
        return;
    }

    int songIndex = getSongIndexByName(song);
    if (songIndex != -1)
    {
        songs[songIndex].modifyContent(k);
    }
    else
        std::cerr << "Error: One or both songs not found." << std::endl;
}

void Playlist::save(const char* songName, const char* filename) const 
{
    if (!songName || !filename)
    {
        std::cerr << "Error: Invalid song name or filename" << std::endl;
        return;
    }
    for (int i = 0; i < songCount; i++) 
    {
        if (strcmp(songs[i].getName(), songName) == 0) 
        {
            songs[i].getContent().save(filename);
            std::cout << "Saved successfully!" << std::endl;
            return;
        }
    }
    std::cerr << "Error: Song not found." << std::endl;
}