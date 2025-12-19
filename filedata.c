#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef filedata_h
#include "filedata.h"
#endif

Matakuliah* inputDataMatakuliah(int *jumlah) {
    printf("\nMasukkan jumlah matakuliah: ");
    scanf("%d", jumlah);
    bersihkanBufferInput();

    // Alokasi dinamis
    Matakuliah *data = (Matakuliah*) malloc((*jumlah) * sizeof(Matakuliah));
    if (!data) {
        printf("Alokasi memori gagal!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *jumlah; i++) {
        printf("\nMatakuliah #%d\n", i + 1);
        data[i].id = i + 1;

        printf("Kode MK   : ");
        fgets(data[i].kode_mk, MAX_NAME_LEN, stdin);
        data[i].kode_mk[strcspn(data[i].kode_mk, "\n")] = '\0'; // hapus newline

        printf("Nama MK  : ");
        fgets(data[i].nama_mk, MAX_NAME_LEN, stdin);
        data[i].nama_mk[strcspn(data[i].nama_mk, "\n")] = '\0';

        printf("SKS    : ");
        scanf("%d", &data[i].sks);
        bersihkanBufferInput();
    }
    return data;
}

Matakuliah cariMatakuliahByKode(const char *kode_mk){
    Matakuliah found = {0, "", "", 0};
    FILE *fp = fopen(FILE_MATAKULIAH, "r");
    if (!fp) {return found; };

    char baris[256];
    char temp_baris[256];
    char *token;

    fgets(baris, sizeof(baris), fp);

    while (fgets(baris, sizeof(baris), fp)) {
       baris[strcspn(baris, "\n")] = 0;
       strcpy(temp_baris, baris);

       token = strtok(temp_baris, ",");
       found.id = atoi(token);

       token = strtok(NULL, ",");
    
       if (strcmp(token, kode_mk) == 0) {
           strcpy(found.kode_mk, token);

           token = strtok(NULL, ",");
           strcpy(found.nama_mk, token);

           token = strtok(NULL, ",");
           found.sks = atoi(token);

           fclose(fp);
           return found;
       }
    }
    fclose(fp);
    return found;
}

void simpanMatakuliahKeFileCSV(Matakuliah *mk, int jumlah, const char *namaFile) {
    FILE *fp = fopen(namaFile, "w");
    if (!fp) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }
    fprintf(fp, "ID  |  Kode MK  |  Nama MK  |  SKS  |\n");

    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%d,%s,%s,%d\n",
                mk[i].id, mk[i].kode_mk, mk[i].nama_mk, mk[i].sks);
    }

    fclose(fp);
    printf("\nData berhasil disimpan ke file '%s'\n", namaFile);
}

void bacaMatakuliahDariFileCSV(const char *namaFile) {
    FILE *fp = fopen(namaFile, "r");
    if (!fp) {
        printf("File '%s' tidak ditemukan!\n", namaFile);
        return;
    }

    char baris[256];
    int barisKe = 0;

    printf("\n=== Data Mata Kuliah dari File ===\n");
    printf("+----+------------+--------------+------+\n");

    while (fgets(baris, sizeof(baris), fp)) {
        baris[strcspn(baris, "\n")] = 0;

        if (barisKe == 0) {
            printf("| %-2s | %-10s | %-12s | %-4s |\n", "ID", "Kode MK", "Nama MK", "SKS"); 
            printf("+----+------------+--------------+------+\n");
        } else {
            char *token = strtok(baris, ",");
            printf("| %-2s ", token); 

            token = strtok(NULL, ",");
            printf("| %-10s ", token); 

            token = strtok(NULL, ",");
            printf("| %-12s ", token); 

            token = strtok(NULL, ",");
            printf("| %-4s |\n", token); 
            printf("+----+------------+--------------+------+\n");

        }
        barisKe++;
    }

    fclose(fp);
}

