#pragma once
#include <string>
#include "net.h"

class FileSaver
{
public:
	static void saveToFile(const Net& net, const std::string& filename);
	static Net loadFromFile(const std::string& filename);
};