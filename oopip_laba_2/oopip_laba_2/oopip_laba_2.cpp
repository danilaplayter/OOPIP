#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

extern bool check(string something)
{
	for (int i = 0; i < something.size(); i++) {
		if (48 > something[i] || something[i] > 57) {
			return false;
			break;
		}
		return true;
	}
}

class DaySchedule {
public:
    string dayName; 
    string group;   
    string subject; 
    string teacher;

    
    DaySchedule(const string& day, const string& grp, const string& subj, const string& tchr)
        : dayName(day), group(grp), subject(subj), teacher(tchr) {}
};


class Schedule {
private:
    DaySchedule** weekSchedule; 
    int daysCount;             

public:
  
    Schedule(int days) : daysCount(days) {
        weekSchedule = new DaySchedule * [daysCount]; 
        for (int i = 0; i < daysCount; ++i) {
            weekSchedule[i] = nullptr; 
        }
    }

   
    ~Schedule() {
        for (int i = 0; i < daysCount; ++i) {
            delete weekSchedule[i]; 
        }
        delete[] weekSchedule;
    }

  
    void addDaySchedule(int dayIndex, const string& dayName, const string& group, const string& subject, const string& teacher) {
        if (dayIndex >= 0 && dayIndex < daysCount) {
            weekSchedule[dayIndex] = new DaySchedule(dayName, group, subject, teacher);
        }
    }

   
    void printDaySchedule(int dayIndex) const {
        if (dayIndex >= 0 && dayIndex < daysCount && weekSchedule[dayIndex] != nullptr) {
            const DaySchedule* day = weekSchedule[dayIndex];
            cout << "Расписание на " << day->dayName << ":\n";
            cout << setw(20) << left << "Группа" << setw(20) << "Предмет" << setw(20) << "Преподаватель" << "\n";
            cout << setfill('-') << setw(60) << "" << setfill(' ') << "\n";
            cout << setw(20) << left << day->group << setw(20) << day->subject << setw(20) << day->teacher << "\n";
        }
        else {
           cout << "Расписание на этот день отсутствует.\n";
        }
    }

  
    friend ostream& operator<<(ostream& os, const Schedule& schedule);
};

ostream& operator<<(ostream& os, const Schedule& schedule) {
    os << "Недельное расписание:\n";
    os << setw(25) << left << "День" << setw(25) << "Группа" << setw(30) << "Предмет" << setw(30) << "Преподаватель" << right << "\n";
    os << setfill('-') << setw(80) << "" << setfill(' ') << "\n";

    for (int i = 0; i < schedule.daysCount; ++i) {
        if (schedule.weekSchedule[i] != nullptr) {
            const DaySchedule* day = schedule.weekSchedule[i];
            os << setw(25) << left << day->dayName << setw(25) << day->group << setw(30) << day->subject << setw(30) << day->teacher << "\n";
        }
    }
    return os;
}

int main() {

    Schedule weeklySchedule(5);

    weeklySchedule.addDaySchedule(0, "Понедельник", "Группа 101", "Математика", "Иванов И.И.");
    weeklySchedule.addDaySchedule(1, "Вторник", "Группа 102", "Физика", "Петров П.П.");
    weeklySchedule.addDaySchedule(2, "Среда", "Группа 103", "Информатика", "Сидоров С.С.");
    weeklySchedule.addDaySchedule(3, "Четверг", "Группа 104", "Химия", "Кузнецов К.К.");
    weeklySchedule.addDaySchedule(4, "Пятница", "Группа 105", "Биология", "Николаев Н.Н.");

    string dayIndex, flag;
    do
    {
        cout << "Выбирете действие: \n1.Вывести рассписание по дню недели\n2.Вывести рассписание на всю неделю\n3. Закончить программу.\nВведите номер опереции: ";
        cin >> flag;
        if (check(flag))
        {
            if (stoi(flag) == 1) {
                cout << "\nВведите номер дня недели (1-5): ";
                cin >> dayIndex;
                if (check(dayIndex)) {
                    weeklySchedule.printDaySchedule(stoi(dayIndex) - 1);
                }
                else {
                    cout << "Введите число, а не символы.\n";
                }
            }
            if (stoi(flag) == 2) {
                cout << weeklySchedule;
            }
            if (stoi(flag) == 3) {
                break;
            }

        }
    } while (true);

    return 0;
}