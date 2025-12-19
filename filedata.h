#define MAX_NAME_LEN 100
#define MAX_PRODI_LEN 50
#define MAX_NIM_LEN 20
#define MAX_MK_KRS 10
#define FILE_MATAKULIAH "data_matakuliah.csv"
#define FILE_MAHASISWA "data_mahasiswa.csv"
#define FILE_KRS "data_krs.csv"

typedef struct {
    int id;
    char kode_mk[MAX_NAME_LEN];
    char nama_mk[MAX_PRODI_LEN];
    int sks;
} Matakuliah;

typedef struct {
    int id;
    char nim[MAX_NIM_LEN];
    char nama[MAX_NAME_LEN];
    char prodi[MAX_PRODI_LEN];
    float ipk;
} Mahasiswa;

typedef struct {
    int id;
    char nim[MAX_NAME_LEN];
    char kode_mk[MAX_MK_KRS][MAX_PRODI_LEN];
    int sks_list[MAX_MK_KRS];
    int jumlah_mk;
    int total_sks;
} KRS;

Mahasiswa cariMahasiswaByNIM(const char *nim);
Matakuliah cariMatakuliahByKode(const char *kode);

Matakuliah* inputDataMatakuliah(int *jumlah);
Mahasiswa* inputDataMahasiswa(int *jumlah);
KRS* inputDataKRS(int *jumlah);
void simpanMatakuliahKeFileCSV(Matakuliah *mk, int jumlah, const char *namaFile);
void simpanMahasiswaKeFileCSV(Mahasiswa *mhs, int jumlah, const char *namaFile);
void simpanKRSKeFileCSV(KRS *krs, int jumlah, const char *namaFile);
void bacaMatakuliahDariFileCSV(const char *namaFile);
void bacaMahasiswaDariFileCSV(const char *namaFile);
void bacaKRSDariFileCSV(const char *namaFile);
void bersihkanBufferInput();