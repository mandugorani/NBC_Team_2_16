#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// 캐릭터 클래스를 정의한다면?
class Character
{
public:
    string name;
    int level;
    int maxHealth;
    int currentHealth;
    int maxMana;
    int currentMana;
    int attackPower;
    int experience;
    int gold;


    // 캐릭터의 초기값 (생성자)
    Character(string charName)
        : name(charName), level(1), maxHealth(200), currentHealth(200),
        maxMana(50), currentMana(50), 
        attackPower(30), experience(0), gold(0) {
    }


    // 레벨업 구현
    void levelUp()
    {
        if (level < 10) // 레벨업은 10보다 아래일때
        {
            level++;
            // 최대체력 +20, 마나 +10
            maxHealth += 20;
            maxMana += 10;
            // 공격력 +5
            attackPower += 5;
            // 체력과 마나를 최대치로 회복
            currentHealth = maxHealth;
            currentMana = maxMana;
            experience = 0; // 레벨업 후에 경험치를 다시 0으로 초기화 
            cout << name << " 은(는) " << level << "레벨로 레벨업했다!" << endl;
            cout << "최대 체력 " << maxHealth << "(으)로 증가, 최대 마나 " << maxMana << "(으)로 증가, 공격력 " << attackPower << "(으)로 증가" << endl;
        }
    }

    void gainExperience(int exp)
    {
        experience += exp;
        cout << name << "는 " << exp << " 경험치를 얻었다!" << endl;
        if (experience >= 100)
        {
            levelUp();
        }
    }

    void useSkill(string skillName, int manaCost)
    { if (currentMana >= manaCost)
    {
        currentMana -= manaCost;
        int skillDamage = static_cast<int>(attackPower * 1.5);
        cout << name << "이(가) [" << skillName << "]를 사용했다!" << endl;
        cout << "남은 마나: " << currentMana << "/" << maxMana << endl;
    }
    else
    {
        cout << "마나가 부족합니다!" << endl;
    }
    }

    void displayStatus()
    {
        cout << "Character: " << name << endl;
        cout << "레벨: " << level << ", HP: " << currentHealth << "/" << maxHealth << ", MP: " << currentMana << "/" << maxMana << ", 공격력: " << attackPower << ", 골드: " << gold << ", 경험치: " << experience << "/100" << endl;
    }
};

// 랜덤 범위 함수
int randRange(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

// 몬스터 타입 구조체
struct MonsterType
{
    string name;        // 몬스터 이름
    int minHealth;      // 최소 채력
    int maxHealth;      // 최대 채력
    int minAttack;      // 최소 공격력
    int maxAttack;      // 최대 공격력
    int minGold;        // 최소 골드
    int maxGold;        // 최대 골드
    double spawnChance; // 등장 확률 (%)

    MonsterType(const string& name, int minHealth, int maxHealth, int minAttack, int maxAttack, int minGold, int maxGold, double spawnChance)
        : name(name), minHealth(minHealth), maxHealth(maxHealth), minAttack(minAttack), maxAttack(maxAttack), minGold(minGold), maxGold(maxGold), spawnChance(spawnChance) {}
};

// 몬스터 종류 리스트
vector<MonsterType> monsterTypes =
{
    {"고블린", 100, 130, 10, 15, 5, 10, 50.0},
    {"스켈레톤", 150, 190, 13, 20, 10, 20, 40.0},
    {"오크", 250, 320, 25, 40, 20, 30, 9.0},
    {"보물 고블린", 20, 30, 1, 5, 100, 150, 1.0}
};

// Monster 클래스
class Monster
{
public:
    string name;    // 몬스터 이름
    int health;     // 채력
    int attackPower;// 공격력
    int goldDrop;   // 골드

    // 레벨 기반 생성자
    Monster(const string& MonsterName, int Level, int minHealth, int maxHealth, int minAttack, int maxAttack, int minGold, int maxGold)
    {
        name = MonsterName;
        health = randRange(minHealth + Level * 10, maxHealth + Level * 10);
        attackPower = randRange(minAttack + Level * 2, maxAttack + Level * 2);
        goldDrop = randRange(minGold, maxGold);
    }
};

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
    return Monster(
        monsterTypes[0].name,
        playerLevel,
        monsterTypes[0].minHealth,
        monsterTypes[0].maxHealth,
        monsterTypes[0].minAttack,
        monsterTypes[0].maxAttack,
        monsterTypes[0].minGold,
        monsterTypes[0].maxGold
    ); // 기본적으로 첫 번째 몬스터 반환
}

