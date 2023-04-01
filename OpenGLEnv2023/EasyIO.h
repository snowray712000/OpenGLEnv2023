#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <tchar.h>

namespace EasyIO {
    // 注意: 當使用 windows api dialog 選取檔案時，也會切換 current directory。
    std::string getCurrentDirectory();
    // windows 有時候會用到的，因為 windows 取得是回傳 \\ 而非 / 
    std::string replaceBackslashWithSlash(std::string str);
    // 1. 結尾不會有 '/'。
    std::string getExecutableDirectory();
    // if (OpenFileDialog(nullptr, "XYZ or STL Files (*.xyz;*.stl)\0*.xyz;*.stl\0Xyz Files (*.xyz)\0*.xyz\0STL Files (*.stl)\0*.stl\0All Files (*.*)\0*.*\0", buf, MAX_PATH)) {
    bool OpenFileDialog(HWND hwnd, LPCTSTR filter, LPTSTR selectedFilePath, DWORD selectedFilePathLength);
    bool isPathExist(std::string path);
}



namespace EasyIO {
    class RelativePathConvertor {
        // 辅助函数：分割路径字符串为路径名和目录名
        void splitPath(const std::string& path, std::string& dirname, std::string& filename);
    public:
        // 1. 生成相对路径，注意，一定要 / 而不能 \\，可使用 replaceBackslashWithSlash 來處理
        // 2. 若參數 currect 沒傳，則用 exe 目前目錄
        // 3. 目前目錄，結尾需要 /
        std::string makeRelativePath(const std::string& pathFull, std::string pathCurrentDirection = "");
        inline void useSample() {
            std::string pathFull = "/home/user/project/data/file.txt";
            std::string pathCurrentDirection = "/home/user/project/src/";
            std::string pathRelative = makeRelativePath(pathFull, pathCurrentDirection);
            // std::cout << pathRelative << std::endl;  // 输出 "../../data/file.txt"
        }
    };
}
