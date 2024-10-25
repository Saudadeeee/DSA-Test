#include <iostream>
#include <cstring>
using namespace std;

// Cấu trúc lưu thông tin ngày sinh
struct Ngay {
    int ngay, thang, nam;
};

// Cấu trúc lưu thông tin sinh viên
struct SinhVien {
    int maSV;
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[50];
    char khoa[50];
};

// Cấu trúc Node trong danh sách liên kết
struct Node {
    SinhVien data;
    Node *link;
};

// Cấu trúc danh sách liên kết
struct List {
    Node *first;
    Node *last;
};

// Khởi tạo danh sách liên kết
void khoiTaoList(List &l) {
    l.first = l.last = nullptr;
}

// Tạo node trong danh sách liên kết
Node* taoNode(SinhVien sv) {
    Node *p = new Node;
    if (p != nullptr) {
        p->data = sv;
        p->link = nullptr;
    }
    return p;
}

// Khởi tạo ngày sinh
void nhapNgay(Ngay &ngay) {
    cout << "Nhap ngay, thang, nam: ";
    cin >> ngay.ngay >> ngay.thang >> ngay.nam;
}

void nhapSinhVien(SinhVien &sv) {
    cout << "Nhap ma SV: ";
    cin >> sv.maSV;
    cout << "Nhap ho ten: ";
    cin.ignore();
    cin.getline(sv.hoTen, 50);
    cout << "Nhap gioi tinh (0 - Nu, 1 - Nam): ";
    cin >> sv.gioiTinh;
    cout << "Nhap ngay sinh:\n";
    nhapNgay(sv.ngaySinh);
    cout << "Nhap dia chi: ";
    cin.ignore();
    cin.getline(sv.diaChi, 100);
    cout << "Nhap lop: ";
    cin >> sv.lop;
    cout << "Nhap khoa: ";
    cin >> sv.khoa;
}

// Thêm sinh viên vào danh sách theo mã sinh viên
//Ý tưởng sẽ là khi thêm vào sẽ so sánh mã sinh viên với các sinh viên có sẵn đã tồn tại trong danh sách 
void themSinhVien(List &l, SinhVien sv) {
    Node *p = taoNode(sv);
    if (l.first == nullptr || sv.maSV < l.first->data.maSV) {
        p->link = l.first;
        l.first = p;
        if (l.last == nullptr)
            l.last = p;
    } else {
        Node *q = l.first;
        while (q->link != nullptr && q->link->data.maSV < sv.maSV) {
            q = q->link;
        }
        p->link = q->link;
        q->link = p;
        if (q == l.last)
            l.last = p;
    }
}

// In danh sách sinh viên
void inDanhSachSinhVien(const List &l) {
    Node *p = l.first;
    while (p != nullptr) {
        cout << "Ma SV: " << p->data.maSV << ", Ho ten: " << p->data.hoTen << ", Ngay sinh: "
             << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << endl;
        p = p->link;
    }
}

// Tìm và xuất sinh viên có cùng ngày sinh
void timVaXuatSinhVienCungNgaySinh(const List &l) {
    Node *p = l.first;
    bool found = false;
    while (p != nullptr) {
        Node *q = p->link;
        while (q != nullptr) {
            if (p->data.ngaySinh.ngay == q->data.ngaySinh.ngay &&
                p->data.ngaySinh.thang == q->data.ngaySinh.thang &&
                p->data.ngaySinh.nam == q->data.ngaySinh.nam) {
                cout << "Ma SV: " << p->data.maSV << ", Ho ten: " << p->data.hoTen << ", Ngay sinh: "
                     << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << endl;
                cout << "Ma SV: " << q->data.maSV << ", Ho ten: " << q->data.hoTen << ", Ngay sinh: "
                     << q->data.ngaySinh.ngay << "/" << q->data.ngaySinh.thang << "/" << q->data.ngaySinh.nam << endl;
                found = true;
            }
            q = q->link;
        }
        p = p->link;
    }
    if (!found) {
        cout << "Khong tim thay sinh vien cung ngay sinh" << endl;
    }
}

// Loại bỏ sinh viên có cùng ngày sinh
void loaiBoSinhVienCungNgaySinh(List &l) {
    Node *p = l.first;
    Node *prev = nullptr;
    while (p != nullptr) {
        Node *q = p->link;
        bool found = false;
        while (q != nullptr) {//So sánh từng thành phần trong ngày sinh
            if (p->data.ngaySinh.ngay == q->data.ngaySinh.ngay &&
                p->data.ngaySinh.thang == q->data.ngaySinh.thang &&
                p->data.ngaySinh.nam == q->data.ngaySinh.nam) {
                found = true;
                break;
            }
            q = q->link;
        }
        if (found) {
            if (prev == nullptr) { // xoa o dau danh sach
                l.first = p->link;
                delete p;
                p = l.first;
            } else { // xoa o giua hoac cuoi
                prev->link = p->link;
                delete p;
                p = prev->link;
            }
        } else {
            prev = p;
            p = p->link;
        }
    }
}

int main(){
    //Khai báo list
    List l;
    khoiTaoList(l);
    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        SinhVien sv;
        cout << "Nhap thong tin sinh vien thu " << i + 1 << ":\n";
        nhapSinhVien(sv);
        themSinhVien(l, sv);
    }

    cout << "\nDanh sach sinh vien sau khi sap xep:\n";
    inDanhSachSinhVien(l);

    cout << "\nSinh vien co cung ngay sinh:\n";
    timVaXuatSinhVienCungNgaySinh(l);

    cout << "\nXoa sinh vien co cung ngay sinh...\n";
    loaiBoSinhVienCungNgaySinh(l);
    cout << "\nDanh sach sinh vien sau khi xoa:\n";
    inDanhSachSinhVien(l);

    return 0;
}