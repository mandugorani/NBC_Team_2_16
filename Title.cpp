#include <iostream>

using namespace std;

void titleDraw() {

	system("mode con:cols=100 lines=30 | title �� �� �� ��");
	cout << endl << endl << endl << endl;
	cout << "                            ##          #         ############    " << endl;
	cout << "                             #         #               ##         " << endl;
	cout << "                             #        # #            #    #       " << endl;
	cout << "                             #       #    #         #   #  #      " << endl;
	cout << "                             #       #    #             #         " << endl;
	cout << "                             #        # #         #############   " << endl;
	cout << endl << endl << endl << endl << endl << endl;
	cout << "                                      1. ���� ����" << endl;
	cout << "                                      2. ���� ����" << endl;
	cout << endl << endl << endl << endl;
	cout << "                                      ���� : ";
	int choice;
	cin >> choice;

	if (choice == 1) {
		cout << "������ ���۵˴ϴ�!" << endl;
		// startGame();
	}
	else {
		cout << "������ �����մϴ�." << endl;
	}

}

int main() {
	titleDraw();
	return 0;
}