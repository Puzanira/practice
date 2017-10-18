//============================================================================
// Name        : ClassAbitur.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*Выделение отдельных структур сделано для того, чтобы в
 * переменные в конструкторе вызывались только явно */

struct Surname{
	string value;
	explicit Surname(string new_value){ //обЗательно явно преобразования типа к string
		value = new_value;
	}
};

struct Name{
	string value;
	explicit Name(string new_value){
		value = new_value;
	}
};

struct Patronim{
	string value;
	explicit Patronim(string new_value){
		value = new_value;
	}
};

struct Adress{
	string value;
	explicit Adress(string new_value){
		value = new_value;
	}
};

struct Marks{
	vector<int> value;
	explicit Marks(vector<int> new_value){
		value = new_value;
	}
};

class Abitur{
public:
	Abitur() {
		UpdateSumm();
	}

	Abitur(Surname new_surname,

			/* до структур было:
			 *
			const string& new_surname,
			surname = new_surname; */

		   Name new_name,
		   Patronim new_patronim,
		   Adress new_adress,
		   Marks new_marks){
		surname = new_surname.value;
		name = new_name.value;
		patronim = new_patronim.value;
		adress = new_adress.value;
		marks = new_marks.value;
		UpdateSumm();
	}

	Abitur(const Abitur& abitur){
		*this = abitur;
	}

	const Abitur& operator= (const Abitur& abitur){   //оператор присваивания
		surname = abitur.surname;				// abitur1 = abitur2 (сработает даже
		name = abitur.name;						// если не в момент создания
		patronim = abitur.patronim;
		adress = abitur.adress;
		marks = abitur.marks;
		summ = abitur.summ;
		return *this;
	}

	virtual ~Abitur() {} //полиморфизм

	const string& GetSurame() const { //ссылки при возврате больших обьектов
		return surname;				  //избегаем копирования в стек
	}
	const string& GetName() const {	  //при вызове f() = b без конст
			return name;
	}
	const string& GetPatronim() const { // && вызвана только для rvalue
			return patronim;
	}
	const string& GetAdress() const {
			return adress;
	}
	const vector<int>& GetMarks() const {
			return marks;
	}
	const int& GetSummMarks() const {
			return summ;
	}

	void SetSurname(const string& new_surname) {
		surname = new_surname;
	}
	void SetName(const string& new_name) {
			name = new_name;
	}
	void SetPatronim(const string& new_patronim) {
			patronim = new_patronim;
	}
	void SetAdress(const string& new_adress) {
			adress = new_adress;
	}
	void SetMarks(const vector<int>& new_marks) {
			marks = new_marks;
			UpdateSumm();
	}
	void AddMark(const int& mark){ //marktype&
			marks.push_back(mark);
			UpdateSumm();
	}

	/*int ComputeAverageSumm() const{
		int count = 0;
		for_each(marks.begin(), marks.end(), [&](int& mark){count += mark;});
		return (marks.size() >0 ? count / marks.size() : 0);
	} */

	int ComputeSumm(const vector<int>& marks) const{
			int new_summ = 0;
			for (int mark : marks){
					new_summ += mark;
			}
			//for_each(marks.begin(), marks.end(), [&](int& mark){summ += mark;});
			return new_summ;
	}

private:
	void UpdateSumm(){
		summ = ComputeSumm(marks);
	}
	string surname;
	string name;
	string patronim;
	string adress;
	vector<int> marks;
	int summ;

};

void PrintAbitur(const Abitur& abitur){ //интерфейсное представление объекта
	cout << "Abiturient: ";
	cout << abitur.GetSurame() << ' '; //печатать - не свойство абитуриента
	cout << abitur.GetName() << ' ';   //возможент разнообразный вывод
	cout << abitur.GetPatronim() << ' ';
	cout << endl;
	cout << "Adress: ";
	cout << abitur.GetAdress() << ' ';
	cout << endl;
	cout << "Marks: ";
	for (int mark : abitur.GetMarks()){
		cout << mark << ' ';
	}
	cout << endl;
}

void PrintAllAbiturs(const vector<Abitur>& allAbiturs){
	for (const Abitur& abitur : allAbiturs){
		PrintAbitur(abitur);
		cout << endl;
	}
}

void PrintDvoeshniks(const vector<Abitur>& allAbiturs){
	cout << "Abiturs with mark less than 30: " << endl;
	for (const Abitur& abitur : allAbiturs){
		for(int mark : abitur.GetMarks()){
			if (mark < 30){
				PrintAbitur(abitur);
				cout << endl;
				break;
			}
		}
	}
}

void PrintProhodnoi(const vector<Abitur>& allAbiturs){
	int treshold;
	double average;
	cout << "Theshold: ";
	cin >> treshold;
	cout << "Abiturs with average mark > " << treshold << ": " << endl;
	for (const Abitur& abitur : allAbiturs){
			average = (abitur.GetSummMarks() / (double)abitur.GetMarks().size());
			if ( average > treshold){
				PrintAbitur(abitur);
				cout << "With average: " << average << endl << endl;
			}
	}
}

void SortAbiturs (vector<Abitur>& allAbiturs){
	sort(allAbiturs.begin(), allAbiturs.end(), [](Abitur& a, Abitur& b){return a.GetSummMarks() > b.GetSummMarks();});
}

void PrintBest(vector<Abitur>& allAbiturs){
	int N;
	cout << "How much best abiturs?: ";
	cin >> N;
	SortAbiturs(allAbiturs);
	int i = 0;
	for (const Abitur& abitur : allAbiturs){
			if (i >= N){
				break;
			}
			PrintAbitur(abitur);
			cout << endl;
			i++;
		}
}


int main() {

	// Abitur abitur = {"P", "Ivan", "S", "Stoy. 12", {1,2}};

	vector<Abitur> allAbiturs = {{Surname("Ivanon"), Name("Ivan"), Patronim("Ivanovich"),
			 	 	 	 	 	 Adress("Vologda, Lenina, 45"), Marks({76, 86, 96})},

								{Surname("Sidorov"), Name("Sidor"), Patronim("Sirorovich"),
								 Adress("Moscow, Mira, 16"), Marks({98, 96, 94})},

								{Surname("Viktorov"), Name("Victor"), Patronim("Victorovich"),
								Adress("Sevastopol, Krasnaya, 27b"), Marks({34, 82, 73})},

								{Surname("Litvinov"), Name("Egor"), Patronim("Sergeevich"),
								 Adress("Zazhopinsk, Ass, 228a"), Marks({32, 45, 86})},

								{Surname("Alexandrov"), Name("Alexandr"), Patronim("Alexandrovich"),
								Adress("Gorkii, Slez, 12a"), Marks({44, 95, 25})}};

	Abitur abitur1 = {Surname("Petrov"), Name("Petr"), Patronim("Petrovich"),
					 Adress("Ekat, Shevskaya, 29"), Marks({23, 30, 45})};
	allAbiturs.push_back(abitur1);

	PrintAllAbiturs(allAbiturs);
	cout << endl;

	PrintDvoeshniks(allAbiturs);
	cout << endl;

	PrintProhodnoi(allAbiturs);
	cout << endl;

	PrintBest(allAbiturs);

	return 0;
}
