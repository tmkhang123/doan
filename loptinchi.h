#include <iomanip>
void LuuVaoFile(const string& tenFile, const DSLTC& dsltc) {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong the mo file " << tenFile << endl;
        return;
    }

    for (int i = 0; i < dsltc.n; ++i) {
        file << dsltc.nodes[i]->MaMH << endl;
        file << dsltc.nodes[i]->NienKhoa << endl;
        file << dsltc.nodes[i]->HocKy << endl;
        file << dsltc.nodes[i]->Nhom << endl;
        file << dsltc.nodes[i]->SoSVMin << endl;
        file << dsltc.nodes[i]->SoSVMax << endl;
        file << dsltc.nodes[i]->TrangThaiLTC << endl;
        file << dsltc.nodes[i]->MaLopTC << endl;

        // Ghi danh sách sinh viên đăng ký
        PTRDK p = dsltc.nodes[i]->FirstDK;
        while (p != nullptr) {
            file << p->dk.MaSV << " " << p->dk.TrangThai << " " << p->dk.Diem << endl;
            p = p->next;
        }

        if (i < dsltc.n - 1) {
            file << endl;  // Thêm dòng trống giữa các lớp tín chỉ, ngoại trừ lớp cuối cùng
        }
    }

    file.close();
    cout << "Luu danh sach lop tin chi vao file " << tenFile << " thanh cong." << endl;
}

