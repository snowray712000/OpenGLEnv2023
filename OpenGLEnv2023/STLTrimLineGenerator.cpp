#include "STLTrimLineGenerator.h"
#include <vector>
#include <unordered_map>
#include "EasyIO.h"
#include <algorithm> //any_of
#include <iostream>
#include <fstream>
 void STLTrimLineGeneratorBatchFlow::main() {
	auto dir = EasyIO::OpenDirectoryDialog();

	auto filePairs = enumFilePair(dir);
	for (auto& a1 : filePairs) {
		mainTrim(a1.first, a1.second);
	}
}

std::unordered_map<stringT, std::vector<stringT>> STLTrimLineGeneratorBatchFlow::enumFilePair(const stringT& dir) {
	std::vector<stringT> files;
	EasyIO::ListFilesRecursive(dir, files);

	// fullpathRemoveExtension [stl pts]
	std::unordered_map<stringT, std::vector<stringT>> groupByPath;
	for (auto& path : files) {
		stringT ext = EasyIO::getPathExtension(path);
		stringT na2 = stringT(EasyIO::getPathRemoveExtension(path).c_str()); // �|: �����n�N�䭫�s�����s�� string, �_�h���M���@�ˡA�o�|�Q�������P�C

		groupByPath[na2].push_back(ext);
	}
	return groupByPath;
}

// TODO: �B�z�@�աA�γo��
void mainTrim(const stringT& path, const std::vector<stringT>& extensions) {
	auto fnContainAny = [&](LPCTSTR ext) {
		return std::any_of(extensions.begin(), extensions.end(), [&](const stringT& a1) {return a1 == ext; });
	};

	if (fnContainAny(_T(".stl")) && fnContainAny(_T(".pts"))) {
		// �Ҥl�A�|�ϥΨ� .stl .pts
		std::cout << EasyString::toCout(path + _T(".stl")) << std::endl;
		std::cout << EasyString::toCout(path + _T(".pts")) << std::endl;


		// �Ҥl�A���X���G _result.pts
		stringT pathResult = path + _T("_result.pts");
		std::ofstream file;
		file.open(pathResult, std::ios::out | std::ios::binary);
		if (file.is_open()) {

			file.close();
		}
		else {
			std::cout << "file open failure \n" ;
		}

	}
}
