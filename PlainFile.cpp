#include "PlainFile.h"

#include <iostream>
#include <fstream>

PlainFile::PlainFile( string file_name, bool read_mode, bool write_mode, string file_content )
	: File ( file_name, read_mode, write_mode) , content(file_content)
{}

PlainFile::~PlainFile()
{
	//cout << "~PlainFile() 실행 " << endl;
}

void PlainFile::changeContent( string cont )
{
	content = cont;
}

void PlainFile::display() // 파일명, 접근권한, 파일내용
{
	char write_mode;
	char read_mode;
	read_mode = getReadMode() == true ? 'r' : NULL ;
	write_mode = getWriteMode() == true ? 'w' : NULL;
	cout << getName() << "  " << ((read_mode == 'r' || write_mode == 'w') ? "+" : "" )
			<< read_mode << write_mode <<"  "<< content << endl;
}

void PlainFile::saveToFile(ofstream& out,int level, string name, bool rMode, bool wMode, string content)
{
	level++;
	string mode = modeToString(rMode, wMode);
	out <<level<<'\t' << name <<'\t'<<mode<<'\t'<<content<<endl;
}

string PlainFile::getContent() const
{
	return content;
}