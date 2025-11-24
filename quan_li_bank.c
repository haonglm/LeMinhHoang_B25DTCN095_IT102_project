#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 1000
#define PAGE_SIZE 10

typedef struct{
    char accountId[20]; // ma tai khoan
    char fullName[50];
    char phone[15];
    double balance;  // so du
    int status;  // 1: kich hoat / 0: khoa
} Account;

typedef struct{
    char transId[20];
    char senderId[20];
    char receiverId[20];
    double amount;
    char type[10];  // chuyen khoan, tien gui, rut tien
    char date[20];  // YYYY/MM/DD
} Transaction;

//luu du lieu trong bo nho
Account accounts[MAX_ACCOUNTS];
int accountCount = 0;
Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;

//tim tai khoan theo id
int find_account_index(const char id[]) {
    for (int i = 0; i < accountCount; i++) {
        if( strcmp(accounts[i].accountId, id) == 0 ) {
        return i;
        }
    }
    return -1;
}

void strip_newline(char str[]) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
    }
}

void add_account_new(){
    //kiem tra so luong tai khoan
    if (accountCount >= MAX_ACCOUNTS) {
    printf("tai khoan da day. khong the them !!!\n");
    return;
    }
    // khai bao bien tam thoi de luu thong tin nhap
    Account newAcc;
    // nhap accountId
    printf("Nhap accountId: ");
    scanf("%19s",newAcc.accountId);
    getchar(); // xoa \n con lai

    if(strlen(newAcc.accountId) == 0 || find_account_index(newAcc.accountId) != -1) {
    printf("Loi: Id rong hoac da ton tai !!!\n");
    return;
    }
    // nhap ho ten va kiem tra
    printf("nhap ho ten: ");
    fgets(newAcc.fullName, sizeof(newAcc.fullName), stdin);
    strip_newline(newAcc.fullName);
    if(strlen(newAcc.fullName) == 0) {
    printf("ho ten khong duoc de trong\n");
    return;
    }
    // nhap so dien thoai va kiem tra
    printf("nhap phone: ");
    scanf("%14s",newAcc.phone);
    getchar();
    if(strlen(newAcc.phone) == 0) {
    printf("so dien thoai khong duoc de trong\n");
    return;
    }

    //khoi tao so du va tai khoan
    newAcc.balance = 0;
    newAcc.status = 1;
    //them vao mang accounts
    accounts[accountCount] = newAcc;
    accountCount++;
    printf("them tai khoan thanh cong !!!\n");
};

void update_account_new() {
	char id[20];
	char tmpName[50];
	char tmpPhone[20];
	
	printf("nhap ID tai khoan can cap nhat: ");
	scanf("%19s",id);
	getchar();
	
	int idx = find_account_index(id);
	if(idx == -1){
		printf("loi: khong tim thay tai khoan !!!\n");
		return;	
	} 
	printf("thong tin hien tai: \n");
	printf("ten: %s\n",accounts[idx].fullName);
	printf("sdt: %s\n",accounts[idx].phone);
	
	printf("nhap ten moi (neu khong thi enter de giu nguyen): ");
	fgets(tmpName, sizeof(tmpName), stdin);
	strip_newline(tmpName);
	
	printf("nhap sdt moi (neu khong thi enter de giu nguyen): ");
	fgets(tmpPhone, sizeof(tmpPhone), stdin);
	strip_newline(tmpPhone);
	//cap nhat ten
	if(strlen(tmpName) > 0){
		strncpy(accounts[idx].fullName, tmpName, sizeof(accounts[idx].fullName) - 1);
		accounts[idx].fullName[sizeof(accounts[idx].fullName) - 1] = '\0';
	}
	
	
	//kiem tra sdt trung
	if(strlen(tmpPhone) > 0){
		for (int i = 0; i < accountCount; i++){
			if(i != idx && strcmp(accounts[i].phone, tmpPhone) == 0){
				printf("loi: sdt da ton tai !!!\n");
				return;
			}
		}
		//cap nhat sdt moi(chi chay neu khong bi trung)
		strncpy(accounts[idx].phone, tmpPhone, sizeof(accounts[idx].phone) - 1);
		accounts[idx].phone[sizeof(accounts[idx].phone) - 1]= '\0';
	}
	printf("cap nhat thanh cong !!!\n");
};
	

int main(){

    int choice;
    while(1){
    printf("\n========= QUAN LY TAI KHOAN =========\n");
    printf("1. them tai khoan moi\n");
    printf("2. cap nhat thong tin\n");
    printf("3. quan ly trang thai (khoa / xoa)\n");
    printf("4. tra cuu (tim kiem)\n");
    printf("5. danh sach (phan trang)\n");
    printf("6. sap xep danh sach\n");
    printf("7. giao dich chuyen khoan\n");
    printf("8. lich su giao dich\n");
    printf("0.thoat chuong trinh\n");

    printf("moi ban nhap lua chon: ");
    scanf("%d",&choice);

    switch(choice){
    case 1:
    	add_account_new();
        break;
    case 2:
    	update_account_new();
        break;
    case 3:
        break;
    case 4:
        break;
    }
}
    return 0;
}
