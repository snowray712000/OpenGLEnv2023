#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <tchar.h>
#include "EasyString.h"

namespace EasyIO {
    // 注意: 當使用 windows api dialog 選取檔案時，也會切換 current directory。
    stringT getCurrentDirectory();
    // windows 有時候會用到的，因為 windows 取得是回傳 \\ 而非 / 
    stringT replaceBackslashWithSlash(stringT str);
    // 1. 結尾不會有 '/'。
    stringT getExecutableDirectory();
    // if (OpenFileDialog(nullptr, "XYZ or STL Files (*.xyz;*.stl)\0*.xyz;*.stl\0Xyz Files (*.xyz)\0*.xyz\0STL Files (*.stl)\0*.stl\0All Files (*.*)\0*.*\0", buf, MAX_PATH)) {
    // 太複雜，請用 OpenFileDialogEasy 或 OpenFileDialogEasyImage 等等
    bool OpenFileDialog(HWND hwnd, LPCTSTR filter, LPTSTR selectedFilePath, DWORD selectedFilePathLength);
    // 開啟對話方塊，選擇目錄。
    stringT OpenDirectoryDialog();
    bool isPathExist(stringT path);
    // _T("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0")
    // _T("txt")
    stringT SaveFileDialog(LPCTSTR filter, LPCTSTR defExt);
    void ListFilesRecursive(const stringT& path, std::vector<stringT>& files);

}
namespace EasyIO {
    inline stringT OpenFileDialogEasy(LPCTSTR filter) {
        TCHAR r2[MAX_PATH];
        bool r1 = OpenFileDialog(nullptr, filter, r2, MAX_PATH);
        if (r1 == false) {
            return stringT();
        }
        return stringT(r2);
    }
    inline stringT OpenFileDialogEasyImage() {
        LPCTSTR filter = _T("Image Files(*.bmp;*.jpg;*.jpeg;*.png;*.gif;*.ico;*.tiff;*.tif)\0*.bmp;*.jpg;*.jpeg;*.png;*.gif;*.ico;*.tiff;*.tif\0All Files(*.*)\0*.*\0");
        return OpenFileDialogEasy(filter);
    }
}


namespace EasyIO {
    class RelativePathConvertor {
        // 辅助函数：分割路径字符串为路径名和目录名
        void splitPath(const stringT& path, stringT& dirname, stringT& filename);
    public:
        // 1. 生成相对路径，注意，一定要 / 而不能 \\，可使用 replaceBackslashWithSlash 來處理
        // 2. 若參數 currect 沒傳，則用 exe 目前目錄
        // 3. 目前目錄，結尾需要 /
        stringT makeRelativePath(const stringT& pathFull, stringT pathCurrentDirection = _T(""));
        inline void useSample() {
            stringT pathFull = _T("/home/user/project/data/file.txt");
            stringT pathCurrentDirection = _T("/home/user/project/src/");
            stringT pathRelative = makeRelativePath(pathFull, pathCurrentDirection);
            // std::cout << pathRelative << std::endl;  // 输出 "../../data/file.txt"
        }
    };
}
