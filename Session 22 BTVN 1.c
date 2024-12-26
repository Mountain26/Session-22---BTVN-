#include <stdio.h>
#include <string.h>

struct SinhVien {
    char id[50];
    char name[50];
    int age;
};

struct SinhVien sv[100]; // global
int numberStudent = 0;

// Khai báo các hàm
void getStudentByFile();// tao ham de sinh vien o trong file sinhvien.bin
void printStudent();// tao ham in danh sach sinh vien
void addStudent(); // // tao ham them sinh vien
void save_students();
void edit_student();
void delete_student();
void search_student();
void sort_students();

int main() {
    
    getStudentByFile();
    int choose;
    do {
        printf("1. In danh sach sinh vien \n");
        printf("2. Them sinh vien \n");
        printf("3. Sua thong tin sinh vien \n");
        printf("4. Xoa sinh vien \n");
        printf("5. Tim thong tin sinh vien \n");
        printf("6. Sap xep sinh vien \n");
        printf("7. Thoat \n");
        printf("Moi ban nhap lua chon: ");
        scanf("%d", &choose);
        getchar();
        switch (choose) {
            case 1: {
                printStudent();
                break;
            }
            case 2: {
                addStudent();
                break;
            }
            case 3: {
                // sua sinh vien
  			/*
  			B1: nhap ma sinh vien
  			B2: kiem tra co ton tai sinh vien
  				+ neu ton tai: thi cho nguoi dung nhap lai name, tuoi
  				==> di update ==> luu lai trong file
  			    + neu khong co : ==> hien thi khong co sinh vien!
			  */
                edit_student();
                break;
            }
            case 4: {
                delete_student();
                break;
            }
            case 5: {
                search_student();
                break;
            }
            case 6: {
                sort_students();
                break;
            }
            case 7: {
                printf("Thoat chuong trinh.\n");
                break;
            }
            default: {
                printf("Lua chon khong hop le. Vui long chon lai.\n");
            }
        }
    } while (choose != 7);
    return 0;
}

void getStudentByFile() {
    FILE *file;
    // Mo file
    file = fopen("sinhvien.bin", "rb");
    if (file == NULL) {
        printf("Khong the mo file \n");
        return;
    }
    // Thao tac voi file: lay du lieu tu trong file
    numberStudent = fread(sv, sizeof(struct SinhVien), 100, file);
    // Ðong file
    fclose(file);
}

void printStudent() {
    if (numberStudent == 0) {
        printf("Khong co sinh vien \n");
        return;
    }
    for (int i = 0; i < numberStudent; i++) {
        printf("Thong tin sinh vien thu %d \n", i + 1);
        printf("Ma sv: %s \n", sv[i].id);
        printf("Ten sv: %s \n", sv[i].name);
        printf("Tuoi sv: %d \n", sv[i].age);
    }
}

// Ham them sinh vien 
void addStudent() {
    if (numberStudent >= 100) {
        printf("Danh sach sinh vien da day \n");
        return;
    }
    struct SinhVien sv1;
    // Cho nguoi dung nhap thong tin sinh vien
    printf("Nhap id: ");
    fgets(sv1.id, sizeof(sv1.id), stdin);
    sv1.id[strcspn(sv1.id, "\n")] = '\0';
    printf("Nhap ten: ");
    fgets(sv1.name, sizeof(sv1.name), stdin);
    sv1.name[strcspn(sv1.name, "\n")] = '\0';
    printf("Nhap tuoi: ");
    scanf("%d", &sv1.age);
    getchar();
    sv[numberStudent] = sv1;
    numberStudent++;
    save_students();
}

void save_students() {
    FILE *file;
    // Mo file
    file = fopen("sinhvien.bin", "wb");
    if (file == NULL) {
        printf("Khong the mo file de luu \n");
        return;
    }
    // Thao tác voi file
    fwrite(sv, sizeof(struct SinhVien), numberStudent, file);
    // Ðóng file
    fclose(file);
}

void edit_student() {
    char id[50];
    printf("Nhap ID sinh vien can sua: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    for (int i = 0; i < numberStudent; i++) {
        if (strcmp(sv[i].id, id) == 0) {
            printf("Nhap Ten moi: ");
            fgets(sv[i].name, sizeof(sv[i].name), stdin);
            sv[i].name[strcspn(sv[i].name, "\n")] = '\0';

            printf("Nhap Tuoi moi: ");
            scanf("%d", &sv[i].age);
            getchar();

            save_students();
            printf("Da sua thong tin sinh vien.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %s\n", id);
}

void delete_student() {
    char id[50];
    printf("Nhap ID sinh vien can xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    for (int i = 0; i < numberStudent; i++) {
        if (strcmp(sv[i].id, id) == 0) {
            for (int j = i; j < numberStudent - 1; j++) {
                sv[j] = sv[j + 1];
            }
            numberStudent--;
            save_students();
            printf("Da xoa sinh vien.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %s\n", id);
}

void search_student() {
    char id[50];
    printf("Nhap ID sinh vien can tim: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    for (int i = 0; i < numberStudent; i++) {
        if (strcmp(sv[i].id, id) == 0) {
            printf("ID: %s, Name: %s, Age: %d\n", sv[i].id, sv[i].name, sv[i].age);
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %s\n", id);
}

void sort_students() {
    for (int i = 0; i < numberStudent - 1; i++) {
        for (int j = i + 1; j < numberStudent; j++) {
            if (strcmp(sv[i].id, sv[j].id) > 0) {
                struct SinhVien temp = sv[i];
                sv[i] = sv[j];
                sv[j] = temp;
            }
        }
    }
    printf("Da sap xep danh sach sinh vien.\n");
}