Mahasiswa* inputDataMahasiswa(int *jumlah) {
    printf("\nMasukkan jumlah mahasiswa: ");
    scanf("%d", jumlah);
    bersihkanBufferInput();

    // Alokasi dinamis
    Mahasiswa *data = (Mahasiswa*) malloc((*jumlah) * sizeof(Mahasiswa));
    if (!data) {
        printf("Alokasi memori gagal!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *jumlah; i++) {
        printf("\nMahasiswa #%d\n", i + 1);
        data[i].id = i + 1;

        printf("NIM   : ");
        fgets(data[i].nim, MAX_NIM_LEN, stdin);
        data[i].nim[strcspn(data[i].nim, "\n")] = '\0';

        printf("Nama   : ");
        fgets(data[i].nama, MAX_NAME_LEN, stdin);
        data[i].nama[strcspn(data[i].nama, "\n")] = '\0'; // hapus newline

        printf("Prodi  : ");
        fgets(data[i].prodi, MAX_PRODI_LEN, stdin);
        data[i].prodi[strcspn(data[i].prodi, "\n")] = '\0';

        printf("IPK    : ");
        scanf("%f", &data[i].ipk);
        bersihkanBufferInput();
    }

    return data;
}

Mahasiswa cariMahasiswaByNIM(const char *nim){
    Mahasiswa found = {0, "", "", 0};
    FILE *fp = fopen(FILE_MAHASISWA, "r");
    if (!fp) {return found; };

    char baris[256];
    char temp_baris[256];
    char *token;

    fgets(baris, sizeof(baris), fp);

    while (fgets(baris, sizeof(baris), fp)) {
       baris[strcspn(baris, "\n")] = 0;
       strcpy(temp_baris, baris);

       token = strtok(temp_baris, ",");
       found.id = atoi(token);

       token = strtok(NULL, ",");
    
       if (strcmp(token, nim) == 0) {
           strcpy(found.nim, token);

           token = strtok(NULL, ",");
           strcpy(found.nama, token);

           token = strtok(NULL, ",");
           strcpy(found.prodi, token);

           token = strtok(NULL, ",");
           found.ipk = atof(token);

           fclose(fp);
           return found;
       }
    }
    fclose(fp);
    return found;
}

void simpanMahasiswaKeFileCSV(Mahasiswa *mhs, int jumlah, const char *namaFile) {
    FILE *fp = fopen(namaFile, "w");
    if (!fp) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }

    fprintf(fp, "ID  |  NIM  |  Nama  |  Prodi  |  IPK  |\n");

    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%d,%s,%s,%s,%.2f\n",
                mhs[i].id, mhs[i].nim, mhs[i].nama, mhs[i].prodi, mhs[i].ipk);
    }

    fclose(fp);
    printf("\nData berhasil disimpan ke file '%s'\n", namaFile);
}

void bacaMahasiswaDariFileCSV(const char *namaFile) {
    FILE *fp = fopen(namaFile, "r");
    if (!fp) {
        printf("File '%s' tidak ditemukan!\n", namaFile);
        return;
    }

    char baris[256];
    int barisKe = 0;

    printf("\n=== Data Mahasiswa dari File ===\n");
    printf("+----+-----------------+----------------------+-----------------+-------+\n");

    while (fgets(baris, sizeof(baris), fp)) {
        baris[strcspn(baris, "\n")] = 0;

        if (barisKe == 0) {
            printf("| %-2s | %-15s | %-20s | %-15s | %-5s |\n", "ID", "NIM", "Nama", "Prodi", "IPK"); 
            printf("+----+-----------------+----------------------+-----------------+-------+\n");
        } else {
            char *token = strtok(baris, ",");
            printf("| %-2s ", token); 

            token = strtok(NULL, ",");
            printf("| %-15s ", token); 

            token = strtok(NULL, ",");
            printf("| %-20s ", token); 

            token = strtok(NULL, ",");
            printf("| %-15s ", token); 

            token = strtok(NULL, ",");
            printf("| %-5s |\n", token); 
            printf("+----+-----------------+----------------------+-----------------+-------+\n");
        }
        barisKe++;
    }
    fclose(fp);
}

