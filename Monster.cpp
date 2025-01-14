#include "Monster.h"
#include <cstdlib>

// 구현부에 선언 있는지 확인
// 랜덤 범위 함수 구현
int randRange(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

// 몬스터 종류 리스트
// 이름, 체력, 공격력, 골드, 확률
vector<MonsterType> monsterTypes =
{
    {"고블린", 80, 110, 8, 13, 5, 10, 50.0},
    {"스켈레톤", 120, 180, 10, 18, 10, 20, 40.0},
    {"오크", 200, 280, 20, 35, 20, 30, 9.0},
    {"보물 고블린", 20, 30, 1, 5, 100, 150, 1.0}
};

// 보스 몬스터
Monster generateBossMonster()
{
    string bossName = "정예 오크";       // 보스 전용 이름
    int bossHealth = 1000;      // 보스 체력
    int bossAttackPower = 70;   // 보스 공격력
    int bossGoldDrop = 500;     // 보스 처치 시 보상 골드

    return Monster(bossName, 10, bossHealth, bossHealth, bossAttackPower, bossAttackPower, bossGoldDrop, bossGoldDrop);
}

// MonsterType 생성자 구현
MonsterType::MonsterType(const string& name, int minHealth, int maxHealth, int minAttack, int maxAttack, int minGold, int maxGold, double spawnChance)
    :name(name), minHealth(minHealth), maxHealth(maxHealth), minAttack(minAttack), maxAttack(maxAttack), minGold(minGold), maxGold(maxGold), spawnChance(spawnChance) {}

// Monster 생성자 구현
Monster::Monster(const string& MonsterName, int Level, int minHealth, int maxHealth, int minAttack, int maxAttack, int minGold, int maxGold)
{
    name = MonsterName;
    health = randRange(minHealth + Level * 10, maxHealth + Level * 10);
    attackPower = randRange(minAttack + Level * 2, maxAttack + Level * 2);
    goldDrop = randRange(minGold, maxGold);
}

// 랜덤 몬스터 생성 함수
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

    // 기본적으로 첫 번째 몬스터 반환
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