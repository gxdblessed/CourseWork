#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Student {
	int ID = 0;
	int group = 0;
	int stipend = 0;
	int birthYear = 0;
	int marks[5] = { 0,0,0,0,0 };
	string name = "";
};

template <typename T>
struct Node {
	T data;
	Node* next = nullptr;
	Node* prev = nullptr;
};

template <typename T>
struct List {
	int size = 0;
	int currentIndex = 0;
	Node<T>* current = nullptr;
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;
	void toFirst() {
		if (!size) return;
		current = head;
		currentIndex = 0;
	}
	void toLast() {
		if (!size) return;
		current = tail;
		currentIndex = count() - 1;
	}
	void toNext() {
		if (!size) return;
		current = current->next;
		currentIndex++;
	}
	void toPrev() {
		if (!size) return;
		current = current->prev;
		currentIndex--;
	}
	void currentTo(int index) {
		if (!size) return;
		if ((currentIndex - index) > index) {
			toFirst();
		}
		if ((count() - 1 - index) < (index - currentIndex)) {
			toLast();
		}
		while (index > currentIndex) {
			toNext();
		}
		while (index < currentIndex) {
			toPrev();
		}
	}
	void removeCurrent() {
		if (!size) return;
		Node<T>* delNode = current;
		if ((delNode != head) and (delNode != tail)) {
			delNode->prev->next = delNode->next;
			delNode->next->prev = delNode->prev;
			current = current->next;
		}
		if (delNode == head) {
			head = delNode->next;
			if (delNode->next != nullptr) {
				delNode->next->prev = nullptr;
				current = current->next;
			}
		}
		if (delNode == tail) {
			tail = delNode->prev;
			if (delNode->prev != nullptr) {
				delNode->prev->next = nullptr;
				toPrev();
			}
		}
		delete delNode;
		size--;
		if (!size) current = nullptr;
	}
	void insertBeforeCurrent(T data) {
		if (!size) return;
		Node<T>* newNode = new Node<T>;
		size++;
		currentIndex++;
		newNode->data = data;
		newNode->next = current;
		newNode->prev = current->prev;
		if (current->prev != nullptr) current->prev->next = newNode;
		current->prev = newNode;
		if (current == head) { head = newNode; }
	}
	Node<T>* getCurrent(int index) {
		currentTo(index);
		return current;
	}
	void add(T data) {
		Node<T>* newNode = new Node<T>;
		newNode->data = data;
		if (!size) {
			currentIndex = 0;
			current = newNode;
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		size++;
	}
	void insert(int index, T data) {
		if ((!size) or (index == size)) {
			add(data);
		}
		else {
			currentTo(index);
			insertBeforeCurrent(data);
		}
	}
	void removeAt(int index) {
		currentTo(index);
		removeCurrent();
	}
	T elementAt(int index) {
		currentTo(index);
		return current->data;
	}
	int count() {
		return size;
	}
	void clear() {
		for (int i = size; i > 0; i--) {
			removeCurrent();
		}
	}
};

Student cinStudent(int& ID) {
	Student student;
	student.ID = ID++;
	cout << endl;
	cout << "Имя студента: ";
	cin.ignore();
	getline(cin, student.name);
	cout << "Группа студента: ";
	cin >> student.group;
	cout << "Оценки студента: ";
	for (int i = 0; i < 5; i++) {
		cin >> student.marks[i];
	}
	cout << "Стипендия студента: ";
	cin >> student.stipend;
	cout << "Год рождения студента: ";
	cin >> student.birthYear;
	return student;
}
void coutStudent(Student student) {
	cout << "Номер студента: " << student.ID << endl;
	cout << "Имя студента: " << student.name << endl;
	cout << "Группа студента: " << student.group << endl;
	cout << "Оценки студента: ";
	for (int i = 0; i < 5; i++) {
		cout << student.marks[i] << " ";
	}
	cout << endl;
	cout << "Стипендия студента: " << student.stipend << endl;
	cout << "Дата рождения студента: " << student.birthYear << endl;
}
void removeGroup(List<Student>& studentList, int group) {
	for (int i = 0; i < studentList.count(); i++) {
		if (studentList.elementAt(i).group == group) {
			studentList.removeCurrent();
			i--;
		}
	}
}
void removeStudent(List<Student>& studentList, int ID) {
	for (int i = 0; i < studentList.count(); i++) {
		if (studentList.elementAt(i).ID == ID) {
			studentList.removeCurrent();
			return;
		}
	}
}

void belowAverageGradeStudents(List<Student> list) {
	if (list.count() == 0) return;
	List<string> outputList;
	double average = 0;
	for (int i = 0; i < list.count(); i++) {
		for (int j = 0; j < 5; j++) {
			average += list.elementAt(i).marks[j];
		}
	}
	average = average / (5 * list.count());
	for (int i = 0; i < list.count(); i++) {
		double currentAverage = 0;
		for (int j = 0; j < 5; j++) {
			currentAverage += list.elementAt(i).marks[j];
		}
		currentAverage = currentAverage / 5;
		if (currentAverage < average) outputList.add(list.elementAt(i).name);
	}
	for (int i = 0; i < outputList.count() - 1; i++) {
		string min = outputList.elementAt(i);
		for (int j = i; j < outputList.count(); j++) {
			if (min > outputList.elementAt(j)) {
				outputList.insert(i, outputList.elementAt(j));
				outputList.removeAt(j + 1);
			}
		}
	}
	for (int i = 0; i < outputList.count(); i++) {
		cout << outputList.elementAt(i) << endl;
	}
}
Student getStudentByID(List<Student> studentList, int ID) {
	for (int i = 0; i < studentList.count(); i++) {
		if (studentList.elementAt(i).ID == ID) {
			return studentList.elementAt(i);
		}
	}
	Student student;
	return student;
}

int toint(string str) {
	int num = 0, k = 0;
	for (int i = str.size() - 1; i >= 0; i--, k++) {
		num += (str[i] - 48) * pow(10, k);
	}
	return num;
}
int* tointarr(string str) {
	int arr[5] = {}, k = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] != ' ') {
			arr[k] = str[i] - 48;
			k++;
		}
	}
	return arr;
}

