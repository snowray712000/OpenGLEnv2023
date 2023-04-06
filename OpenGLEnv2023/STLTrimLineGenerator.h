#pragma once
#include "EasyString.h"
#include <vector>
#include <unordered_map>

// TODO: 處理一組，用這個
void mainTrim(const stringT& path, const std::vector<stringT>& extensions);

class STLTrimLineGeneratorBatchFlow {
public:
	void main();
private:
	std::unordered_map<stringT, std::vector<stringT>> enumFilePair(const stringT& dir);
};