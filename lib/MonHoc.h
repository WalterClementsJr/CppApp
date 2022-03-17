#pragma once

#include <string>

using namespace std;

struct MonHoc {
    string ms;
    string ten;
    int sltclt;
    int sltcth;

    MonHoc() {
        ms = "";
        ten = "";
        sltclt = 0;
        sltcth = 0;   
    }

    MonHoc(string ms, string ten, int sltclt, int sltcth) {
        this->ms = ms;
        this->ten = ten;
        this->sltclt = sltclt;
        this->sltcth = sltcth;
    }
    string toString() { return ms + "," + ten + "," + to_string(sltclt) + "," + to_string(sltcth); }
};

class NodeMonHoc {
   public:
    MonHoc monhoc;
    NodeMonHoc *left;
    NodeMonHoc *right;

    NodeMonHoc() {
        left = NULL;
        right = NULL;
    }
};
