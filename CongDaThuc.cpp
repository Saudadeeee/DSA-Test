/*Cài đặt giải thuật để nhập và in ra hai đa thức theo định dạng như sau:
f(x) = x^10 + 1;
g(x) = x^15 + x^7 + x^2 + 1; 
In ra tổng của 2 đa thức h(x) = f(x) + g(x) (*)
Ưu tiên cài đặt CTDL và giải thuật để sử dụng bộ nhớ tối ưu nhất*/

#include <iostream>

struct Node{
    int heso;
    int bac;
    Node* next;
};

Node* createNode(int heso, int bac){
    Node* newNode = new Node;
    newNode -> heso = heso;
    newNode -> bac = bac;
    newNode -> next = NULL;
    return newNode;
}
void them_so_hang(Node** head, int heso, int bac){
    Node* newNode = createNode(heso, bac);
    if(*head == NULL || (*head) -> bac < newNode -> bac){
        newNode -> next = *head;
        *head = newNode;
    }
    else{
        Node* current = *head;
        while(current -> next!= NULL && current -> next -> bac > newNode -> bac){
            current = current -> next;
        }
        if(current -> bac == bac){
            current -> heso += heso;
        }
        else{
            newNode -> next = current -> next;
            current -> next = newNode;
        }
    }
}

void Display(Node* head){
    if(head == NULL){
        printf("Empty\n");
        return;
    }
    Node* current = head;
    while(current != NULL){
        if(current -> heso != 0){
            if(current -> bac != 0){
                printf("%dx^%d", current -> heso, current -> bac);
            }
            else{
                printf("%d", current -> heso);
            }
            if(current -> next != NULL && current -> next -> heso > 0){
                printf(" + ");
            }
        }
        current = current -> next;
    }
    printf("\n");
}
Node* Sum_of_funct(Node* f, Node* g){
    Node* result = NULL;
    while(f != NULL || g != NULL){
        if(f&&(!g||f->bac > g->bac)){
            them_so_hang(&result, f->heso, f->bac);
            f = f -> next;
        }
        else if(g&&(!f||f->bac < g->bac)){
            them_so_hang(&result, g->heso, g->bac);
            g = g -> next;
        }
        else{
            int sum = f->heso + g->heso;
            them_so_hang(&result, sum, f->bac);
            f = f -> next;
            g = g -> next;
        }
    }
    return result;
}
Node* input(){
    Node* head = NULL;
    int n;
    printf("Nhap so so hang: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        int heso, bac;
        printf("Nhap he so: ");
        scanf("%d", &heso);
        printf("Nhap bac: ");
        scanf("%d", &bac);
        them_so_hang(&head, heso, bac);
    }
    return head;
}
void freeList(Node* head){
    Node* current;
    while(head != NULL){
        current = head;
        head = head -> next;
        delete current;
    }
}
int main(){
    printf("Nhap da thuc f(x): \n");
    Node* f = input();
    printf("f(x) = ");
    Display(f);
    printf("Nhap da thuc g(x): \n");
    Node* g = input();
    printf("g(x) = ");
    Display(g);
    Node* sum = Sum_of_funct(f, g);
    printf("h(x) = f(x) + g(x) = ");
    Display(sum);
    freeList(f);
    freeList(g);
    freeList(sum);
    return 0;
}