#include "EasyString.h"
#include <string>
#include <locale>
#include <codecvt>
#include <Windows.h>

namespace EasyString {
	// 可直接使用 u8"這就是utf8" 了
	std::string stringwToUTF8(const std::wstring& str) {
		// 創建轉換器
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

		// 將 wstring 轉換為 string
		std::string utf8_str = converter.to_bytes(str);
		return utf8_str;
	}
	// 若常數，可直接使用 u8"這utf8中文"
	// 運作邏輯是，先將 ascii 轉為 unicode ， 再 unicode 轉為 utf8 ，再轉為 ascii 
	std::string stringToUTF8(const std::string& str) {
		// 計算轉換後需要的緩衝區大小
		int wideLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), NULL, 0);

		// 轉換為 UTF-16 編碼的字串
		wchar_t* wideStr = new wchar_t[wideLen + 1];
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), wideStr, wideLen);
		wideStr[wideLen] = 0;

		// 計算轉換後需要的緩衝區大小
		int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);

		// 轉換為 UTF-8 編碼的字串
		char* utf8Str = new char[utf8Len + 1];
		WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, utf8Len, NULL, NULL);
		utf8Str[utf8Len] = 0;

		// 釋放資源
		delete[] wideStr;

		return std::string(utf8Str);
	}
}
