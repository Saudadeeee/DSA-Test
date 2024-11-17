#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *link;
};
struct List {
    Node *first;
    Node *last;
};
void khoiTaoList(List &l) {
    l.first = l.last = nullptr;
}
Node* taoNode(int data) {
    Node *p = new Node;
    if (p != nullptr) {
        p->data = data;
        p->link = nullptr;
    }
    return p;
}
void xoaNodeDau(List &l) {
    if (l.first != nullptr) {
        Node *p = l.first;
        l.first = l.first->link;
        delete p;
        if (l.first == nullptr) {
            l.last = nullptr;
        }
    }
}
void inDanhSach(const List &l) {
    Node *p = l.first;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->link;
    }
    cout << endl;
}
void xoaNodeCuoi(List &l) {
    if (l.first != nullptr) {
        if (l.first == l.last) { 
            delete l.first;
            l.first = l.last = nullptr;
        } else {
            Node *p = l.first;
            while (p->link != l.last) {
                p = p->link;
            }
            delete l.last;
            l.last = p;
            l.last->link = nullptr;
        }
    }
}
void xoaNodeSau(List &l, Node *node) {
    if (node != nullptr && node->link != nullptr) {
        Node *p = node->link;
        node->link = p->link;
        if (p == l.last) {
            l.last = node;
        }
        delete p;
    }
}
void nhapNodeTuBanPhim(List &l) {
    int data;
    cout << "Nhap gia tri cho node: ";
    cin >> data;
    Node *p = taoNode(data);
    if (l.first == nullptr) {
        l.first = l.last = p;
    } else {
        l.last->link = p;
        l.last = p;
    }
}

int main() {
    List l;
    khoiTaoList(l);
    int n;
    cout << "Nhap so luong node: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        nhapNodeTuBanPhim(l);
    }
     cout << "Danh sach sau khi nhap: ";
    inDanhSach(l);
    xoaNodeDau(l);
    cout << "Danh sach sau khi xoa node dau: ";
    inDanhSach(l);
    xoaNodeCuoi(l);
    cout << "Danh sach sau khi xoa node cuoi: ";
    inDanhSach(l);
    Node *node = l.first->link; 
    xoaNodeSau(l, node);
    cout << "Danh sach sau khi xoa node sau node thu hai: ";
    inDanhSach(l);

    return 0;
}