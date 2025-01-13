#include <iostream>

using namespace std;

void titleDraw() {

	system("mode con:cols=100 lines=30 | title 게 임 제 목");
	cout << endl << endl << endl << endl;
	cout << "                            ##          #         ############    " << endl;
	cout << "                             #         #               ##         " << endl;
	cout << "                             #        # #            #    #       " << endl;
	cout << "                             #       #    #         #   #  #      " << endl;
	cout << "                             #       #    #             #         " << endl;
	cout << "                             #        # #         #############   " << endl;
	cout << endl << endl << endl << endl << endl << endl;
	cout << "                                      1. 게임 시작" << endl;
	cout << "                                      2. 게임 종료" << endl;
	cout << endl << endl << endl << endl;
	cout << "                                      선택 : ";
	int choice;
	cin >> choice;

	if (choice == 1) {
		cout << "게임이 시작됩니다!" << endl;
		// startGame();
	}
	else {
		cout << "게임을 종료합니다." << endl;
	}

}

int main() {
	titleDraw();
	return 0;
}