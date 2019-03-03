#include<iostream>
#include<cmath>
#include<math.h>
#include<cstdlib>
#include<cstdio>
#include <ctime>
#include <conio.h>
using namespace std;

//sprawdzanie danych
bool test(int & input) {
	cin.clear();
	cin.sync();
	cin >> input;
	return cin.fail();

};

//oh god, why am I using "or" instead of ||, and why am I using or inistead of and anyway, those checks have horrible logic, but at least it works (this was my first ever side project)
//I don't want to change anything, I am just adding those comments, I want to keep it just the way it is (besides me translating it to English from Polish)
//No idea why I have return at the end of every void... but hey, it doesn't make it perform any worse (I think)

//funkcja do podawania zakresu
void zakres(int & iloscLiczb, int & temporary) {

	int zakresLiczb;


	do {
		system("CLS");
		cout << "Current range: from 1 to " << temporary << endl;
		cout << "Current amount of numbers to guess: " << iloscLiczb << endl << endl;

		cout << "Input upper limit of numbers to guess, min 4" << endl << "Range also can't be lower than amount of numbers to guess" << endl;

	} while (test(zakresLiczb) or zakresLiczb < 4 or zakresLiczb < iloscLiczb);
	temporary = zakresLiczb;
	system("CLS");
	return;
};

//funkcja do podawania ilosci liczb
void ilosc(int & zakresLiczb, int & temporary) {

	int iloscLiczb;

	do {
		system("CLS");
		cout << "Current range: from 1 to " << zakresLiczb << endl;
		cout << "Current amount of numbers to guess: " << temporary << endl << endl;

		cout << "Input amount of numbers to guess " << endl << "min - 3, maks - " << zakresLiczb << " (upper range)." << endl;

	} while (test(iloscLiczb) or iloscLiczb<3 or iloscLiczb>zakresLiczb);
	temporary = iloscLiczb;
	system("CLS");
	return;
};
//funkcja do zmiany historii

void historyFunction(int & temporary) {

	int history;


	do {
		system("CLS");
		cout << "Current amount of showed results: " << temporary << endl;
		cout << "Input amount of results shown (min is 1)" << endl;

	} while (test(history) or history < 1);
	temporary = history;
	return;
};


//funkcja do menu
void menu(int & zakresLiczb, int & iloscLiczb, int & history) {

	int switchChange;

	do {
		do {
			system("CLS");
			cout << "Current range: from 1 to " << zakresLiczb << endl;
			cout << "Current amount of numbers to guess: " << iloscLiczb << endl;
			cout << "Current amount of showed results: " << history << endl << endl;

			cout << "OPTIONS" << endl;
			cout << "Press 1 to change range of numbers to guess from." << endl;
			cout << "Press 2 to change amount of numbers to guess." << endl;
			cout << "Press 3 to change amount of shown results." << endl;
			cout << "Press 4 to go back" << endl;
		} while (test(switchChange));
		switch (switchChange) {
			case 1: zakres(iloscLiczb, zakresLiczb); break;
			case 2: ilosc(zakresLiczb, iloscLiczb); break;
			case 3: historyFunction(history); break;
			default: break;
		}


	} while (switchChange != 4);
	return;
};


