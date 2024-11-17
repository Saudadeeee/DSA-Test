#include <iostream>
using namespace std;

// Cấu trúc lưu thông tin về file
struct File {
    string name;
    long size;
    time_t creationTime;
    File *next; //
};

struct Folder {
    File *first;
    File *last;
};

// Khởi tạo folder
void khoiTaoFolder(Folder &folder) {
    folder.first = folder.last= nullptr;
}

// Tạo file mới
File* taoFile(const string &name, long size, time_t creationTime) {
    File *file = new File;
    file->name = name;
    file->size = size;
    file->creationTime = creationTime;
    file->next = nullptr;
    return file;
}

// Thêm file vào folder
void themFile(Folder &folder, const string &name, long size, time_t creationTime) {
    File *file = taoFile(name, size, creationTime);
    if (folder.first == nullptr) {
        folder.first = folder.last = file;
    } else {
        folder.last->next = file;
        folder.last = file;
    }
}
void nhapThongTinFile(Folder &folder) {
    int n;
    cout << "Nhap so luong file: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string name;
        long size;
        time_t creationTime;
        cout << "Nhap ten file: ";
        cin >> name;
        cout << "Nhap dung luong file (bytes): ";
        cin >> size;
        cout << "Nhap thoi gian tao file (epoch time): ";
        cin >> creationTime;
        themFile(folder, name, size, creationTime);
    }
}
void sapXepFile(Folder &folder) {
    if (folder.first == nullptr) return;

    for (File *i = folder.first; i != nullptr; i = i->next) {
        for (File *j = i->next; j != nullptr; j = j->next) {
            if (i->size > j->size) {
                swap(i->name, j->name);
                swap(i->size, j->size);
                swap(i->creationTime, j->creationTime);
            }
        }
    }
}
void xoaFile(Folder &folder) {
    if (folder.first == nullptr) return;

    // Tìm dung lượng bé nhất
    long minSize = folder.first->size;
    for (File *file = folder.first; file != nullptr; file = file->next) {
        if (file->size < minSize) {
            minSize = file->size;
        }
    }
    File *prev = nullptr;
    File *current = folder.first;
    while (current != nullptr) {
        if (current->size == minSize) {
            if (prev == nullptr) { 
                folder.first = current->next;
                delete current;
                current = folder.first;
            } else { 
                prev->next = current->next;
                delete current;
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
    folder.last = prev;
}
void inDanhSachFile(const Folder &folder) {
    for (File *file = folder.first; file != nullptr; file = file->next) {
        cout << "Ten file: " << file->name << ", Dung luong: " << file->size << " bytes, Thoi gian tao: " << file->creationTime << endl;
    }
}
int main() {
    Folder folder;
    khoiTaoFolder(folder);
    nhapThongTinFile(folder);

    sapXepFile(folder);
    cout << "\nDanh sach file sau khi sap xep theo dung luong tang dan:\n";
    inDanhSachFile(folder);
    xoaFile(folder);
    cout << "\nDanh sach file sau khi xoa cac file co dung luong be nhat va thoi gian luu lau nhat:\n";
    inDanhSachFile(folder);
    return 0;
}