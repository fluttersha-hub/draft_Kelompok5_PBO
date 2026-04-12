#include <iostream>
using namespace std;

struct Tugas {
    int nomorTugas;
    string namaTugas;
    string mataKuliah;
    string deadline;
    string status;
};

class ManajemenTugas {
public:
    string daftarMatkul[4] = {"Struktur Data", "OOP", 
                                "Metode Numerik", "Statistika"};
    Tugas daftarTugas[20];
    int jumlahTugas = 0;

    void tampilkanMatkul() {
        cout << "== Daftar Mata Kuliah ==" << endl;
        for (int i = 0; i < 4; i++) {
            cout << i+1 << ". " << daftarMatkul[i] << endl;
        }
    }

    void tambahTugas() {
        Tugas tugas;

        if (jumlahTugas == 20) {
            cout << "Tugas sudah penuh !" << endl;
            cout << "----------------------------\n";

            return;
        }

        cout << "Masukkan Nama Tugas: ";
        cin.ignore();
        getline(cin, tugas.namaTugas);

        cout << endl;
        tampilkanMatkul();
        int pilihMK; 
        cout << "\nPilih Mata Kuliah: ";
        cin >> pilihMK;

        if (pilihMK < 1 || pilihMK > 4) {
            cout << "\nPilihan tidak valid !" << endl;
            cout << "----------------------------\n";
            return;
        }

        tugas.mataKuliah = daftarMatkul[pilihMK - 1];

        cout << "\nDeadline (DD/MM/YYYY): ";
        cin >> tugas.deadline;

        tugas.nomorTugas = jumlahTugas + 1;

        tugas.status = "Belum"; // otomatis terisi "Belum"

        daftarTugas[jumlahTugas] = tugas;
        jumlahTugas++;
        cout << "\n-- Tugas berhasil ditambahkan ! --" << endl;
    }

    void hapusTugas() {
        if (jumlahTugas == 0) {
            cout << "Belum ada tugas !" << endl;
            cout << "----------------------------\n";
            return;
        }

        tampilkanTugas();
        int inputNomor;
        cout << "\nMasukkan nomor tugas yang ingin dihapus: ";
        cin >> inputNomor;

        int indeks = -1;
        for (int i = 0; i < jumlahTugas; i++) {
            if (daftarTugas[i].nomorTugas == inputNomor) {
                indeks = i;
                break;
            }
        }

        if (indeks == -1) {
            cout << "\nNomor tugas tidak ditemukan !" << endl;
            cout << "----------------------------\n";
            return;
        }

        for (int i = indeks; i < jumlahTugas - 1; i++) {
            daftarTugas[i] = daftarTugas[i + 1];
            daftarTugas[i].nomorTugas = i + 1; // Update nomor tugas
        }
        jumlahTugas--;
        cout << "\n-- Tugas berhasil dihapus ! --" << endl;
    }
    
    void tampilkanTugas() {
        if (jumlahTugas == 0) {
            cout << "Belum ada tugas !" << endl;
            cout << "----------------------------\n";
            return;
        }

        cout << "==== Daftar Tugas ====" << endl;
        for (int i = 0; i < jumlahTugas; i++) {
            cout << daftarTugas[i].nomorTugas << ". "; // menampilkan nomor tugas, kayak "1. Nama   : ..."
            cout << "Nama     : " << daftarTugas[i].namaTugas << endl;
            cout << "   Matkul   : " << daftarTugas[i].mataKuliah << endl;
            cout << "   Deadline : " << daftarTugas[i].deadline << endl;
            cout << "   Status   : " << daftarTugas[i].status << endl;
            cout << "----------------------------" << endl;
        }
    }

