#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

using namespace std;

// 인벤토리 클래스
class Inventory {
private:
    vector<shared_ptr<Item>> items;

public:
    void addItem(const shared_ptr<Item>& item) {
        items.push_back(item);
        cout << item->getName() << "을(를) 인벤토리에 추가했습니다.\n";
    }

    void useItem(Character& character) {
        if (items.empty()) {
            cout << "인벤토리가 비어 있습니다!\n";
            return;
        }

        cout << "\n=== 인벤토리 ===" << endl;
        for (size_t i = 0; i < items.size(); ++i) {
            cout << i + 1 << ". " << items[i]->getName() << endl;
        }
        cout << items.size() + 1 << ". 나가기\n";

        cout << "사용할 아이템 번호를 선택하세요: ";
        int choice;
        cin >> choice;

        if (choice == items.size() + 1) {
            cout << "인벤토리를 닫습니다.\n";
            return;
        }

        if (choice < 1 || choice > items.size()) {
            cout << "잘못된 선택입니다.\n";
            return;
        }

        items[choice - 1]->use(character);
        items.erase(items.begin() + (choice - 1)); // 사용 후 삭제
    }

    void showInventory() const {
        cout << "\n=== 현재 인벤토리 ===\n";
        if (items.empty()) {
            cout << "인벤토리가 비어 있습니다.\n";
        }
        else {
            for (const auto& item : items) {
                cout << "- " << item->getName() << endl;
            }
        }
    }
};