void veBang(int x, int y, int soCot, int chieuRongCot[], int soDong) {
    // Vẽ hàng đầu
    gotoxy(x, y);
    cout << char(201); // Góc trên trái
    for (int i = 0; i < soCot; i++) {
        for (int j = 0; j < chieuRongCot[i]; j++) cout << char(205); // Đường ngang
        if (i < soCot - 1) cout << char(203); // Giao giữa các cột
    }
    cout << char(187); // Góc trên phải

    // Vẽ các dòng dữ liệu
    for (int i = 1; i <= soDong; i++) {
        gotoxy(x, y + i);
        cout << char(186); // Cột trái
        for (int j = 0; j < soCot; j++) {
            gotoxy(x + 1 + chieuRongCot[j] * j, y + i);
            cout << string(chieuRongCot[j], ' '); // Không gian dữ liệu
            cout << char(186); // Giao giữa các cột
        }
    }

    // Vẽ hàng cuối
    gotoxy(x, y + soDong + 1);
    cout << char(200); // Góc dưới trái
    for (int i = 0; i < soCot; i++) {
        for (int j = 0; j < chieuRongCot[i]; j++) cout << char(205); // Đường ngang
        if (i < soCot - 1) cout << char(202); // Giao giữa các cột
    }
    cout << char(188); // Góc dưới phải
}
void HienThiDanhSachLopTinChi(const DSLTC& dsltc, PTRMH root) {
    ifstream file("DSLTC.txt");
    if (!file.is_open()) {
        cout << "Khong mo duoc file DSLTC.txt" << endl;
        return;
    }

    // Định nghĩa độ rộng của các cột
    int chieuRongCot[] = { 12, 15, 8, 8, 10, 10, 12, 10 };
    int soCot = sizeof(chieuRongCot) / sizeof(chieuRongCot[0]);

    // Vẽ bảng với tiêu đề
    veBang(5, 2, soCot, chieuRongCot, 10); // 10 dòng ví dụ

    // In tiêu đề cột
    gotoxy(6, 3); cout << "Ma MH";
    gotoxy(18, 3); cout << "Nien Khoa";
    gotoxy(34, 3); cout << "Hoc Ky";
    gotoxy(44, 3); cout << "Nhom";
    gotoxy(54, 3); cout << "SV Min";
    gotoxy(66, 3); cout << "SV Max";
    gotoxy(78, 3); cout << "Trang Thai";
    gotoxy(92, 3); cout << "ID Lop";

    string maMH, nienKhoa;
    int hocKy, nhom, svMin, svMax, trangThai, idLop;

    int y = 4; // Vị trí bắt đầu in dữ liệu
    while (file >> maMH >> nienKhoa >> hocKy >> nhom >> svMin >> svMax >> trangThai >> idLop) {
        gotoxy(6, y); cout << setw(10) << left << maMH;
        gotoxy(18, y); cout << setw(12) << left << nienKhoa;
        gotoxy(34, y); cout << setw(8) << left << hocKy;
        gotoxy(44, y); cout << setw(8) << left << nhom;
        gotoxy(54, y); cout << setw(10) << left << svMin;
        gotoxy(66, y); cout << setw(10) << left << svMax;
        gotoxy(78, y); cout << setw(12) << left << trangThai;
        gotoxy(92, y); cout << setw(10) << left << idLop;
        y++;
    }
    file.close();
}
void InDanhSachLopTinChi(const DSLTC& dsltc, PTRMH root, const string& nienKhoa, int hocKy) {

    bool found = false;

    for (int i = 0; i < dsltc.n; ++i) {
        if (dsltc.nodes[i]->NienKhoa == nienKhoa && dsltc.nodes[i]->HocKy == hocKy) {
            found = true;
            cout << "Danh sach lop tin chi cho nien khoa " << nienKhoa << " va hoc ky " << hocKy << ":" << endl;
            PTRMH mhNode = timKiemMonHoc(root, dsltc.nodes[i]->MaMH);
            string tenMH;
            if (mhNode != nullptr) {
                tenMH = mhNode->mh.TenMH;
            }
            else {
                tenMH = "Khong tim thay";
            }

            // Hiển thị thông tin chi tiết của từng lớp tín chỉ
            cout << "Ma Lop TC: " << dsltc.nodes[i]->MaLopTC << endl;
            cout << "Ma MH: " << dsltc.nodes[i]->MaMH << endl;
            cout << "Ten MH: " << tenMH << endl;
            cout << "Nien khoa: " << dsltc.nodes[i]->NienKhoa << endl;
            cout << "Hoc ky: " << dsltc.nodes[i]->HocKy << endl;
            cout << "Nhom: " << dsltc.nodes[i]->Nhom << endl;
            cout << "So SV toi thieu: " << dsltc.nodes[i]->SoSVMin << endl;
            cout << "So SV toi da: " << dsltc.nodes[i]->SoSVMax << endl;
            cout << "Trang thai: " << (dsltc.nodes[i]->TrangThaiLTC == 1 ? "Mo" : "Huy") << endl;
            cout << "-----------------------------" << endl;
        }

    }
    if(!found){
        cout << "Khong tim thay lop tin chi nao cho nien khoa " << nienKhoa << " va hoc ky " << hocKy << "." << endl;
        return;
    }
    

}
void ThemLopTinChi(DSLTC& dsltc, int& currentMaLopTC, PTRMH root) {
    HienThiDanhSachLopTinChi(dsltc, root);

    if (dsltc.n >= MaxLTC) {
        cout << "Danh sach lop tin chi da day." << endl;
        return;
    }

    LopTinChi* newLTC = new LopTinChi;
    newLTC->MaLopTC = currentMaLopTC++;

    cout << "Nhap ma mon hoc: ";
    cin.ignore();
    getline(cin, newLTC->MaMH);

    if (timKiemMonHoc(root, newLTC->MaMH) == nullptr) {
        cout << "Ma mon hoc khong ton tai. Vui long nhap lai." << endl;
        delete newLTC;
        currentMaLopTC--; 
        return;
    }

    cout << "Nhap nien khoa: ";
    getline(cin, newLTC->NienKhoa);

    cout << "Nhap hoc ky: ";
    cin >> newLTC->HocKy;
    cin.ignore();

    cout << "Nhap nhom: ";
    cin >> newLTC->Nhom;
    cin.ignore();
    for (int i = 0; i < dsltc.n; ++i) {
        if (dsltc.nodes[i]->NienKhoa == newLTC->NienKhoa &&
            dsltc.nodes[i]->HocKy == newLTC->HocKy &&
            dsltc.nodes[i]->Nhom == newLTC->Nhom && dsltc.nodes[i]->MaMH == newLTC->MaMH) {
            cout << "Lop tin chi da ton tai cho mon hoc, nien khoa, hoc ky, nhom nay. Vui long nhap lai." << endl;
            delete newLTC;
            currentMaLopTC--; 
            return;
        }
    }

    cout << "Nhap so SV toi thieu: ";
    cin >> newLTC->SoSVMin;
    cin.ignore();

    cout << "Nhap so SV toi da: ";
    cin >> newLTC->SoSVMax;
    cin.ignore();

    newLTC->TrangThaiLTC = 1;
    newLTC->FirstDK = nullptr;
    char save;
    cout << "Ban co muon  khong? (y/n): ";
    cin >> save;
    if (save == 'y' || save == 'Y') {
        dsltc.nodes[dsltc.n++] = newLTC;
        LuuVaoFile("DSLTC.txt", dsltc);
        cout << "Them lop tin chi thanh cong!" << endl;
    }
}



