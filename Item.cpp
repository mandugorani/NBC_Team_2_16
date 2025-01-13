#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// 플레이어 클래스 정의
class Character {
public:
    string name;
    int level = 1;
    int gold = 100;
    int currentHealth = 200;
    int maxHealth = 200;
    int mana = 100;
    int maxMana = 100;
    int attackPower = 30;
	int experience = 0;


    void displayStatus() {
        cout << "\n=== 플레이어 상태 ===" << endl;
        cout << "체력: " << currentHealth << "/" << maxHealth << endl;
        cout << "마나: " << mana << "/" << maxMana << endl;
        cout << "공격력: " << attackPower << endl;
        cout << "보유 골드: " << gold << "G" << endl;
    }
};

// 아이템 인터페이스 정의 (추상 클래스)
class Item {
public:
    virtual ~Item() {}
    virtual string getName() const = 0; // 아이템 이름 반환
    virtual int getPrice() const = 0;  // 아이템 가격 반환
    virtual void use(Character& Character) const = 0; // 아이템 효과 적용
};

// 체력 포션(소) 클래스
class SmallHealthPotion : public Item {
public:
    string getName() const override {
        return "체력 포션(소)";
    }

    int getPrice() const override {
        return 25;
    }

    void use(Character& Character) const override {
        int healAmount = 80;
        Character.currentHealth = min(Character.currentHealth + healAmount, Character.maxHealth);
        cout << "체력이 " << healAmount << "만큼 회복되었습니다. (현재 체력: "
            << Character.currentHealth << "/" << Character.maxHealth << ")" << endl;
    }
};

// 체력 포션(대) 클래스
class LargeHealthPotion : public Item {
public:
    string getName() const override {
        return "체력 포션(대)";
    }

    int getPrice() const override {
        return 60;
    }

    void use(Character& Character) const override {
        int healAmount = 200;
        Character.currentHealth = min(Character.currentHealth + healAmount, Character.maxHealth);
        cout << "체력이 " << healAmount << "만큼 회복되었습니다. (현재 체력: "
            << Character.currentHealth << "/" << Character.maxHealth << ")" << endl;
    }
};

// 마나 포션 클래스
class ManaPotion : public Item {
public:
    string getName() const override {
        return "마나 포션";
    }

    int getPrice() const override {
        return 30;
    }

    void use(Character& Character) const override {
        int manaAmount = 100;
        Character.mana = min(Character.mana + manaAmount, Character.maxMana);
        cout << "마나가 " << manaAmount << "만큼 회복되었습니다. (현재 마나: "
            << Character.mana << "/" << Character.maxMana << ")" << endl;
    }
};

// 공격력 강화 클래스
class AttackBoost : public Item {
public:
    string getName() const override {
        return "공격력 강화";
    }

    int getPrice() const override {
        return 50;
    }

    void use(Character& Character) const override {
        Character.attackPower = static_cast<int>(Character.attackPower * 1.5);
        cout << "공격력이 강화되었습니다! (현재 공격력: " << Character.attackPower << ")" << endl;
    }
};

// 상점 함수
void shop(Character& Character, vector<shared_ptr<Item>>& inventory) {
    vector<shared_ptr<Item>> shopItems = {
        make_shared<SmallHealthPotion>(),
        make_shared<LargeHealthPotion>(),
        make_shared<ManaPotion>(),
        make_shared<AttackBoost>(),
    };

    while (true) {
        cout << "\n=== 상점 ===" << endl;
        Character.displayStatus();
        cout << endl << endl;
        cout << "1. 아이템 구매" << endl;
        cout << "2. 아이템 판매" << endl;
        cout << "3. 상점 나가기" << endl;

        cout << "원하는 작업을 선택하세요: ";
        int choice;
        cin >> choice;

        if (choice == 3) {
            cout << "상점을 나갑니다." << endl;
            break;
        }

        if (choice == 1) {
            // 아이템 구매
            cout << "\n구매 가능한 아이템 목록:" << endl;
            for (size_t i = 0; i < shopItems.size(); ++i) {
                cout << i + 1 << ". " << shopItems[i]->getName()
                    << " - " << shopItems[i]->getPrice() << "G" << endl;
            }
            cout << shopItems.size() + 1 << ". 뒤로 가기" << endl;

            cout << "구매할 아이템 번호를 선택하세요: ";
            int itemChoice;
            cin >> itemChoice;

            if (itemChoice == shopItems.size() + 1) {
                continue;
            }

            if (itemChoice < 1 || itemChoice > shopItems.size()) {
                cout << "잘못된 선택입니다. 다시 시도하세요." << endl;
                continue;
            }

            shared_ptr<Item> selectedItem = shopItems[itemChoice - 1];
            if (Character.gold >= selectedItem->getPrice()) {
                Character.gold -= selectedItem->getPrice();
                inventory.push_back(selectedItem);
                cout << selectedItem->getName() << "을(를) 구매했습니다!" << endl;
            }
            else {
                cout << "골드가 부족합니다!" << endl;
            }
        }
        else if (choice == 2) {
            // 아이템 판매
            if (inventory.empty()) {
                cout << "인벤토리가 비어 있습니다!" << endl;
                continue;
            }

            cout << "\n판매 가능한 아이템 목록:" << endl;
            for (size_t i = 0; i < inventory.size(); ++i) {
                cout << i + 1 << ". " << inventory[i]->getName()
                    << " - " << inventory[i]->getPrice() / 2 << "G (판매 가격)" << endl;
            }
            cout << inventory.size() + 1 << ". 뒤로 가기" << endl;

            cout << "판매할 아이템 번호를 선택하세요: ";
            int sellChoice;
            cin >> sellChoice;

            if (sellChoice == inventory.size() + 1) {
                continue;
            }

            if (sellChoice < 1 || sellChoice > inventory.size()) {
                cout << "잘못된 선택입니다. 다시 시도하세요." << endl;
                continue;
            }

            shared_ptr<Item> selectedItem = inventory[sellChoice - 1];
            int sellPrice = selectedItem->getPrice() / 2;
            Character.gold += sellPrice;
            inventory.erase(inventory.begin() + sellChoice - 1);

            cout << selectedItem->getName() << "을(를) " << sellPrice
                << "G에 판매했습니다!" << endl;
        }
        else {
            cout << "잘못된 선택입니다. 다시 시도하세요." << endl;
        }
    }
}

int main() {
    Character Character;
    vector<shared_ptr<Item>> inventory;

    cout << "게임에 오신 것을 환영합니다!" << endl;

    shop(Character, inventory);

    cout << "\n게임을 종료합니다." << endl;
    Character.displayStatus();
    return 0;
}
