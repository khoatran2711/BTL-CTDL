#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int maCB;
    char hoTen[20], phongBan[15], chucVu[15];
    float hsLuong;
}Data;

struct node{
    Data data;
    struct node *nPrev;
    struct node *nNext;
};

typedef struct node Node;


typedef struct{
    Node *pHead;    // dia chi cua phan tu dau tien
    Node *pTail;    // dia chi cua phan tu cuoi cung
}List;


void CreateList(List *l){ 
    l->pHead = NULL;
    l->pTail = NULL;
}

Node* CreateNode(Data data){
    Node *p;
    p = (Node*)malloc(sizeof(Node));

    if(p==NULL) exit(1);

    p->nPrev = NULL;
    p->nNext = NULL;
    p->data = data;

    return p;
}

void AddHead(List *list, Data data){
    Node *temp = CreateNode(data);

    if(list->pHead == NULL){
        list->pHead = temp;
        list->pTail = list->pHead;
    }else{
        temp->nNext = list->pHead;
        list->pHead = temp;
    }
}

void AddTail(List *list, Data data){
    Node *temp = CreateNode(data);

    if(list->pHead == NULL){
        AddHead(list, data);
    }else{
        temp->nPrev = list->pTail;
        list->pTail->nNext = temp;
        list->pTail = temp;
    }

}

void PrintCmt(){
    printf("\n=--------------------------------------------------------=");
}

Data *NhapData(Data *data, int *n){
    data = (Data*)malloc(sizeof(Data));

    printf("\nNhap maCB: ");
    scanf("%d", &data->maCB);
    fflush(stdout);
    if(data->maCB <= 0) return NULL;
    
    printf("Nhap ho ten: ");
    getchar();
    gets(data->hoTen);

    printf("Nhap phong ban: ");
    gets(data->phongBan);

    printf("Nhap chuc vu: ");
    gets(data->chucVu); //, 15, stdin);

    do{
        printf("Nhap he so luong: ");
        scanf("%f", &data->hsLuong);
    }while (data->hsLuong < 0);
    

    PrintCmt();
    //n++;

    return data;
}

// In ra thong tin ko co luong
void PrintInformationNormal(Node *p){
    printf("\n%5d %20s %15s %15s %8.1f", p->data.maCB, p->data.hoTen, p->data.phongBan, p->data.chucVu, p->data.hsLuong);
}

// In ra thong tin voi luong
void PrintInformationWithLuong(Node *p){
    printf("\n%5d %20s %15s %15s %8.1f %8.1f", p->data.maCB, p->data.hoTen, p->data.phongBan, p->data.chucVu, p->data.hsLuong, p->data.hsLuong * 1150000);
}

// Goi in
void Print(List *list, Node *p, int isLuong){         // 0: ko in ra luong || 1: in ra luong = ct : luong = hsluong * 1150000
    
    char maCB[] = "Ma CB"; 
    char hoTen[] = "Ho ten"; 
    char phongBan[] = "Phong ban"; 
    char chucVu[] = "Chuc vu"; 
    char hsLuong[] = "hs luong"; 
    char strLuong[] = "luong"; 

    PrintCmt();
    if(isLuong == 0){
        printf("\n%5s %20s %15s %15s %4s", maCB, hoTen, phongBan, chucVu, hsLuong);
        while(p != NULL){     
            PrintInformationNormal(p);
            p = p->nNext;    
        }
        
    }else{
        printf("\n%5s %20s %15s %15s %4s %8s", maCB, hoTen, phongBan, chucVu, hsLuong, strLuong);
        while(p != NULL){    
            PrintInformationWithLuong(p); 
            p = p->nNext;   
        }
    }
    PrintCmt();
}

// In ra danh sach voi hs luong >= 4.9
void PrintIf(List *list, Node *p){
    float hs = 4.9f;
    char maCB[] = "Ma CB"; 
    char hoTen[] = "Ho ten"; 
    char phongBan[] = "Phong ban"; 
    char chucVu[] = "Chuc vu"; 
    char hsLuong[] = "hs luong"; 
    char strLuong[] = "luong"; 

    PrintCmt();
    printf("\n%5s %20s %15s %15s %4s %8s", maCB, hoTen, phongBan, chucVu, hsLuong, strLuong);
    while(p != NULL){     
        if(p->data.hsLuong >= hs)
            PrintInformationWithLuong(p);
        p = p->nNext;    
    }  

    PrintCmt();
}


// 1: bo qua || 0: chua dem
int IsCounted(Node *p){
    Node *temp = p;
    while (temp != NULL)
    {
        if(strcmp(p->data.phongBan, temp->data.phongBan) != 0){
            return 1;
        }

        temp = temp->nPrev;
    }

    return 0;
}

// Count member 
void CountMemberInPB(List *list, Node *p){
    p = list->pHead;
    int count;
    char strPhongBan[] = "Phong ban"; 
    char strCount[] = "Count"; 

    PrintCmt();
    printf("\n%15s %8s ", strPhongBan, strCount);

    while (p != NULL)
    {
        count = 0;
        Node *temp;
        if(IsCounted(p) == 0){
            temp = p;
            while(temp != NULL){
                if(strcmp(temp->data.phongBan, p->data.phongBan) == 0){
                    count++;
                }
                temp = temp->nNext;
            }

            printf("\n%15s %8d", p->data.phongBan, count);
        }

        p = p->nNext;
    }

    PrintCmt();
}

int main(){  
    int choose = -1;
    int n = 0;
    Node *p;
    List *list;
    CreateList(list);        
    Data *data;
    do{
        printf("\n=====Chuong trinh quan ly nhan su=====");
        printf("\n|| 1: Nhap danh sach.");
        printf("\n|| 2: Them 1 can bo vao vi tri.");
        printf("\n|| 3: Tinh luong cho nhan vien.");
        printf("\n|| 4: In danh sach can bo theo phong ban.");
        printf("\n|| 5: In cac can bo co he so luong >= 4.9.");
        printf("\n|| 6: Xuat.");
        printf("\n|| 0: Thoat?");
        printf("\n======================================");
        printf("\nNhap lua chon: ");
        scanf("%d", &choose);

        if(choose == 1){
            do{            
                data = NhapData(data, &n);
                if(data == NULL) 
                    break;                    
                else 
                    AddTail(list, *data);

            }while(1); 
        }
        else if(choose == 2){
            printf("TODO:");
        }
        else if(choose == 3){
            p = list->pHead;
            Print(list, p, 1);
        }
        else if(choose == 4){
            p = list->pHead;
            CountMemberInPB(list, p);
        }
        else if(choose == 5){
            p = list->pHead;
            PrintIf(list, p);
        }
        else if(choose ==  6){
            p = list->pHead;
            Print(list, p, 0);
        }

    }while(choose > 0);
}
