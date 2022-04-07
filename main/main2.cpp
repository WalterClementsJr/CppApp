// #include "drawing.h"
#include <iostream>

#include "Helper.h"
#include "SinhVien.h"
#include "import.h"

using namespace std;
int dem;

void testDSSV(DSSV &ds) {


    ofstream fileWriter("./build/data/sinhvien.csv");

    SinhVien s1("1", "N", "N", "nam", "2123", "5234");
    SinhVien s2("2", "N", "N", "nam", "2123", "5234");
    SinhVien s3("3", "NA", "N", "nam", "2123", "5234");
    SinhVien s4("4", "N", "N", "nam", "2123", "5234");

    ds.insertFirst(ds.First, s1);
    ds.insertFirst(ds.First, s2);
    ds.insertFirst(ds.First, s3);
    ds.insertFirst(ds.First, s4);

    ds.duyet(ds.First);
    ds.ghiFile(ds.First, fileWriter);
}
void xemDSSV(DSSV &ds){
    SinhVien sv;
    ifstream fileRead("./build/data/sinhvien.csv");
    //filein.open(fileRead,ios::in);
    //ds.docFile(fileRead,sv);
    ds.xuatSV(sv);
    fileRead.close();
}

int main() {
    // cout<<"Hello";
    // keyTest();
    DSSV ds;

    testDSSV(ds);
    cout<<"So luong sinh vien: "<<dem;
    
    system("pause");
    return 0;
}
