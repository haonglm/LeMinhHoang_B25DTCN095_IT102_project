#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

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
Account accounts[MAX_ACCOUNTS] = {
    {"AC1001","Nguyen Van A","0987000001",5000,1},
    {"AC1002","Tran Thi B","0987000002",6200,1},
    {"AC1003","Le Van C","0987000003",7400,1},
    {"AC1004","Pham Thi D","0987000004",5100,1},
    {"AC1005","Do Van E","0987000005",3300,1},
    {"AC1006","Nguyen Van F","0987000006",8800,1},
    {"AC1007","Hoang Thi G","0987000007",9200,1},
    {"AC1008","Bui Van H","0987000008",1500,1},
    {"AC1009","Dang Thi I","0987000009",2700,1},
    {"AC1010","Ngo Van J","0987000010",4600,1},

    {"AC1011","Nguyen Van K","0987000011",5100,1},
    {"AC1012","Le Thi L","0987000012",2300,1},
    {"AC1013","Pham Van M","0987000013",9000,1},
    {"AC1014","Tran Thi N","0987000014",7800,1},
    {"AC1015","Hoang Van O","0987000015",4100,1},
    {"AC1016","Do Thi P","0987000016",3200,1},
    {"AC1017","Bui Van Q","0987000017",1500,1},
    {"AC1018","Ngo Thi R","0987000018",2200,1},
    {"AC1019","Dang Van S","0987000019",3300,1},
    {"AC1020","Le Thi T","0987000020",9900,1},

    {"AC1021","Nguyen Van U","0987000021",7700,1},
    {"AC1022","Tran Thi V","0987000022",6600,1},
    {"AC1023","Pham Van W","0987000023",5500,1},
    {"AC1024","Do Thi X","0987000024",4300,1},
    {"AC1025","Hoang Van Y","0987000025",8000,1},
    {"AC1026","Le Thi Z","0987000026",9500,1},
    {"AC1027","Nguyen Thanh A","0987000027",3100,1},
    {"AC1028","Tran Minh B","0987000028",7200,1},
    {"AC1029","Pham Hong C","0987000029",5600,1},
    {"AC1030","Do Kieu D","0987000030",6400,1},

    {"AC1031","Hoang Bao E","0987000031",8700,1},
    {"AC1032","Nguyen Lan F","0987000032",9200,1},
    {"AC1033","Tran My G","0987000033",4800,1},
    {"AC1034","Le Quoc H","0987000034",3000,1},
    {"AC1035","Pham Tuan I","0987000035",5100,1},
};
int accountCount = 35;
Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;

//nguyen mau ham 
int find_account_index(const char id[]); 
void strip_newline(char str[]);
void clear_stdin();
void get_current_date(char *dateStr);
void add_account_new();
void update_account_new();
void management_status();
void search_account();
void Pagination();
void sort_accounts();
void transfer_money();

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
    case 5:
		Pagination(); 
		break; 
	case 6:
		sort_accounts();
		break;
	case 7:
		transfer_money();
		break;
	case 0:
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

