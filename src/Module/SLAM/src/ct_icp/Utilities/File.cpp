#include "File.h"


File::File(std::string path, openMode flag) : _path(path), _mode(flag)
{
	switch (_mode)
	{
	case fileOpenMode_IN:
	{
		_file = fstream(_path, ios::in | ios::binary);
		break;
	}
	case fileOpenMode_OUT:
	{
		_file = fstream(_path, ios::out | ios::binary);
		break;
	}
	}

	if(!_file.good())
	{
		cout << "ERROR: can't open " << _path << std::endl;
	}
}


File::~File()
{
	_file.close();
}
