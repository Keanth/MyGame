#include "stdafx.h"
#include "IOManager.h"
#include <fstream>

int IOManager::AppendToFile(std::string fileName, std::string data)
{
	std::ofstream LOG(fileName, std::ios::app);
	if (LOG.fail())
	{
		return 1;
	}

	LOG << data << std::endl;

	return 0;
}