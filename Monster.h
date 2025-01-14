#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <vector>

using namespace std;

// 헤더에는 선언만 있어야 한다
// 랜덤 범위 함수 선언
int randRange(int min, int max);

// 몬스터 타입 구조체 선언
struct MonsterType
{
    string name;        // 몬스터 이름
    int minHealth;      // 최소 체력
    int maxHealth;      // 최대 체력
    int minAttack;      // 최소 공격력
    int maxAttack;      // 최대 공격력
    int minGold;        // 최소 골드
    int maxGold;        // 최대 골드
    double spawnChance; // 등장 확률 (%)

    MonsterType(const string& name, int minHealth, int maxHealth, int minAttack, int maxAttack, int minGold, int maxGold, double spawnChance);
};

// Monster 클래스 선언
class Monster
{
public:
    string name;    // 몬스터 이름
    int health;     // 체력
    int attackPower;// 공격력
    int goldDrop;   // 골드

    //생성자 선언
    Monster(const string& MonsterName, int Level, int minHealth, int maxHealth, int minAttack, int maxAttack, int minGold, int maxGold);
};

// 몬스터 종류 리스트 선언
extern vector<MonsterType> monsterType;

// 랜덤 몬스터 생성 함수 선언
Monster generateRandomMonster(int playerLevel);

// 보스 몬스터 선언
Monster generateBossMonster();

#endif // MONSTER_H

// 수정 선언부에 구현부 코드가 섞여있었다.