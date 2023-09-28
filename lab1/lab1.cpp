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
			cout << "Состояние: ВКЛ." << endl << endl;
		else
			cout << "Состояние: ВЫКЛ." << endl << endl;
	}
}
void AddCS(CS& cs) {
	float workingWS = 0;
	float allWS = 0;
	string name;
	float effic;
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
				workingWS++;
				allWS++;
			}
			else if (n == 2) {
				WSs.push_back(false);
				allWS++;
			}
			else {
				cout << "Неверно введен ответ";
				j--;
			}
		}
		effic = workingWS / allWS * 100;
	}
	cs = { name, count, WSs, effic};
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
		float workingWS = 0;
		float allWS = 0;
		for (int i=0; i < cs.WS.size(); i++) {
			if (cs.WS[i])
				workingWS++;
			allWS++;
		}
		cs.efficiency =  workingWS / allWS * 100;
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
	if (cs.name != " ") {
		file << cs.name << endl;
	}
	else {
		file << "КС" << endl;
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
	char Pname[30];
	if (file.is_open()) {
		file >> Pname;//Эта штука изобретена укропами, взята буквально с боем, вы можете себе представить лицо человека, который придумал Ansi
		pipe.name = Pname;
		file >> pipe.length;
		file >> pipe.diameter;
		file >> pipe.isWorking;
	}
	else {
		cout << "\n\nОшибка загрузки файла pipes.txt\n\n";
	}
	file.close();
}

void LoadDataCS(CS& cs) {
	ifstream file("CSs.txt");
	if (file.is_open()) {
		file >> cs.name;	}
	else {
		cout << "\n\nОшибка загрузки файл CSs.txt\n\n";
	}
	file.close();

	ifstream filen("WS.txt");
	int yn;
	if (filen.is_open()) {
		int allWS = 0;
		int workWS = 0;
		while (!filen.eof()) {
			filen >> yn;
			if (yn == 1) {
				cs.WS.push_back(true);
				workWS++;
			}
			else
				cs.WS.push_back(false);
			allWS++;
		};
		cs.wrkshopsCount = allWS;
		cs.efficiency = workWS / allWS * 100;
	}
	else {
		cout << "\n\nОшибка загрузки файл WS.txt\n\n";
	}
	filen.close();
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
			LoadDataPipe(pipe);
			LoadDataCS(cs);
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