// 전투 함수
void battleStart(Character& player);
void startGame();
void battle(Character& player);
void generateItem(Character& player);

// Main 함수
int main()
{
    srand(time(0)); // 코파일럿이 넣으래서 넣음
    startGame();
    return 0;
}

void startGame()
{
    string name;
    cout << "캐릭터의 이름을 입력하세요: ";
    getline(cin, name);

    while (name.empty() || name.find(' ') != string::npos)
    {
        cout << "캐릭터의 이름에 공백을 넣을 수 없습니다: ";
        getline(cin, name);
    }

    Character player(name);
    cout << "캐릭터 생성 완료!" << endl;
    player.displayStatus();

    // 캐릭터 생성 후 전투
    while (player.level < 10)
    {
        battleStart(player);
    }

    // 보스가 등장하는것 구현
    cout << "축하합니다! " << player.name << " 레벨 10 달성!" << endl;
    cout << "보스 몬스터 등장:" << endl;
    Monster boss = generateRandomMonster(10);
    cout << "보스 이름: " << boss.name << "보스 HP: " << boss.health << ", 보스의 공격력: " << boss.attackPower << endl;

    // 밑에 보스전 코드 추가(다른방식으로? 같은방식으로?)
}

void battleStart(Character& player)
{
    char choice;
    while (true)
    {
        cout << "전투를 시작하시겠습니까? (Y/N): ";
        cin >> choice;
        choice = toupper(choice); // 대소문자 구분 없애기

        if (choice == 'Y')
        {
            battle(player);
            break;
        }
        else if (choice == 'N')
        {
            cout << "전투를 건너뛰고 메인 루프로 돌아갑니다." << endl;
            break;
        }
        else
        {
            cout << "잘못된 입력입니다. Y 또는 N을 입력해주세요." << endl;
        }
    }
}

void battle(Character& player)
{
    Monster enemy = generateRandomMonster(player.level);
    cout << enemy.name << " 몬스터 등장! HP: " << enemy.health << ", 공격력: " << enemy.attackPower << endl;

    while (enemy.health > 0)
    {
        cout << "\n1. 공격  2. 스킬 사용  3. 상태 보기" << endl;
        cout << "선택: ";
        int choice;
        cin >> choice;

        if (choice == 1) // 기본 공격
        {
            enemy.health -= player.attackPower;
            cout << player.name << " 이(가) " << enemy.name << "을(를) 공격! 남은 HP : " << enemy.health << endl;
        }
        else if (choice == 2) // 스킬 사용
        {
            player.useSkill("Judgment Blade", 20);
            enemy.health -= player.attackPower * 1.5; // 스킬은 공격력의 1.5배
            cout << enemy.name << "의 남은 HP: " << enemy.health << endl;
        }
        else if (choice == 3) // 상태 확인
        {
            player.displayStatus();
            continue; // 상태를 본 후 다시 선택
        }
        else
        {
            cout << "잘못된 입력입니다. 다시 선택하세요." << endl;
            continue; // 잘못된 입력 시 다시 선택
        }

        // Check if monster is defeated
        if (enemy.health <= 0)
        {
            cout << "승리!" << endl;
            player.gainExperience(50); // 경험치를 50 얻는다고 가정
            player.gold += enemy.goldDrop; // 몬스터에 설정된 골드 값   
            cout << player.name << " 이(가) " << enemy.goldDrop << " 골드를 획득했습니다!" << endl;
            generateItem(player); // 아이템 드랍 함수 호출
            player.displayStatus();
            break;
        }

        // 몬스터 공격
        player.currentHealth -= enemy.attackPower;
        cout << enemy.name << "의 공격! " << player.name << " 의 HP가 " << player.currentHealth << "로 감소!" << endl;

        // 패배시
        if (player.currentHealth <= 0)
        {
            cout << player.name << " 가 패배했습니다." << endl;
            exit(0);
        }
    }
}

void generateItem(Character& player)
{
    if (rand() % 100 < 30)  // 30%
    {
        int itemEffect = rand() % 2; // 0: 체력 회복, 1: 공격력 증가
        if (itemEffect == 0)
        {
            player.currentHealth += 50;
            if (player.currentHealth > player.maxHealth)
            {
                player.currentHealth = player.maxHealth; // 체력 초과 방지
            }
            cout << "체력을 회복해주는 아이템 발견! 체력 회복 후 체력: " << player.currentHealth << endl;
        }
        else {
            player.attackPower += 10;
            cout << "공격력을 올려주는 아이템 발견! 총 공격력: " << player.attackPower << endl;
        }
    }
    else
    {
        cout << "아이템이 없다." << endl;
    }
}