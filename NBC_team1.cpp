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
    int attackPower;
    int experience;
    int gold;
    

    // ĳ������ �ʱⰪ (������)
    Character(string charName)
        : name(charName), level(1), maxHealth(200), currentHealth(200),
        attackPower(30), experience(0), gold(0) {
    }


    // ������ ����
    void levelUp() {
        if (level < 10) {
            level++;
            maxHealth += 20;
            attackPower += 5;
            currentHealth = maxHealth; // ü���� �ִ�ġ�� ȸ���ϴ°� ����
			experience = 0; // ������ �Ŀ� ����ġ�� �ٽ� 0���� �ʱ�ȭ
            cout << name << " ��(��) " << level << "������ �������ߴ�!" << endl;
            cout << "�ִ� ü�� " << maxHealth << "�� ����, ���ݷ� " << attackPower << "�� ����" << endl;
        }
    }

    void gainExperience(int exp) {
        experience += exp;
        cout << name << "�� " << exp << " ����ġ�� �����!" << endl;
        if (experience >= 100) {
            levelUp();
        }
    }

    void displayStatus() {
        cout << "Character: " << name << endl;
        cout << "����: " << level << ", HP: " << currentHealth << "/" << maxHealth << ", ���ݷ�: " << attackPower << endl;
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
        battle(player);
    }

    // ������ �����ϴ°� ����
    cout << "�����մϴ�! " << player.name << " ���� 10 �޼�!" << endl;
    cout << "���� ���� ����:" << endl;
    Monster boss(10);
    cout << "���� HP: " << boss.health << ", ������ ���ݷ�: " << boss.attackPower << endl;

    // �ؿ� ������ �ڵ� �߰�(�ٸ��������? �����������?)
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
            cout << player.name << " earned gold! Total Gold: " << player.gold << endl;
			generateItem(player); // ������ ��� �Լ� ȣ��
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