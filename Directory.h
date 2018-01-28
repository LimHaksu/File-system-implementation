#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "File.h"
#include <vector>
#include <fstream>
#include "PlainFile.h"

class Directory : public File
{
public:
	Directory ( string, bool, bool, Directory* );
	Directory ( string, bool, bool );
	~Directory ();
	void createDir( string, bool, bool );
	void createFile( string, bool, bool, string );
	void del( string );
	void saveToFile(ofstream& ,string, bool, bool);
	virtual void display();
	File* findFile( string );
	Directory* getHighRankDirectory() const;
	bool checkNameOverlap( string );

private:
	vector<File*> files;
	Directory* highRank;
};

#endif