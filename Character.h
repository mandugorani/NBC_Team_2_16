#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>

class Character {
public:
    std::string name;       // 캐릭터 이름
    int level;              // 레벨
    int currentHealth;      // 현재 체력
    int maxHealth;          // 최대 체력
    int attackPower;        // 공격력
    int experience;         // 경험치
    int experienceToLevelUp; // 레벨업에 필요한 경험치

    // 생성자
    Character(std::string charName);

    // 캐릭터 상태 출력 함수
    void displayStatus();

    // 경험치 얻기
    void gainExperience(int exp);

    // 레벨업 함수
    void levelUp();

    // 스킬 사용 함수 (예시로 "Judgment Blade" 사용)
    void useSkill(const std::string& skillName, int manaCost);
};

#endif
