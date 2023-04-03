#pragma once
#include <string>
#include <locale>
#include <codecvt>

#ifdef UNICODE
#ifndef stringT
#define stringT std::wstring
#define strlenT std::wcslen
#define stringstreamT std::wstringstream
#endif
#else
#ifndef stringT
#define stringT std::string
#define strlenT std::strlen
#define stringstreamT std::stringstream
#endif
#endif


namespace EasyString {

    // 成功. 且它是核心. 
    // 可直接使用 u8"這就是utf8" 了
    std::string stringwToUTF8(const std::wstring& str);

    // 若常數，可直接使用 u8"這utf8中文"
    // 運作邏輯是，先將 ascii 轉為 unicode ， 再 unicode 轉為 utf8 ，再轉為 ascii 
    std::string stringToUTF8(const std::string& str);

    // cout 遇到 wstring 時，遇到中文會斷掉
    // 雖然將 console視窗 設為 unicdoe 編碼可解決，但常用 cout 的人會出現異常
    // 因此還是不要把 console 視窗設為 unicdoe ，而是將 wstring 轉為 string
    std::string stringwTostring(const std::wstring& str);

}