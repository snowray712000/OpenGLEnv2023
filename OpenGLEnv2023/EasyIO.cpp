#include "EasyIO.h"
#include <Windows.h>
#include <Shlwapi.h> // // PathFileExists 加入 Shlwapi.h 標頭檔
#pragma comment (lib, "Shlwapi.lib") // 加入 Shlwapi.lib 庫文件
namespace EasyIO {
    // 注意: 當使用 windows api dialog 選取檔案時，也會切換 current directory。
    std::string getCurrentDirectory() {
        DWORD buflen = MAX_PATH + 1;
        char buf[MAX_PATH + 1];
        if (GetCurrentDirectoryA(buflen, buf) == 0) {
            // 获取失败，可以在此处添加错误处理代码
            return "";
        }
        return buf;
    }
    // windows 有時候會用到的，因為 windows 取得是回傳 \\ 而非 / 
    std::string replaceBackslashWithSlash(std::string str) {
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] == '\\') {
                str.replace(i, 1, "/");
            }
        }
        return str;
    }
    std::string getExecutableDirectory() {
        char buf[MAX_PATH + 1];
        if (GetModuleFileNameA(NULL, buf, MAX_PATH + 1) == 0) {
            // 获取失败，可以在此处添加错误处理代码
            return "";
        }
        std::string path = buf;
        size_t pos = path.find_last_of("\\/");
        if (pos != std::string::npos) {
            path = path.substr(0, pos);
        }
        return path;
    }

    // if (OpenFileDialog(nullptr, "XYZ or STL Files (*.xyz;*.stl)\0*.xyz;*.stl\0Xyz Files (*.xyz)\0*.xyz\0STL Files (*.stl)\0*.stl\0All Files (*.*)\0*.*\0", buf, MAX_PATH)) {
    bool OpenFileDialog(HWND hwnd, LPCTSTR filter, LPTSTR selectedFilePath, DWORD selectedFilePathLength)
    {
        OPENFILENAME ofn;
        TCHAR szFile[MAX_PATH] = { 0 };
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = hwnd;
        ofn.lpstrFilter = filter;
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
        if (GetOpenFileName(&ofn) == TRUE)
        {
            _tcscpy_s(selectedFilePath, selectedFilePathLength, szFile);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool isPathExist(std::string path) {
        return PathFileExistsA(path.c_str());
    }

    // 辅助函数：分割路径字符串为路径名和目录名
    inline void RelativePathConvertor::splitPath(const std::string& path, std::string& dirname, std::string& filename) {
        size_t pos = path.find_last_of('/');
        if (pos == std::string::npos) {
            dirname = "";
            filename = path;
        }
        else {
            dirname = path.substr(0, pos);
            filename = path.substr(pos + 1);
        }
    }

    std::string RelativePathConvertor::makeRelativePath(const std::string& pathFull, std::string pathCurrentDirection) {
        if (pathCurrentDirection.empty()) {
            pathCurrentDirection = EasyIO::replaceBackslashWithSlash(EasyIO::getExecutableDirectory() + '/');
        }

        std::string dirFull, dirCurr, fileFull, fileCurr;
        splitPath(pathFull, dirFull, fileFull);
        splitPath(pathCurrentDirection, dirCurr, fileCurr);

        // 按照目录深度分割路径
        std::vector<std::string> dirsFull, dirsCurr;
        std::stringstream ssFull(dirFull), ssCurr(dirCurr);
        std::string dir;
        while (std::getline(ssFull, dir, '/')) {
            dirsFull.push_back(dir);
        }
        while (std::getline(ssCurr, dir, '/')) {
            dirsCurr.push_back(dir);
        }

        // 找到共同的前缀路径
        size_t i = 0;
        while (i < dirsFull.size() && i < dirsCurr.size() && dirsFull[i] == dirsCurr[i]) {
            i++;
        }

        // 生成相对路径
        std::string pathRelative;
        for (size_t j = i; j < dirsCurr.size(); j++) {
            pathRelative += "../";
        }
        for (size_t j = i; j < dirsFull.size(); j++) {
            pathRelative += dirsFull[j] + "/";
        }
        pathRelative += fileFull;
        return pathRelative;
    }

}

