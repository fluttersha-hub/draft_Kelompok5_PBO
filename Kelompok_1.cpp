#include <iostream>
#include <string>
using namespace std;

struct Tugas {
    string namaTugas;
    string mataKuliah;
    string deadline;
    int prioritas;
    string status;
    Tugas* next;
    Tugas* subTugas;
};

struct Akun {
    string username;
    string password;
    string namaLengkap;
};

struct NodeQueue {
    Tugas* dataTugas;
    NodeQueue* next;
};

int inputAngka(int min, int max) {
    int x;
    while (true) {
        cin >> x;
        if (!cin.fail() && x >= min && x <= max) {
            cin.ignore(1000, '\n');
            return x;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInput tidak valid! Masukkan angka yang benar: ";
    }
}

class ManajemenTugas {
protected:
    Tugas* head;
    Tugas* undoStack[10];
    int topUndo;
    NodeQueue* qFront;
    NodeQueue* qRear;

    string daftarMatkul[8] = {
        "Struktur Data", "OOP", "Statistika dan Probabilitas",
        "Metode Numerik", "Analisis Kompleksitas Algoritma", "Kewirausahaan",
        "Pendidikan Karakter dan Anti Korupsi", "Kewarganegaraan"
    };

public:
    ManajemenTugas() {
        head = NULL;
        topUndo = -1;
        qFront = NULL;
        qRear = NULL;
    }

    void bersihkanLayar() {
            system("cls");
    }

    void klikEnter() {
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
    }

    void hapusSubTugas(Tugas* n) {
        if (!n) return;
        if (n->subTugas) hapusSubTugas(n->subTugas);
        if (n->next) hapusSubTugas(n->next);
        delete n;
    }

    void resetData() {
        while (head != NULL) {
            Tugas* temp = head;
            head = head->next;
            if (temp->subTugas) hapusSubTugas(temp->subTugas);
            delete temp;
        }
        while (qFront) {
            NodeQueue* hapus = qFront;
            qFront = qFront->next;
            delete hapus;
        }
        qRear = NULL;

        for (int i = 0; 1 <= topUndo; i++) {
            delete undoStack[i];
        }
        topUndo = -1;
    }

    void tugasAwal(string nama, string mk, string dl, int prio) {
        Tugas* baru = new Tugas;
        baru->namaTugas = nama;
        baru->mataKuliah = mk;
        baru->deadline = dl;
        baru->prioritas = prio;
        baru->status = "Belum";
        baru->subTugas = NULL;
        baru->next = head;
        head = baru;
    }

    void inisialisasiTugas(string namaLengkap) {
        resetData();
        if (namaLengkap == "Humaira") {
            tugasAwal("Laporan Praktikum", "Struktur Data", "19052026", 1);
            tugasAwal("Laporan Proposal", "Kewirausahaan", "25052026", 2);
            tugasAwal("Project Akhir", "OOP", "27052026", 3);
        } else if (namaLengkap == "Amisha") {
            tugasAwal("Tugas DataSet", "Statistika dan Probabilitas", "21052026", 1);
            tugasAwal("Membuat Resume", "Kewarganegaraan", "22052026", 3);
        }
    }
};

class Login : public ManajemenTugas {
public:
    string login() {
        Akun daftarAkun[3] = {
            {"omar", "omarganteng", "Humaira"},
            {"amiw", "1119", "Amisha"},
            {"faqihganteng", "faqih07", "Fariid Faqih"}
        };
        string username, pass;
        while (true) {
            bersihkanLayar();
            cout << "========================================================" << endl;
            cout << "            SISTEM MANAJEMEN TUGAS MAHASISWA            " << endl;
            cout << "========================================================" << endl;
            cout << "Silakan Masuk terlebih dahulu.\n";
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> pass;
            for (int i = 0; i < 3; i++) {
                if (username == daftarAkun[i].username && pass == daftarAkun[i].password) {
                    inisialisasiTugas(daftarAkun[i].namaLengkap);
                    return daftarAkun[i].namaLengkap;
                }
            }
            cout << "\nAkses Ditolak! Coba lagi." << endl;
            cin.get(); 
            klikEnter();
        }
    }
};

class Dashboard : public Login {
public:
    void tampilkanDashboard(string nama) {
        int total = 0, selesai = 0;
        Tugas* temp = head;
        while (temp != NULL) {
            total++;
            if (temp->status == "Selesai") selesai++;
            temp = temp->next;
        }

        float persen = 0;
        if (total > 0) persen = (float)selesai / total * 100;

        cout << "==============================================================" << endl;
        cout << "               SISTEM MANAJEMEN TUGAS MAHASISWA               " << endl;
        cout << "==============================================================" << endl;
        cout << "| Halo, " << nama << "!" << endl;
        cout << "  Hari Ini: Selasa, 19/05/2026" << endl << endl;

        cout << "+--------------------- STATISTIK TUGAS ----------------------+" << endl;
        cout << "| Total Tugas       : " << total << "                                      |" << endl;
        cout << "| Tugas Selesai     : " << selesai << "                                      |" << endl;
        cout << "| Tugas Menunggu    : " << (total - selesai) << "                                      |" << endl;
        cout << "+------------------------------------------------------------+" << endl << endl;

        cout << "--------------------- DALAM PENGERJAAN -----------------------" << endl;
        if (qFront) {
            cout << "| >> SEKARANG: " << qFront->dataTugas->namaTugas << endl;
            if (qFront->next) cout << "| >> BERIKUTNYA: " << qFront->next->dataTugas->namaTugas << endl;
        } else {
            cout << "| >> Tidak ada tugas dalam antrian." << endl;
        }
        cout << "--------------------------------------------------------------" << endl << endl;

        cout << "------------------------ INFO TUGAS --------------------------" << endl;
        temp = head;
        string batasTanggal = "19052026";
        bool ada = false;

        while (temp) {
            if (temp->deadline <= batasTanggal && temp->status == "Belum") {
                cout << "| >> !!! Tugas '" << temp->namaTugas << "' melewati deadline !!!" << endl;
                ada = true;
            }
            temp = temp->next;
        }
        if (!ada) cout << "| >> Semua tugas aman dalam jadwal." << endl;
        cout << "--------------------------------------------------------------" << endl << endl;

        cout << "==============================================================" << endl;
        cout << "PROGRESS TUGAS: [";
        int lebarBar = 39;
        int progressBar = (persen / 100) * lebarBar;
        for (int i = 0; i < lebarBar; ++i) {
            if (i < progressBar) cout << "#";
            else cout << ".";
        }
        cout << "] " << (int)persen << "%" << endl;
        cout << "==============================================================" << endl << endl;
    }
};

class AddTugas : public Dashboard {
public:
    void tambahTugas() {
        bersihkanLayar();
        Tugas* baru = new Tugas;
        cout << "=============== TAMBAH TUGAS BARU ===============" << endl;
        cout << "\nNama Tugas         : "; getline(cin, baru->namaTugas);

        cout << "-------------------------------------------------" << endl;
        int pilih;
        while (true) {
            cout << "\nDaftar Mata Kuliah:" << endl;
            for (int i = 0; i < 8; i++) cout << i + 1 << ". " << daftarMatkul[i] << endl;
            cout << "\nPilih (1-8): "; pilih = inputAngka(1,8);
            if (pilih >= 1 && pilih <= 8) break;
        }

        cout << "-------------------------------------------------" << endl;
        baru->mataKuliah = daftarMatkul[pilih - 1];
        cout << "Deadline (DDMMYYYY): "; cin >> baru->deadline;
        cout << "\n1 = Sangat Penting | 2 = Penting | 3 = Tidak Mendesak" << endl;
        cout << "Prioritas            : "; baru->prioritas = inputAngka(1,3);
        baru->status = "Belum";
        baru->subTugas = NULL;
        baru->next = head;
        head = baru;
        cout << "-------------------------------------------------" << endl;
        cout << ">>> Tugas Berhasil Disimpan <<<" << endl;
        klikEnter();
    }
};

class SortingTugas : public AddTugas { 
public:
    void urutkanTugas() {
    if (!head || !head->next) return;

    bool swapped;
    do {
        swapped = false;
        Tugas** ptr = &head;

        while ((*ptr)->next) {
            Tugas* a = *ptr;
            Tugas* b = a->next;

            bool harusTukar = false;

            if (a->prioritas > b->prioritas) harusTukar = true;
            else if (a->prioritas == b->prioritas) {
                if (a->deadline > b->deadline) harusTukar = true;
            }

            if (harusTukar) {
                a->next = b->next;
                b->next = a;
                *ptr = b;
                swapped = true;
            }

            ptr = &((*ptr)->next);
        }
    } while (swapped);
}
};

class ViewTugas : public SortingTugas {
public:
    void tampilkanTugas() { // tampilkan tugas sekalian bajalankan sorting dan tandai tugas yang sudah selesai
        int tugas;
        do {
            bersihkanLayar();
            cout << "================== DAFTAR TUGAS SAAT INI ==================\n\n";
            cout << "No    Deadline\t\tPrioritas\tNama Tugas + [Status]" << endl;
            cout << "--------------------------------------------------------------" << endl;
            Tugas* temp = head;
            int jumlahTugas = 0;
            if (!temp) cout << "Daftar masih kosong." << endl;
            while (temp) {
                cout << ++jumlahTugas << ".    [" << temp->deadline << "]\t" << temp->prioritas << "\t\t"
                    << temp->namaTugas << " (" << temp->mataKuliah << ") [" << temp->status << "]" << endl << endl;
                temp = temp->next;
            }
            cout << "--------------------------------------------------------------" << endl;
            cout << "1. Urutkan Otomatis (Prioritas & Deadline)" << endl;
            cout << "2. Tandai Selesai" << endl;
            cout << "0. Kembali ke Dashboard" << endl;
            cout << "Pilih: "; tugas = inputAngka(0,2);

            cout << "-----------------------------------------------------------------------" << endl;
            if (tugas == 1) urutkanTugas();
            else if (tugas == 2 && head) {
                int nomor;
                cout << "Pilih nomor: "; 
                while (true) {
                    cin >> nomor;
                    if (!cin.fail() && nomor >= 1 && nomor <= jumlahTugas) {
                        cin.ignore(1000, '\n');
                        break;
                    }
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\nInput tidak valid! Masukkan angka yang benar: ";
                }
                Tugas* t = head;
                for (int j = 1; j < nomor && t; j++) t = t->next;
                if (t) t->status = "Selesai";
            }
        } while (tugas != 0);
    }
};

class TugasDikerjakan : public ViewTugas {
public:
    void menuTugasDikerjakan() {
        int pilih;
        do {
            bersihkanLayar();
            cout << "================== TUGAS YANG SEDANG DIKERJAKAN ==================" << endl << endl;

            if (!qFront) {
                cout << "[ Kosong ]" << endl;
            } else {
                NodeQueue* temp = qFront;
                int i = 1;
                while (temp) {
                    cout << (i == 1 ? ">> SEKARANG: " : "   Antrian " + to_string(i) + ": ");
                    cout << temp->dataTugas->namaTugas << " (" << temp->dataTugas->mataKuliah << ")\n";
                    temp = temp->next;
                    i++;
                }
            }

            cout << "\n-------------------------------------------------------------" << endl;
            cout << "| 1. Tambah Tugas                                            |" << endl;
            cout << "| 2. Selesaikan Tugas Teratas                                |" << endl;
            cout << "| 0. Kembali ke Dashboard                                    |" << endl;
            cout << "-------------------------------------------------------------" << endl;
            cout << "Pilih: "; pilih = inputAngka(0,2);

            if (pilih == 1) {
                if (!head) { cout << "Daftar tugas kosong!"; klikEnter(); continue; }

                Tugas* temp = head;
                int jumlahTugas = 0;
                cout << "\n----------------------- Pilih Tugas --------------------------\n";
                while (temp) {
                    cout << ++jumlahTugas << ". " << temp->namaTugas << " [" << temp->status << "]\n";
                    temp = temp->next;
                }
                
                int nomor;
                cout << "Pilih nomor: "; 
                while (true) {
                    cin >> nomor;
                    if (!cin.fail() && nomor >= 1 && nomor <= jumlahTugas) {
                        cin.ignore(1000, '\n');
                        break;
                    }
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\nInput tidak valid! Masukkan angka yang benar: ";
                }

                Tugas* dipilih = head;
                for (int j = 1; j < nomor && dipilih; j++) dipilih = dipilih->next;

                bool sudahAda = false;
                NodeQueue* cek = qFront;
                while (cek) {
                    if (cek->dataTugas == dipilih) {
                        sudahAda = true;
                        break;
                    }
                    cek = cek->next;
                }

                if (sudahAda) {
                    cout << "-------------------------------------------------------------" << endl;
                    cout << ">> Tugas sudah ada di antrian!" << endl;
                    klikEnter();
                    continue;
                }



                if (dipilih) {
                    NodeQueue* baru = new NodeQueue;
                    baru->dataTugas = dipilih;
                    baru->next = NULL;
                    if (qRear == NULL) qFront = qRear = baru;
                    else { qRear->next = baru; qRear = baru; }
                    cout << ">> Berhasil masuk antrian!";
                }
            } else if (pilih == 2) {
                if (!qFront) { cout << "Antrian sudah kosong!"; }
                else {
                    NodeQueue* hapus = qFront;
                    hapus->dataTugas->status = "Selesai";
                    qFront = qFront->next;
                    if (qFront == NULL) qRear = NULL;
                    cout << "\n>> Tugas '" << hapus->dataTugas->namaTugas << "' Selesai!" << endl;
                    delete hapus;
                }
                klikEnter();
            }
        } while (pilih != 0);
    }
};

class Hierarki : public TugasDikerjakan {
public:
    void tampilkanHierarki(Tugas* n, int level) {
    while (n) {
        for (int i = 0; i < level; i++) 
            cout << "|   ";

        if (level > 0) 
            cout << "|-- ";

        cout << n->namaTugas << " [" << n->status << "]" << endl;

        if (n->subTugas) {
            tampilkanHierarki(n->subTugas, level + 1);
        }
        n = n->next;
        }
    }

    void tambahSubTugas() {
        if (!head) {
            cout << "--------------------------------------------------------" << endl;
            cout << "Belum ada tugas. Tambahkan tugas dulu!" << endl;
            klikEnter();
            return;
        }

        bersihkanLayar();
        cout << "====================== PILIH TUGAS =====================" << endl;
        Tugas* temp = head;
        int jumlahTugas = 0;
        while (temp) {
            cout << ++jumlahTugas << ". " << temp->namaTugas << endl;
            temp = temp->next;;
        }
        cout << "--------------------------------------------------------" << endl;

        int pilih;
        cout << "Pilih nomor: "; 
        while (true) {
            cin >> pilih;
            if (!cin.fail() && pilih >= 1 && pilih <= jumlahTugas) {
                cin.ignore(1000, '\n');
                break;
            }
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInput tidak valid! Masukkan angka yang benar: ";
        }

        Tugas* parent = head;
        for (int j = 1; j < pilih && parent; j++) parent = parent->next;

        if (!parent) {
        cout << "\nNomor tidak valid!" << endl;
        klikEnter();
        return;
        }

        Tugas* anakBaru = new Tugas;
        cout << "\n--------- Tambah Sub-Tugas untuk " << parent->namaTugas << " ---------" << endl;
        cout << "Masukkan Nama: "; getline(cin, anakBaru->namaTugas);
        anakBaru->mataKuliah = parent->mataKuliah;
        anakBaru->deadline = parent->deadline;
        anakBaru->prioritas = parent->prioritas;
        anakBaru->status = "Belum";
        anakBaru->subTugas = NULL;

        anakBaru->next = parent->subTugas;
        parent->subTugas = anakBaru;

        cout << "--------------------------------------------------------" << endl;
        cout << ">> Sub-Tugas Berhasil Ditambahkan!" << endl;
        klikEnter();
    }

    void menuHierarki() {
        bersihkanLayar();
        cout << "================= POHON RENCANA TUGAS =================" << endl;
        if (!head) cout << "Data Kosong." << endl;
        else tampilkanHierarki(head, 0);

        cout << "--------------------------------------------------------" << endl;
        cout << "1. Buat Sub-Tugas Baru" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilih: "; int pilih = inputAngka(0,1);
        if (pilih == 1) tambahSubTugas();
    }
};

class SearchTugas : public Hierarki {
public:
    void cariTugas() {
        bersihkanLayar();
        if (!head) {
            cout << "Daftar tugas kosong." << endl;
            klikEnter();
            return;
        }

        int pilih;
        cout << "========== CARI TUGAS BERDASARKAN MATA KULIAH ==========" << endl;
        for (int i = 0; i < 8; i++) cout << i + 1 << ". " << daftarMatkul[i] << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Pilih Matkul yang dicari (1-8): "; pilih = inputAngka(1,8);
        cout << "--------------------------------------------------------" << endl;

        string kunci = daftarMatkul[pilih - 1];
        Tugas* temp = head;
        bool ditemukan = false;
        int no = 1;

        bersihkanLayar();
        cout << "HASIL PENCARIAN MATA KULIAH: " << kunci << endl;
        cout << "========================================================" << endl;

        while (temp != NULL) {
            if (temp->mataKuliah == kunci) {
                cout << no++ << ". Nama Tugas : " << temp->namaTugas << endl;
                cout << "   Deadline   : " << temp->deadline << endl;
                cout << "   Prioritas  : " << temp->prioritas << endl;
                cout << "   Status     : " << temp->status << endl;
                cout << "--------------------------------------------------------" << endl;
                ditemukan = true;
            }
            temp = temp->next;
        }

        if (!ditemukan) {
            cout << "Tidak ada tugas untuk mata kuliah ini." << endl;
            cout << "--------------------------------------------------------" << endl;
        }

        klikEnter();
    }
};

class DeleteTugas : public SearchTugas{
public:
    void hapusTugas() {
        while (true) {
            bersihkanLayar();
            if (!head) { 
                cout << "====================== HAPUS TUGAS =====================" << endl;
                cout << "Daftar kosong." << endl; klikEnter(); return; 
            }

            cout << "====================== HAPUS TUGAS =====================" << endl;
            Tugas* temp = head;
            int jumlahTugas = 0;
            while (temp) {
                cout << ++jumlahTugas << ". " << temp->namaTugas << " (" << temp->mataKuliah << ")" << endl;
                temp = temp->next;
            }
            cout << "0. Batal" << endl;

            cout << "--------------------------------------------------------" << endl;
            int pilHapus;
            cout << "Masukkan Nomor: ";
            while (true) {
                cin >> pilHapus;
                if (!cin.fail() && pilHapus >= 0 && pilHapus <= jumlahTugas) {
                    cin.ignore(1000, '\n');
                    break;
                }
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInput tidak valid! Masukkan angka yang benar: ";
            }
            if (pilHapus == 0) return;

            Tugas* curr = head, *prev = NULL;
            for (int i = 1; i < pilHapus; i++) {
                prev = curr;
                curr = curr->next;
            }

            if (topUndo < 9) {
                Tugas* copyTugas = new Tugas(*curr);
                copyTugas->next = NULL;
                undoStack[++topUndo] = copyTugas;
            }

            if (!prev) head = curr->next;
            else prev->next = curr->next;

            cout << "--------------------------------------------------------" << endl;
            cout << ">> Tugas '" << curr->namaTugas << "' & Sub-tugasnya Berhasil Dihapus!" << endl;

            if (curr->subTugas) hapusSubTugas(curr->subTugas);
            delete curr;

            klikEnter();
            break;
        }
    }
};

class RestoreTugas : public DeleteTugas {
public:
    void pulihkanTugas() {
        if (topUndo == -1) {
            bersihkanLayar();
            cout << "==================== PULIHKAN TUGAS ====================" << endl;
            cout << "Daftar kosong." << endl;
            klikEnter();
            return;
        }

        while (true) {
            bersihkanLayar();
            cout << "==================== PULIHKAN TUGAS ====================" << endl;
            cout << "Pilih tugas yang ingin dipulihkan:" << endl;
            int jumlahUndo = topUndo + 1;
            for (int i = 0; i <= topUndo; i++) {
                cout << i + 1 << ". " << undoStack[i]->namaTugas << " (" << undoStack[i]->mataKuliah << ")" << endl;
            }
            cout << "0. Kembali" << endl;

            cout << "--------------------------------------------------------" << endl;
            int pilih;
            cout << "Pilih Nomor: ";
            while (true) {
                cin >> pilih;
                if (!cin.fail() && pilih >= 0 && pilih <= jumlahUndo) {
                    cin.ignore(1000, '\n');
                    break;
                }
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nInput tidak valid! Masukkan angka yang benar: ";
            }
            if (pilih == 0) return;

            int idx = pilih - 1;
            Tugas* kembali = undoStack[idx];

            for (int i = idx; i < topUndo; i++) {
                undoStack[i] = undoStack[i + 1];
            }
            undoStack[topUndo] = NULL;
            topUndo--;

            kembali->next = head;
            head = kembali;
            cout << "--------------------------------------------------------" << endl;
            cout << ">> Tugas '" << kembali->namaTugas << "' telah dipulihkan!" << endl;
            klikEnter();
            break;
        }
    }
};

int main() {
    RestoreTugas sistem; 

    while (true) {
        string userNama = sistem.login();
        int pilihan;
        do {
            sistem.bersihkanLayar();
            sistem.tampilkanDashboard(userNama);
            cout << "--------------------------------------------------------------" << endl;
            cout << "                         MENU UTAMA                           " << endl;
            cout << "--------------------------------------------------------------" << endl;
            cout << "| 1. Tambah Tugas                                            |" << endl;
            cout << "| 2. Tampilkan Semua Tugas                                   |" << endl;
            cout << "| 3. Tugas Yang Sedang Dikerjakan                            |" << endl;
            cout << "| 4. Manajemen Tugas Besar                                   |" << endl;
            cout << "| 5. Cari Tugas                                              |" << endl;
            cout << "| 6. Hapus Tugas                                             |" << endl;
            cout << "| 7. Pulihkan Tugas                                          |" << endl;
            cout << "| 8. Keluar Akun                                             |" << endl;
            cout << "| 0. Tutup Program                                           |" << endl;
            cout << "--------------------------------------------------------------" << endl;
            cout << "Pilih Menu: "; pilihan = inputAngka(0,8);

            switch (pilihan) {
                case 1: sistem.tambahTugas();    break;
                case 2: sistem.tampilkanTugas(); break;
                case 3: sistem.menuTugasDikerjakan(); break;
                case 4: sistem.menuHierarki();   break;
                case 5: sistem.cariTugas();      break;
                case 6: sistem.hapusTugas();     break;
                case 7: sistem.pulihkanTugas();  break;
                case 0: 
                cout << "======================================================" << endl;
                cout << "   Terima kasih sudah menggunakan Program Ini ^^      " << endl;
                cout << "======================================================" << endl;
                return 0;
            }
        } while (pilihan != 8);

        sistem.resetData();
    }
    return 0;
}