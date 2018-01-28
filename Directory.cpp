#include "Directory.h"
#include <iostream>
#include <typeinfo>

Directory::Directory(string directory_name, bool read_mode, bool write_mode , Directory* high)
	: File(directory_name, read_mode, write_mode ),highRank(high){}

Directory::Directory(string directory_name, bool read_mode, bool write_mode)
	: File(directory_name, read_mode, write_mode ),highRank(NULL){}

Directory::~Directory()
{
	//cout << this->getName() <<"��Ʈ���� ���� " <<endl;
	vector<File*>::iterator iter;
	for ( iter = files.begin() ; iter < files.end() ; iter++ ){
		if( typeid( **iter ) == typeid( Directory ))
				delete static_cast<Directory*>( *iter );
			else if( typeid( **iter ) == typeid( PlainFile ))
				delete static_cast<PlainFile*>( *iter );
	}
}

void Directory::saveToFile(ofstream& out, string name, bool rMode, bool wMode)
{
	static int level = 0; // tree�������� level. root level = 1
	level++;
	string mode;
	mode = modeToString(rMode, wMode);
	out << level << '\t'<< '/' << getName()<<'\t'<< mode << endl;
	vector<File*>::iterator iter;
	for( iter = files.begin(); iter < files.end() ; iter++){
		if( typeid(**iter) == typeid( Directory ) ){
			Directory* ptr = static_cast<Directory*>(*iter);
			ptr->saveToFile(out,ptr->getName(), ptr->getReadMode(), ptr->getWriteMode());
		}
		else if( typeid(**iter) == typeid( PlainFile ) ){
			PlainFile* ptr = static_cast<PlainFile*>(*iter);
			ptr->saveToFile(out,level, ptr->getName(), ptr->getReadMode(), ptr->getWriteMode(), ptr->getContent());
		}
	}
	level--;
}

void Directory::createDir( string name, bool read_mode, bool write_mode)
{
	if(name == "." || name == "..")
		cout << "���丮 �������� : (�������� ���� �̸�)" <<endl;
	else{
		Directory* temp = new Directory( name, read_mode, write_mode, this );
		files.push_back(temp);
	}
}
void Directory::createFile( string name, bool read_mode, bool write_mode, string content )
{
	if(name == "." || name == "..")
		cout << "���� �������� : (�������� ���� �̸�)" <<endl;
	else{
		PlainFile* temp = new PlainFile( name, read_mode, write_mode, content );
		files.push_back(temp);
	}
}

void Directory::del( string name )
{
	vector<File*>::iterator iter;
	for ( iter = files.begin() ; iter < files.end() ; iter++ ){
		if( (*iter)->getName() == name ){
			if( typeid( **iter ) == typeid( Directory ))
				delete dynamic_cast<Directory*>( *iter );
			else if( typeid( **iter ) == typeid( PlainFile ))
				delete dynamic_cast<PlainFile*>( *iter );
			files.erase( iter );	
			cout << name << "���� �Ϸ�"<< endl;
			return;
		}
	}	
	cout << "���� ���� : ( " <<name << " )�� �������� �ʽ��ϴ�." << endl;
}

void Directory::display()
{
	if(files.size() == 0 )
		cout << "������ �Դϴ�."<< endl;
	else{
		vector<File*>::iterator iter;
		char write_mode;
		char read_mode;
		for( iter = files.begin() ; iter < files.end() ; iter++ ){
			read_mode = (*iter)->getReadMode() == true ? 'r' : NULL ;
			write_mode = (*iter)->getWriteMode() == true ? 'w' : NULL;
			cout << (*iter)->getName() << (typeid( **iter ) == typeid( Directory ) ? "/" : "" )<<"  " << ((read_mode == 'r' || write_mode == 'w') ? "+" : "" )
				<< read_mode << write_mode << endl;
		}
	}
}

File* Directory::findFile( string name )
{
	vector<File*>::iterator iter;
	for( iter = files.begin(); iter < files.end() ; iter++ ){
		if ( (*iter)->getName() == name )
			return *iter;
	}
	cout << "ã�� ���� : ( " <<name << " )�� �������� �ʽ��ϴ�." << endl; //�����޼���
	return NULL;
}

Directory* Directory::getHighRankDirectory() const
{
	return highRank;
}

bool Directory::checkNameOverlap( string name )
{
	vector<File*>::iterator iter;
	for ( iter = files.begin() ; iter < files.end() ; iter++){
		if((*iter)->getName() == name)
			return true;
	}

	return false;
}