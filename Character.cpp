#include "Character.h"
#include <iostream>

Character::Character(std::string charName)
{
    name = charName;
    level = 1;
    currentHealth = 200;
    maxHealth = 200;
    attackPower = 30;
    experience = 0;
    experienceToLevelUp = 100;  // 처음엔 100 경험치로 레벨업
}

void Character::displayStatus()
{
    std::cout << "이름: " << name << ", 레벨: " << level << ", 체력: " << currentHealth << "/" << maxHealth << ", 공격력: " << attackPower << ", 경험치: " << experience << "/" << experienceToLevelUp << std::endl;
}

void Character::gainExperience(int exp)
{
    experience += exp;
    std::cout << name << " 이(가) " << exp << " 경험치를 얻었습니다!" << std::endl;

    // 경험치가 충분하면 레벨업
    while (experience >= experienceToLevelUp) {
        experience -= experienceToLevelUp;
        levelUp();
    }
}

void Character::levelUp()
{
    if (level < 10) {
        level++;
        experienceToLevelUp += 100;  // 레벨업 시 필요한 경험치 증가
        maxHealth += level * 20;     // 레벨업 시 체력 증가
        attackPower += level * 5;    // 레벨업 시 공격력 증가
        currentHealth = maxHealth;  // 체력은 최대 체력으로 회복
        std::cout << name << " 이(가) 레벨 " << level << " 로 레벨업했습니다!" << std::endl;
    }
}

void Character::useSkill(const std::string& skillName, int manaCost)
{
    std::cout << skillName << " 스킬을 사용했습니다! 마나 " << manaCost << " 소모!" << std::endl;
}