void fileInput(List<Student>& list, int& ID) {
	Student student;
	ifstream input;
	input.open("input.txt");
	string str;
	int number = 0;
	int* arr;
	while (getline(input, str)) {
		number++;
		switch (number) {
		case 1:
			student.name = str;
			break;
		case 2:
			student.group = toint(str);
			break;
		case 3:
			arr = tointarr(str);
			for (int i = 0; i < 5; i++) {
				student.marks[i] = arr[i];
			}
			break;
		case 4:
			student.stipend = toint(str);
			break;
		case 5:
			student.birthYear = toint(str);
			student.ID = ID++;
			list.add(student);
			number = 0;
			break;
		}
	}
	input.close();
}

void fileOutput(List<Student> list) {
	ofstream output;
	output.open("output.txt");
	for (int i = 0; i < list.count(); i++) {
		Student student = list.elementAt(i);
		output << student.name << endl;
		output << student.group << endl;
		for (int j = 0; j < 5; j++) { output << student.marks[j] << " "; }
		output << endl << student.stipend << endl;
		output << student.birthYear << endl;
		output << student.ID << endl;
	}
	output.close();
}

void menu() {
	cout << "(0) Завершить программу" << endl;
	cout << "(1) Добавление студента" << endl;
	cout << "(2) Удалить студента по номеру" << endl;
	cout << "(3) Изменить данные о студенте по номеру" << endl;
	cout << "(4) Вывести данные о студенте по номеру" << endl;
	cout << "(5) Показать студентов по параметру" << endl;
	cout << "(6) Вывести информацию о всех студентах" << endl;
	cout << endl;
	cout << "(7) Добавление группы студентов" << endl;
	cout << "(8) Удаление группы студентов" << endl;
	cout << "(9) Редактирование номера группы" << endl;
	cout << "(10) Показать группу студентов" << endl;
	cout << "(11) Показать студентов с оценками ниже стреднего" << endl;
	cout << endl;
	cout << "(12) Файловый ввод данных" << endl;
	cout << "(13) Файловый вывод данных" << endl;
}
void submenu() {
	cout << "(0) Отмена" << endl;
	cout << "(1) Имя" << endl;
	cout << "(2) Год рождения" << endl;
	cout << "(3) Группа" << endl;
	cout << "(4) Оценки" << endl;
	cout << "(5) Стипендия" << endl;
	cout << endl;
}
void submenu2() {
	cout << "(0) Отмена" << endl;
	cout << "(1) Имя" << endl;
	cout << "(2) Год рождения" << endl;
	cout << "(3) Стипендия" << endl;
	cout << endl;
}
void main() {
	system("chcp 1251>NULL");
	List<Student> studentList;
	int ID = 1;
	int choice = 0;
	int choice2 = 0;
	int input = 0;
	while (true) {
		system("cls");
		menu();
		cout << "Выбор: ";
		cin >> choice;
		switch (choice)
		{
		case (0): {
			return;
		}
		case (1): {
			cout << "Введите данные о студенте";
			studentList.add(cinStudent(ID));
			cout << "Студент добавлен" << endl;
			break;
		}
		case (2): {
			if (studentList.count() == 0) break;
			cout << "Введите номер студента: ";
			cin >> input;
			removeStudent(studentList, input);
			cout << "Студент удален" << endl;
			break;
		}
		case (3): {
			if (studentList.count() == 0) break;
			cout << "Номер студента, данные которого хотите изменить: ";
			cin >> input;
			cout << "Что хотите изменить?" << endl;
			submenu();
			cout << "Выбор: ";
			cin >> choice2;
			switch (choice2)
			{
			case (0): {
				break;
			}
			case (1): {
				Student student = getStudentByID(studentList, input);
				if (student.ID == 0) break;
				removeStudent(studentList, input);
				string input2 = "";
				cout << "Введите новые данные: ";
				cin >> input2;
				student.name = input2;
				studentList.add(student);
				break;
			}
			case (2): {
				Student student = getStudentByID(studentList, input);
				if (student.ID == 0) break;
				removeStudent(studentList, input);
				int input2 = 0;
				cout << "Введите новые данные: ";
				cin >> input2;
				student.birthYear = input2;
				studentList.add(student);
				break;
			}
			case (3): {
				Student student = getStudentByID(studentList, input);
				if (student.ID == 0) break;
				removeStudent(studentList, input);
				int input2 = 0;
				cout << "Введите новые данные: ";
				cin >> input2;
				student.group = input2;
				studentList.add(student);
				break;
			}
			case (4): {
				Student student = getStudentByID(studentList, input);
				if (student.ID == 0) break;
				removeStudent(studentList, input);
				int input2 = 0;
				cout << "Введите новые данные: ";
				for (int i = 0; i < 5; i++) {
					cin >> input2;
					student.marks[i] = input2;
				}
				studentList.add(student);
				break;
			}
			case (5): {
				Student student = getStudentByID(studentList, input);
				if (student.ID == 0) break;
				removeStudent(studentList, input);
				int input2 = 0;
				cout << "Введите новые данные: ";
				cin >> input2;
				student.stipend = input2;
				studentList.add(student);
				break;
			}
			default: {
				cout << "Неизвестная команда, попробуйте снова" << endl;
				break;
			}
			}
			break;
		}
		case (4): {
			if (studentList.count() == 0) break;
			cout << "Введите номер студента: ";
			cin >> input;
			coutStudent(getStudentByID(studentList, input));
			break;
		}
		case (5): {
			if (studentList.count() == 0) break;
			cout << "Какой параметр?" << endl;
			submenu2();
			cout << "Выбор: ";
			cin >> choice2;
			switch (choice2)
			{
			case (0): {
				break;
			}
			case (1): {
				cout << "Имя: ";
				string input2 = "";
				cin >> input2;
				for (int i = 0; i < studentList.count(); i++) {
					if (studentList.elementAt(i).name == input2) {
						coutStudent(studentList.elementAt(i));
						cout << endl;
					}
				}
				break;
			}
			case (2): {
				cout << "Дата рождения: ";
				cin >> input;
				for (int i = 0; i < studentList.count(); i++) {
					if (studentList.elementAt(i).birthYear == input) {
						coutStudent(studentList.elementAt(i));
						cout << endl;
					}
				}
				break;
			}
			case (3): {
				cout << "Стипендия: ";
				cin >> input;
				for (int i = 0; i < studentList.count(); i++) {
					if (studentList.elementAt(i).stipend == input) {
						coutStudent(studentList.elementAt(i));
						cout << endl;
					}
				}
				break;
			}
			default: {
				cout << "Неизвестная команда, попробуйте снова:" << endl;
				break;
			}
			}
			break;
		}
		case (6): {
			cout << "Все студенты:" << endl;
			for (int i = 0; i < studentList.count(); i++) {
				coutStudent(studentList.elementAt(i));
			}
			break;
		}
		case (7): {
			cout << "Количество студентов: ";
			cin >> input;
			cout << "Введите данные о студентах";
			for (int i = 0; i < input; i++) {
				studentList.add(cinStudent(ID));
			}
			cout << "Студенты добавлены" << endl;
			break;
		}
		case (8): {
			if (studentList.count() == 0) break;
			cout << "Группа, которую нужно удалить: ";
			cin >> input;
			removeGroup(studentList, input);
			cout << "Группа удалена: " << endl;
			break;
		}
		case (9): {
			if (studentList.count() == 0) break;
			int input2;
			cout << "Изменить номер группы: ";
			cin >> input;
			cout << "Новый номер группы: ";
			cin >> input2;
			for (int i = 0; i < studentList.count(); i++) {
				if (studentList.elementAt(i).group == input) {
					Student student = studentList.elementAt(i);
					removeStudent(studentList, student.ID);
					i--;
					student.group = input2;
					studentList.add(student);
				}
			}
			cout << "Номер группы изменен" << endl;
			break;
		}
		case (10): {
			if (studentList.count() == 0) break;
			cout << "Вывести номер группы: ";
			cin >> input;
			for (int i = 0; i < studentList.count(); i++) {
				if (studentList.elementAt(i).group == input) {
					coutStudent(studentList.elementAt(i));
				}
			}
			break;
		}
		case (11): {
			cout << "Учащиеся с оценками ниже среднего" << endl;
			belowAverageGradeStudents(studentList);
			break;
		}
		case (12): {
			fileInput(studentList, ID);
			break;
		}
		case (13): {
			fileOutput(studentList);
			break;
		}
		default: {
			cout << "Неизвестная команда, порпобуйте снова" << endl;
			break;
		}
		}
		system("pause");
	}
}