#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// �÷��̾� Ŭ���� ����
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
        cout << "\n=== �÷��̾� ���� ===" << endl;
        cout << "ü��: " << currentHealth << "/" << maxHealth << endl;
        cout << "����: " << mana << "/" << maxMana << endl;
        cout << "���ݷ�: " << attackPower << endl;
        cout << "���� ���: " << gold << "G" << endl;
    }
};

// ������ �������̽� ���� (�߻� Ŭ����)
class Item {
public:
    virtual ~Item() {}
    virtual string getName() const = 0; // ������ �̸� ��ȯ
    virtual int getPrice() const = 0;  // ������ ���� ��ȯ
    virtual void use(Character& Character) const = 0; // ������ ȿ�� ����
};

// ü�� ����(��) Ŭ����
class SmallHealthPotion : public Item {
public:
    string getName() const override {
        return "ü�� ����(��)";
    }

    int getPrice() const override {
        return 25;
    }

    void use(Character& Character) const override {
        int healAmount = 80;
        Character.currentHealth = min(Character.currentHealth + healAmount, Character.maxHealth);
        cout << "ü���� " << healAmount << "��ŭ ȸ���Ǿ����ϴ�. (���� ü��: "
            << Character.currentHealth << "/" << Character.maxHealth << ")" << endl;
    }
};

// ü�� ����(��) Ŭ����
class LargeHealthPotion : public Item {
public:
    string getName() const override {
        return "ü�� ����(��)";
    }

    int getPrice() const override {
        return 60;
    }

    void use(Character& Character) const override {
        int healAmount = 200;
        Character.currentHealth = min(Character.currentHealth + healAmount, Character.maxHealth);
        cout << "ü���� " << healAmount << "��ŭ ȸ���Ǿ����ϴ�. (���� ü��: "
            << Character.currentHealth << "/" << Character.maxHealth << ")" << endl;
    }
};

// ���� ���� Ŭ����
class ManaPotion : public Item {
public:
    string getName() const override {
        return "���� ����";
    }

    int getPrice() const override {
        return 30;
    }

    void use(Character& Character) const override {
        int manaAmount = 100;
        Character.mana = min(Character.mana + manaAmount, Character.maxMana);
        cout << "������ " << manaAmount << "��ŭ ȸ���Ǿ����ϴ�. (���� ����: "
            << Character.mana << "/" << Character.maxMana << ")" << endl;
    }
};

// ���ݷ� ��ȭ Ŭ����
class AttackBoost : public Item {
public:
    string getName() const override {
        return "���ݷ� ��ȭ";
    }

    int getPrice() const override {
        return 50;
    }

    void use(Character& Character) const override {
        Character.attackPower = static_cast<int>(Character.attackPower * 1.5);
        cout << "���ݷ��� ��ȭ�Ǿ����ϴ�! (���� ���ݷ�: " << Character.attackPower << ")" << endl;
    }
};

// ���� �Լ�
void shop(Character& Character, vector<shared_ptr<Item>>& inventory) {
    vector<shared_ptr<Item>> shopItems = {
        make_shared<SmallHealthPotion>(),
        make_shared<LargeHealthPotion>(),
        make_shared<ManaPotion>(),
        make_shared<AttackBoost>(),
    };

    while (true) {
        cout << "\n=== ���� ===" << endl;
        Character.displayStatus();
        cout << endl << endl;
        cout << "1. ������ ����" << endl;
        cout << "2. ������ �Ǹ�" << endl;
        cout << "3. ���� ������" << endl;

        cout << "���ϴ� �۾��� �����ϼ���: ";
        int choice;
        cin >> choice;

        if (choice == 3) {
            cout << "������ �����ϴ�." << endl;
            break;
        }

        if (choice == 1) {
            // ������ ����
            cout << "\n���� ������ ������ ���:" << endl;
            for (size_t i = 0; i < shopItems.size(); ++i) {
                cout << i + 1 << ". " << shopItems[i]->getName()
                    << " - " << shopItems[i]->getPrice() << "G" << endl;
            }
            cout << shopItems.size() + 1 << ". �ڷ� ����" << endl;

            cout << "������ ������ ��ȣ�� �����ϼ���: ";
            int itemChoice;
            cin >> itemChoice;

            if (itemChoice == shopItems.size() + 1) {
                continue;
            }

            if (itemChoice < 1 || itemChoice > shopItems.size()) {
                cout << "�߸��� �����Դϴ�. �ٽ� �õ��ϼ���." << endl;
                continue;
            }

            shared_ptr<Item> selectedItem = shopItems[itemChoice - 1];
            if (Character.gold >= selectedItem->getPrice()) {
                Character.gold -= selectedItem->getPrice();
                inventory.push_back(selectedItem);
                cout << selectedItem->getName() << "��(��) �����߽��ϴ�!" << endl;
            }
            else {
                cout << "��尡 �����մϴ�!" << endl;
            }
        }
        else if (choice == 2) {
            // ������ �Ǹ�
            if (inventory.empty()) {
                cout << "�κ��丮�� ��� �ֽ��ϴ�!" << endl;
                continue;
            }

            cout << "\n�Ǹ� ������ ������ ���:" << endl;
            for (size_t i = 0; i < inventory.size(); ++i) {
                cout << i + 1 << ". " << inventory[i]->getName()
                    << " - " << inventory[i]->getPrice() / 2 << "G (�Ǹ� ����)" << endl;
            }
            cout << inventory.size() + 1 << ". �ڷ� ����" << endl;

            cout << "�Ǹ��� ������ ��ȣ�� �����ϼ���: ";
            int sellChoice;
            cin >> sellChoice;

            if (sellChoice == inventory.size() + 1) {
                continue;
            }

            if (sellChoice < 1 || sellChoice > inventory.size()) {
                cout << "�߸��� �����Դϴ�. �ٽ� �õ��ϼ���." << endl;
                continue;
            }

            shared_ptr<Item> selectedItem = inventory[sellChoice - 1];
            int sellPrice = selectedItem->getPrice() / 2;
            Character.gold += sellPrice;
            inventory.erase(inventory.begin() + sellChoice - 1);

            cout << selectedItem->getName() << "��(��) " << sellPrice
                << "G�� �Ǹ��߽��ϴ�!" << endl;
        }
        else {
            cout << "�߸��� �����Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }
}

int main() {
    Character Character;
    vector<shared_ptr<Item>> inventory;

    cout << "���ӿ� ���� ���� ȯ���մϴ�!" << endl;

    shop(Character, inventory);

    cout << "\n������ �����մϴ�." << endl;
    Character.displayStatus();
    return 0;
}
