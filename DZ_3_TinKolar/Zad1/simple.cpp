#include<iostream>
#include<thread>
#include<chrono>
#include <cstdlib>
#include"Tocka.h"


using namespace std;

void show_me_board(Tocka start, Tocka finish, Tocka temp,int REDAKA,int STUPACA) {


	for (int i = 0; i < REDAKA; i++) {
		for (int j = 0; j < STUPACA; j++) {

			if (start.x == i && start.y == j) {
				cout << "S";
			}
			else if (finish.x == i && finish.y == j) {
				cout << "F";
			}
			else if (temp.x != start.x && temp.x == i && temp.y == j) {
				cout << "x";
			}
			else {
				cout << "_";
			}
		}
		cout << endl;
	}

}

int main() {

	int REDAKA = 20;
	int STUPACA = 40;

	Tocka start,finish,temp;

	cout << "Start x: ";
	cin >> start.x;
	cout << "Start y: ";
	cin >> start.y;

	temp = start;

	cout << "Finish x: ";
	cin >> finish.x;
	cout << "Finsih y: ";
	cin >> finish.y;


	while (temp.x != finish.x || temp.y != finish.y) {

		if (temp.x < finish.x) {
			temp.x++;
		}
		else if(temp.x > finish.x){
			temp.x--;
		}
		else {
			if (temp.y < finish.y) {
				temp.y++;
			}
			else if (temp.y > finish.y) {
				temp.y--;
			}
		}
		this_thread::sleep_for(chrono::milliseconds(200));
		system("cls");
		show_me_board(start, finish, temp, REDAKA, STUPACA);

	}

	return 0;
}