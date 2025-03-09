#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

fstream file_routes;

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


class local_time {

private:
	int hour;
	int minute;
public:

	local_time(int h = 0, int m = 0) : hour(h), minute(m) {}
	local_time(const local_time& other) : hour(other.hour), minute(other.minute) {}

	int get_hour() const {
		return hour;
	}
	int get_minute() const {
		return minute;
	}

	void set_hour(int h) {
		hour = h;
	}

	void set_minute(int m) {
		minute = m;
	}

	string to_format() const {
		string buffer;
		return to_string(hour) + ':' + to_string(minute);
	}

};

class local_date {

private:
	int year;
	int month;
	int day;

public:
	local_date(int y = 200, int m = 1, int d = 1) : year(y), month(m), day(d) {}
	local_date(const local_date& other) : year(other.year), month(other.month), day(other.day) {}

	int get_year() const {
		return year;
	}
	int get_month() const {
		return month;
	}
	int get_day() {
		return day;
	}

	void set_year(int y) {
		year = y;
	}
	void set_month(int m) {
		month = m;
	}
	void set_day(int d) {
		day = d;
	}

	string to_format() const {
		return to_string(year) + '-' + to_string(month) + '-' + to_string(day);
	}

};

class local_date_time {

private:
	local_date date;
	local_time time;
public:
	local_date_time(const local_date& d = local_date(), const local_time& t = local_time()) : date(d), time(t) {}
	local_date_time(const local_date_time& other) : date(other.date), time(other.time) {}

	local_date get_date() const {
		return date;
	}
	local_time get_time() const {
		return time;
	}

	void set_date(const local_date& d) {
		date = d;
	}
	void set_time(const local_time& t) {
		time = t;
	}

	string to_format() const {
		return date.to_format() + " " + time.to_format();
	}

};

class route {
private:
	int route_id;
	int distance;
	local_date_time departure, arrival;

public:
	route(int id = 0, int dist = 0, const local_date_time& dep = local_date_time(), const local_date_time& arr = local_date_time()) : route_id(id), distance(dist), departure(dep), arrival(arr) {}
	route(const route& other) : route_id(other.route_id), distance(other.distance), departure(other.departure), arrival(other.arrival) {}

	int getRouteId() const {
		return route_id;
	}
	int getDistance() const {
		return distance;
	}
	local_date_time getDeparture() const {
		return departure;
	}
	local_date_time getArrival() const {
		return arrival;
	}

	void setArrival(const local_date_time& arr) {
		arrival = arr;
	}
	void setRouteId(int id) {
		route_id = id;
	}
	void setDistance(int dist) {
		distance = dist;
	}
	void setDeparture(const local_date_time& dep) {
		departure = dep;
	}

	string to_format() const {
		return "Маршрут ID: " + to_string(route_id) + ", Дистанция: " + to_string(distance) + " км, Отправление: " + departure.to_format() + ", Прибывание: " + arrival.to_format();
	}

	static void write_to_file(const vector<route>& routes, const string& filename) {
		ofstream file(filename);
		if (!file.is_open()) {
			cout << "Список маршрутов пуст.\n";
		}
		for (const auto& route : routes) {
			file << route.to_format() << endl;
		}
		file.close();
	}

};

string find_the_shortest_route(const vector<route>& routes) {

	route shortest_route = routes[0];
	for (int i = 0; i < routes.size()-1; i++) {
		if (routes[i].getDistance() < shortest_route.getDistance()) {
			shortest_route = routes[i];
		}
	}
	return shortest_route.to_format();

}

void clear() {
	file_routes.open("Routes_Tusk.txt", ios::out);
	file_routes.close();
	file_routes.open("Routes_Tusk.txt", ios::app);
	file_routes.close();
}

void put_data_into_file(const vector<route>& routes) {
	clear();
	if (routes.size() > 1) {
		file_routes.open("Routes_Tusk.txt", ios::app);
		for (int i = 0; i < routes.size() - 1; i++) {
			file_routes << routes[i].to_format() << endl;
		}
		file_routes.close();
	}
	else {
		cout << "Вы не ввели маршруты, либо не считали из файла.\n";
	}
}

