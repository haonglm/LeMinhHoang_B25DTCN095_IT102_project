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
    char senderId[20]; //id nguoi gui  
    char receiverId[20]; // id nguoi nhan  
    double amount; // so luong 
    char type[10];  // chuyen khoan, tien gui, rut tien
    char date[20];  // YYYY/MM/DD
} Transaction; // giao dich  

//luu du lieu trong bo nho
Account accounts[MAX_ACCOUNTS];
int accountCount = 0;
Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;

//nguyen mau ham 
int find_account_index(const char id[]); 
void strip_newline(char str[]);
void clear_stdin();
void add_account_new();
void update_account_new();
void management_status();
void search_account();

int main(){

    int choice;
    while(1){
    printf("\n========= QUAN LY TAI KHOAN NGAN HANG  =========\n");
    printf("1. them tai khoan moi\n");
    printf("2. cap nhat thong tin\n");
    printf("3. quan ly trang thai (khoa / xoa)\n");
    printf("4. tra cuu (tim kiem)\n");
    printf("5. danh sach (phan trang)\n");
    printf("6. sap xep danh sach\n");
    printf("7. giao dich chuyen khoan\n");
    printf("8. lich su giao dich\n");
    printf("0. thoat chuong trinh\n");

    printf("moi ban nhap lua chon: ");
    scanf("%d",&choice);
	clear_stdin(); 
    
	switch(choice){
    case 1:
    	add_account_new();
        break;
    case 2:
    	update_account_new();
        break;
    case 3:
    	management_status();
        break;
    case 4:
    	search_account();
        break;
    }
}
    return 0;
}


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

void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// case 1 : ham them tk moi 
void add_account_new() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Danh sach tai khoan da day. Khong the them!\n");
        return;
    }

    Account newAcc;

    // Nhap accountId
    while (1) {
        printf("Nhap accountId : ");
        if (fgets(newAcc.accountId, sizeof(newAcc.accountId), stdin) == NULL) {
            printf("Loi nhap. Thu lai.\n");
            continue;
        }
        strip_newline(newAcc.accountId);
		
        if (strlen(newAcc.accountId) == 0){
            printf("Id khong de trong !!\n");
			continue;
			}
        
        if (find_account_index(newAcc.accountId) != -1) {
            printf("ID da ton tai!\n");
            continue;
        }

        break; // ID hop le 
    }

    // Nhap ho tên
    while (1) {
        printf("Nhap ho ten: ");
        if (fgets(newAcc.fullName, sizeof(newAcc.fullName), stdin) == NULL) {
            printf("Loi nhap. Thu lai.\n");
            continue;
        }
        strip_newline(newAcc.fullName);

        if (strlen(newAcc.fullName) == 0){
            printf("ten khong de trong, nhap lai !!\n"); 
			continue;
			}
        break;
    }

    // Nhap sdt 
    while (1) {
        char tmpPhone[64];
        printf("Nhap sdt: ");
        if (fgets(tmpPhone, sizeof(tmpPhone), stdin) == NULL) {
            printf("Loi nhap. Thu lai.\n");
            continue;
        }
        strip_newline(tmpPhone);

        if (strlen(tmpPhone) == 0){
            printf("sdt khong de trong, nhap lai !!!\n");
			continue;
			}
        
		int duplicate = 0;
        for (int i = 0; i < accountCount; i++) {
            if (strcmp(accounts[i].phone, tmpPhone) == 0) {
                duplicate = 1;
                break;
            }
        }
        
		if (duplicate) {
            printf("SDT da ton tai!\n");
            continue;
        }

        strncpy(newAcc.phone, tmpPhone, sizeof(newAcc.phone) - 1);
        newAcc.phone[sizeof(newAcc.phone) - 1] = '\0';
        break;
    }

    // Khoi tao so du va trang thai  
    newAcc.balance = 0.0;
    newAcc.status = 1;

    accounts[accountCount++] = newAcc;
    printf("Them tai khoan thanh cong!\n");
}

// case 2: ham cap nhat thong tin
void update_account_new() {
	char id[20];
	char tmpName[50];
	char tmpPhone[20];
	
	printf("nhap ID tai khoan can cap nhat: ");
	fgets(id, sizeof(id), stdin);
	strip_newline(id);

	
	int idx = find_account_index(id);
	if(idx == -1){
		printf("loi khong tim thay tai khoan !!!\n");
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
				printf("loi sdt da ton tai !!!\n");
				return;
			}
		}
		//cap nhat sdt moi(chi chay neu khong bi trung)
		strncpy(accounts[idx].phone, tmpPhone, sizeof(accounts[idx].phone) - 1);
		accounts[idx].phone[sizeof(accounts[idx].phone) - 1]= '\0';
	}
	printf("cap nhat thanh cong !!!\n");
};
	
