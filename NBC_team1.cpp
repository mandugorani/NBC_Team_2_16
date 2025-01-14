#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Character.h"  // 이미 만들어진 Character 클래스 포함

using namespace std;

class Monster
{
public:
    string name;      // 몬스터 이름
    int health;       // 몬스터 체력
    int attackPower;  // 몬스터 공격력

    // 몬스터 생성자
    Monster(int level);

    // 랜덤 값 생성 함수 (min과 max 사이의 값 반환)
    int randRange(int min, int max);
};

// 몬스터 클래스 구현

Monster::Monster(int level)
{
    name = "몬스터";
    health = randRange(level * 20, level * 30);  // 몬스터 체력 생성
    attackPower = randRange(level * 5, level * 10);  // 몬스터 공격력 생성
}

int Monster::randRange(int min, int max)
{
    return min + (rand() % (max - min + 1));  // min과 max 사이의 랜덤값 생성
}

// 전투 함수
void battle(Character& player, Monster& enemy)
{
    while (enemy.health > 0)
    {
        cout << "\n1. 공격  2. 스킬 사용  3. 상태 보기" << endl;
        cout << "선택: ";
        int choice;
        cin >> choice;

        if (choice == 1) {  // 기본 공격
            enemy.health -= player.attackPower;
            cout << player.name << " 이(가) 몬스터를 공격! 몬스터의 남은 HP: " << enemy.health << endl;
        }
        else if (choice == 2) {  // 스킬 사용
            player.useSkill("Judgment Blade", 20);  // 예시로 "Judgment Blade" 스킬 사용
            enemy.health -= static_cast<int>(player.attackPower * 1.5);
        }
        else if (choice == 3) {  // 상태 확인
            player.displayStatus();
            continue;  // 상태를 본 후 다시 선택
        }
        else {
            cout << "잘못된 입력입니다." << endl;
            continue;
        }

        // 몬스터가 쓰러졌는지 확인
        if (enemy.health <= 0) {
            cout << "승리! " << endl;
            player.gainExperience(50);  // 경험치 50 얻기
            player.displayStatus();
            break;
        }

        // 몬스터의 반격
        player.currentHealth -= enemy.attackPower;
        cout << "몬스터의 공격! " << player.name << " 의 HP가 " << player.currentHealth << "로 감소!" << endl;

        // 플레이어가 패배했는지 확인
        if (player.currentHealth <= 0) {
            cout << player.name << " 이(가) 패배했습니다. 게임 종료." << endl;
            exit(0);
        }
    }
}

int main() {
    srand(time(0));  // 난수 초기화

    string name;
    cout << "캐릭터의 이름을 입력하세요: ";
    getline(cin, name);

    while (name.empty() || name.find(' ') != string::npos) {
        cout << "이름에 공백을 넣을 수 없습니다. 다시 입력하세요: ";
        getline(cin, name);
    }

    Character player(name);  // 생성 시 히든 캐릭터가 활성화되지 않음
    player.displayStatus();  // 캐릭터 상태 출력

    // 전투 루프
    while (player.level < 10) {  // 레벨 10에 도달할 때까지 전투 진행
        cout << "전투를 시작합니다!" << endl;
        Monster enemy(player.level);  // 플레이어 레벨에 맞춰 몬스터 생성
        battle(player, enemy);  // 몬스터와 전투 시작
    }

    // 레벨 10 도달 후 보스 등장
    cout << "축하합니다! " << player.name << " 은(는) 레벨 10에 도달했습니다!" << endl;
    cout << "보스 몬스터 등장!" << endl;
    Monster boss(10);  // 보스 몬스터 생성
    cout << "보스 HP: " << boss.health << ", 보스 공격력: " << boss.attackPower << endl;

    // 보스와 전투
    battle(player, boss);

    return 0;
}
