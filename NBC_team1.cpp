#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Monster.h"

using namespace std;

// 캐릭터 클래스를 정의한다면?
class Character {
public:
    string name;
    int level;
    int maxHealth;
    int currentHealth;
    int attackPower;
    int experience;
    int gold;

    // 캐릭터의 초기값 (생성자)
    Character(string charName)
        : name(charName), level(1), maxHealth(200), currentHealth(200),
        attackPower(30), experience(0), gold(0) {
    }

    // 레벨업 구현
    void levelUp() {
        if (level < 10) {
            level++;
            maxHealth += 20;
            attackPower += 5;
            currentHealth = maxHealth; // 체력을 최대치로 회복하는것 구현
            experience = 0; // 레벨업 후에 경험치를 다시 0으로 초기화
            cout << name << " 은(는) " << level << "레벨로 레벨업했다!" << endl;
            cout << "최대 체력 " << maxHealth << "로 증가, 공격력 " << attackPower << "로 증가" << endl;
        }
    }

    void gainExperience(int exp) {
        experience += exp;
        cout << name << "는 " << exp << " 경험치를 얻었다!" << endl;
        if (experience >= 100) {
            levelUp();
        }
    }

    void displayStatus() {
        cout << "Character: " << name << endl;
        cout << "레벨: " << level << ", HP: " << currentHealth << "/" << maxHealth << ", 공격력: " << attackPower << ", 골드: " << gold << endl;
    }
};
void battleStart(Character& player);

// 전투 함수
void startGame();
void battle(Character& player);
void generateItem(Character& player);

// Main 함수
int main() {
    srand(time(0)); // 코파일럿이 넣으래서 넣음
    startGame();
    return 0;
}

void startGame() {
    string name;
    cout << "캐릭터의 이름을 입력하세요: ";
    getline(cin, name);

    while (name.empty() || name.find(' ') != string::npos) {
        cout << "캐릭터의 이름에 공백을 넣을 수 없습니다: ";
        getline(cin, name);
    }

    Character player(name);
    cout << "캐릭터 생성 완료!" << endl;
    player.displayStatus();

    // 캐릭터 생성 후 전투
    while (player.level < 10) {
        battleStart(player);
    }

    // 보스가 등장하는것 구현
    cout << "축하합니다! " << player.name << " 레벨 10 달성!" << endl;
    cout << "보스 몬스터 등장:" << endl;
    Monster boss = generateBossMonster();
    cout << "보스 이름: " << boss.name << " HP: " << boss.health << ", 공격력: " << boss.attackPower << endl;

    // 밑에 보스전 코드 추가(다른방식으로? 같은방식으로?)
}

void battleStart(Character& player) {
    char choice;
    while (true) {
        cout << "전투를 시작하시겠습니까? (Y/N): ";
        cin >> choice;
        choice = toupper(choice); // 대소문자 구분 없애기

        if (choice == 'Y') {
            battle(player);
            break;
        }
        else if (choice == 'N') {
            cout << "전투를 건너뛰고 메인 루프로 돌아갑니다." << endl;
            break;
        }
        else {
            cout << "잘못된 입력입니다. Y 또는 N을 입력해주세요." << endl;
        }
    }
}

void battle(Character& player) {
    Monster enemy = generateRandomMonster(player.level);
    cout << enemy.name <<"몬스터 등장! HP: " << enemy.health << ", 공격력: " << enemy.attackPower << endl;

    while (enemy.health > 0) {
        // Player attack
        enemy.health -= player.attackPower;
        cout << player.name << " 이(가) " << enemy.name << "을(를) 공격! 남은 HP : " << enemy.health << endl;

        // Check if monster is defeated
        if (enemy.health <= 0) {
            cout << "승리!" << endl;
			player.gainExperience(50); // 경험치를 50 얻는다고 가정
			player.gold += enemy.goldDrop; // 몬스터에 설정된 골드 값   
            cout << player.name << " 이(가) " << enemy.goldDrop << " 골드를 획득했습니다!" << endl;
			generateItem(player); // 아이템 드랍 함수 호출
            break;
        }

        // 공격(몬스터의)
        player.currentHealth -= enemy.attackPower;
        cout << enemy.name << "의 공격" << player.name << " 의 HP가 " << player.currentHealth << "로 감소!" << endl;

        // 패배시
        if (player.currentHealth <= 0) {
            cout << player.name << " 가 패배했습니다." << endl;
            exit(0);
        }
    }
}

void generateItem(Character& player) {
    if (rand() % 100 < 30) { // 30%
        int itemEffect = rand() % 2; // 0: 체력 회복, 1: 공격력 증가
        if (itemEffect == 0) {
            player.currentHealth += 50;
            if (player.currentHealth > player.maxHealth) {
                player.currentHealth = player.maxHealth; // 체력 초과 방지
            }
            cout << "체력을 회복해주는 아이템 발견! 체력 회복 후 체력: " << player.currentHealth << endl;
        }
        else {
            player.attackPower += 10;
            cout << "공격력을 올려주는 아이템 발견! 총 공격력: " << player.attackPower << endl;
        }
    }
    else {
        cout << "아이템이 없다." << endl;
    }
}