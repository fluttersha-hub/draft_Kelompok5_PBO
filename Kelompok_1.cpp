#include <iostream>
#include <string>
using namespace std;

struct Tugas {
    string namaTugas;
    string mataKuliah;
    string deadline;
    int prioritas;
    string status;
    Tugas* next;       // Pointer ke tugas selanjutnya (Linked List)
    Tugas* subTugas;   // Pointer ke sub-tugas (Tree / Hierarki)
};

// Struct untuk Antrian tugas yang dikerjakan
struct NodeQueue {
    Tugas* dataTugas;
    NodeQueue* next;
};

struct Akun {
    string username;
    string password;
    string namaLengkap;

    Tugas* head = NULL;
    Tugas* undoStack[10];
    int topUndo = -1;
    NodeQueue* qFront = NULL;
    NodeQueue* qRear = NULL;
    bool sudahInisialisasi = false;
};

class SistemDasar {
public:
    void bersihkanLayar() {
        system("cls"); 
    }

    void klikEnter() {
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
    }

    // Fungsi untuk memastikan inputan berupa angka yang valid
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
};

class SistemAkun {
protected:
    Akun daftarAkun[50];
    int jumlahAkun;
    int idUserAktif;
    SistemDasar util;

public:
    SistemAkun() {
        idUserAktif = -1;
        // Data akun bawaan
        daftarAkun[0] = {"omar", "omarganteng", "Humaira"};
        daftarAkun[1] = {"amiw", "1119", "Amisha"};
        daftarAkun[2] = {"faqihganteng", "faqih07", "Fariid Faqih"};
        jumlahAkun = 3;
    }

    int menuAwal() {
        int pilihan;
        while (true) {
            util.bersihkanLayar();
            cout << "========================================================\n";
            cout << "            SISTEM MANAJEMEN TUGAS MAHASISWA            \n";
            cout << "========================================================\n";
            cout << "1. Registrasi Akun\n";
            cout << "2. Masuk\n";
            cout << "0. Tutup Program\n";
            cout << "Pilih: ";
            pilihan = util.inputAngka(0, 2);

            string user, pass;
            if (pilihan == 1) {
                util.bersihkanLayar();
                cout << "========================================================\n";
                cout << "                   REGISTRASI AKUN                      \n";
                cout << "========================================================\n";
                cout << "Username     : "; cin >> daftarAkun[jumlahAkun].username;
                cout << "Password     : "; cin >> daftarAkun[jumlahAkun].password;
                cin.ignore();
                cout << "Nama Lengkap : "; getline(cin, daftarAkun[jumlahAkun].namaLengkap);
                
                jumlahAkun++;
                cout << "\nRegistrasi Berhasil! Silakan Login menggunakan akun baru Anda.\n";
                util.klikEnter();

            } else if (pilihan == 2) {
                util.bersihkanLayar();
                cout << "========================================================\n";
                cout << "                   MASUK KE AKUN ANDA                   \n";
                cout << "========================================================\n";
                cout << "Username   : "; cin >> user;
                cout << "Password   : "; cin >> pass;
                cin.ignore(); 

                bool berhasil = false;
                for (int i = 0; i < jumlahAkun; i++) {
                    if (user == daftarAkun[i].username && pass == daftarAkun[i].password) {
                        idUserAktif = i;
                        return i;
                    }
                }
                cout << "\nAkses Ditolak! Username atau Password salah." << endl;
                util.klikEnter();

            } else {
                cout << "======================================================" << endl;
                cout << "   Terima kasih sudah menggunakan Program Ini ^^      " << endl;
                cout << "======================================================" << endl;
                return -1;
            }
        }
    }
};

class ManajemenTugas : public SistemDasar, public SistemAkun {
protected:
    Tugas*& getHead() { 
        return daftarAkun[idUserAktif].head; 
    }
    NodeQueue*& getQFront() { 
        return daftarAkun[idUserAktif].qFront; 
    }
    NodeQueue*& getQRear() { 
        return daftarAkun[idUserAktif].qRear; 
    }

    string daftarMatkul[8] = {
        "Struktur Data", "OOP", "Statistika dan Probabilitas",
        "Metode Numerik", "Analisis Kompleksitas Algoritma", "Kewirausahaan",
        "Pendidikan Karakter dan Anti Korupsi", "Kewarganegaraan"
    };

public:
    ManajemenTugas() {
        
    }