int main() {
	vector<route> routes;

	routes.resize(1);

	string choice, some;
	local_date_time temp_local_date_time;
	local_date temp_date;
	local_time temp_time;

	do {
		cout << "1. Ввести новый маршрут.\n2. Вывести все маршруты.\n3. Вывести маршрут с наименьньшей дистанцией.\n4. Записать данные в файл.\n5.Закончить программу\nВведите номер оперции: ";
		cin >> choice;
		if (check(choice)) {
			switch (stoi(choice)) {
			case 1:
			{
				cout << "Введите ID маршрута: ";
				cin >> some;
				if (check(some)) {
					routes[routes.size()-1].setRouteId(stoi(some));
				}
				else {
					cout << "Введите число, а не символы.\n";
					break;
				}

				cout << "Введите длину маршрута: ";
				cin >> some;
				if (check(some)) {
					routes[routes.size()-1].setDistance(stoi(some));
				}
				else {
					cout << "Введите число, а не символы.\n";
					break;
				}

				cout << "Введите время отправления.\nВведите год отправления: ";
				cin >> some;
				if (check(some)) {
					if (stoi(some) > 2024 && stoi(some) < 2040) {
						temp_date.set_year(stoi(some));
					}
					else {
						cout << "Вы ввели год неверный год. Он либо меньше 2025, либо больше 2050\n";
						break;
					}
				}
				else {
					cout << "Введите число, а не символы.\n";
					break;
				}
				cout << "Введите месяц отправления: ";
				cin >> some;
				if (check(some)) {
					if (stoi(some) > 0 && stoi(some) < 13) {
						temp_date.set_month(stoi(some));
					}
					else {
						cout << "Введите корректное значение месяца.\n";
						break;
					}
				}
				else {
					cout << "Введите число, а не символы.\n";
					break;
				}
				cout << "Введите день отправления: ";
				cin >> some;
				if (check(some)) {
					if (stoi(some) > 0 && stoi(some) < 32) {
						temp_date.set_day(stoi(some));
					}
					else {
						cout << "Введите корректное значение месяца.\n";
						break;
					}
				}
				else {
					cout << "Введите число, а не символы.\n";
					break;
				}

				temp_local_date_time.set_date(temp_date);

				cout << "Введите часы отправления: ";
				cin >> some;
				if (check(some)) {
					if (stoi(some) >= 0 && stoi(some) <= 24) {
						temp_time.set_hour(stoi(some));
					}
					else {
						cout << "Введите корректное значение часов.\n";
						break;
					}
				}
				else {
					cout << "Введите число, а не символы.\n";
					break;
				}
				cout << "Введите минуты отправления: ";
				cin >> some;
				if (check(some)) {
					if (stoi(some) >= 0 && stoi(some) <= 60) {
						temp_time.set_minute(stoi(some));
					}
					else {
						cout << "Введите корректное значение минут.\n";
						break;
					}
				}
				else {
					cout << "Введите число, а не символы.\n";
					break;
				}

				temp_local_date_time.set_time(temp_time);

				routes[routes.size() - 1].setDeparture(temp_local_date_time);

				cout << "Введите время прибытия.\nВведите год прибытия: ";
				cin >> some;
				if (check(some)) {
					if (stoi(some) > 2024 && stoi(some) < 2040) {
						temp_date.set_year(stoi(some));
					}
					else {
						cout << "Вы ввели год неверный год. Он либо меньше 2025, либо больше 2050\n";
						break;
					}
				}
				else {
					cout << "Введите число, а не символы.\n";
					break;
				}
				cout << "Введите месяц прибытия: ";
				cin >> some;
				if (check(some)) {
					if (stoi(some) > 0 && stoi(some) < 13) {
						temp_date.set_month(stoi(some));
					}
					else {
						cout << "Введите корректное значение месяца.\n";
						break;
					}
				}
				else {
					cout << "Введите число, а не символы.\n";
					break;
				}
				cout << "Введите день прибытия: ";
				cin >> some;
				if (check(some)) {
					if (stoi(some) > 0 && stoi(some) < 32) {
						temp_date.set_day(stoi(some));
					}
					else {
						cout << "Введите корректное значение месяца.\n";
						break;
					}
				}
				else {
					cout << "Введите число, а не символы.\n";
					break;
				}

				temp_local_date_time.set_date(temp_date);

				cout << "Введите часы отправления: ";
				cin >> some;
				if (check(some)) {
					if (stoi(some) >= 0 && stoi(some) <= 24) {
						temp_time.set_hour(stoi(some));
					}
					else {
						cout << "Введите корректное значение часов.\n";
						break;
					}
				}
				else {
					cout << "Введите число, а не символы.\n";
					break;
				}
				cout << "Введите минуты отправления: ";
				cin >> some;
				if (check(some)) {
					if (stoi(some) >= 0 && stoi(some) <= 60) {
						temp_time.set_minute(stoi(some));
					}
					else {
						cout << "Введите корректное значение минут.\n";
						break;
					}
				}
				else {
					cout << "Введите число, а не символы.\n";
					break;
				}

				temp_local_date_time.set_time(temp_time);

				routes[routes.size() - 1].setArrival(temp_local_date_time);

				routes.resize(routes.size() + 1);
				
				break;
			}
			case 2:
			{
				if (routes.size() > 1) {
					for (int i = 0; i < routes.size() - 1; i++) {
						cout << routes[i].to_format() << endl;
					}
				}
				else {
					cout << "Вы не ввели маршруты, либо не считали из файла.\n";
				}

				break;
			}
			case 3:
			{
				if (routes.size() == 1) {
					cout << "Вы не ввели маршруты, либо не считали их из файла.\n";
				}
				else {
					cout << "Самый короткий маршрут: " << find_the_shortest_route(routes);
					cout << endl;
				}
				break;
			}
			case 4: {
				if (routes.size() > 1) {
					put_data_into_file(routes);
				}
				else {
					cout << "Вы не ввели маршруты, либо не считали из файла.\n";
				}
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

}