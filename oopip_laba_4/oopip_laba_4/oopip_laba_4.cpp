#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
string something, full_name, birth_year, registration_address, position, department, programming_language;

bool check(string something)
{
	for (int i = 0; i < something.size(); i++) {
		if (48 > something[i] || something[i] > 57) {
			return false;
			break;
		}
		return true;
	}
}

class Person {
	string full_name;
	int birth_year;
	string registration_address;

public:
	Person(string& name, int year, string& adress) : full_name(name), birth_year(year), registration_address(adress) {}

	string get_full_name() const {
		return full_name;
	}
	int get_birth_year() const {
		return birth_year;
	}
	string get_registration_address() const {
		return registration_address;
	}

	void set_full_name(string& name) {
		full_name = name;
	}
	void set_birth_year(int year) {
		birth_year = year;
	}
	void set_registration_address(string& adress) {
		registration_address = adress;
	}

	virtual void print_info() const {
		cout << "ФИО: " << full_name << ", Год рождения: " << birth_year << ", Адрес регистрации: " << registration_address << endl;
	}

};

class Worker : public Person {
	string position;
public:
	Worker( string& name, int year, string& address, string& pos) : Person(name, year, address), position(pos) {};
	
	string get_position() const {
		return position;
	}

	void set_position(string& pos) {
		position = pos;
	}

	void print_info() const override {
		Person::print_info();
		cout << "Должность: " << position << endl;
	}

};

class Manager : public Person {

	string department;

public: 
	Manager( string& name, int year, string& address, string& dept) : Person(name, year, address), department(dept) {}
	
	string get_department() const {
		return department;
	}

	void set_department(string& dept) {
		department = dept;
	}

	void print_info() const override{
		Person::print_info();
		cout << "Отдел: " << department << endl;
	}

};

class It_Employee : public Person {

	string programming_language;

public:
	It_Employee( string& name, int year, string& address, string language) : Person(name, year, address), programming_language(language) {}
	
	string get_programming_language() const {
		return programming_language;
	}

	void set_programming_language(string& language) {
		programming_language = language;
	}

	void print_info() const override{
		Person::print_info();
		cout << "Язык программирования: " << programming_language << endl;
	}
};

void print_and_save_employees(const vector<Person*>& employees, const string& filename) {
	string target_address;
	cout << "Введите адрес: ";
	cin.ignore();
	getline(cin, target_address);
	ofstream file(filename);
	for (const auto& employee : employees) {
		if (employee->get_registration_address() == target_address) {
			employee->print_info();
			file << "ФИО: " << employee->get_full_name() << ", Год рождения: " << employee->get_birth_year() << ", Адрес регистрации: " << employee->get_registration_address() << endl;
		}
	}
	file.close();

}

void print_menu() {
	cout << "1. Добавить сотрудника\n";
	cout << "2. Вывести всех сотрудников\n";
	cout << "3. Найти сотрудников по адресу регистрации\n";
	cout << "4. Записать в файл сотрудников с нужным адресом.\n";
	cout << "5. Выйти из программы\n";
	cout << "Выберите действие: ";
}

void add_employee(vector<Person*>& employees) {
	string name, address, additioanal_info, year, type;

	cout << "Введите ФИО: ";
	cin.ignore();
	getline(cin, name);

	cout << "Введите год рождения: ";
	cin >> year;
	
	if (check(year)) {


		cout << "Введите адрес регистрации: ";
		cin.ignore();
		getline(cin, address);

		cout << "Выберите тип сотрудника (1 - Рабочий, 2 - Руководитель, 3 - IT-сотрудник): ";
		cin >> type;
		if (check(type)) {
			switch (stoi(type)) {
			case 1:
			{
				cout << "Введите должность: ";
				cin.ignore();
				getline(cin, additioanal_info);
				employees.push_back(new Worker(name, stoi(year), address, additioanal_info));
				break;
			}
			case 2:
			{
				cout << "Введите отдел: ";
				cin.ignore();
				getline(cin, additioanal_info);
				employees.push_back(new Manager(name, stoi(year), address, additioanal_info));
				break;
			}
			case 3:
			{
				cout << "Введите язык программирования: ";
				cin.ignore();
				getline(cin, additioanal_info);
				employees.push_back(new It_Employee(name, stoi(year), address, additioanal_info));
				break;
			}
			default:
				cout << "Неверный тип сотрудника!\n";
				break;
			}

			cout << "Сотрудник добавлен!\n";
		}
		else {
			cout << "Введите число, а не символы.\n";
		}
	}
	else {
		cout << "Введите число, а не символы.\n";
	}
}


void print_all_employees(const vector<Person*>& employees) {
	if (employees.empty()) {
		cout << "Список сотрудников пуст.\n";
		return;
	}

	for (const auto& employee : employees) {
		employee->print_info();
		
		cout << "-------------------\n";
	}
}

void find_employees_by_address(const vector<Person*>& employees) {
	string targetAddress;
	cout << "Введите адрес регистрации для поиска: ";
	cin.ignore();
	getline(cin, targetAddress);

	bool found = false;
	for (const auto& employee : employees) {
		if (employee->get_registration_address() == targetAddress) {
			employee->print_info();
			found = true;
		}
	}

	if (!found) {
		cout << "Сотрудники с таким адресом не найдены.\n";
	}
}

int main() {
	vector<Person*> employees;
	string choice;
	
	do {
		print_menu();
		cin >> choice;
		if (check(choice)) {
			switch (stoi(choice)) {
			case 1:
			{
				add_employee(employees);
				break;
			}
			case 2:
			{
				cout << "-------------------\n";
				print_all_employees(employees);
				break;
			}
			case 3:
			{
				find_employees_by_address(employees);
				break;
			}
			case 4: {
				print_and_save_employees(employees, "employees.txt");
				break;
			}
			case 5:
			{
				cout << "Выход из программы.\n";
				return false;
			}
			default:
			{
				cout << "Неверный выбор. Попробуйте снова.\n";
				break;
			}
			}
		}
		else {
			cout << "Введите число, а не симолы.\n";
		}
	} while (true);



	for (auto& employee : employees) {
		delete employee;
	}


}