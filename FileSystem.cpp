#include "FileSystem.h"

#include <typeinfo>
#include <iostream>
#include <fstream>

#define CHECK_W_MODE(ptr) if(user_mode != super_user && ptr->getWriteMode() == false){ \
			cout << "���� ������ �����ϴ�." << endl; \
        }else

#define CHECK_R_MODE(ptr) if(user_mode != super_user && ptr->getReadMode() == false){ \
			cout << "�б� ������ �����ϴ�." << endl;   \
		}else

#define CHECK_NAME_OVERLAP(name) if( cwd->checkNameOverlap( name ) == true ) \
				cout << "���丮 �ȿ� �̸��� ���� ������ �ֽ��ϴ�."<< endl;\
			else

FileSystem::FileSystem(int mode)
{
	load();
	user_mode = mode;	
}//,root("root", true, true ),cwd(&root){} // 

void FileSystem::changeDirectory( string name )
{
	if( name == ".." ){
		if( cwd == root )
			cout << "�ֻ��� ���丮�Դϴ�." << endl;
		else
			cwd = cwd->getHighRankDirectory();
	}else{
		File * temp = cwd->findFile( name );
		if( temp != NULL && typeid( *temp ) == typeid( Directory ) ){
			CHECK_R_MODE(temp)
				cwd = static_cast<Directory*>( temp );
		}
		else
			cout << name << " ���丮�� �������� �ʽ��ϴ�. " << endl;
	}
}

void FileSystem::displayCWD( Directory* temp)
{
	if( temp != root )
		displayCWD( temp->getHighRankDirectory() );
	cout << '/'<< temp->getName();
}

void FileSystem::changeUserMode ( int mode )
{
	user_mode = mode;
}


void FileSystem::save()
{
	ofstream file_save("_filesystem.dat");
	if(!file_save.is_open()) {		
		cout << "\"_filesystem.dat\" ���� ���� ����." << endl;
		exit(1);					
	}
	root->saveToFile(file_save,root->getName(),root->getReadMode(),root->getWriteMode());
	cout << "\"_filesystem.dat\" ���� �Ϸ�"<< endl;
	file_save.close();
}
void FileSystem::load()
{
	user_mode = super_user;
	ifstream file_open("_filesystem.dat");
	if(!file_open.is_open()) {		
		cout << "\"_filesystem.dat\" ������ �����ϴ�." << endl;
		cout << "root ���丮 ����" <<endl;
		root = new Directory( "root", true, true );
	}
	else{
		createRoot(file_open);
		int pre = 1;
		while( !file_open.eof() ){
			pre = readOneLine(file_open, pre);
		}
		file_open.close();
		cout << "\"_filesystem.dat\" �ҷ����� �Ϸ�"<< endl;
	}
	cwd = root;
}

void FileSystem::createRoot(ifstream& in)
{
	int level;
	string name;
	string mode;
	bool read_mode;
	bool write_mode;
	in >> level >> name >> mode;
	operandToAccessMode( mode, read_mode, write_mode );
	//name.erase(0,1);
	name = name.substr(1);
	root = new Directory( name, read_mode, write_mode );
	cwd = root;
}

int FileSystem::readOneLine(ifstream& in, int pre_level)
{
	int level;
	string name;
	string mode;
	string content;
	bool read_mode;
	bool write_mode;
	if( in >> level ){
		in >> name >> mode;
		operandToAccessMode( mode, read_mode, write_mode);
		if ( name[0] == '/' ){
			name = name.substr(1);
			//Directory* new_dir = new Directory( name, read_mode, write_mode, cwd->getHighRankDirectory() ) ;
			if( pre_level >= level )
				for( int temp = pre_level ; temp >= level; temp--)
					cwd = cwd->getHighRankDirectory();
			cwd->createDir( name, read_mode, write_mode );
			changeDirectory( name );
		}
		else{
			in >> content;
			if( pre_level >= level )
				for( int temp = pre_level ; temp >= level; temp--)
					cwd = cwd->getHighRankDirectory();
			cwd->createFile( name, read_mode, write_mode, content );
			level--;
		}
	}
	return level;
}
	
	
void FileSystem::exe()
{
	while(1){
		string command;
		cout << "% ";
		cin >> command;
		if( command == "new" ){
			newCom();
		}
		else if( command == "del" ){
			delCom();
		}
		else if( command == "mkdir" ){
			mkdirCom();
		}
		else if( command == "disp" ){
			dispCom();
		}
		else if( command == "chdir" ){
			chdirCom();
		}
		else if( command == "chmod" ){
			chmodCom();
		}
		else if( command == "chcon" ){
			chconCom();
		}
		else if( command == "cwd" ){
			cwdCom();
		}
		else if( command == "exit"){
			exitCom();
			return;
		}else{
			cout << "��ɾ �߸� �Է��ϼ̽��ϴ�." <<endl;
			cin.clear();
			cin.ignore( cin.rdbuf()->in_avail() );
		}
	}
}