int main() {
	int repeat = 0;

	do {
		int zakresLiczb = 6, iloscLiczb = 4, history = 3;


		//wybor akcji
		int choose = 0;
		do {
			do {
				system("CLS");
				cout << "Current range: from 1 to " << zakresLiczb << endl;
				cout << "Current amount of numbers to guess: " << iloscLiczb << endl;
				cout << "Current amount of shown results: " << history << endl << endl;
				cout << "Press 1 to start playing." << endl << "Press 2 to go into options." << endl << "Press 2 to look at instructions." << endl;
			} while (test(choose));
			system("CLS");
			switch (choose) {
				case 2:
					menu(zakresLiczb, iloscLiczb, history);	break;
				case 3: {
					cout << "The goal of the game is to figure out numbers that computer chose in specific order." << endl << "You're chosing range of the numbers, amount of them and amount of results shown." << endl;
					cout << "Amount of shown results means amount of your previous propositions" << endl << "that are shown (alongside with the computer's response)" << endl << endl;
					cout << "Example:" << endl << "Range of numbers to guess 1-6" << endl << "Amount of numbers to guess - 4" << endl;
					cout << "Computer chose numbers 1 3 2 6 (which you of course can't see)" << endl;
					cout << "Your proposition is 1 3 6 4" << endl << endl;
					cout << "When number is in correct place, computer returns 2," << endl << "when it's in wrong place, it returns 1, and when it doesn't exist - 0" << endl << endl;
					cout << "So... the computer's response will involve numbers 2 0 1 1" << endl << endl;
					cout << "In order to make it harder, the numbers are shown in random order," << endl << "for example, one of the possible outputs is: 0 1 2 1" << endl << endl;
					cout << "Try to figure out the answer in the lower amount of rounds possible" << endl << "GOOD LUCK!" << endl << endl;
					cout << "Press enter to go back" << endl;
					cin.get();
					cin.get();
					break;
				}
				default:break;
			}
			system("CLS");
		} while (choose != 1);

		//losowanie liczb
		int tab[iloscLiczb];
		srand(time(0));


		//this is horrible, really horrible, but it gets the hob done
		for (int i = 0; i < iloscLiczb; i++) {
			tab[i] = rand() % zakresLiczb + 1;

			for (int check = 0; check < i; check++) {

				while (tab[i] == tab[check]) {
					tab[i] = rand() % zakresLiczb + 1;
					check = 0;
				}
			}

		}


		//I guess this was done using a different compiler, since I can't do that
		int wynik[iloscLiczb];
		int answers[iloscLiczb];

		//oh god, 2 years... Now i now how horrible that was, I never liked it even at the start, but I had no idea how to get around it so I created this monstrosity

		int prevWynik[9999][iloscLiczb];
		int prevAnswers[9999][iloscLiczb];
		//zmienna do sprawdzania konca gry 0=nie koniec, 1=koniec
		int end = 0;
		//licznik tur
		int tura = 0;
		//uzupe³nienie odpowiedzi zerami
		for (int i = 0; i < iloscLiczb; i++) {
			answers[i] = 0;
		}

		//loop dla gry
		do {
			tura++;

			//pokazywanie wyników
			for (int i = 0; i < iloscLiczb; i++) {


				if (tura > history + 1) {
					for (int i = 1; i <= tura - 1; i++) {

						if (i <= history) {
							cout << "Proposed answer: ";
							for (int c = 0; c < iloscLiczb; c++) {
								cout << prevWynik[tura - history + i - 1][c] << " ";
							}

							cout << endl;

							cout << "Computer's response: ";

							for (int c = 0; c < iloscLiczb; c++) {
								cout << prevAnswers[tura - history + i - 1][c] << " ";
							}

							cout << endl << endl;

						}

					}


				} else {

					for (int i = 1; i <= tura - 1; i++) {

						if (i <= history) {
							cout << "Proposed answer: ";
							for (int c = 0; c < iloscLiczb; c++) {
								cout << prevWynik[i][c] << " ";
							}

							cout << endl;

							cout << "Computer's response: ";

							for (int c = 0; c < iloscLiczb; c++) {
								cout << prevAnswers[i][c] << " ";
							}

							cout << endl << endl;

						}


					}
				}

				if (i > 0) {
					cout << "Previously entered numbers: ";
					for (int c = 0; c < i; c++) {
						cout << wynik[c] << " ";
					}
					cout << endl;
				}


				//wpisywanie liczb
				do {


					cout << "Enter " << i + 1 << " number: ";

					//system("CLS");
				} while (test(wynik[i]));
				prevWynik[tura][i] = wynik[i];
				system("CLS");

			}

			//sprawdzanie wynikow
			for (int i = 0; i < iloscLiczb; i++) {

				if (wynik[i] == tab[i]) {
					answers[i] = 2;
				} else {
					for (int c = 0; c < iloscLiczb; c++) {
						if (wynik[i] == tab[c]) {
							answers[i] = 1;
							break;
						} else { answers[i] = 0; }

					}
				}
			}
			//tablica z losowymi wartoœciami
			int randTable[iloscLiczb];

			for (int i = 0; i < iloscLiczb; i++) {
				randTable[i] = rand() % iloscLiczb;

				for (int check = 0; check < i; check++) {

					while (randTable[i] == randTable[check]) {
						randTable[i] = rand() % iloscLiczb;
						check = 0;
					}
				}

			}

			//wyœwietlanie odpowiedzi kompa

			/*
				for (int i=0; i<iloscLiczb; i++){
				cout<<answers[i]<<" ";
			}
			*/



			for (int i = 0; i < iloscLiczb; i++) {
				int c = randTable[i];
				prevAnswers[tura][i] = answers[c];
			}


			//sprawdzanie czy gra siê skoñczy³a
			for (int i = 0; i < iloscLiczb; i++) {

				if (answers[i] != 2) { end = 0; break; } else { end = 1; }

			}

			//zjeb check

			// yeah.... at least I made it so it won't break
			if (tura == 9999) { end = 1; }


			//also this made it easier to test c:

			//if (tura!=9999)tura=9998;

			//end=1;

		} while (end == 0);
		do {
			system("CLS");
			if (tura != 9999) {
				//pokazywanie poprawnego wyniku
				cout << "Correct answer: ";
				for (int c = 0; c < iloscLiczb; c++) {
					cout << prevWynik[tura][c] << " ";
				}
				//koniec pokazywania ?

				cout << endl << "You won in " << tura << " rounds." << endl << "CONGRATULATIONS";
			}

			else { cout << "Unfortunately tou reached limit of rounds (9999)"; }
			cout << endl << endl << "Press 1 to start again." << endl;


		} while (test(repeat));

	} while (repeat == 1);
	cout << "Thank you for playing, next time try to bead your record! :D";
	cin.get();
	cin.get();
	return 0;
}
