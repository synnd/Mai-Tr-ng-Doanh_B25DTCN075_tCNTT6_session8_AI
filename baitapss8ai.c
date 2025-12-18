#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa số lượng sinh viên tối đa
#define MAX_SV 100
#define FILE_NAME "danhsachsinhvien_v2.txt"

// 1. CẬP NHẬT STRUCT: Thêm trường age
typedef struct {
    int id;
    char ten[50];
    int age; // <--- Moi them
    float gpa;
} SinhVien;

// --- KHAI BÁO CÁC HÀM ---
void xoaXuongDong(char* str);
int kiemTraIDTrung(SinhVien ds[], int n, int id);
void themSinhVien(SinhVien ds[], int *n);
void inDanhSach(SinhVien ds[], int n);
void luuFile(SinhVien ds[], int n);
void docFile(SinhVien ds[], int *n);
void timSinhVienByID(SinhVien ds[], int n);
void tinhGPATrungBinh(SinhVien ds[], int n);
void sapXepTheoGPA(SinhVien ds[], int n);
void themSinhVienCoKiemTra(SinhVien ds[], int *n);
void xoaSinhVien(SinhVien ds[], int *n);
void menu();

// --- HÀM MAIN ---
int main() {
    SinhVien ds[MAX_SV]={
        {101, "Nguyen Van An", 20, 8.5},
        {102, "Tran Thi Binh", 19, 7.2},
        {103, "Le Van Cuong", 21, 6.5},
        {104, "Pham Thi Dung", 20, 9.1},
        {105, "Hoang Van Em", 22, 5.5},
        {106, "Vu Thi Hoa", 19, 8.0},
        {107, "Dang Van Giang", 21, 7.8},
        {108, "Bui Thi Hanh", 20, 9.5},
        {109, "Do Van Hung", 23, 4.5},
        {110, "Ngo Thi Kim", 19, 6.8}
};
    int n = 10; 
    int choice;

    do {
        menu();
        if (scanf("%d", &choice) != 1) {
            printf("\n>> Loi: Vui long nhap mot so nguyen!\n");
            while(getchar() != '\n'); 
            continue;
        }

        switch (choice) {
            case 1: themSinhVien(ds, &n); break;
            case 2: inDanhSach(ds, n); break;
            case 3: luuFile(ds, n); break;
            case 4: docFile(ds, &n); break;
            case 5: timSinhVienByID(ds, n); break;
            case 6: tinhGPATrungBinh(ds, n); break;
            case 7: sapXepTheoGPA(ds, n); break;
            case 8: themSinhVienCoKiemTra(ds, &n); break;
            case 9: xoaSinhVien(ds, &n); break;
            case 0: printf("\n>> Da thoat chuong trinh.\n"); break;
            default: printf("\n>> Lua chon khong hop le!\n");
        }
    } while (choice != 0);

    return 0;
}

// --- CÁC HÀM CHI TIẾT ---

void menu() {
    printf("\n===== MENU QUAN LY SINH VIEN =====\n");
    printf("1. Them sinh vien\n");
    printf("2. In danh sach sinh vien\n");
    printf("3. Luu danh sach vao file\n");
    printf("4. Doc danh sach tu file\n");
    printf("5. Tim sinh vien theo ID\n");
    printf("6. Tinh GPA trung binh\n");
    printf("7. Sap xep sinh vien theo GPA giam dan\n");
    printf("8. Them sinh vien (Co kiem tra ID)\n");
    printf("9. Xoa sinh vien theo ID\n");
    printf("0. Thoat\n");
    printf("Nhap lua chon: ");
}

