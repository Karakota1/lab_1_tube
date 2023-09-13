#include <iostream>
#include <vector>
#include <Windows.h>
#include <winuser.h>

using namespace std;


struct Pipe {
	string name;
	int length;
};

struct CS {
	string name;
	int wrkshopsCount;
	vector <bool> WS;
	float efficiency = 100;
};

vector <Pipe> pipeMas;
vector <CS> CSs;

int Menu() {
	int number;
	std::cout << "\n1.Добавить труду\n2.Добавить КС\n3.Список Труб\n4.Список Кс\n5.Редактировать трубу\n6.Редактировать Кс\n7.Сохранить\n8.Загрузить\n0.Выход\n\n";
	std::cin >> number;
	return number;
}

void AddPipe() {
	int n;
	cout << "\nВведите число труб: ";
	cin >> n;
	for (int i=0; i < n; i++) {
		string name;
		int length;
		cout << "Введите имя и длину трубы:\n";
		cin >> name >> length;
		pipeMas.push_back({ name, length });
	}
}

void ViewPipes() {
	cout << "Список труб:\n";
	for (int i = 0; i < pipeMas.size(); i++) {
		cout << "Порядковый номер: " << i + 1 << endl;
		cout << "Название трубы: " << pipeMas[i].name << endl;
		cout << "Длина трубы: " << pipeMas[i].length << endl << endl;
	}
}
void AddCS() {
	int n;
	cout << "\nВвидите число Кс: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		string name;
		int count;
		vector <bool> WSs;
		cout << "Ввидите название КС и число его цехов:\n";
		cin >> name >> count;
		if (count > 0) {
			for (int i=0; i < count; i++) {
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
				}
			}
		}
		else {
			continue;
		}
		CSs.push_back({ name, count, WSs,100 });
	}
}

void ViewCSs() {
	for (int i = 0; i < CSs.size(); i++) {
		cout << "Название КС: " << CSs[i].name << endl;
		cout << "Число Цехов: " << CSs[i].wrkshopsCount << endl << endl;
		for (int j = 0; j < CSs[i].WS.size(); j++) {
			if (CSs[i].WS[j])
				cout << "Цех №" << j << "      " << "В рабочем состоянии" << endl;
			else
				cout << "Цех №" << j << "      " << "Не в рабочем состоянии" << endl;
		}
	}
}

void PipeChange() {
	int n;
	int k;
	string name;
	int length;
	if (pipeMas.size() > 0) {
		ViewPipes();
		cout << "\n\tВыберете трубу для редактирования: ";
		cin >> n;
		cout << "\n\nВыдерете, что будете редактировать:\n1.Название\n2.Длина\n";
		cin >> k;
		if (k == 1) {
			cin >> name;
			pipeMas[n - 1].name = name;
		}
		else if (k == 2) {
			cin >> length;
			pipeMas[n - 1].length = length;
		}
	}
}

void CSChange() {

}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true) {
		int number = Menu();
		if (number == 1) {
			AddPipe();
		}
		else if (number == 2) {
			AddCS();
		}
		else if (number == 3) {
			ViewPipes();
		}
		else if (number == 4) {
			ViewCSs();
		}
		else if (number == 5) {
			PipeChange();
		}
	}
	return 0;
}