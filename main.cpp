#include "FileSystem.h"
#include <iostream>
using namespace std;

int main(void)
{
	int mode;
	int select;
	do{
		cout << "파일관리 시스템"<<endl;
		cout << "Mode    : 1. Super user" << endl;
		cout << "Select  : 2. User" << endl;
		cout << "% ";
		cin >> select;
		switch(select){
		case 1:	mode = super_user; // enum {user = 0, super_user}
			break;
		case 2: mode = user;
			break;
		default:
			cout<<"잘못 입력하셨습니다."<< endl;
		}
	}while(select != 1 && select != 2);

	FileSystem system(mode);
	system.exe();
	return 0;
}