KRS* inputDataKRS(int *jumlah) {
    printf("\nMasukkan jumlah KRS: ");
    scanf("%d", jumlah);
    bersihkanBufferInput();

    // Alokasi dinamis
    KRS *data = (KRS*) malloc((*jumlah) * sizeof(KRS));
    if (!data) {
        printf("Alokasi memori gagal!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *jumlah; i++) {
        Mahasiswa mhs;

        printf("\nKRS #%d\n", i + 1);
        data[i].id = i + 1;
        data[i].total_sks = 0;
        data[i].jumlah_mk = 0;

        do {
            printf("NIM   : ");
            fgets(data[i].nim, MAX_NAME_LEN, stdin);
            data[i].nim[strcspn(data[i].nim, "\n")] = '\0'; // hapus newline
            
            mhs = cariMahasiswaByNIM(data[i].nim);

            if (mhs.id == 0) {
                printf("NIM TIDAK DITEMUKAN");
             } else {
                printf("Mahasiswa: %s (%s)\n", mhs.nama, mhs.prodi);
             }
            
        } while (mhs.id == 0);

         printf("Masukkan jumlah MK (Max %d)", MAX_MK_KRS); 
         scanf("%d", &data[i].jumlah_mk);
         bersihkanBufferInput();

        if (data[i].jumlah_mk > MAX_MK_KRS) data[i].jumlah_mk = MAX_MK_KRS;

        for (int j = 0; j < data[i].jumlah_mk; j++) {
        Matakuliah mk;
        char input_kode_mk[MAX_PRODI_LEN];

        do {
            printf("Kode MK ke-%d : ", j + 1);
            fgets(input_kode_mk, MAX_NAME_LEN, stdin);
            input_kode_mk[strcspn(input_kode_mk, "\n")] = '\0';

            mk = cariMatakuliahByKode(input_kode_mk);

            if (mk.id == 0) {
                printf("Kode MK TIDAK DITEMUKAN");
             } else {
                strcpy(data[i].kode_mk[j], input_kode_mk);
                data[i].sks_list[j] = mk.sks;
                data[i].total_sks += mk.sks;
                printf("Matakuliah: %s (%d SKS). Total SKS: %d\n", mk.nama_mk, mk.sks, data[i].total_sks);
             }
        
        } while (mk.id == 0);
      }
    }
    return data;
}

void simpanKRSKeFileCSV(KRS *krs, int jumlah, const char *namaFile) {
    FILE *fp = fopen(namaFile, "w");
    if (!fp) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }
    long size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    if (size == 0) {
        fprintf(fp, "ID,NIM,Kode MK\n");
    }

    for (int i = 0; i < jumlah; i++) {
        for (int j = 0; j < krs[i].jumlah_mk; j++) {
        fprintf(fp, "%d,%s,%s\n", krs[i].id, krs[i].nim, krs[i].kode_mk[j]);
        }
    }

    fclose(fp);
    printf("\nData berhasil disimpan ke file '%s'\n", namaFile);
}

void bacaKRSDariFileCSV(const char *namaFile) {
    FILE *fp = fopen(namaFile, "r");
    if (!fp) {
        printf("File '%s' tidak ditemukan!\n", namaFile);
        return;
    }
    char nim_sebelumnya[MAX_NIM_LEN] = "";
    int total_sks_kumulatif = 0;
    int barisKe = 0;
    char baris[512];
    char temp_baris[512];

    printf("\n====== Data KRS dari File ======\n");
    printf("+----+-----------------+----------------------+-----------------+-------+------------+--------------+------+-----------+\n");
    printf("| %-2s | %-15s | %-20s | %-15s | %-5s | %-10s | %-12s | %-4s | %-9s |\n", "ID", "NIM", "Nama", "Prodi", "IPK", "Kode MK", "Nama MK", "SKS", "Total SKS"); 
    printf("+----+-----------------+----------------------+-----------------+-------+------------+--------------+------+-----------+\n");

    while (fgets(baris, sizeof(baris), fp)) {
       if (barisKe == 0){
        barisKe++;
        continue;
       }

       char *token;
        baris[strcspn(baris, "\n")] = 0;
        strcpy(temp_baris, baris);

        token = strtok(temp_baris, ",");
        char id_krs[5]; strcpy(id_krs, token ? token : "---");
        
        token = strtok(NULL, ",");
        char nim_krs[MAX_NAME_LEN];
        strcpy(nim_krs, token ? token : "---");

        token = strtok(NULL, ","); 
        char kode_mk_krs[MAX_NAME_LEN]; 
        strcpy(kode_mk_krs, token ? token : "---");
            
        Mahasiswa mhs = cariMahasiswaByNIM(nim_krs);
        Matakuliah mk = cariMatakuliahByKode(kode_mk_krs);

        int sks_mk = mk.sks; 

        if (strcmp(nim_krs, nim_sebelumnya) != 0 && barisKe > 1) {
            printf("+----+-----------------+----------------------+-----------------+-------+------------+--------------+------+-----------+\n");
            total_sks_kumulatif = 0;
        }
        total_sks_kumulatif += sks_mk;

        printf("| %-2s ", id_krs);
        printf("| %-15s ", nim_krs);
        printf("| %-20s ", mhs.id != 0 ? mhs.nama : "");
        printf("| %-15s ", mhs.id != 0 ? mhs.prodi : "");

        char ipk_str[6];
        sprintf(ipk_str, "%.2f", mhs.ipk);
        printf("| %-5s ", mhs.ipk != 0 ? ipk_str : "---");

        printf("| %-10s ", mk.id != 0 ? mk.nama_mk : "");
        printf("| %-12s ", kode_mk_krs);
        printf("| %-4d ", sks_mk);
        printf("| %-9d |\n", total_sks_kumulatif);

        strcpy(nim_sebelumnya, nim_krs);
        barisKe++;
    }
    printf("+----+-----------------+----------------------+-----------------+-------+------------+--------------+------+-----------+\n");
    fclose(fp);
}

void bersihkanBufferInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
