﻿#include "EasyIO.h"
#include <Windows.h>
#include <Shlwapi.h> // // PathFileExists 加入 Shlwapi.h 標頭檔
#pragma comment (lib, "Shlwapi.lib") // 加入 Shlwapi.lib 庫文件
namespace EasyIO {
    // 注意: 當使用 windows api dialog 選取檔案時，也會切換 current directory。
    stringT getCurrentDirectory() {
        DWORD buflen = MAX_PATH + 1;
        TCHAR buf[MAX_PATH + 1];
        if (GetCurrentDirectory(buflen, buf) == 0) {
            // 获取失败，可以在此处添加错误处理代码
            return stringT();
        }
        return buf;
    }

    // windows 有時候會用到的，因為 windows 取得是回傳 \\ 而非 / 
    stringT replaceBackslashWithSlash(stringT str) {
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] == _T('\\')) {
                str.replace(i, 1, _T("/"));
            }
        }
        return str;
    }
    stringT getExecutableDirectory() {
        TCHAR buf[MAX_PATH + 1];
        if (GetModuleFileName(NULL, buf, MAX_PATH + 1) == 0) {
            // 获取失败，可以在此处添加错误处理代码
            return stringT();
        }
        stringT path = buf;
        size_t pos = path.find_last_of(_T("\\/"));
        if (pos != stringT::npos) {
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

    bool isPathExist(stringT path) {
        return PathFileExists(path.c_str());
    }

    // 辅助函数：分割路径字符串为路径名和目录名
    inline void RelativePathConvertor::splitPath(const stringT& path, stringT& dirname, stringT& filename) {
        size_t pos = path.find_last_of(_T('/'));
        if (pos == std::string::npos) {
            dirname = _T("");
            filename = path;
        }
        else {
            dirname = path.substr(0, pos);
            filename = path.substr(pos + 1);
        }
    }

    stringT RelativePathConvertor::makeRelativePath(const stringT& pathFull, stringT pathCurrentDirection) {
        if (pathCurrentDirection.empty()) {
            pathCurrentDirection = EasyIO::replaceBackslashWithSlash(EasyIO::getExecutableDirectory() + _T('/'));
        }

        stringT dirFull, dirCurr, fileFull, fileCurr;
        splitPath(pathFull, dirFull, fileFull);
        splitPath(pathCurrentDirection, dirCurr, fileCurr);

        // 按照目录深度分割路径
        std::vector<stringT> dirsFull, dirsCurr;
        stringstreamT ssFull(dirFull), ssCurr(dirCurr);
        stringT dir;
        while (std::getline(ssFull, dir, _T('/'))) {
            dirsFull.push_back(dir);
        }
        while (std::getline(ssCurr, dir, _T('/'))) {
            dirsCurr.push_back(dir);
        }

        // 找到共同的前缀路径
        size_t i = 0;
        while (i < dirsFull.size() && i < dirsCurr.size() && dirsFull[i] == dirsCurr[i]) {
            i++;
        }

        // 生成相对路径
        stringT pathRelative;
        for (size_t j = i; j < dirsCurr.size(); j++) {
            pathRelative += _T("../");
        }
        for (size_t j = i; j < dirsFull.size(); j++) {
            pathRelative += dirsFull[j] + _T("/");
        }
        pathRelative += fileFull;
        return pathRelative;
    }

}

