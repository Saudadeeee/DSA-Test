#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>

using namespace std;

struct Node {
    string word;
    Node* next;
    
    Node(string w) : word(w), next(nullptr) {}
};

void addNode(Node*& head, const string& word) {
    Node* newNode = new Node(word);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

string findMostFrequentWord(Node* head) {
    unordered_map<string, int> wordCount;
    Node* temp = head;
    
    while (temp != nullptr) {
        wordCount[temp->word]++;
        temp = temp->next;
    }
    
    string mostFrequentWord;
    int maxCount = 0;
    
    for (const auto& pair : wordCount) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequentWord = pair.first;
        }
    }
    
    return mostFrequentWord;
}

void removeRedundantWords(Node*& head) {
    Node* current = head;
    Node* prev = nullptr;
    
    while (current != nullptr && current->next != nullptr) {
        if (current->word == current->next->word) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
}

int countUniqueWords(Node* head) {
    unordered_map<string, bool> uniqueWords;
    Node* temp = head;
    
    while (temp != nullptr) {
        uniqueWords[temp->word] = true;
        temp = temp->next;
    }
    
    return uniqueWords.size();
}

// Hàm để nhập câu và chia thành các từ
void processSentence(Node*& head, const string& sentence) {
    stringstream ss(sentence);
    string word;
    
    while (ss >> word) {
        addNode(head, word);
    }
}

int main() {
    string sentence;
    cout << "Nhập câu: ";
    getline(cin, sentence);
    Node* head = nullptr;

    // Xử lý câu để lưu vào danh sách liên kết
    processSentence(head, sentence);
    
    // Tìm từ xuất hiện nhiều nhất
    string mostFrequent = findMostFrequentWord(head);
    cout << "Từ xuất hiện nhiều nhất: " << mostFrequent << endl;
    
    // Loại bỏ từ láy
    removeRedundantWords(head);
    
    // Đếm số từ vựng
    int uniqueWordCount = countUniqueWords(head);
    cout << "Số lượng từ vựng: " << uniqueWordCount << endl;
    
    return 0;
}