    void updateTugas() {
    if (jumlahTugas == 0) {
        cout << "Belum ada tugas !" << endl;
        cout << "----------------------------\n";
        return;
    }

    tampilkanTugas();
    int inputNomor;
    cout << "Masukkan nomor tugas yang ingin diupdate: ";
    cin >> inputNomor;

    int indeks = -1;
    for (int i = 0; i < jumlahTugas; i++) {
        if (daftarTugas[i].nomorTugas == inputNomor) {
            indeks = i;
            break;
        }
    }

    if (indeks == -1) {
        cout << "\nNomor tugas tidak ditemukan !" << endl;
        cout << "----------------------------\n";
        return;
    }

    int pilihStatus;
    cout << "\n== Update Status ==" << endl;
    cout << "1. Belum" << endl;
    cout << "2. Selesai" << endl;
    cout << "Pilih Status: ";
    cin >> pilihStatus;

    if (pilihStatus == 1) {
        daftarTugas[indeks].status = "Belum";

    } else if (pilihStatus == 2) {
        daftarTugas[indeks].status = "Selesai";
        
    } else {
        cout << "\nPilihan tidak valid !" << endl;
        cout << "----------------------------\n";

        return;
    }

    cout << "\n-- Status tugas berhasil diupdate ! --" << endl;
    }

    void filterTugas() {
    if (jumlahTugas == 0) {
            cout << "Belum ada tugas !" << endl;
            cout << "----------------------------\n";
            return;
        }

        int pilihFilter;
        cout << "=== Filter Tugas ===" << endl;
        cout << "1. Status = Belum" << endl;
        cout << "2. Status = Selesai" << endl;
        cout << "Pilih: ";
        cin >> pilihFilter;
        cout << "----------------------------";

        string statusFilter;
        if (pilihFilter == 1) {
            statusFilter = "Belum";
        } else if (pilihFilter == 2) {
            statusFilter = "Selesai";
        } else {
            cout << "\nPilihan tidak valid !" << endl;
            cout << "----------------------------\n";
            return;
        }

        bool adaTugas = false;
        cout << "\n-- Status = " << statusFilter << " --\n";
        for (int i = 0; i < jumlahTugas; i++) { 
            if (daftarTugas[i].status == statusFilter) {
                cout << daftarTugas[i].nomorTugas << ". "; // menampilkan nomor tugas, kayak "1. Nama   : ..."
                cout << "Nama     : " << daftarTugas[i].namaTugas << endl;
                cout << "   Matkul   : " << daftarTugas[i].mataKuliah << endl;
                cout << "   Deadline : " << daftarTugas[i].deadline << endl;
                cout << "   Status   : " << daftarTugas[i].status << endl;
                cout << "----------------------------" << endl;
                adaTugas = true;
            }
        }

        if (!adaTugas) {
            cout << "\nTidak ada tugas dengan status " << statusFilter << "!" << endl;
        }
    }
};

int main() {
    ManajemenTugas sistem;
    int pilihan;

    do {
        cout << "\n== Sistem Manajemen Tugas Mahasiswa ==" << endl;
        cout << "1. Tambah Tugas" << endl;
        cout << "2. Hapus Tugas" << endl;
        cout << "3. Update Status Tugas" << endl;
        cout << "4. Tampilkan Semua Tugas" << endl;
        cout << "5. Filter Tugas" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "----------------------------\n";
            sistem.tambahTugas();

        } else if (pilihan == 2) {
            cout << "----------------------------\n";
            sistem.hapusTugas();

        } else if (pilihan == 3) {
            cout << "----------------------------\n";
            sistem.updateTugas();

        } else if (pilihan == 4) {
            cout << "----------------------------\n";
            sistem.tampilkanTugas();

        } else if (pilihan == 5) {
            cout << "----------------------------\n";
            sistem.filterTugas();

        } else if (pilihan == 0) {
            cout << "----------------------------\n";
            cout << "Terima kasih telah menggunakan program kami !" << endl;

        } else {
            cout << "----------------------------\n";
            cout << "Pilihan tidak valid !" << endl;
        }

    } while (pilihan != 0);

    return 0;
}