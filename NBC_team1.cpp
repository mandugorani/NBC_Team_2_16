#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// ĳ���� Ŭ������ �����Ѵٸ�?
class Character {
public:
	string name;
	int level;
	int maxHealth;
	int currentHealth;
	int maxMana;        // �ִ� ����
	int currentMana;    // ���� ����
	int attackPower;
	int experience;
	int gold;

	// ������
	Character(string charName)
		: name(charName), level(1), maxHealth(200), currentHealth(200),
		maxMana(50), currentMana(50), attackPower(30), experience(0), gold(0) {
	}

	// ������ �޼���
	void levelUp() {
		if (level < 10) { // ������ 10���� ���� ���� ������ ����
			level++;
			maxHealth += 20; // ������ �� �ִ� ü�� ����
			maxMana += 10; // ������ �� �ִ� ���� ����
			attackPower += 5; // ������ �� ���ݷ� ����
			currentHealth = maxHealth; // ü�°� ������ �ִ�ġ�� ȸ��
			currentMana = maxMana; // ������ ü���� �ִ�ġ�� ȸ��
			experience = 0; // ����ġ �ʱ�ȭ
			cout << name << "��(��) " << level << "������ �������ߴ�!" << endl; // ������ �޽��� ���
			cout << "�ִ� ü��: " << maxHealth << ", �ִ� ����: " << maxMana
				<< ", ���ݷ�: " << attackPower << endl; 
		}
	}

	// ����ġ ȹ��
	void gainExperience(int exp) { // ����ġ ȹ�� �޼���
		experience += exp;
		cout << name << " �� " << exp << " ����ġ�� �����!" << endl; // ����ġ ȹ�� �޽��� ���
		if (experience >= 100) { // ����ġ�� 100 �̻��̸� ������
			levelUp();
		}
	}

	// ��ų ��� (Judgment Blade)
	void useSkill(string skillName, int manaCost) { // ��ų ��� �޼���
		if (currentMana >= manaCost) { // ������ ����ϸ� ��ų ���
			currentMana -= manaCost; // ���� ����
			int skillDamage = static_cast<int>(attackPower * 1.5); // ��ų ������ ���
			cout << name << "��(��) [" << skillName << "]�� ����ߴ�!" << endl;
			cout << "���Ϳ��� " << skillDamage << "�� �������� ������!" << endl;
			cout << "���� ����: " << currentMana << "/" << maxMana << endl;
		}
		else {
			cout << "������ �����մϴ�! ���� ����: " << currentMana << "/" << maxMana << endl; // ���� ���� �޽��� ���
		}
	}

	// ���� ǥ��
	void displayStatus() { // ĳ���� ���� ǥ�� �޼���
		cout << "ĳ����: " << name << endl;
		cout << "����: " << level << ", HP: " << currentHealth << "/" << maxHealth
			<< ", MP: " << currentMana << "/" << maxMana << ", ���ݷ�: " << attackPower << ", ���� ��� : " << gold << ", ���� ����ġ: " << experience << "/100" << endl;
	}
};

// Monster Ŭ������ �����Ѵٸ�?
class Monster {
public:
	int health;
	int attackPower;
	int randRange(int min, int max) {
		return min + (rand() % (max - min + 1)); // min���� max ������ ������ ���� ��ȯ
	}
	Monster(int level) {
		health = randRange(level * 20, level * 30);   // level * 20���� level * 30 ������ ���� ü�� ����
		attackPower = randRange(level * 5, level * 10);
	}
};

void battleStart(Character& player);
void startGame();
void battle(Character& player);
void generateItem(Character& player);

// Main �Լ�
int main() {
	srand(time(0)); // �����Ϸ��� �������� ����
	startGame();
	return 0;
}

void startGame() {
	string name;
	cout << "ĳ������ �̸��� �Է��ϼ���: ";
	getline(cin, name);

	while (name.empty() || name.find(' ') != string::npos) {
		cout << "ĳ������ �̸��� ������ ���� �� �����ϴ�: ";
		getline(cin, name);
	}

	Character player(name);
	cout << "ĳ���� ���� �Ϸ�!" << endl;
	player.displayStatus();

	// ĳ���� ���� �� ����
	while (player.level < 10) {
		battleStart(player);
	}

	// ������ �����ϴ°� ����
	cout << "�����մϴ�! " << player.name << " ���� 10 �޼�!" << endl;
	cout << "���� ���� ����:" << endl;
	Monster boss(10);
	cout << "���� HP: " << boss.health << ", ������ ���ݷ�: " << boss.attackPower << endl;

	// �ؿ� ������ �ڵ� �߰�(�ٸ��������? �����������?)
}

void battleStart(Character& player) {
	char choice;
	while (true) {
		cout << "������ �����Ͻðڽ��ϱ�? (Y/N): ";
		cin >> choice;
		choice = toupper(choice); // ��ҹ��� ���� ���ֱ�

		if (choice == 'Y') {
			battle(player);
			break;
		}
		else if (choice == 'N') {
			cout << "������ �ǳʶٰ� ���� ������ ���ư��ϴ�." << endl;
			break;
		}
		else {
			cout << "�߸��� �Է��Դϴ�. Y �Ǵ� N�� �Է����ּ���." << endl;
		}
	}
}

void battle(Character& player) {
	Monster enemy(player.level);
	cout << "���� ����! ���� HP: " << enemy.health << ", ���� ���ݷ�: " << enemy.attackPower << endl;

	while (enemy.health > 0) {
		// Player attack
		enemy.health -= player.attackPower;
		cout << player.name << " ��(��) ���͸� ����! ������ ���� HP: " << enemy.health << endl;

		// Check if monster is defeated
		if (enemy.health <= 0) {
			cout << "�¸�!" << endl;
			player.gainExperience(50); // ����ġ�� 50 ��´ٰ� ����
			player.gold += (rand() % 11) + 10; // 10~20 ��� ȹ��   
			cout << player.name << " ��" << player.gold << " ��带 ȹ���ߴ�!" << endl;
			generateItem(player); // ������ ��� �Լ� ȣ��
			cout << "���� ����!" << endl;
			player.displayStatus();
			break;
		}

		// ����(������)
		player.currentHealth -= enemy.attackPower;
		cout << "������ ����! " << player.name << " �� HP�� " << player.currentHealth << "�� ����!" << endl;

		// �й��
		if (player.currentHealth <= 0) {
			cout << player.name << " �� �й��߽��ϴ�." << endl;
			exit(0);
		}
	}
}

void generateItem(Character& player) {
	if (rand() % 100 < 30) { // 30%
		int itemEffect = rand() % 2; // 0: ü�� ȸ��, 1: ���ݷ� ����
		if (itemEffect == 0) {
			player.currentHealth += 50;
			if (player.currentHealth > player.maxHealth) {
				player.currentHealth = player.maxHealth; // ü�� �ʰ� ����
			}
			cout << "ü���� ȸ�����ִ� ������ �߰�! ü�� ȸ�� �� ü��: " << player.currentHealth << endl;
		}
		else {
			player.attackPower += 10;
			cout << "���ݷ��� �÷��ִ� ������ �߰�! �� ���ݷ�: " << player.attackPower << endl;
		}
	}
	else {
		cout << "�������� ����." << endl;
	}
}