void XoaLopTinChi(DSLTC& dsltc, PTRMH root) {
    HienThiDanhSachLopTinChi(dsltc, root);
    bool found = false;
    int maLopTC;
    cout << "Nhap ma lop tin chi can xoa: ";
    cin >> maLopTC;
    cin.ignore();
    for (int i = 0; i < dsltc.n; ++i) {
        if (dsltc.nodes[i]->MaLopTC == maLopTC) {
            found = true;
            cout << "Ban co that su muon xoa khong? (y/n): ";
            char save;
            cin >> save;
            if (save == 'y' || save == 'Y') {
                delete dsltc.nodes[i];
                dsltc.nodes[i] = dsltc.nodes[--dsltc.n]; 
                cout << "Xoa lop tin chi thanh cong!" << endl;
                LuuVaoFile("DSLTC.txt", dsltc);
            }
            return;
        }       
    }
    if (!found) {
        cout << "Khong tim thay lop tin chi." << endl;
        system("pause");
        return;
    }
       

}


void HieuChinhLopTinChi(DSLTC& dsltc, PTRMH root) {
    HienThiDanhSachLopTinChi(dsltc, root);
    bool found = false;
    int maLopTC;
    cout << "Nhap ma lop tin chi can hieu chinh: ";
    cin >> maLopTC;
    cin.ignore();
    for (int i = 0; i < dsltc.n; ++i) {
        if (dsltc.nodes[i]->MaLopTC == maLopTC) {
            found = true;
            LopTinChi *ltc = new LopTinChi();
            ltc->MaLopTC = dsltc.nodes[i]->MaLopTC;
            ltc->MaMH = dsltc.nodes[i]->MaMH;
            ltc->NienKhoa = dsltc.nodes[i]->NienKhoa;
            ltc->HocKy = dsltc.nodes[i]->HocKy;
            ltc->Nhom = dsltc.nodes[i]->Nhom;
            ltc->SoSVMin = dsltc.nodes[i]->SoSVMin;
            ltc->SoSVMax = dsltc.nodes[i]->SoSVMax;
            ltc->TrangThaiLTC = dsltc.nodes[i]->TrangThaiLTC;
            ltc->FirstDK=dsltc.nodes[i]->FirstDK;
            cout << "Nhap thong tin moi cho lop tin chi (de trong neu khong thay doi):\n";

            // Nhập các thông tin khác
            cout << "Nhap Nien Khoa (" << ltc->NienKhoa << "): ";
            string newNienKhoa;
            getline(cin, newNienKhoa);
            if (!newNienKhoa.empty()) ltc->NienKhoa = newNienKhoa;

            cout << "Nhap Hoc Ky (" << ltc->HocKy << "): ";
            string newHocKy;
            getline(cin, newHocKy);
            if (!newHocKy.empty()) ltc->HocKy = stoi(newHocKy);

            cout << "Nhap Nhom (" << ltc->Nhom << "): ";
            string newNhom;
            getline(cin, newNhom);
            if (!newNhom.empty()) ltc->Nhom = stoi(newNhom);

            cout << "Nhap So SV toi thieu (" << ltc->SoSVMin << "): ";
            string newSoSVMin;
            getline(cin, newSoSVMin);
            if (!newSoSVMin.empty()) ltc->SoSVMin = stoi(newSoSVMin);

            cout << "Nhap So SV toi da (" << ltc->SoSVMax << "): ";
            string newSoSVMax;
            getline(cin, newSoSVMax);
            if (!newSoSVMax.empty()) ltc->SoSVMax = stoi(newSoSVMax);

            cout << "Nhap Trang Thai Lop Tin Chi (0: huy, 1: mo) (" << ltc->TrangThaiLTC << "): ";
            string newTrangThaiLTC;
            getline(cin, newTrangThaiLTC);
            if (!newTrangThaiLTC.empty()) ltc->TrangThaiLTC = stoi(newTrangThaiLTC);
            char save;
            cout << "Ban co muon luu thay doi khong? (y/n): ";
            cin >> save;
            if(save == 'y' || save == 'Y'){
                //delete [] dsltc.nodes[i];
                dsltc.nodes[i] = ltc;
                LuuVaoFile("DSLTC.txt",dsltc);
            }
            break;
        }
    }

    if (!found) {
        cout << "Khong tim thay lop tin chi voi ma " << maLopTC << "\n";
        return;
    }

}
void DocLTC(const string& tenFile, DSLTC& dsltc, int& currentMaLopTC) {
    ifstream inFile(tenFile);

    if (!inFile.is_open()) {
        cout << "Khong the mo file " << tenFile << endl;
        return;
    }

    currentMaLopTC = 1;
    dsltc.n = 0;
    while (!inFile.eof()) {
        dsltc.nodes[dsltc.n] = new LopTinChi;

        // Đọc thông tin lớp tín chỉ
        getline(inFile, dsltc.nodes[dsltc.n]->MaMH);
        if (dsltc.nodes[dsltc.n]->MaMH.empty()) {
            delete dsltc.nodes[dsltc.n];
            break;
        }
        getline(inFile, dsltc.nodes[dsltc.n]->NienKhoa);
        inFile >> dsltc.nodes[dsltc.n]->HocKy;
        inFile >> dsltc.nodes[dsltc.n]->Nhom;
        inFile >> dsltc.nodes[dsltc.n]->SoSVMin;
        inFile >> dsltc.nodes[dsltc.n]->SoSVMax;
        inFile >> dsltc.nodes[dsltc.n]->TrangThaiLTC;
        inFile >> dsltc.nodes[dsltc.n]->MaLopTC;
        inFile.ignore(); // Bỏ qua ký tự newline sau khi đọc số nguyên

        // Đọc danh sách sinh viên đăng ký ngay sau thông tin lớp tín chỉ
        string line;
        while (getline(inFile, line)) {
            if (line.empty()) {
                break;  // Kết thúc danh sách sinh viên của lớp này khi gặp dòng trống
            }
            istringstream iss(line);
            string maSV;
            int trangThai;
            float diem;
            iss >> maSV >> trangThai >> diem;

            PTRDK newDK = new nodeDangKy;
            newDK->dk.MaSV = maSV;
            newDK->dk.TrangThai = trangThai;
            newDK->dk.Diem = diem;
            newDK->next = dsltc.nodes[dsltc.n]->FirstDK;
            dsltc.nodes[dsltc.n]->FirstDK = newDK;
        }

        dsltc.n++;
    }

    inFile.close();
    cout << "Tai du lieu thanh cong!" << endl;
}




void HuyLopTinChi(DSLTC& dsltc) {
    for (int i = 0; i < dsltc.n; ++i) {
        LopTinChi* ltc = dsltc.nodes[i];
        int countSV = 0;
        PTRDK p = ltc->FirstDK;

        while (p != NULL) {
            if (p->dk.TrangThai == 1) {
                countSV++;
            }
            p = p->next;
        }

        if (countSV < ltc->SoSVMin) {
            cout << "Lop tin chi Ma Lop TC: " << ltc->MaLopTC << " co so SV dang ky < So SV Min. Ban co muon huy lop nay? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                while (ltc->FirstDK != nullptr) {
                    PTRDK temp = ltc->FirstDK;
                    ltc->FirstDK = ltc->FirstDK->next;
                    delete temp;
                }

                ltc->TrangThaiLTC = 0;
                cout << "Da huy lop tin chi Ma Lop TC: " << ltc->MaLopTC << endl;
            }
        }
    }
}
