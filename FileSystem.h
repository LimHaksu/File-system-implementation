#ifndef FILE_SYSTEM
#define FILE_SYSTEM

#include "File.h"
#include "Directory.h"
#include "PlainFile.h"

enum { user = 0, super_user };

class FileSystem{
public:
	FileSystem(int);
	void changeDirectory(string);
	void displayCWD( Directory* );
	void changeUserMode( int );
	void load();
	void save();
	void exe();
private:
	int user_mode;	
	Directory* root;
	Directory* cwd;

	void createRoot(ifstream&);
	int readOneLine(ifstream&, int);

	void newCom();
	void delCom();
	void mkdirCom();
	void dispCom();
	void chdirCom();
	void chmodCom();
	void chconCom();
	void cwdCom();
	void exitCom();

	void operandToAccessMode( string, bool&, bool& );
};

#endif