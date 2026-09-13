#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class LopHoc {
private:
    string tenLop;
    int siSo;
    float* dsDiem;

    // Bien static dung chung cho tat ca doi tuong
    static int soLuongLop;

public:
    // Constructor mac dinh
    LopHoc() : tenLop("Chua dat ten"), siSo(0), dsDiem(nullptr) {
        soLuongLop++;
    }

    // Constructor co tham so
    LopHoc(string ten, int ss) : tenLop(ten), siSo(ss) {
        if (siSo > 0) {
            dsDiem = new float[siSo];

            for (int i = 0; i < siSo; i++) {
                dsDiem[i] = 0;
            }
        } else {
            siSo = 0;
            dsDiem = nullptr;
        }

        soLuongLop++;
    }

    // Copy Constructor - sao chep sau (Deep Copy)
    LopHoc(const LopHoc& other) {
        tenLop = other.tenLop;
        siSo = other.siSo;

        if (siSo > 0) {
            dsDiem = new float[siSo];

            for (int i = 0; i < siSo; i++) {
                dsDiem[i] = other.dsDiem[i];
            }
        } else {
            dsDiem = nullptr;
        }

        soLuongLop++;
    }

    // Destructor
    ~LopHoc() {
        delete[] dsDiem;
        soLuongLop--;
    }

    // Nhap diem
    void NhapDiem() {
        if (siSo == 0) {
            cout << "Lop khong co sinh vien.\n";
            return;
        }

        for (int i = 0; i < siSo; i++) {
            do {
                cout << "Nhap diem sinh vien " << i + 1 << ": ";
                cin >> dsDiem[i];

                if (dsDiem[i] < 0 || dsDiem[i] > 10) {
                    cout << "Diem phai nam trong khoang 0 - 10!\n";
                }
            } while (dsDiem[i] < 0 || dsDiem[i] > 10);
        }
    }

    // Xuat diem - phuong thuc const
    void XuatDiem() const {
        cout << "\nTen lop: " << tenLop << endl;
        cout << "Si so: " << siSo << endl;
        cout << "Danh sach diem: ";

        for (int i = 0; i < siSo; i++) {
            cout << fixed << setprecision(2) << dsDiem[i] << " ";
        }

        cout << endl;
    }

    // Tinh diem trung binh - phuong thuc const
    float TinhDiemTrungBinh() const {
        if (siSo == 0) {
            return 0;
        }

        float tong = 0;

        for (int i = 0; i < siSo; i++) {
            tong += dsDiem[i];
        }

        return tong / siSo;
    }

    // Getter const
    string GetTenLop() const {
        return tenLop;
    }

    // Phuong thuc static
    static int LaySoLuongLop() {
        return soLuongLop;
    }

    // Ham friend
    friend void SoSanhDiemTrungBinh(
        const LopHoc& lop1,
        const LopHoc& lop2
    );
};

// Khoi tao bien static ben ngoai class
int LopHoc::soLuongLop = 0;

// Ham friend: khong co LopHoc::
void SoSanhDiemTrungBinh(
    const LopHoc& lop1,
    const LopHoc& lop2
) {
    float dtb1 = lop1.TinhDiemTrungBinh();
    float dtb2 = lop2.TinhDiemTrungBinh();

    cout << "\n--- SO SANH DIEM TRUNG BINH ---\n";

    if (dtb1 > dtb2) {
        cout << lop1.tenLop << " co diem trung binh cao hon.\n";
    }
    else if (dtb1 < dtb2) {
        cout << lop2.tenLop << " co diem trung binh cao hon.\n";
    }
    else {
        cout << "Hai lop co diem trung binh bang nhau.\n";
    }

    cout << fixed << setprecision(2);
    cout << lop1.tenLop << ": " << dtb1 << endl;
    cout << lop2.tenLop << ": " << dtb2 << endl;
}

int main() {
    cout << "========================================\n";
    cout << "     LAB 06 - LOP HOC C++\n";
    cout << " Static - Const - Friend - Deep Copy\n";
    cout << "========================================\n\n";

    cout << "So luong lop ban dau: "
         << LopHoc::LaySoLuongLop() << endl;

    // Tao lop thu nhat
    LopHoc lop1("CNTT K24A", 3);
    cout << "Sau khi tao lop1: "
         << LopHoc::LaySoLuongLop() << " lop\n";

    lop1.NhapDiem();
    lop1.XuatDiem();

    // Tao lop thu hai
    LopHoc lop2("CNTT K24B", 3);
    cout << "\nSau khi tao lop2: "
         << LopHoc::LaySoLuongLop() << " lop\n";

    lop2.NhapDiem();
    lop2.XuatDiem();

    // Copy Constructor - Deep Copy
    LopHoc lop3 = lop1;

    cout << "\nSau khi sao chep lop1 thanh lop3: "
         << LopHoc::LaySoLuongLop() << " lop\n";

    cout << "\n--- LOP3 SAU KHI DEEP COPY ---\n";
    lop3.XuatDiem();

    // Tinh diem trung binh
    cout << "\nDiem trung binh lop1: "
         << fixed << setprecision(2)
         << lop1.TinhDiemTrungBinh() << endl;

    cout << "Diem trung binh lop2: "
         << lop2.TinhDiemTrungBinh() << endl;

    // Ham friend
    SoSanhDiemTrungBinh(lop1, lop2);

    cout << "\n========================================\n";
    cout << "Ket thuc chuong trinh.\n";
    cout << "Destructor se tu dong giai phong bo nho.\n";
    cout << "========================================\n";

    return 0;
}
