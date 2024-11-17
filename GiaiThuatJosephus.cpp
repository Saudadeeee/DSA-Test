#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};


int josephus(int N, int M) {
    
    Node* head = new Node(1);
    Node* current = head;
    for (int i = 2; i <= N; ++i) {
        current->next = new Node(i);
        current = current->next;
    }
    current->next = head; // hoàn tất vòng tròn

    // Xử lý loại bỏ tuần tự
    while (current->next != current) { // Duyệt cho đến khi chỉ còn một nút
        // Di chuyển đến người thứ M - 1
        for (int count = 1; count < M; ++count) {
            current = current->next;
        }
        // Loại bỏ người thứ M
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
    }

    int winner = current->data;
    delete current; // Giải phóng bộ nhớ
    return winner;
}

int main() {
    int N, M;
    cout << "Nhap so luong nguoi choi N: ";
    cin >> N;
    cout << "Nhap buoc loai bo M: ";
    cin >> M;

    int winner = josephus(N, M);
    cout << "Nguoi chien thang cuoi cung la: " << winner << endl;

    return 0;
}
