#pragma once
#include"Time.h"
#include "Genre.h"
#include "Content.h"
#include<iostream>
#include<fstream>
#include "GlobalConstants.h"

class Song
{
private:
    char name[MAX_NAME_LENGTH] = "unknown";
    Time duration;
    Genre genre;
    Content content;
public:
    Song(const char* name, int hours, int minutes, int seconds, const char* genre, const char* filename);
    Song();  
    
    const char* getName() const;
    int getDuration() const;
    const Content& getContent() const;
    const Genre& getGenre() const;
    void setGenre(const char* genre);
    void setName(const char* name);
    void setContent(const Content& content);
    void setContent(const char* filename);
    void setTime(const Time& time);

    void modifyContent(int k);
    void mixContent(const Song& other);
    void print() const;
    void save(const char* filename) const;
};