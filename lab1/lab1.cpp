#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;


struct Pipe {
	string name;
	int length;
};

void AddPipe() {
	vector <Pipe> pipeMas;
	int n;
	cin >> n;
	for (int i=0; i < n; i++) {
		string name;
		int length;
		cin >> name >> length;
		pipeMas.push_back({ name, length });
	}

	for (int i = 0; i< pipeMas.size();i++) {
		cout << "Название трубы: " << pipeMas[i].name << endl;
		cout << "Длина трубы: " << pipeMas[i].length << endl << endl;
	}
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	AddPipe();
	return 0;
}