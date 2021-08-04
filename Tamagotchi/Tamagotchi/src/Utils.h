#pragma once
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#pragma comment(lib, "User32.lib")
#include <comdef.h>

#include<iostream>
#include<vector>
#include <locale>
#include <codecvt>
#include <string>





std::vector<std::string> split(const std::string& txt, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    std::vector<std::string> strs;

    while (pos != std::string::npos)
    {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;
        pos = txt.find(ch, initialPos);
    }
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs;
}


std::string join(std::vector<std::string>& list, char ch)
{
    std::string str = "";
    std::string j(1, ch);

    for (size_t i = 0; i < list.size(); i++)
    {
        str += list[i];
        str += j;
    }
    return str;
}

struct DirectoryItem {
    std::string name;
    std::string alternateName;
    bool isFile;
    DWORD attributes;
    unsigned long  hightPart;
    unsigned long lowPart;
    FILETIME creation;
    FILETIME lastAccess;
    FILETIME lastWrite;
};

void readdir(std::string dir,std::vector<DirectoryItem>* items)
{
    WIN32_FIND_DATA ffd;
    //LARGE_INTEGER filesize;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring tmp(converter.from_bytes(dir));

    TCHAR* szDir = (wchar_t*)tmp.c_str();
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

    hFind = FindFirstFileW(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
    {

        return;
    }

    do
    {
        DirectoryItem item;
        item.name = converter.to_bytes(ffd.cFileName);
        item.alternateName = converter.to_bytes(ffd.cAlternateFileName);
        item.creation = ffd.ftCreationTime;
        item.lastAccess = ffd.ftLastAccessTime;
        item.lastWrite = ffd.ftLastWriteTime;
        item.lowPart = ffd.nFileSizeLow;
        item.hightPart = ffd.nFileSizeHigh;
        item.attributes = ffd.dwFileAttributes;

        if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            item.isFile = true;
        }else
        {
            item.isFile = false;
        }

        items->push_back(item);
    } while (FindNextFileW(hFind, &ffd) != NULL);

}

bool contains_list(std::vector<std::string> l1, std::vector<std::string> l2)
{
    for (size_t i = 0; i < l1.size(); i++)
    {
        for (size_t k = 0; k < l2.size(); k++)
        {
            if (l1[i] == l2[k])
            {
                l1.erase(l1.begin() + i);
                i--;
                break;
            }
        }
    }

    return !l1.size() ? true : false;
}