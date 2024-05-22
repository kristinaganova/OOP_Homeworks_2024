#pragma once
#include "GlobalConstants.h"

 class Content
{
    char content[MAX_CONTENT_LENGTH] = "";
    unsigned contentLength = 0;

public:
    Content();
    Content(const char* content, unsigned contentLength);

    void setContent(const char* content);
    void setContentLenght(unsigned contentLength);

    const char* getContent() const;
    int getContentLenght() const;

    void transformEachKthBitToOne(int k);
    void mixContent(const Content& other);
    void save(const char* filename) const;
    void readContent(const char* filename);
};
