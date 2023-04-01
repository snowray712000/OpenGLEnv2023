#pragma once
#include <string>
#include <locale>
#include <codecvt>

namespace EasyString {

    // 成功. 且它是核心. 
    // 可直接使用 u8"這就是utf8" 了
    std::string stringwToUTF8(const std::wstring& str);

    // 若常數，可直接使用 u8"這utf8中文"
    // 運作邏輯是，先將 ascii 轉為 unicode ， 再 unicode 轉為 utf8 ，再轉為 ascii 
    std::string stringToUTF8(const std::string& str);

}