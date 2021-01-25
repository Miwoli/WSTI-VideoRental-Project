#pragma once
#include <string>
#include <vector>

class Model {
public:
	std::string modelToString();
	Model vectorOfStringsToModel(std::vector<std::string>);
};