void get_current_date(char *dateStr){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(dateStr, "%04d/%02d/%02d", tm.tm_year +1900, tm.tm_mon + 1, tm.tm_mday);
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
		//kiem tra rong  
        if (strlen(tmpPhone) == 0){
            printf("sdt khong de trong, nhap lai !!!\n");
			continue;
			}
        //kiem tra do dai
		if(strlen(tmpPhone) != 10) {
			printf("sdt phai du 10 so, vui long nhap lai.\n");
			continue;
		}
		
		//kiem tra ky tu 
		int letter = 0; //bien flag, 0 la khong co chu, 1 la co chu 
		for(int i = 0; i < strlen(tmpPhone); i++){
			if(isdigit(tmpPhone[i]) == 0){  // tra ve 0 nghia la khong phai so
				letter = 1;
				break;
			}
		}
		if(letter == 1){
			printf("loi so dien thoai chi co 10 so, khong phai chu cai !!!\n");
			continue;
		}
		
		//kiem tra trung lap
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
	int flag = -1;
	while(1){
	printf("nhap ID tai khoan can cap nhat: ");
	fgets(id, sizeof(id), stdin);
	strip_newline(id);
	
	if(strcmp(id, "") == 0){
		printf("id khong duoc de trong\n");
		continue;
	}
	
	for(int i = 0; i < accountCount; i++){
		if(strcmp(id, accounts[i].accountId) == 0){
			flag = i;
			break;
		}
	}
	if(flag == -1){
		printf("khong tim thay tai khoan.\n");
		continue;	
		}
		break;
	}
	printf("thong tin hien tai: \n");
	printf("ten: %s\n",accounts[flag].fullName);
	printf("sdt: %s\n",accounts[flag].phone);
	
	printf("nhap ten moi (neu khong thi enter de giu nguyen): ");
	fgets(tmpName, sizeof(tmpName), stdin);
	strip_newline(tmpName);
	if(strcmp(tmpName,"") == 0){
		printf("thong tin duoc giu nguyen.\n");
	}else{
		strcpy(accounts[flag].fullName, tmpName);
	}
	
	int isDuplicate = 0;
	while(1){
	printf("nhap sdt moi (neu khong thi enter de giu nguyen): ");
	fgets(tmpPhone, sizeof(tmpPhone), stdin);
	strip_newline(tmpPhone);
	
	//kiem tra sdt trung
		for (int i = 0; i < accountCount; i++){
			if(i != flag && strcmp(accounts[i].phone, tmpPhone) == 0){
				isDuplicate = 1;
				break;
			}
		}
		
		if(isDuplicate == 1){
			printf("loi sdt da ton tai !!!\n");
			continue;
		}
		//cap nhat sdt moi(chi chay neu khong bi trung)
		strncpy(accounts[flag].phone, tmpPhone, sizeof(accounts[flag].phone) - 1);
		accounts[flag].phone[sizeof(accounts[flag].phone) - 1]= '\0';
	break;
}

	printf("cap nhat thanh cong !!!\n");
}
	