void xoaXuongDong(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int kiemTraIDTrung(SinhVien ds[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (ds[i].id == id) return 1;
    }
    return 0;
}

// 2. CẬP NHẬT NHẬP LIỆU: Thêm nhập Tuổi
void themSinhVienCoKiemTra(SinhVien ds[], int *n) {
    if (*n >= MAX_SV) {
        printf("\n>> Danh sach day!\n");
        return;
    }

    SinhVien svMoi;
    
    // Nhập ID
    printf("Nhap ID: ");
    while (scanf("%d", &svMoi.id) != 1) {
        printf(">> ID phai la so. Nhap lai: ");
        while(getchar() != '\n');
    }
    
    if (kiemTraIDTrung(ds, *n, svMoi.id)) {
        printf("\n>> Loi: ID %d da ton tai!\n", svMoi.id);
        return;
    }

    // Nhập Tên
    while(getchar() != '\n'); 
    printf("Nhap Ten: ");
    fgets(svMoi.ten, sizeof(svMoi.ten), stdin);
    xoaXuongDong(svMoi.ten);

    if (strlen(svMoi.ten) == 0) {
        printf("\n>> Loi: Ten khong duoc de trong!\n");
        return;
    }

    // --- CẬP NHẬT: Nhập Tuổi ---
    printf("Nhap Tuoi (18-100): ");
    while (scanf("%d", &svMoi.age) != 1 || svMoi.age < 18 || svMoi.age > 100) {
        printf(">> Tuoi khong hop le (phai la so tu 18-100). Nhap lai: ");
        while(getchar() != '\n');
    }

    // Nhập GPA
    printf("Nhap GPA (0-4): ");
    while (scanf("%f", &svMoi.gpa) != 1 || svMoi.gpa < 0 || svMoi.gpa > 4) {
        printf(">> GPA khong hop le. Nhap lai: ");
        while(getchar() != '\n');
    }

    ds[*n] = svMoi;
    (*n)++;
    printf("\n>> Them sinh vien thanh cong!\n");
}

void themSinhVien(SinhVien ds[], int *n) {
    themSinhVienCoKiemTra(ds, n);
}

// 3. CẬP NHẬT HIỂN THỊ: Thêm cột Tuổi
void inDanhSach(SinhVien ds[], int n) {
    if (n == 0) {
        printf("\n>> Danh sach rong!\n");
        return;
    }
    printf("\n--- DANH SACH SINH VIEN ---\n");
    // Thêm cột Tuổi vào tiêu đề
    printf("%-10s %-25s %-10s %-10s\n", "ID", "Ho Ten", "Tuoi", "GPA");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        // In thêm biến age
        printf("%-10d %-25s %-10d %-10.2f\n", ds[i].id, ds[i].ten, ds[i].age, ds[i].gpa);
    }
}

// 4. CẬP NHẬT LƯU FILE: Ghi thêm Tuổi
void luuFile(SinhVien ds[], int n) {
    FILE *f = fopen(FILE_NAME, "w");
    if (f == NULL) {
        printf("\n>> Loi mo file!\n");
        return;
    }
    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; i++) {
        // Cấu trúc file: ID -> Tên -> Tuổi -> GPA
        fprintf(f, "%d\n%s\n%d\n%.2f\n", ds[i].id, ds[i].ten, ds[i].age, ds[i].gpa);
    }
    fclose(f);
    printf("\n>> Da luu file %s\n", FILE_NAME);
}

// 5. CẬP NHẬT ĐỌC FILE: Đọc thêm Tuổi
void docFile(SinhVien ds[], int *n) {
    FILE *f = fopen(FILE_NAME, "r");
    if (f == NULL) {
        printf("\n>> Khong tim thay file %s!\n", FILE_NAME);
        return;
    }
    
    fscanf(f, "%d", n);
    for (int i = 0; i < *n; i++) {
        fscanf(f, "%d\n", &ds[i].id);
        fgets(ds[i].ten, sizeof(ds[i].ten), f);
        xoaXuongDong(ds[i].ten);
        
        // Đọc tuổi
        fscanf(f, "%d", &ds[i].age); 
        // Đọc GPA
        fscanf(f, "%f", &ds[i].gpa);
    }
    fclose(f);
    printf("\n>> Da doc du lieu thanh cong! So luong: %d\n", *n);
}

// 6. CẬP NHẬT TÌM KIẾM: Hiển thị Tuổi khi tìm thấy
void timSinhVienByID(SinhVien ds[], int n) {
    int idCantim;
    printf("Nhap ID can tim: ");
    scanf("%d", &idCantim);

    for (int i = 0; i < n; i++) {
        if (ds[i].id == idCantim) {
            printf("\n>> Tim thay: ID: %d - Ten: %s - Tuoi: %d - GPA: %.2f\n", 
                   ds[i].id, ds[i].ten, ds[i].age, ds[i].gpa);
            return;
        }
    }
    printf("\n>> Khong tim thay ID %d\n", idCantim);
}

void tinhGPATrungBinh(SinhVien ds[], int n) {
    if (n == 0) {
        printf("\n>> Danh sach rong!\n");
        return;
    }
    float tong = 0;
    for (int i = 0; i < n; i++) {
        tong += ds[i].gpa;
    }
    printf("\n>> GPA trung binh: %.2f\n", tong / n);
}

void sapXepTheoGPA(SinhVien ds[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ds[j].gpa < ds[j + 1].gpa) {
                SinhVien temp = ds[j];
                ds[j] = ds[j + 1];
                ds[j + 1] = temp;
            }
        }
    }
    printf("\n>> Da sap xep giam dan theo GPA!\n");
    inDanhSach(ds, n);
}

void xoaSinhVien(SinhVien ds[], int *n) {
    int idCanXoa;
    printf("Nhap ID can xoa: ");
    scanf("%d", &idCanXoa);
    int pos = -1;
    for (int i = 0; i < *n; i++) {
        if (ds[i].id == idCanXoa) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("\n>> Khong tim thay ID %d!\n", idCanXoa);
    } else {
        for (int i = pos; i < *n - 1; i++) {
            ds[i] = ds[i+1];
        }
        (*n)--;
        printf("\n>> Da xoa ID %d\n", idCanXoa);
    }
}