    void hapusSubTugas(Tugas* n) {
        if (!n) return;
        if (n->subTugas) hapusSubTugas(n->subTugas);
        if (n->next) hapusSubTugas(n->next);
        delete n;
    }

    void inisialisasiTugas(string nama, string mk, string dl, int prio) {
        Tugas* baru = new Tugas;
        baru->namaTugas = nama;
        baru->mataKuliah = mk;
        baru->deadline = dl;
        baru->prioritas = prio;
        baru->status = "Belum";
        baru->subTugas = NULL;
        baru->next = getHead();
        getHead() = baru;
    }

    void tugasAwal() {
        if (idUserAktif == -1) return;
        if (daftarAkun[idUserAktif].sudahInisialisasi) return;

        string namaLengkap = daftarAkun[idUserAktif].namaLengkap;

        if (namaLengkap == "Humaira") {
            inisialisasiTugas("Laporan Praktikum", "Struktur Data", "20260519", 1);
            inisialisasiTugas("Laporan Proposal", "Kewirausahaan", "20260525", 2);
            inisialisasiTugas("Project Akhir", "OOP", "20260527", 3);
        } else if (namaLengkap == "Amisha") {
            inisialisasiTugas("Tugas DataSet", "Statistika dan Probabilitas", "20260521", 1);
            inisialisasiTugas("Membuat Resume", "Kewarganegaraan", "20260522", 3);
        }

        daftarAkun[idUserAktif].sudahInisialisasi = true;
    }
};

class FiturSistem : public ManajemenTugas {
public:
    void tampilkanDashboard() {
        Tugas*& head = getHead(); 
        NodeQueue*& qFront = getQFront();
            
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
        cout << "| Halo, " << daftarAkun[idUserAktif].namaLengkap << "!" << endl;
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
        string batasTanggal = "20260519";
        bool ada = false;

        while (temp) {
            if (temp->deadline < batasTanggal && temp->status == "Belum") {
                cout << "| >> Tugas '" << temp->namaTugas << "' melewati deadline !!!" << endl;
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

    void tambahTugas() {
        Tugas*& head = getHead();
        bersihkanLayar();
        
        Tugas* baru = new Tugas;
        cout << "=============== TAMBAH TUGAS BARU ===============" << endl;
        cout << "\nNama Tugas         : "; 
        getline(cin, baru->namaTugas);

        cout << "-------------------------------------------------" << endl;
        int pilih;
        while (true) {
            cout << "\nDaftar Mata Kuliah:" << endl;
            for (int i = 0; i < 8; i++) cout << i + 1 << ". " << daftarMatkul[i] << endl;
            cout << "\nPilih (1-8): "; pilih = inputAngka(1, 8);
            if (pilih >= 1 && pilih <= 8) break;
        }

        cout << "-------------------------------------------------" << endl;
        baru->mataKuliah = daftarMatkul[pilih - 1];
        cout << "Deadline (YYYYMMDD): "; cin >> baru->deadline;
        cout << "\n1 = Sangat Penting | 2 = Penting | 3 = Tidak Mendesak" << endl;
        cout << "Prioritas            : "; baru->prioritas = inputAngka(1, 3);
        
        baru->status = "Belum";
        baru->subTugas = NULL;
        baru->next = head; // Menyambungkan di awal Linked List
        head = baru;

        cout << "-------------------------------------------------" << endl;
        cout << ">>> Tugas Berhasil Disimpan <<<" << endl;
        klikEnter();
    }

    void urutkanTugas() {
        Tugas*& head = getHead();

        if (!head || !head->next) return;

        bool ditukar;
        do {
            ditukar = false;
            Tugas* curr = head;

            while (curr->next != NULL) {
                bool harusTukar = false;
                
                if (curr->prioritas > curr->next->prioritas) {
                    harusTukar = true;
                } else if (curr->prioritas == curr->next->prioritas) {
                    if (curr->deadline > curr->next->deadline) {
                        harusTukar = true;
                    }
                }

                if (harusTukar) {
                    // Isinya ditukar, list tetap menyambung dengan baik
                    swap(curr->namaTugas, curr->next->namaTugas);
                    swap(curr->mataKuliah, curr->next->mataKuliah);
                    swap(curr->deadline, curr->next->deadline);
                    swap(curr->prioritas, curr->next->prioritas);
                    swap(curr->status, curr->next->status);
                    swap(curr->subTugas, curr->next->subTugas);
                    
                    ditukar = true;
                }
                curr = curr->next;
            }
        } while (ditukar);
    }

    void tampilkanTugas() {
        int tugasPilihan;
        Tugas*& head = getHead();

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
            cout << "Pilih: "; tugasPilihan = inputAngka(0, 2);

            cout << "-----------------------------------------------------------------------" << endl;
            
            if (tugasPilihan == 1) {
                urutkanTugas();
            } else if (tugasPilihan == 2 && head) {
                int nomor;
                cout << "Pilih nomor: "; 
                nomor = inputAngka(1, jumlahTugas);
                
                Tugas* t = head;
                for (int j = 1; j < nomor && t; j++) {
                    t = t->next;
                }
                if (t) t->status = "Selesai";
            }
        } while (tugasPilihan != 0);
    }

    void menuTugasDikerjakan() {
        int pilih;
        Tugas*& head = getHead();
        NodeQueue*& qFront = getQFront(); 
        NodeQueue*& qRear = getQRear();

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
            cout << "Pilih: "; pilih = inputAngka(0, 2);

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
                nomor = inputAngka(1, jumlahTugas);

                Tugas* dipilih = head;
                for (int j = 1; j < nomor && dipilih; j++) dipilih = dipilih->next;

                // Cek apakah sudah ada di queue
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

                if (dipilih->status == "Selesai") {
                    cout << "\n>> Tugas sudah selesai, tidak perlu dikerjakan lagi!" << endl;
                    klikEnter(); 
                    continue;
                }

                // Masukkan ke Queue
                if (dipilih) {
                    NodeQueue* baru = new NodeQueue;
                    baru->dataTugas = dipilih;
                    baru->next = NULL;
                    if (qRear == NULL) {
                        qFront = qRear = baru;
                    } else { 
                        qRear->next = baru; 
                        qRear = baru; 
                    }
                    cout << ">> Berhasil masuk antrian!";
                }
            } else if (pilih == 2) {
                if (!qFront) { 
                    cout << "Antrian sudah kosong!"; 
                } else {
                    NodeQueue* hapus = qFront;
                    hapus->dataTugas->status = "Selesai";
                    
                    qFront = qFront->next;
                    if (qFront == NULL) qRear = NULL; // Queue habis
                    
                    cout << "\n>> Tugas '" << hapus->dataTugas->namaTugas << "' Selesai!" << endl;
                    delete hapus;
                }
                klikEnter();
            }
        } while (pilih != 0);
    }

