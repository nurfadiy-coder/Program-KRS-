#ifndef filedata_h //agar supaya tidak diinclude lebih dari sekali
#include "filedata.h"   
#endif

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
int main(int argc, char *argv[]) {
    int jumlah;
    int pilihan = 0;

    if (argc > 1) {
        pilihan = atoi(argv[1]);
    }

    if (pilihan == 1) {
        printf("\n===INPUT MATAKULIAH===");
        Matakuliah *daftar_mk = inputDataMatakuliah(&jumlah);
        simpanMatakuliahKeFileCSV(daftar_mk, jumlah, FILE_MATAKULIAH);
        free(daftar_mk);
        bacaMatakuliahDariFileCSV(FILE_MATAKULIAH);
    }
        
    else if (pilihan == 2) {
        printf("\n===INPUT MAHASISWA===");
        Mahasiswa *daftar_mhs = inputDataMahasiswa(&jumlah);
        simpanMahasiswaKeFileCSV(daftar_mhs, jumlah, FILE_MAHASISWA);
        free(daftar_mhs);
        bacaMahasiswaDariFileCSV(FILE_MAHASISWA);
    }

    else if (pilihan == 3) {
        printf("\n===INPUT KRS===");
        KRS *daftar_krs = inputDataKRS(&jumlah);
        simpanKRSKeFileCSV(daftar_krs, jumlah, FILE_KRS);
        free(daftar_krs);
        bacaKRSDariFileCSV(FILE_KRS);
    }

    else {
        printf("\n===PILIHAN TIDAK VALID===\n");
    }

   

    return 0;
}