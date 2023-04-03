#include "EasyString.h"
#include <string>
#include <locale>
#include <codecvt>
#include <Windows.h>

//#include <fcntl.h>  // _O_U16TEXT
//#include <io.h>     // _setmode
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

	std::string stringwTostring(const std::wstring& str) {
		// 将 std::wstring 转换为 std::string
		std::wstring_convert<std::codecvt_byname<wchar_t, char, std::mbstate_t>> converter(new std::codecvt_byname<wchar_t, char, std::mbstate_t>(""));
		return converter.to_bytes(str); // path 變數內容是正確的，但 cout 到中文會斷掉了。

		// 将控制台代码页设置为 UTF-16
		// 變數內容是正確的，因此將 console 設定為 Unicode
		//_setmode(_fileno(stdout), _O_U16TEXT);
	}
}