// case 3: quan li trang thai (khoa / xoa)
void management_status(){
	char id[20];
	int choice;
	
	printf("\n==== QUAN LY TRANG THAI KHOA & XOA ====\n");
	printf("nhap Id tai khoan can thao tac: ");
	
	//nhap Id
	if(fgets(id, sizeof(id), stdin) == NULL){
		printf("Loi nhap ID !!!\n");
		return;
	}
	strip_newline(id);
	
	// validation: tim kiem tai khoan
	int idx = find_account_index(id);
	if (idx == -1){
		printf("khong tim thay tai khoan co ID: %s", id);
		return;
	}
	//hien thi thong tin hien tai
	printf("\nTai khoan [%s] hien tai:\n",accounts[idx].accountId);
	printf("Ho ten: %s\n",accounts[idx].fullName);
	printf("So du: %.2lf\n",accounts[idx].balance);
	printf("trang thai: %s\n",accounts[idx].status == 1 ? "kich hoat (1)" : "khoa (0)");
	
	//lua chon hanh dong(khoa / xoa)
	printf("\nchon thao tac:\n");
	printf("1. khoa tai khoan. \n");
	printf("2. xoa tai khoan. \n");
	printf("moi ban nhap lua chon (1 or 2): ");
	
	// xu ly lua chon va loi nhap
	if(scanf("%d",&choice) != 1 || (choice != 1 && choice != 2)){
		printf("loi lua chon khong hop le. vui long thu lai !!!\n");
		clear_stdin();
		return;
	}
	clear_stdin();
	
	if(choice == 1){
		if(accounts[idx].status == 0){
			printf("tai khoan da bi khoa truoc do !!!\n");
		}else{
			accounts[idx].status = 0;
			printf("tai khoan [%s] da bi khoa thanh cong. \n",accounts[idx].accountId);
			printf("tai khoan se khong the thuc hien giao dich chuyen tien nua. \n");
		}
	}else if(choice == 2) {
		// kt so du truoc khi delete
		if(accounts[idx].balance > 0){
			printf("loi: tai khoan [%s] van con so du (%.2lf). khong the xoa vinh vien. \n", id, accounts[idx].balance);
			return;
		}
		
		//xu ly xoa bang cach dich phan tu
		for(int i = idx; i < accountCount ; i++){
			accounts[i] = accounts[i + 1];
		}
		accountCount--;
		printf("tai khoan [%s] da bi xoa vinh vien khoi he thong !!!\n", id);
	}
	
	
}

// case 4: 
void search_account(){
	int choice;
	char keyword[50];
	int foundCount = 0;
	
	printf("\n=== CHUC NANG TRA CUU TAI KHOAN ===\n");
	printf("chon tieu chi tra cuu: \n");
	printf("1. tim kiem theo Account ID\n");
	printf("2. tim theo ho ten\n");
	printf("moi ban nhap lua chon (1 or 2): ");
	
	// su ly doc va loi nhap
	if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Loi: Lua chon khong hop le. Thao tac bi huy.\n");
        clear_stdin();
        return;
    }
    clear_stdin(); // Xoa bo nho dem sau scanf
    
    printf("nhap tu khoa tim kiem: ");
    if(fgets(keyword, sizeof(keyword), stdin) == NULL){
    	printf("loi nhap xoa.\n");
    	return;
	}
	strip_newline(keyword);
	
	//validation: kiem tra rong
	if(strlen(keyword) == 0){
		printf("tu khoa khong duoc rong !!\n");
		return;
	}
	printf("\nket qua tim kiem: \n");
	
	for(int i = 0; i < accountCount; i++){
		int match = 0;
		if(choice == 1){ //tim kiem tk theo account ID
			if(strcmp(accounts[i].accountId, keyword) == 0){
				match = 1;
			}
		} else if (choice == 2) {
			if(strstr(accounts[i].fullName, keyword) != NULL){
				match = 1;
			}
		}
		if(match){
            foundCount++;
            printf("----------------------------------------\n");
            printf("ID:        %s\n", accounts[i].accountId);
            printf("Ho ten:    %s\n", accounts[i].fullName);
            printf("Dien thoai: %s\n", accounts[i].phone);
            printf("So du:     %.2lf\n", accounts[i].balance);
            printf("Trang thai: %s\n", accounts[i].status == 1 ? "Kich hoat" : "Khoa");
			// neu ng dung chon lua chon 1 thi kq la duy nhat ,thoat som de tang toc
            if (choice == 1) break;
		}
	}
	
	printf("------------------------------------\n");
	if(foundCount == 0){
		//output : that bai
		printf("khong co ket qua phu hop.\n");
	}else{
		//out put : thanh cong
		printf("tim thay %d tai khoan", foundCount);
	}
} 
