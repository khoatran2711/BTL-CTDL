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

Node* CreateNode(Data *data){
    Node *p;
    p = (Node*)malloc(sizeof(Node));

    if(p==NULL) exit(1);

    p->nPrev = NULL;
    p->nNext = NULL;
    p->data = *data;

    return p;
}

void AddHead(List *list, Data *data){
    Node *temp = CreateNode(data);

    if(list->pHead == NULL){
        list->pHead = temp;
        list->pTail = list->pHead;
    }else{
        temp->nNext = list->pHead;
        list->pHead->nPrev = temp;
        list->pHead = temp;
    }
}

void AddTail(List *list, Data *data){
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

//New
int IsAvailable(List *list, int maCB){
    Node *p = list->pHead;
    while(p != NULL){
        if( p->data.maCB == maCB)
            return 0;
        p = p->nNext;
    }
    return 1;
}

Data *NhapData(List *list, Data *data){
    
    //New
    do{
        printf("\nNhap maCB: ");
        scanf("%d", &data->maCB);
        
        if(data->maCB < 1) return NULL;
        if(IsAvailable(list, data->maCB) == 1) break;
        else printf("MaCB is't avaiable!\n");
    }while(1);

    fflush(stdout);
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

    return data;
}

// In ra thong tin ko co luong
void PrintInformationNormal(Node *p, int stt){
    printf("\n%5d %5d %20s %15s %15s %8.1f", stt, p->data.maCB, p->data.hoTen, p->data.phongBan, p->data.chucVu, p->data.hsLuong);
}

// In ra thong tin voi luong
void PrintInformationWithLuong(Node *p, int stt){
    printf("\n%5d %5d %20s %15s %15s %8.1f %8.1f", stt, p->data.maCB, p->data.hoTen, p->data.phongBan, p->data.chucVu, p->data.hsLuong, p->data.hsLuong * 1150000);
}

// Goi in
void Print(List *list, int isLuong){         // 0: ko in ra luong || 1: in ra luong = ct : luong = hsluong * 1150000
    
    char stt[] = "STT";
    char maCB[] = "Ma CB"; 
    char hoTen[] = "Ho ten"; 
    char phongBan[] = "Phong ban"; 
    char chucVu[] = "Chuc vu"; 
    char hsLuong[] = "hs luong"; 
    char strLuong[] = "luong"; 

    Node *p = list->pHead;

    PrintCmt();
    int count;
    if(isLuong == 0){
        count = 0;
        printf("\n%5s %5s %20s %15s %15s %4s", stt, maCB, hoTen, phongBan, chucVu, hsLuong);
        while(p != NULL){    
            count++; 
            PrintInformationNormal(p, count);
            p = p->nNext;    
        }
        
    }else{
        count = 0;
        printf("\n%5s %5s %20s %15s %15s %4s %8s", stt, maCB, hoTen, phongBan, chucVu, hsLuong, strLuong);
        while(p != NULL){
            count++;    
            PrintInformationWithLuong(p, count); 
            p = p->nNext;   
        }
    }
    PrintCmt();
}

// In ra danh sach voi hs luong >= 4.9
void PrintIf(List *list){
    float hs = 4.9f;
    char stt[] = "STT";
    char maCB[] = "Ma CB"; 
    char hoTen[] = "Ho ten"; 
    char phongBan[] = "Phong ban"; 
    char chucVu[] = "Chuc vu"; 
    char hsLuong[] = "hs luong"; 
    char strLuong[] = "luong"; 

    Node *p = list->pHead;

    PrintCmt();
    int count = 0;
    printf("\n%5s %5s %20s %15s %15s %4s %8s", stt, maCB, hoTen, phongBan, chucVu, hsLuong, strLuong);
    while(p != NULL){     
        count++;
        if(p->data.hsLuong >= hs)
            PrintInformationWithLuong(p, count);
        p = p->nNext;    
    }  

    PrintCmt();
}


// 1: bo qua || 0: chua dem
int IsCounted(Node *p){
    Node *temp = p->nPrev;
    while (temp != NULL)
    {
        if(strcmp(p->data.phongBan, temp->data.phongBan) == 0){
            return 1;
        }

        temp = temp->nPrev;
    }

    return 0;
}

// Count member 
void CountMemberInPB(List *list){
    Node *p = list->pHead;
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

void InsertPos(List *list, Data *data, int pos){   
    int count = 0;
    
    Node *p = list->pHead;
    Node *temp = CreateNode(data);
    Node *prev = NULL;

    if(pos <= 1){
        AddHead(list, data);
        return;
    }

    while(p != NULL && count < pos){
        count++;
        if(count == pos){
            temp->nPrev = p->nPrev;
            temp->nNext = p;

            p->nPrev = temp;
            prev->nNext = temp;

            return;           
        }
        prev = p;
        p = p->nNext;
    }

    AddTail(list, data);
}

void InsertByPos(List *list){
    Node *p;
    p = list->pHead;
    Print(list, 0);

    int pos;
    printf("\nNhap STT muon chen: ");
    scanf("%d", &pos);

    Data *data;
    data = (Data*)malloc(sizeof(Data));

    //New
    data = NhapData(list, data);
    
    //New
    if(data == NULL) {
        printf("\nBan da huy");
        return;
    }
    InsertPos(list, data, pos);
}

void ScanInput(List *list, Data *data){ 
    
    //New
    data = NhapData(list, data);
    if(data == NULL) 
        return;   
    else    
        AddTail(list, data);
    ScanInput(list, data);
    
}

void PrintMenu(){
    printf("\n=====Chuong trinh quan ly nhan su=====");
    printf("\n|| 1: Nhap danh sach.");
    printf("\n|| 2: Them 1 can bo vao vi tri.");
    printf("\n|| 3: Tinh luong cho nhan vien.");
    printf("\n|| 4: In danh sach can bo theo phong ban.");
    printf("\n|| 5: In cac can bo co he so luong >= 4.9.");
    printf("\n|| 0: Thoat?");
    printf("\n======================================");
    printf("\nNhap lua chon: ");
}


int main(){   
    int choose = -1;
    int n = 0;

    //New
    int isScan = 0;
    Node *p;
    List *list = (List*)malloc(sizeof(List));
    CreateList(list);   
	Data *data = (Data*)malloc(sizeof(Data));
    do{
        PrintMenu();
        scanf("%d", &choose);

        //New
        if(choose != 1 && isScan == 0){
            printf("\nMoi ban nhap danh sach.");
            continue;
        }else if(choose == 1 && isScan == 1){
            printf("\nBan da nhap danh sach.");
            continue;
        }

        if(choose == 1){  		
    		ScanInput(list, data);   
            isScan = 1;
        }
        else if(choose == 2){
            InsertByPos(list);
        }
        else if(choose == 3){
            
            Print(list, 1);
        }
        else if(choose == 4){
            CountMemberInPB(list);
        }
        else if(choose == 5){
            PrintIf(list);
        }

    }while(choose > 0);
}