void FileSystem::newCom()
{
	string first_op;
	string second_op;
	string third_op;
	bool read_mode;
	bool write_mode;
	cin >> first_op;
	if( first_op[0] == '+' ){
		operandToAccessMode( first_op, read_mode, write_mode );			
		cin >> second_op >> third_op;
		CHECK_W_MODE(cwd){
			CHECK_NAME_OVERLAP(second_op)
				cwd->createFile( second_op , read_mode, write_mode, third_op );				
		}
	}
	else{
		cin >> second_op;
		CHECK_W_MODE(cwd){
			CHECK_NAME_OVERLAP(first_op)
				cwd->createFile( first_op , true, true, second_op );
		}
	}
}

void FileSystem::delCom()
{
	string first_op;
	cin >> first_op;
	CHECK_W_MODE(cwd)
		cwd->del( first_op );
}

void FileSystem::mkdirCom()
{
	string first_op;
	string second_op;
	bool read_mode;
	bool write_mode;
	cin >> first_op;
	if( first_op[0] == '+' ){
		operandToAccessMode( first_op, read_mode, write_mode );			
		cin >> second_op;
		CHECK_W_MODE(cwd){
			CHECK_NAME_OVERLAP(second_op)	
				cwd->createDir( second_op , read_mode, write_mode);
		}
	}
	else{
		CHECK_W_MODE(cwd){
			CHECK_NAME_OVERLAP(first_op)
				cwd->createDir( first_op , true, true );
		}
	}
}

void FileSystem::dispCom()
{
	string first_op;
	cin >> first_op;
	if( first_op == ".")
		cwd->display();
	else{
		File* file = cwd->findFile( first_op );
		if(file != NULL ){
			CHECK_R_MODE(file)
			//if( user_mode == super_user || file->getReadMode() == true )
				file->display();
			//else
			//	cout << file->getName() << " ���� �б� ������ �����ϴ�." << endl;
		}
	}
}

void FileSystem::chdirCom()
{
	string first_op;
	cin >> first_op;
	changeDirectory( first_op );
}

void FileSystem::chmodCom()
{
	string first_op;
	string second_op;
	bool read_mode;
	bool write_mode;

	cin >> first_op >> second_op;
	if( first_op[0] == '+' ){
		operandToAccessMode ( first_op, read_mode, write_mode );
		CHECK_W_MODE(cwd){ // CWD�� ������� Ȯ��
			File* filePtr = cwd->findFile( second_op );
			if( filePtr != NULL )
				CHECK_W_MODE(filePtr){ // file�� ������� Ȯ��
					filePtr->changeMode( read_mode, write_mode );
			}
		}
	}else
		cout << "��ɾ� ������ �߸��Ǿ����ϴ�." << endl;
}

void FileSystem::chconCom()
{
	string first_op;
	string second_op;
	cin >> first_op >> second_op;
	CHECK_W_MODE(cwd) // CWD�� ������� Ȯ��
	{
		File* filePtr = cwd->findFile( first_op );
		if( filePtr != NULL){
		//if(user_mode == super_user || filePtr->getWriteMode() == true)
		CHECK_W_MODE(filePtr) // file�� ������� Ȯ��
			static_cast<PlainFile*>(filePtr)->changeContent(second_op);
		//else
			//cout << filePtr->getName() <<" ���� ��������� �����ϴ�." << endl;
		}
	}
}

void FileSystem::cwdCom()
{
	displayCWD( cwd );
	cout<< endl;
}

void FileSystem::exitCom()
{
	save();
}

void FileSystem::operandToAccessMode( string operand, bool& r_mode, bool& w_mode )
{
	if( operand.length() > 1){
		if( operand[1] == 'r' ){
			r_mode = true;
			if( operand.length() == 3){
				if( operand[2] == 'w')
					w_mode = true;
				else
					w_mode = false;
			}
			else
				w_mode = false;
		}
		else if( operand[1] == 'w'){
			if (operand.length() == 3){
				if( operand[2] == 'r')
					r_mode = true;
			}
			else{
				r_mode = false;
				w_mode = true;
			}
		}
		else{
			r_mode = false;
			w_mode = false;
		}
	}
	else{
		r_mode = false;
		w_mode = false;
	}
}

