#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

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
        cout << "����: " << level << ", HP: " << currentHealth << "/" << maxHealth << ", ���ݷ�: " << attackPower << ", ���: " << gold << endl;
    }
};

// ���� ���� �Լ�
int randRange(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

// ���� Ÿ�� ����ü
struct MonsterType
{
    string name;        // ���� �̸�
    int minHealth;      // �ּ� ä��
    int maxHealth;      // �ִ� ä��
    int minAttack;      // �ּ� ���ݷ�
    int maxAttack;      // �ִ� ���ݷ�
    int minGold;        // �ּ� ���
    int maxGold;        // �ִ� ���
    double spawnChance; // ���� Ȯ�� (%)

    MonsterType(const string& name, int minHealth, int maxHealth, int minAttack, int maxAttack, int minGold, int maxGold, double spawnChance)
        : name(name), minHealth(minHealth), maxHealth(maxHealth), minAttack(minAttack), maxAttack(maxAttack), minGold(minGold), maxGold(maxGold), spawnChance(spawnChance) {}
};

// ���� ���� ����Ʈ
vector<MonsterType> monsterTypes =
{
    {"���", 100, 130, 10, 15, 5, 10, 50.0},
    {"���̷���", 150, 190, 13, 20, 10, 20, 40.0},
    {"��ũ", 250, 320, 25, 40, 20, 30, 9.0},
    {"���� ���", 20, 30, 1, 5, 100, 150, 1.0}
};

// Monster Ŭ����
class Monster
{
public:
    string name;    // ���� �̸�
    int health;     // ä��
    int attackPower;// ���ݷ�
    int goldDrop;   // ���

    // ���� ��� ������
    Monster(const string& MonsterName, int Level, int minHealth, int maxHealth, int minAttack, int maxAttack, int minGold, int maxGold)
    {
        name = MonsterName;
        health = randRange(minHealth + Level * 10, maxHealth + Level * 10);
        attackPower = randRange(minAttack + Level * 2, maxAttack + Level * 2);
        goldDrop = randRange(minGold, maxGold);
    }
};

// ���� ���� ���� �Լ�
Monster generateRandomMonster(int playerLevel)
{
    double roll = (rand() % 100) + 1;
    double cumulativeChance = 0.0;

    for (const auto& type : monsterTypes)
    {
        cumulativeChance += type.spawnChance;
        if (roll <= cumulativeChance)
        {
            return Monster(
                type.name,
                playerLevel,
                type.minHealth,
                type.maxHealth,
                type.minAttack,
                type.maxAttack,
                type.minGold,
                type.maxGold
            );
        }
    }
    return Monster(
        monsterTypes[0].name,
        playerLevel,
        monsterTypes[0].minHealth,
        monsterTypes[0].maxHealth,
        monsterTypes[0].minAttack,
        monsterTypes[0].maxAttack,
        monsterTypes[0].minGold,
        monsterTypes[0].maxGold
    ); // �⺻������ ù ��° ���� ��ȯ
}

// ���� �Լ�
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
    Monster boss = generateRandomMonster(10);
    cout << "���� �̸�: " << boss.name << "���� HP: " << boss.health << ", ������ ���ݷ�: " << boss.attackPower << endl;

    // �ؿ� ������ �ڵ� �߰�(�ٸ��������? �����������?)
}

void battle(Character& player) {
    Monster enemy = generateRandomMonster(player.level);
    cout << enemy.name <<"���� ����! HP: " << enemy.health << ", ���ݷ�: " << enemy.attackPower << endl;

    while (enemy.health > 0) {
        // Player attack
        enemy.health -= player.attackPower;
        cout << player.name << " ��(��) " << enemy.name << "��(��) ����! ���� HP : " << enemy.health << endl;

        // Check if monster is defeated
        if (enemy.health <= 0) {
            cout << "�¸�!" << endl;
			player.gainExperience(50); // ����ġ�� 50 ��´ٰ� ����
			player.gold += enemy.goldDrop; // ���Ϳ� ������ ��� ��   
            cout << player.name << " ��(��) " << enemy.goldDrop << " ��带 ȹ���߽��ϴ�!" << endl;
			generateItem(player); // ������ ��� �Լ� ȣ��
            break;
        }

        // ����(������)
        player.currentHealth -= enemy.attackPower;
        cout << enemy.name << "�� ����" << player.name << " �� HP�� " << player.currentHealth << "�� ����!" << endl;

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