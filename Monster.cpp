#include "Monster.h"
#include <cstdlib>

// �����ο� ���� �ִ��� Ȯ��
// ���� ���� �Լ� ����
int randRange(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

// ���� ���� ����Ʈ
// �̸�, ü��, ���ݷ�, ���, Ȯ��
vector<MonsterType> monsterTypes =
{
    {"���", 80, 110, 8, 13, 5, 10, 50.0},
    {"���̷���", 120, 180, 10, 18, 10, 20, 40.0},
    {"��ũ", 200, 280, 20, 35, 20, 30, 9.0},
    {"���� ���", 20, 30, 1, 5, 100, 150, 1.0}
};

// ���� ����
Monster generateBossMonster()
{
    string bossName = "���� ��ũ";       // ���� ���� �̸�
    int bossHealth = 1000;      // ���� ü��
    int bossAttackPower = 70;   // ���� ���ݷ�
    int bossGoldDrop = 500;     // ���� óġ �� ���� ���

    return Monster(bossName, 10, bossHealth, bossHealth, bossAttackPower, bossAttackPower, bossGoldDrop, bossGoldDrop);
}

// MonsterType ������ ����
MonsterType::MonsterType(const string& name, int minHealth, int maxHealth, int minAttack, int maxAttack, int minGold, int maxGold, double spawnChance)
    :name(name), minHealth(minHealth), maxHealth(maxHealth), minAttack(minAttack), maxAttack(maxAttack), minGold(minGold), maxGold(maxGold), spawnChance(spawnChance) {}

// Monster ������ ����
Monster::Monster(const string& MonsterName, int Level, int minHealth, int maxHealth, int minAttack, int maxAttack, int minGold, int maxGold)
{
    name = MonsterName;
    health = randRange(minHealth + Level * 10, maxHealth + Level * 10);
    attackPower = randRange(minAttack + Level * 2, maxAttack + Level * 2);
    goldDrop = randRange(minGold, maxGold);
}

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

    // �⺻������ ù ��° ���� ��ȯ
    return Monster(
        monsterTypes[0].name,
        playerLevel,
        monsterTypes[0].minHealth,
        monsterTypes[0].maxHealth,
        monsterTypes[0].minAttack,
        monsterTypes[0].maxAttack,
        monsterTypes[0].minGold,
        monsterTypes[0].maxGold
    );
}