    void tampilkanHierarki(Tugas* n, int level) {
        while (n) {
            for (int i = 0; i < level; i++) cout << "|   ";
            if (level > 0) cout << "|-- ";
            cout << n->namaTugas << " [" << n->status << "]" << endl;

            if (n->subTugas) {
                tampilkanHierarki(n->subTugas, level + 1);
            }
            n = n->next;
        }
    }

    void menuHierarki() {
        Tugas*& head = getHead();
        bersihkanLayar();
        cout << "================= POHON RENCANA TUGAS =================" << endl;
        if (!head) cout << "Data Kosong." << endl;
        else tampilkanHierarki(head, 0);

        cout << "--------------------------------------------------------" << endl;
        cout << "1. Buat Sub-Tugas Baru" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilih: "; 
        int pilih = inputAngka(0, 1);
        
        if (pilih == 1) {
            if (!head) {
                cout << "--------------------------------------------------------" << endl;
                cout << "Belum ada tugas utama. Tambahkan tugas dulu!" << endl;
                klikEnter();
                return;
            }

            bersihkanLayar();
            cout << "====================== PILIH TUGAS =====================" << endl;
            Tugas* temp = head;
            int jumlahTugas = 0;
            while (temp) {
                cout << ++jumlahTugas << ". " << temp->namaTugas << endl;
                temp = temp->next;
            }
            cout << "--------------------------------------------------------" << endl;

            int pilihanTugas;
            cout << "Pilih nomor: "; 
            pilihanTugas = inputAngka(1, jumlahTugas);

            Tugas* parent = head;
            for (int j = 1; j < pilihanTugas && parent; j++) parent = parent->next;

            if (parent) {
                Tugas* anakBaru = new Tugas;
                cout << "\n--------- Tambah Sub-Tugas untuk " << parent->namaTugas << " ---------" << endl;
                cout << "Masukkan Nama: "; 
                getline(cin, anakBaru->namaTugas);
                
                // Menurunkan sifat/parent
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
        }
    }

    void cariTugas() {
        Tugas*& head = getHead();
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
        cout << "Pilih Matkul yang dicari (1-8): "; pilih = inputAngka(1, 8);
        cout << "--------------------------------------------------------" << endl;

        string kunci = daftarMatkul[pilih - 1];
        Tugas* temp = head;
        bool ditemukan = false;
        int no = 1;

        bersihkanLayar();
        cout << "HASIL PENCARIAN MATA KULIAH: " << kunci << endl;
        cout << "========================================================" << endl;

        // Pencarian linear sederhana
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

    void hapusTugas() {
        Tugas*& head = getHead();                           
        int& topUndo = daftarAkun[idUserAktif].topUndo;     
        auto& undoStack = daftarAkun[idUserAktif].undoStack;

        while (true) {
            bersihkanLayar();
            if (!head) { 
                cout << "====================== HAPUS TUGAS =====================" << endl;
                cout << "Daftar kosong." << endl; 
                klikEnter(); 
                return; 
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
            pilHapus = inputAngka(0, jumlahTugas);
            if (pilHapus == 0) return;

            // Mencari node yang akan dihapus
            Tugas* curr = head;
            Tugas* prev = NULL;
            for (int i = 1; i < pilHapus; i++) {
                prev = curr;
                curr = curr->next;
            }

            // Simpan copy dari node ke dalam Undo Stack (maks 10)
            if (topUndo < 9) {
                Tugas* copyTugas = new Tugas(*curr); 
                copyTugas->next = NULL; 
                copyTugas->subTugas = NULL;
                undoStack[++topUndo] = copyTugas;
            }

            // Lepaskan node dari LinkedList
            if (prev == NULL) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }

            cout << "--------------------------------------------------------" << endl;
            cout << ">> Tugas '" << curr->namaTugas << "' & Sub-tugasnya Berhasil Dihapus!" << endl;

            // Memastikan data di stack tidak memiliki subTugas yang bermasalah memori
            undoStack[topUndo]->subTugas = NULL; 

            // Hapus memori yang sebenarnya
            hapusDariAntrian(curr);
            if (curr->subTugas) hapusSubTugas(curr->subTugas);
            delete curr;

            klikEnter();
            break;
        }
    }

    void hapusDariAntrian(Tugas* target) {
        Tugas*& head = getHead();
        NodeQueue*& qFront = getQFront(); 
        NodeQueue*& qRear = getQRear();
        NodeQueue* prev = NULL;
        NodeQueue* curr = qFront;

        while (curr) {
            if (curr->dataTugas == target) {
                if (prev == NULL) {
                    qFront = curr->next;        
                } else {
                    prev->next = curr->next;    
                }
                if (curr->next == NULL) {
                    qRear = prev;               
                }
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void pulihkanTugas() {
        Tugas*& head = getHead();                           
        int& topUndo = daftarAkun[idUserAktif].topUndo;     
        auto& undoStack = daftarAkun[idUserAktif].undoStack;

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
            pilih = inputAngka(0, jumlahUndo);
            if (pilih == 0) return;

            int idx = pilih - 1;
            Tugas* kembali = undoStack[idx];

            // Geser sisa elemen stack
            for (int i = idx; i < topUndo; i++) {
                undoStack[i] = undoStack[i + 1];
            }
            undoStack[topUndo] = NULL;
            topUndo--;

            // Masukkan kembali ke List
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
    FiturSistem sistem;

    while (true) {
        int userId = sistem.menuAwal(); 
        if (userId == -1) break;

        sistem.tugasAwal();

        int pilihan;
        do {
            sistem.bersihkanLayar();
            sistem.tampilkanDashboard();
            
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
            cout << "Pilih Menu: "; 
            pilihan = sistem.inputAngka(0, 8);

            switch (pilihan) {
                case 1: sistem.tambahTugas();    break;
                case 2: sistem.tampilkanTugas(); break;
                case 3: sistem.menuTugasDikerjakan(); break;
                case 4: sistem.menuHierarki();   break;
                case 5: sistem.cariTugas();      break;
                case 6: sistem.hapusTugas();     break;
                case 7: sistem.pulihkanTugas();  break;
                case 8: 
                    break; 
                case 0: 
                    cout << "======================================================" << endl;
                    cout << "   Terima kasih sudah menggunakan Program Ini ^^      " << endl;
                    cout << "======================================================" << endl;
                    return 0;
            }
        } while (pilihan != 8);
    }
    return 0;
}