// case 3: quan li trang thai (khoa / xoa)
void management_status(){
	char id[20];
	int choice;
	int idx;
	printf("\n==== QUAN LY TRANG THAI KHOA & XOA ====\n");
	while(1){
	printf("nhap Id tai khoan can thao tac: ");
	
	//nhap Id
	if(fgets(id, sizeof(id), stdin) == NULL){
		printf("Loi nhap ID. vui long thu lai !!!\n");
		continue;
	}
	strip_newline(id);
	
	if(strlen(id) == 0){
		printf("id khong duoc de trong !!!\n");
		continue;
	} 
	// validation: tim kiem tai khoan
	idx = find_account_index(id);
	if (idx == -1){
		printf("khong tim thay tai khoan co ID: %s. vui long nhap lai !!\n", id);
		continue;
		}
		break; 
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
	
	char tmp[10]; // bien tam de hung cac phim nhap vao  
	while(1){
	printf("moi ban nhap lua chon (1 or 2): ");
	fgets(tmp, sizeof(tmp), stdin);
	
	if(tmp[0] == '1' && tmp[1] == '\n'){
		choice = 1;
		break;
	} else if (tmp[0] == '2' && tmp[1] == '\n'){
		choice = 2;
		break;
		}
	printf("loi nhap !!! vui long chon 1 hoac 2.\n");
	}
	
	if(choice == 1){
		if(accounts[idx].status == 0){
			printf("tai khoan da bi khoa truoc do !!!\n");
		}else{
			accounts[idx].status = 0;
			printf("tai khoan [%s] da bi khoa thanh cong. \n",accounts[idx].accountId);
			printf("tai khoan se khong the thuc hien giao dich chuyen tien nua. \n");
		}
	}else if(choice == 2) {
		// kiem tra so du truoc khi delete
		if(accounts[idx].balance > 0){
			printf("loi: tai khoan [%s] van con so du (%.2lf). khong the xoa vinh vien. \n", id, accounts[idx].balance);
			return;
		}
		
		//xu ly xoa bang cach dich phan tu
		for(int i = idx; i < accountCount - 1; i++){
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

//case 5:
void Pagination() {
	int page_number;
	int page_size = 10;
	
	printf("\n==== DANH SACH TAI KHOAN PHAN TRANG ====\n"); 
	
	while(1){
		//tinh tong so trang
		int total_pages = (accountCount + page_size - 1) / page_size; 
	
	// trang muon xem  
	while(1){
            printf("Nhap trang muon xem (1 - %d): ", total_pages);
            if(scanf("%d", &page_number) != 1){
                printf("Loi nhap so!\n");
                clear_stdin();
                continue;
            }
            clear_stdin();

            if(page_number <= 0 || page_number > total_pages){
                printf("Loi: Trang %d khong ton tai (Chi co tu 1 den %d).\n", page_number, total_pages);
                continue;
            }
            break;
        }
	
	//tinh chi so bat dau va ket thuc  
	long start_index = (long) (page_number - 1) * page_size;
	long end_index = start_index + page_size;
	if(end_index > accountCount) end_index = accountCount;
	
	//in 
	printf("\nTrang %d / %d\n",page_number, total_pages);
	for(long i = start_index; i < end_index; i++){
		// STT, accountID, ho ten, sdt, so du, trang 
		printf("%ld. %s | %s | %s | %.2f | %s\n",i+1, accounts[i].accountId, accounts[i].fullName, accounts[i].phone, accounts[i].balance, accounts[i].status == 1 ? "kich hoat" : "khoa"); 
	} 
	return;
	}	 
} 

void sort_accounts(){
	int choice;
	char tmp[10];
	
	printf("\n=== SAP XEP DANH SACH TAI KHOAN ===\n");
	printf("1. sap xep theo so du giam dan.\n");
	printf("2. sap xep theo ten (A-Z).\n");
	//nhap lua chon
	while(1) {
        printf("Moi chon kieu sap xep (1 or 2): ");
        fgets(tmp, sizeof(tmp), stdin);

        if (tmp[0] == '1' && tmp[1] == '\n') {
            choice = 1;
            break;
        } 
        else if (tmp[0] == '2' && tmp[1] == '\n') {
            choice = 2;
            break;
        }
        printf("Loi: Vui long chon 1 hoac 2!\n");
    }
    //thuc hien sap xep
    Account temp; //bien doi vi tri
    for(int i = 0; i < accountCount - 1; i++){
    	for(int j = i + 1; j < accountCount; j++){
    		int swap = 0; // bien co de xem co can doi cho khong
    		// xep theo so du
    		if(choice == 1){
    			if(accounts[i].balance < accounts[j].balance){
    				swap = 1;
				}
			} else {
				//xep theo ten
				if(strcmp(accounts[i].fullName, accounts[j].fullName) > 0){
					swap = 1;
				}
			}	
			if(swap){
				temp = accounts[i];
				accounts[i] = accounts[j];
				accounts[j] = temp;
			}
		}
	}
} 

//case 7:
void transfer_money(){
	char senderID[20];
	char receiverID[20];
	char strAmount[50];
	double amount;
	int sIdx = -1; // index ng gui
	int rIdx = -1; // index ng nhan
	
	printf("\n====== GIAO DICH CHUYEN KHOAN ======\n");
	
	//nguoi gui
	while(1){
		printf("\nNhap ID nguoi gui: ");
		if(fgets(senderID, sizeof(senderID), stdin) == NULL) continue;
		strip_newline(senderID);
		
		if(strlen(senderID) == 0){
			printf("ID khong duoc de trong, vui long nhap lai !!!\n");
			continue;
		}
		
		//kiem tra ton tai
		sIdx = find_account_index(senderID);
		if(sIdx == -1){
			printf("loi !!! ID nguoi gui khong co trong he thong !!!\n");
			continue;
		}
		
		//check trang thai tk
		if(accounts[sIdx].status == 0){
			printf("loi !!! tai khoan nay dang bi khoa (status = 0).\n");
			continue;
		}
		
		//neu dung het thi hien thi
		printf("nguoi gui: %s (so du: %.2lf)\n",accounts[sIdx].fullName, accounts[sIdx].balance);
		break;
	}
	
	//nguoi nhan
	while(1){
		printf("\nNHap ID nguoi nhan: ");
		if(fgets(receiverID, sizeof(receiverID), stdin) == NULL) continue;
		strip_newline(receiverID);
		
		//kiem tra trong
		if(strlen(receiverID) == 0){
			printf("loi !!! ID khong duoc de trong.\n");
			continue;
		}
		
		//check ton tai
		rIdx = find_account_index(receiverID);
		if(rIdx == -1){
			printf("loi !!! ID nguoi nhan khong ton tai.\n");
			continue;
		}
		
		// kiem tra trung
		if(strcmp(senderID, receiverID) == 0){
			printf("loi !!! nguoi dung khong duoc chuyen tien cho chinh minh.\n");
			continue;
		}
		
		//kiem tra trang thai
		if(accounts[rIdx].status == 0){
			printf("loi !!! tai khoan nguoi dung dang bi khoa, khong the nhan tien.\n");
			continue;
		}
		
		//dung het thi in
		printf("nguoi nhan: %s\n",accounts[rIdx].fullName);
		break;
	}
	
	//nhap tien
	while(1){
		printf("\nNhap so tien can chuyen: ");
		if(fgets(strAmount, sizeof(strAmount), stdin) == NULL) continue;
		strip_newline(strAmount);
		
		//kiem tra rong
		if(strlen(strAmount) == 0){
			printf("loi !!! so tien khong duoc de trong.\n");
			continue;
		}
		
		//kiem tra ky tu
		int isValid = 1; // bien co ban dau la dung 
		for(int i = 0; i < strlen(strAmount); i++){
			if(isdigit(strAmount[i]) == 0 && strAmount[i] != '.'){
				isValid = 0;
				break;
			}
		}
		if(isValid == 0){
			printf("loi !!! so tien khong duoc chua chu cai.\n");
			continue;
		}
		// chuyen chuoi "5000" thanh 5000.0
		amount = atof(strAmount);
		
		if(amount == 0) return; // neu nhap 0 thi thoat ve menu
		if(amount <= 0){
			printf("loi !! so tien phai > 0.\n");
			continue;
		}
		
		// kiem tra so du
		if(amount > accounts[sIdx].balance){
			printf("so du khong du (tai khoan con: %.2lf)",accounts[sIdx].balance);
			continue;
		}
		break;
	}
	
	//tru va cong tien
	accounts[sIdx].balance -= amount;
	accounts[rIdx].balance += amount;
	
	if(transactionCount < MAX_TRANSACTIONS){
		Transaction newtrans;
		
		//tu dong in ma giao dich: TR001, TR002, ...
		sprintf(newtrans.transId, "TR%04d", transactionCount + 1);
		// copy thong tin vao bien lai
		strcpy(newtrans.senderId, senderID);
		strcpy(newtrans.receiverId, receiverID);
		
		newtrans.amount = amount;
		strcpy(newtrans.type,"transfer"); // loai giao dich
		//goi ham lay ngay gio
		get_current_date(newtrans.date);
		//luu vao mang va tang bien dem so lan giao dich len 1
		transactions[transactionCount++] = newtrans;
	}else{
		printf("canh bao !! bo nho day, khong the luu lich su.\n");
	}
	
	printf("\n===== CHUYEN KHOAN THANH CONG =====\n");
	printf("ma giao dich: %s\n",transactions[transactionCount-1].transId);
	printf("so du moi cua ban: %.2lf\n", accounts[sIdx].balance);
}
