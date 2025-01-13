#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// 캐릭터 클래스를 정의한다면?
class Character {
public:
	string name;
	int level;
	int maxHealth;
	int currentHealth;
	int maxMana;        // 최대 마나
	int currentMana;    // 현재 마나
	int attackPower;
	int experience;
	int gold;

	// 생성자
	Character(string charName)
		: name(charName), level(1), maxHealth(200), currentHealth(200),
		maxMana(50), currentMana(50), attackPower(30), experience(0), gold(0) {
	}

	// 레벨업 메서드
	void levelUp() {
		if (level < 10) { // 레벨이 10보다 작을 때만 레벨업 가능
			level++;
			maxHealth += 20; // 레벨업 시 최대 체력 증가
			maxMana += 10; // 레벨업 시 최대 마나 증가
			attackPower += 5; // 레벨업 시 공격력 증가
			currentHealth = maxHealth; // 체력과 마나를 최대치로 회복
			currentMana = maxMana; // 마나와 체력을 최대치로 회복
			experience = 0; // 경험치 초기화
			cout << name << "은(는) " << level << "레벨로 레벨업했다!" << endl; // 레벨업 메시지 출력
			cout << "최대 체력: " << maxHealth << ", 최대 마나: " << maxMana
				<< ", 공격력: " << attackPower << endl; 
		}
	}

	// 경험치 획득
	void gainExperience(int exp) { // 경험치 획득 메서드
		experience += exp;
		cout << name << " 는 " << exp << " 경험치를 얻었다!" << endl; // 경험치 획득 메시지 출력
		if (experience >= 100) { // 경험치가 100 이상이면 레벨업
			levelUp();
		}
	}

	// 스킬 사용 (Judgment Blade)
	void useSkill(string skillName, int manaCost) { // 스킬 사용 메서드
		if (currentMana >= manaCost) { // 마나가 충분하면 스킬 사용
			currentMana -= manaCost; // 마나 감소
			int skillDamage = static_cast<int>(attackPower * 1.5); // 스킬 데미지 계산
			cout << name << "이(가) [" << skillName << "]를 사용했다!" << endl;
			cout << "몬스터에게 " << skillDamage << "의 데미지를 입혔다!" << endl;
			cout << "남은 마나: " << currentMana << "/" << maxMana << endl;
		}
		else {
			cout << "마나가 부족합니다! 현재 마나: " << currentMana << "/" << maxMana << endl; // 마나 부족 메시지 출력
		}
	}

	// 상태 표시
	void displayStatus() { // 캐릭터 상태 표시 메서드
		cout << "캐릭터: " << name << endl;
		cout << "레벨: " << level << ", HP: " << currentHealth << "/" << maxHealth
			<< ", MP: " << currentMana << "/" << maxMana << ", 공격력: " << attackPower << ", 소지 골드 : " << gold << ", 현재 경험치: " << experience << "/100" << endl;
	}
};

// Monster 클래스를 정의한다면?
class Monster {
public:
	int health;
	int attackPower;
	int randRange(int min, int max) {
		return min + (rand() % (max - min + 1)); // min에서 max 사이의 랜덤한 수를 반환
	}
	Monster(int level) {
		health = randRange(level * 20, level * 30);   // level * 20에서 level * 30 사이의 랜덤 체력 구현
		attackPower = randRange(level * 5, level * 10);
	}
};

void battleStart(Character& player);
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
	Monster boss(10);
	cout << "보스 HP: " << boss.health << ", 보스의 공격력: " << boss.attackPower << endl;

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
	Monster enemy(player.level);
	cout << "몬스터 등장! 몬스터 HP: " << enemy.health << ", 몬스터 공격력: " << enemy.attackPower << endl;

	while (enemy.health > 0) {
		// Player attack
		enemy.health -= player.attackPower;
		cout << player.name << " 이(가) 몬스터를 공격! 몬스터의 남은 HP: " << enemy.health << endl;

		// Check if monster is defeated
		if (enemy.health <= 0) {
			cout << "승리!" << endl;
			player.gainExperience(50); // 경험치를 50 얻는다고 가정
			player.gold += (rand() % 11) + 10; // 10~20 골드 획득   
			cout << player.name << " 는" << player.gold << " 골드를 획득했다!" << endl;
			generateItem(player); // 아이템 드랍 함수 호출
			cout << "전투 종료!" << endl;
			player.displayStatus();
			break;
		}

		// 공격(몬스터의)
		player.currentHealth -= enemy.attackPower;
		cout << "몬스터의 공격! " << player.name << " 의 HP가 " << player.currentHealth << "로 감소!" << endl;

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