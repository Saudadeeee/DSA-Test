
#include <iostream>
#include <string>

// Định nghĩa cấu trúc Gỗ
struct Wood {
    std::string type;
    int size;
    int age;
    Wood* next;
    
    Wood(const std::string& t, int s, int a) : type(t), size(s), age(a), next(nullptr) {}
};

// Định nghĩa stack cho từng loại gỗ
class WoodStack {
public:
    std::string type;
    Wood* top;

    WoodStack(const std::string& t) : type(t), top(nullptr) {}

    // Hàm thêm gỗ vào stack
    void push(int size, int age) {
        Wood* newWood = new Wood(type, size, age);
        newWood->next = top;
        top = newWood;
    }

    // Hàm lấy gỗ ra khỏi stack
    Wood* pop() {
        if (top == nullptr) {
            std::cout << "Trong!" << std::endl;
            return nullptr;
        }
        Wood* topWood = top;
        top = top->next;
        return topWood;
    }

    // Hàm đếm số lượng gỗ có cùng tuổi
    int countSameAge(int age) {
        int count = 0;
        Wood* current = top;
        while (current != nullptr) {
            if (current->age == age) {
                count++;
            }
            current = current->next;
        }
        return count;
    }

    // Hàm hiển thị các thanh gỗ trong stack
    void display() const {
        std::cout << "Loai go " << type << ":\n";
        Wood* current = top;
        while (current != nullptr) {
            std::cout << "  Do dai: " << current->size << ", Tuoi: " << current->age << std::endl;
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    // Tạo stack cho từng loại gỗ
    WoodStack GoKeo("Go_Keo");
    WoodStack GoNghien("Go_Nghien");

    // Thêm gỗ vào kho
    GoKeo.push(5, 10);
    GoKeo.push(3, 15);
    GoNghien.push(4, 8);
    GoKeo.push(3, 10);

    // Hiển thị kho
    std::cout << "Go trong kho:\n";
    GoKeo.display();
    GoNghien.display();

    // Đếm số lượng gỗ cùng tuổi
    std::cout << "So go co so tuoi la 10 la: " << GoKeo.countSameAge(10) << std::endl;

    // Lấy gỗ ra khỏi kho
    Wood* removedWood = GoKeo.pop();
    if (removedWood) {
        std::cout << "So loai go: Type: " << removedWood->type << ", Size: " << removedWood->size
                  << ", Age: " << removedWood->age << std::endl;
        delete removedWood;
    }

    // Hiển thị kho sau khi lấy gỗ
    std::cout << "\nSo go sau khi lay go la:\n";
    GoKeo.display();
    GoNghien.display();

    return 0;
}