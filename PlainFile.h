#ifndef PLAIN_FILE_H
#define PLAIN_FILE_H

#include "File.h"

class PlainFile : public File
{
public:
	PlainFile( string , bool, bool, string );
	~PlainFile();
	void changeContent( string );
	virtual void display();
	void saveToFile(ofstream& ,int ,string, bool, bool, string);
	string getContent() const;
private:
	string content;
};

#endif