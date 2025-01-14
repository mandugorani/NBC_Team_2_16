#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

using namespace std;

// �κ��丮 Ŭ����
class Inventory {
private:
    vector<shared_ptr<Item>> items;

public:
    void addItem(const shared_ptr<Item>& item) {
        items.push_back(item);
        cout << item->getName() << "��(��) �κ��丮�� �߰��߽��ϴ�.\n";
    }

    void useItem(Character& character) {
        if (items.empty()) {
            cout << "�κ��丮�� ��� �ֽ��ϴ�!\n";
            return;
        }

        cout << "\n=== �κ��丮 ===" << endl;
        for (size_t i = 0; i < items.size(); ++i) {
            cout << i + 1 << ". " << items[i]->getName() << endl;
        }
        cout << items.size() + 1 << ". ������\n";

        cout << "����� ������ ��ȣ�� �����ϼ���: ";
        int choice;
        cin >> choice;

        if (choice == items.size() + 1) {
            cout << "�κ��丮�� �ݽ��ϴ�.\n";
            return;
        }

        if (choice < 1 || choice > items.size()) {
            cout << "�߸��� �����Դϴ�.\n";
            return;
        }

        items[choice - 1]->use(character);
        items.erase(items.begin() + (choice - 1)); // ��� �� ����
    }

    void showInventory() const {
        cout << "\n=== ���� �κ��丮 ===\n";
        if (items.empty()) {
            cout << "�κ��丮�� ��� �ֽ��ϴ�.\n";
        }
        else {
            for (const auto& item : items) {
                cout << "- " << item->getName() << endl;
            }
        }
    }
};

