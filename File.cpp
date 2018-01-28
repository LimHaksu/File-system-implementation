#include "File.h"
#include <iostream>


File::File( string file_name, bool read_mode, bool write_mode ):name(file_name),readMode(read_mode),writeMode(write_mode)
{
}

File::~File()
{
	//cout << "~File() ½ÇÇà " << endl;
}

//void File::display(){}

void File::changeMode( bool read, bool write )
{
	readMode = read;
	writeMode = write;
}

string File::modeToString(bool rMode, bool wMode) const
{
	string mode;
	if(rMode == true){
		if(wMode == true)
			mode = "+rw";
		else
			mode = "+r";
	}
	else if(wMode == true)
		mode = "+w";
	else
		mode = "+";

	return mode;
}

bool File::getReadMode() const
{
	return readMode;
}

bool File::getWriteMode() const
{
	return writeMode;
}

string File::getName() const
{
	return name;
}
