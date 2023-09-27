#include <iostream>
#include <vector>
#include <Windows.h>
#include <winuser.h>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;


struct Pipe {
	string name;
	int length;
	int diameter;
	bool isWorking = true;
};

struct CS {
	string name;
	int wrkshopsCount;
	vector <bool> WS;
	float efficiency;
};

int Menu() {
	int number;
	std::cout << "\n1.Добавить трубу\n2.Добавить КС\n3.Список объектов\n4.Редактировать трубы\n5.Редактировать цеха\n6.Сохранить\n7.Загрузить\n0.Выход\n\n";
	std::cin >> number;
	return number;
}

void AddPipe(Pipe& pipe) {
	string name;
	int length;
	int diameter;
	cout << "Введите название, длину и ширину трубы:\n";
	cin >> name >> length >> diameter;
	pipe = { name, length,diameter, true };
}

void ViewPipes(Pipe pipe) {
	if (pipe.length > 0) {
		cout << "Название трубы: " << pipe.name << endl;
		cout << "Длина трубы: " << pipe.length << endl;
		cout << "Диаметр трубы: " << pipe.diameter << endl;
		if (pipe.isWorking)
			cout << "Состояние: ВКЛ." << endl;
		else
			cout << "Состояние: ВЫКЛ." << endl;
	}
}
void AddCS(CS& cs) {
	string name;
	int count;
	vector <bool> WSs;
	cout << "Ввидите название КС и число его цехов:\n";
	cin >> name >> count;
	if (count > 0) {
		for (int j=0; j < count; j++) {
			int n;
			cout << "\nСтанция работает исправно?\n\n1.Да\n2.Нет\n\n";
			cin >> n;
			if (n == 1) {
				WSs.push_back(true);
			}
			else if (n == 2) {
				WSs.push_back(false);
			}
			else {
				cout << "Неверно введен ответ";
				j--;
			}
		}
	}
	cs = { name, count, WSs, 100};
}

void ViewCSs(CS& cs) {
	if (cs.WS.size() != 0) {
		cout << "Название КС: " << cs.name << endl;
		cout << "Число Цехов: " << cs.wrkshopsCount << endl << endl;
		cout << "Эффективность КС: " << cs.efficiency << endl << endl;
		for (int j = 0; j < cs.WS.size(); j++) {
			if (cs.WS[j])
				cout << "\tЦех №" << j + 1 << "      " << "В рабочем состоянии" << endl;
			else
				cout << "\tЦех №" << j + 1 << "      " << "Не в рабочем состоянии" << endl;
		}
		cout << endl;
	}
}

void PipeChange(Pipe& pipe) {
	int n;
	cout << "Состояние:\n1.Работает\n2.Требуется ремонт\n";
	cin >> n;
	switch (n) {
		case 1:
			pipe.isWorking = true;
		case 2:
			pipe.isWorking = false;
	}
}

void CSChange(CS& cs) {
	int n;
	int w;
	string name;
	if (cs.wrkshopsCount > 0) {
		ViewCSs(cs);
		cout << "\n\tВыберете Цех для редактирования: ";
		cin >> w;
		if (cs.WS.size() < w) {
			cout << "\n\nOut of range\n\n";
		}
		else {
			if (cs.WS[w - 1])
				cs.WS[w - 1] = false;
			else
				cs.WS[w - 1] = true;
		}
	}
}

void SavePipesData(Pipe& pipe) {
	ofstream file;
	file.open("pipes.txt", fstream::in | ofstream::out);
	if (!file.is_open()) {
		system("cls");
		cout << "Ошибка чтения файла!";
	}
	if(pipe.length > 0 and pipe.diameter > 0) {
		file << pipe.name << " " << pipe.length << " " << pipe.diameter << " " << pipe.isWorking;
	}
	else {
		file << "pipe" << " " << 0 << " " << 0 << " " << 1;
	}
	file.close();
	system("cls");
	cout << "*Файл успешно сохранен\n";
}

void SaveCSsData(CS& cs) {
	ofstream file;
	file.open("CSs.txt", fstream::in | ofstream::out);
	if (!file.is_open()) {
		system("cls");
		cout << "Ошибка чтения файла!";
	}
	if (cs.wrkshopsCount > 0) {
		file << cs.name << " " << cs.wrkshopsCount << endl;
	}
	else {
		file << "КС" << " " << 0 << endl;
	}
	file.close();

	file.open("WS.txt", fstream::in | ofstream::out);
	if (!file.is_open()) {
		system("cls");
		cout << "Ошибка чтения файла!";
	}
	if(cs.WS.size()>0){
		for (int i = 0; i < cs.WS.size(); i++) {
			if (cs.WS[i]) {
				file << 1 << " ";
			}
			else {
				file << 0 << " ";
			}
			file << endl;
		}
		file.close();
	}
	else {
		cout << "Ошибка";
	}
	
	system("cls");
	cout << "*Файл успешной сохранен\n";
}

void SaveData(Pipe pipe,CS cs) {
	SavePipesData(pipe);
	SaveCSsData(cs);
}

void LoadDataPipe(Pipe& pipe) {
	ifstream file("pipes.txt");
	if (file.is_open()) {
		getline(file, pipe.name);
		file >> pipe.length;
		file >> pipe.diameter;
		file >> pipe.isWorking;
	}
	else {
		cout << "\n\nОшибка загрузки файла pipes.txt\n\n";
	}
	file.close();
}

void LoadDataCS() {

}

int main()
{
	Pipe pipe;
	CS cs;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true) {
		int number = Menu();
		switch (number) {
		case 1:
			system("cls");
			AddPipe(pipe);
			system("cls");
			break;
		case 2:
			system("cls");
			AddCS(cs);
			system("cls");
			break;
		case 3:
			system("cls");
			ViewPipes(pipe);
			ViewCSs(cs);
			break;
		case 4:
			system("cls");
			PipeChange(pipe);
			system("cls");
			break;
		case 5:
			system("cls");
			CSChange(cs);
			system("cls");
			break;
		case 6:
			SaveData(pipe,cs);
			break;
		case 7:
			//LoadDataCS();
			break;
		case 0:
			exit(0);
		default:
			system("cls");
			cout << "Ошибка ввода\n";
			break;
		}
	}
	return 0;
}

