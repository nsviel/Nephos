#pragma once

#include <iostream>
#include <string>
#include <fstream>


enum openMode{ fileOpenMode_OUT = 0, fileOpenMode_IN = 1 };

class File
{
public:
	File(std::string path, openMode flag);
	~File();


protected:
	const openMode _mode;
	string     _path;
	fstream    _file;
};
