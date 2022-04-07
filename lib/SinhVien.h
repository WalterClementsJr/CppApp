#ifndef SINHVIEN_H
#define SINHVIEN_H

#include <iostream>
#include <string>
#include <sstream>
#include<fstream>

using namespace std;

struct SinhVien {
    string maSV;
    string ho;
    string ten;
    string phai;
    string soDT;
    string maLop;
    SinhVien() {
        maSV = "";
        ho = "";
        ten = "";
        phai = "";
        soDT = "";
        maLop = "";
    }
    SinhVien(string maSV, string ho, string ten, string phai, string soDT,
             string maLop) {
        this->maSV = maSV;
        this->ho = ho;
        this->ten = ten;
        this->phai = phai;
        this->soDT = soDT;
        this->maLop = maLop;
    }

    string toString() {
        return maSV + "," + ho + "," + ten + "," + phai + "," + soDT +
               "," + maLop;
    }
};
struct NodeSinhVien {
    SinhVien sinhVien;
    NodeSinhVien *next;

    NodeSinhVien() { next = NULL; }
};
typedef NodeSinhVien *PTRSinhVien;

struct DangKy {
    string maSV;
    float diem;
    bool huyDK;
};

class DSSV {
   private:
    int dem = 0;
   public:
    PTRSinhVien First = NULL;

    DSSV() { khoiTao(First); }
    void khoiTao(PTRSinhVien &First) { First = NULL; }
    void insertFirst(PTRSinhVien &First, SinhVien &sv);
    void insertAfter(PTRSinhVien p, SinhVien sv);
    void duyet(PTRSinhVien First);
    void docFile(fstream &file, SinhVien &sv);
    void ghiFile(PTRSinhVien First, ofstream &file);
    void xuatSV(SinhVien sv);

    
};




// DsSinhVien:DsSinhVien(){}
void DSSV::insertFirst(PTRSinhVien &First, SinhVien &sv) {
    PTRSinhVien p;
    p = new NodeSinhVien;
    p->sinhVien = sv;
    p->next = First;
    First = p;
    dem++;
    
}
void DSSV::insertAfter(PTRSinhVien p, SinhVien sv){
    PTRSinhVien q;
    if(p == NULL)
        cout<<"Add fail";
    else
    {
        q = new NodeSinhVien;
        q->sinhVien = sv;
        q->next = p->next;
        p->next = q;
        dem++;
    }
    
}

void DSSV::duyet(PTRSinhVien First) {
    PTRSinhVien p;
    int stt = 0;
    for (p = First; p != NULL; p = p->next) {
        cout << p->sinhVien.toString() << endl;
    }
}
void DSSV::ghiFile(PTRSinhVien First, ofstream &file){
    PTRSinhVien p;
    int stt = 0;
    for (p = First; p != NULL; p = p->next) {
        file << p->sinhVien.toString() << endl;
    }
    file.close();
    
}

//đọc ghi file
void DSSV::docFile(fstream &filein, SinhVien &sv){
    getline(filein,sv.maSV,',');
    getline(filein,sv.ho,',');
    getline(filein,sv.ten,',');
    getline(filein,sv.phai,',');
    getline(filein,sv.soDT,',');
    getline(filein,sv.maLop,',');

}
void DSSV::xuatSV(SinhVien sv){
    cout<<"\nMaSV:"<<sv.maSV;
    cout<<"\nHo:"<<sv.ho;
    cout<<"\nTen:"<<sv.ten;
    cout<<"\nPhai:"<<sv.phai;
    cout<<"\nSoDT:"<<sv.soDT;
    cout<<"\nMaLop:"<<sv.maLop;
}




#endif