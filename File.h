#ifndef FILE_H
#define FILE_H

#include <string>
using namespace std;

class File
{
public:
	File( string, bool, bool );
	~File();
	virtual void display() = 0;
	void changeMode( bool , bool);
	bool getReadMode() const;
	bool getWriteMode() const;
	string getName() const;
	string modeToString(bool , bool ) const;

private:
	bool readMode;
	bool writeMode;
	string name;
};

#endif