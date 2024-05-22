#include "Content.h"
#include <iostream>
#include <fstream>
#pragma warning(disable:4996)

namespace
{
    size_t getFileSize(std::ifstream& f)
    {
        size_t currentPos = f.tellg();
        f.seekg(0, std::ios::end);
        size_t size = f.tellg();

        f.seekg(currentPos);
        return size;
    }
}

Content::Content() : Content("", 0) {}

Content::Content(const char* content, unsigned contentLength)
{
    setContentLenght(contentLength);
    setContent(content);
}

void Content::setContent(const char* content)
{
    if (!content)
    {
        std::cerr << "Error: Invalid value." << std::endl;
        return;
    }
    if (strlen(content) > MAX_CONTENT_LENGTH)
    {
        std::cerr << "Error: Max content length reached." << std::endl;
        return;
    }
    strcpy(this->content, content);
    this->content[contentLength] = '\0';
}

void Content::setContentLenght(unsigned contentLength)
{
    if (contentLength > MAX_CONTENT_LENGTH)
    {
        std::cerr << "Error: Max content length reached." << std::endl;
        return;
    }
    this->contentLength = contentLength;
}

const char* Content::getContent() const
{
    return this->content;
}

int Content::getContentLenght() const
{
    return this->contentLength;
}

void Content::transformEachKthBitToOne(int k)
{
    if (k < 0)
    {
        std::cerr << "Error: Invalid integer." << std::endl;
        return;
    }

    for (int i = 0; i < contentLength; i++)
    {
        for (int j = 0; j < MAX_BITS_IN_CHAR; j++)
        {
            if ((i * MAX_BITS_IN_CHAR + j + 1) % k == 0)
                content[i] ^= (1 << j); 
        }
    }
}

void Content::mixContent(const Content& other)
{
    int minSize = std::min(contentLength, other.contentLength);
    for (int i = 0; i < minSize; i++) 
        content[i] ^= other.content[i];
}

void Content::save(const char* filename) const
{
    if (!filename)
    {
        std::cerr << "Error: Invalid file name." << std::endl;
        return;
    }

    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to create file " << filename << std::endl;
        return;
    }

    file.write(content, contentLength);

    file.close();
}

void Content::readContent(const char* filename)
{
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    contentLength = getFileSize(ifs);
    ifs.read((char*)content, contentLength);
    content[contentLength] = '\0';

    ifs.close();
}