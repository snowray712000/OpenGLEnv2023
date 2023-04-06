#pragma once
#include "EasyString.h"
#include <vector>
#include <unordered_map>

// TODO: �B�z�@�աA�γo��
void mainTrim(const stringT& path, const std::vector<stringT>& extensions);

class STLTrimLineGeneratorBatchFlow {
public:
	void main();
private:
	std::unordered_map<stringT, std::vector<stringT>> enumFilePair(const stringT& dir);
};