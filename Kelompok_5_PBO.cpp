#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

string toLower(string str) {
    string lowerStr = str;
    for (int i = 0; i < lowerStr.length(); i++) {
        if (lowerStr[i] >= 'A' && lowerStr[i] <= 'Z') {
            lowerStr[i] = lowerStr[i] + 32;
        }
    }
    return lowerStr;
}

int getValidInt(int minVal, int maxVal = 999999) {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear(); // Hapus flag error
            cin.ignore(10000, '\n'); // Buang karakter tidak valid di buffer
            cout << "Input tidak valid! Harap masukkan angka: ";
        } else if (input < minVal || input > maxVal) {
            cin.ignore(10000, '\n'); // Buang sisa buffer (misal input "1a")
            cout << "Pilihan di luar jangkauan (" << minVal;
            if (maxVal != 999999) cout << " - " << maxVal;
            cout << "). Coba lagi: ";
        } else {
            cin.ignore(10000, '\n'); // Bersihkan buffer newline agar siap untuk getline()
            return input;
        }
    }
}

double getValidDouble(double minVal) {
    double input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input tidak valid! Harap masukkan angka: ";
        } else if (input < minVal) {
            cin.ignore(10000, '\n');
            cout << "Angka tidak boleh kurang dari " << minVal << ". Coba lagi: ";
        } else {
            cin.ignore(10000, '\n');
            return input;
        }
    }
}

class Produk {
protected: 
    string nama;
    string merk;
    double harga;
    int stok;
    string kategori;

public:
    // Constructor Initialization List
    Produk(string n, string m, double h, int s, string k) 
        : nama(n), merk(m), harga(h), stok(s), kategori(k) {}
        
    virtual ~Produk() {}

    // Pure Virtual Function
    virtual void tampilkanInfo(int id) = 0; 

    // Getters
    string getNama() { return nama; }
    string getMerk() { return merk; }
    double getHarga() { return harga; }
    int getStok() { return stok; }
    string getKategori() { return kategori; }

    // Setters
    void setStok(int s) { stok = s; }

    // METHOD OVERLOADING (Polymorphism Compile-Time)
    void tambahStok(int tambahan) {
        stok += tambahan;
        cout << "Stok berhasil ditambah sebanyak " << tambahan << " unit.\n";
    }

    void tambahStok(int tambahan, string supplier) {
        stok += tambahan;
        cout << "Stok berhasil ditambah sebanyak " << tambahan << " unit dari supplier: " << supplier << ".\n";
    }
};

class ProdukFisik : public Produk {
private:
    double berat;

public:
    ProdukFisik(string n, string m, double h, int s, string k, double b)
        : Produk(n, m, h, s, k), berat(b) {}

    // METHOD OVERRIDING (Polymorphism Runtime)
    void tampilkanInfo(int id) override {
        cout << left << setw(4) << id 
            << "| " << setw(35) << nama 
            << "| " << setw(15) << merk 
            << "| " << setw(12) << kategori 
            << "| Rp " << setw(9) << harga 
            << "| " << setw(5) << stok 
            << "| " << berat << "g" << endl;
    }
    
    double getBerat() { return berat; }
};

struct ItemKeranjang {
    Produk* produk;
    int qty;
};

class Transaksi {
private:
    int idTransaksi;
    string username;
    ItemKeranjang items[50];
    int itemCount;
    double totalHarga;
    string metodeBayar;
    string status;

public:
    Transaksi(int id, string uname, ItemKeranjang keranjang[], int count, double total, string metode)
        : idTransaksi(id), username(uname), itemCount(count), totalHarga(total), metodeBayar(metode) {
        for (int i = 0; i < count; i++) {
            items[i] = keranjang[i];
        }
        status = "Menunggu Pembayaran";
    }

    int getId() { return idTransaksi; }
    string getUsername() { return username; }
    string getStatus() { return status; }
    
    void setStatus(string s) { status = s; }

    void tampilkanInvoice() {
        cout << "\n============================================\n";
        cout << "INVOICE TRANSAKSI #" << idTransaksi << "\n";
        cout << "Username Pembeli: " << username << "\n";
        cout << "Metode Pembayaran: " << metodeBayar << "\n";
        cout << "Status Pesanan: " << status << "\n";
        cout << "--------------------------------------------\n";
        for (int i = 0; i < itemCount; i++) {
            cout << "- " << items[i].produk->getNama() << " (x" << items[i].qty << ") : Rp " << items[i].produk->getHarga() * items[i].qty << "\n";
        }
        cout << "--------------------------------------------\n";
        cout << "Total Keseluruhan : Rp " << fixed << setprecision(0) << totalHarga << "\n";
        cout << "============================================\n";
    }
};

class Keranjang {
private:
    ItemKeranjang items[50];
    int itemCount;

public:
    Keranjang() : itemCount(0) {}

    void tambahProduk(Produk* p, int qty) {
        if (itemCount >= 50) {
            cout << "Error: Keranjang penuh!\n";
            return;
        }
        items[itemCount].produk = p;
        items[itemCount].qty = qty;
        itemCount++;
        cout << "Produk berhasil ditambahkan ke keranjang!\n";
    }

    double hitungTotal() {
        double total = 0;
        for (int i = 0; i < itemCount; i++) {
            total += (items[i].produk->getHarga() * items[i].qty);
        }
        return total;
    }

    void tampilkan() {
        if (itemCount == 0) {
            cout << "Keranjang masih kosong.\n";
            return;
        }
        cout << "\n--- Isi Keranjang ---\n";
        for (int i = 0; i < itemCount; i++) {
            cout << i + 1 << ". " << items[i].produk->getNama() 
                << " | Jumlah: " << items[i].qty 
                 << " | Subtotal: Rp " << items[i].produk->getHarga() * items[i].qty << "\n";
        }
        cout << "Total Belanja: Rp " << hitungTotal() << "\n";
    }

    void clear() { itemCount = 0; }
    
    int getCount() { return itemCount; }
    ItemKeranjang* getItems() { return items; }
};

class User {
private:
    string username;
    string password;
    string namaLengkap;
    Keranjang keranjang;
    Transaksi* riwayat[50];
    int riwayatCount;

public:
    User() : riwayatCount(0) {}
    User(string u, string p, string n) : username(u), password(p), namaLengkap(n), riwayatCount(0) {}

    string getUsername() { return username; }
    string getPassword() { return password; }
    string getNama() { return namaLengkap; }
    Keranjang* getKeranjang() { return &keranjang; }

    void tambahRiwayat(Transaksi* t) {
        if (riwayatCount < 50) {
            riwayat[riwayatCount] = t;
            riwayatCount++;
        }
    }

    void tampilkanRiwayat() {
        if (riwayatCount == 0) {
            cout << "Belum ada riwayat transaksi.\n";
            return;
        }
        for (int i = 0; i < riwayatCount; i++) {
            riwayat[i]->tampilkanInvoice();
        }
    }
};

Produk* katalog[100];
int jumlahProduk = 0;

User users[50];
int jumlahUser = 0;

Transaksi* semuaTransaksi[100];
int jumlahTransaksi = 0;
int idTransaksiGlobal = 1001;

void inisialisasiDataDummy() {
    katalog[jumlahProduk++] = new ProdukFisik("Somethinc Niacinamide Serum", "Somethinc", 115000, 50, "Skincare", 50);
    katalog[jumlahProduk++] = new ProdukFisik("Skintific 5X Ceramide Gel", "Skintific", 135000, 40, "Skincare", 80);
    katalog[jumlahProduk++] = new ProdukFisik("Wardah UV Shield Sunscreen", "Wardah", 35000, 100, "Skincare", 45);
    katalog[jumlahProduk++] = new ProdukFisik("Azarine Hydrasoothe Sunscreen", "Azarine", 65000, 75, "Skincare", 60);
    katalog[jumlahProduk++] = new ProdukFisik("The Originote Moisturizer", "The Originote", 42000, 120, "Skincare", 70);

    katalog[jumlahProduk++] = new ProdukFisik("Wardah Colorfit Cushion", "Wardah", 105000, 30, "Makeup", 150);
    katalog[jumlahProduk++] = new ProdukFisik("Maybelline Sky High Mascara", "Maybelline", 120000, 45, "Makeup", 30);
    katalog[jumlahProduk++] = new ProdukFisik("Emina Cheeklit Cream Blush", "Emina", 32000, 80, "Makeup", 20);
    katalog[jumlahProduk++] = new ProdukFisik("Implora Lip Cream Matte", "Implora", 24000, 200, "Makeup", 15);
    katalog[jumlahProduk++] = new ProdukFisik("Make Over Powerstay Foundie", "Make Over", 175000, 25, "Makeup", 100);

    katalog[jumlahProduk++] = new ProdukFisik("HMNS Orgasm", "HMNS", 315000, 15, "Parfum", 250);
    katalog[jumlahProduk++] = new ProdukFisik("Carl & Claire Black Dahlia", "Carl & Claire", 275000, 20, "Parfum", 250);
    katalog[jumlahProduk++] = new ProdukFisik("Mykonos Saint Tropez", "Mykonos", 145000, 35, "Parfum", 200);
    katalog[jumlahProduk++] = new ProdukFisik("Kahf Revered Oud", "Kahf", 75000, 60, "Parfum", 150);
    katalog[jumlahProduk++] = new ProdukFisik("Casablanca Eau De Parfum", "Casablanca", 45000, 90, "Parfum", 200);

    katalog[jumlahProduk++] = new ProdukFisik("Scarlett Whitening Lotion", "Scarlett", 75000, 85, "Body Care", 350);
    katalog[jumlahProduk++] = new ProdukFisik("Vaseline Healthy Bright", "Vaseline", 45000, 110, "Body Care", 300);
    katalog[jumlahProduk++] = new ProdukFisik("Marina UV White Lotion", "Marina", 18000, 150, "Body Care", 250);
    katalog[jumlahProduk++] = new ProdukFisik("Lifebuoy Body Wash", "Lifebuoy", 35000, 200, "Body Care", 500);
    katalog[jumlahProduk++] = new ProdukFisik("Dove Deeply Nourishing", "Dove", 42000, 100, "Body Care", 450);
}

void tampilkanKatalog() {
    cout << "\n==================================================================================================\n";
    cout << "                                KATALOG PRODUK BEAUTY STORE                                     \n";
    cout << "==================================================================================================\n";
    cout << left << setw(4) << "ID" 
        << "| " << setw(35) << "Nama Produk" 
        << "| " << setw(15) << "Merk" 
        << "| " << setw(12) << "Kategori" 
        << "| " << setw(12) << "Harga" 
        << "| " << setw(5) << "Stok" 
        << "| Berat" << endl;
    cout << "--------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < jumlahProduk; i++) {
        katalog[i]->tampilkanInfo(i + 1); 
    }
    cout << "==================================================================================================\n";
}

void menuUser(User* userLogin) {
    int pilihan;
    do {
        cout << "\n========== MENU PENGGUNA ==========\n";
        cout << "Halo, " << userLogin->getNama() << "!\n";
        cout << "1. Lihat Semua Katalog\n";
        cout << "2. Cari Produk (Nama)\n";
        cout << "3. Filter Kategori\n";
        cout << "4. Masukkan ke Keranjang\n";
        cout << "5. Lihat Keranjang & Checkout\n";
        cout << "6. Lihat Riwayat Transaksi\n";
        cout << "0. Logout\n";
        cout << "Pilih menu: ";
        
        pilihan = getValidInt(0, 6);

        if (pilihan == 1) {
            tampilkanKatalog();
        } 
        else if (pilihan == 2) {
            string keyword;
            cout << "Masukkan nama produk yang dicari: ";
            getline(cin, keyword);
            keyword = toLower(keyword);
            
            cout << "\n--- Hasil Pencarian ---\n";
            bool found = false;
            for (int i = 0; i < jumlahProduk; i++) {
                if (toLower(katalog[i]->getNama()).find(keyword) != string::npos) {
                    katalog[i]->tampilkanInfo(i + 1);
                    found = true;
                }
            }
            if (!found) cout << "Produk tidak ditemukan.\n";
        }
        else if (pilihan == 3) {
            string kat;
            cout << "Masukkan Kategori (Skincare / Makeup / Parfum / Body Care): ";
            getline(cin, kat);
            kat = toLower(kat);
            
            cout << "\n--- Hasil Filter ---\n";
            bool found = false;
            for (int i = 0; i < jumlahProduk; i++) {
                if (toLower(katalog[i]->getKategori()) == kat) {
                    katalog[i]->tampilkanInfo(i + 1);
                    found = true;
                }
            }
            if (!found) cout << "Kategori tidak ditemukan.\n";
        }
        else if (pilihan == 4) {
            tampilkanKatalog();
            cout << "Masukkan ID Produk: ";
            int id = getValidInt(1);
            
            // Validasi ID ada atau tidak
            if (id > jumlahProduk) {
                cout << "Error: ID Produk tidak ditemukan di katalog!\n";
                continue; // Langsung kembalikan ke menu utama user
            }

            cout << "Masukkan Jumlah (Min 1): ";
            int qty = getValidInt(1);

            Produk* p = katalog[id - 1];
            if (p->getStok() >= qty) {
                userLogin->getKeranjang()->tambahProduk(p, qty);
            } else {
                cout << "Error: Stok tidak mencukupi!\n";
            }
        }
        else if (pilihan == 5) {
            userLogin->getKeranjang()->tampilkan();
            if (userLogin->getKeranjang()->getCount() > 0) {
                string pil;
                cout << "\nLanjut Checkout? (y/n): ";
                getline(cin, pil);
                if (pil == "y" || pil == "Y") {
                    
                    bool valid = true;
                    ItemKeranjang* items = userLogin->getKeranjang()->getItems();
                    int count = userLogin->getKeranjang()->getCount();
                    
                    for (int i = 0; i < count; i++) {
                        if (items[i].produk->getStok() < items[i].qty) {
                            cout << "Maaf, stok " << items[i].produk->getNama() << " habis/kurang saat ini.\n";
                            valid = false;
                            break;
                        }
                    }

                    if (valid) {
                        cout << "Pilih Metode Pembayaran (1. COD, 2. Transfer): ";
                        int metode = getValidInt(1, 2);
                        string m = (metode == 1) ? "COD" : "Transfer Bank";

                        for (int i = 0; i < count; i++) {
                            int stokBaru = items[i].produk->getStok() - items[i].qty;
                            items[i].produk->setStok(stokBaru);
                        }

                        double total = userLogin->getKeranjang()->hitungTotal();
                        Transaksi* trxBaru = new Transaksi(idTransaksiGlobal++, userLogin->getUsername(), items, count, total, m);
                        semuaTransaksi[jumlahTransaksi++] = trxBaru;
                        userLogin->tambahRiwayat(trxBaru);
                        userLogin->getKeranjang()->clear();
                        
                        cout << "Checkout Berhasil! Pesanan sedang diproses.\n";
                    }
                }
            }
        }
        else if (pilihan == 6) {
            userLogin->tampilkanRiwayat();
        }
    } while (pilihan != 0);
}

void menuAdmin() {
    int pilihan;
    do {
        cout << "\n========== MENU ADMIN ==========\n";
        cout << "1. Lihat Katalog Produk\n";
        cout << "2. Tambah Produk Baru\n";
        cout << "3. Restock Produk\n";
        cout << "4. Lihat Semua Transaksi User\n";
        cout << "5. Ubah Status Pesanan\n";
        cout << "0. Logout\n";
        cout << "Pilih menu: ";
        
        pilihan = getValidInt(0, 5);

        if (pilihan == 1) {
            tampilkanKatalog();
        } 
        else if (pilihan == 2) {
            if (jumlahProduk >= 100) {
                cout << "Kapasitas katalog penuh!\n";
                continue;
            }
            string n, m, k;
            cout << "Nama Produk : "; getline(cin, n);
            cout << "Merk        : "; getline(cin, m);
            cout << "Kategori    : "; getline(cin, k);
            
            cout << "Harga       : "; 
            double h = getValidDouble(0);
            
            cout << "Stok Awal   : "; 
            int s = getValidInt(0);
            
            cout << "Berat (g)   : "; 
            double b = getValidDouble(0);

            katalog[jumlahProduk++] = new ProdukFisik(n, m, h, s, k, b);
            cout << "Produk baru berhasil ditambahkan!\n";
        }
        else if (pilihan == 3) {
            tampilkanKatalog();
            cout << "Masukkan ID Produk untuk Restock: ";
            int id = getValidInt(1);
            
            // Validasi ID
            if (id > jumlahProduk) {
                cout << "Error: ID Produk tidak ditemukan!\n";
                continue; // Langsung kembalikan ke menu utama admin
            }

            cout << "Jumlah Restock (Min 1): ";
            int qty = getValidInt(1);
            
            string tanya;
            cout << "Punya nama supplier khusus? (y/n): ";
            getline(cin, tanya);
            
            if (tanya == "y" || tanya == "Y") {
                string sup;
                cout << "Masukkan Nama Supplier: ";
                getline(cin, sup);
                katalog[id - 1]->tambahStok(qty, sup); 
            } else {
                katalog[id - 1]->tambahStok(qty);
            }
        }
        else if (pilihan == 4) {
            if (jumlahTransaksi == 0) {
                cout << "Belum ada pesanan masuk.\n";
            } else {
                for (int i = 0; i < jumlahTransaksi; i++) {
                    semuaTransaksi[i]->tampilkanInvoice();
                }
            }
        }
        else if (pilihan == 5) {
            cout << "Masukkan ID Transaksi: ";
            int idTrx = getValidInt(1000); // Base ID mulai dari 1001
            
            bool found = false;
            for (int i = 0; i < jumlahTransaksi; i++) {
                if (semuaTransaksi[i]->getId() == idTrx) {
                    found = true;
                    cout << "Status saat ini: " << semuaTransaksi[i]->getStatus() << "\n";
                    cout << "Pilih Status Baru (1. Diproses, 2. Dikirim, 3. Selesai): ";
                    
                    int st = getValidInt(1, 3);
                    if (st == 1) semuaTransaksi[i]->setStatus("Diproses");
                    else if (st == 2) semuaTransaksi[i]->setStatus("Dikirim");
                    else if (st == 3) semuaTransaksi[i]->setStatus("Selesai");
                    cout << "Status berhasil diperbarui!\n";
                    break;
                }
            }
            if (!found) cout << "Error: ID Transaksi tidak ditemukan.\n";
        }
    } while (pilihan != 0);
}

int main() {
    inisialisasiDataDummy();
    int menu;

    do {
        cout << "\n============================================\n";
        cout << "    SELAMAT DATANG DI GLOWUP BEAUTY STORE    \n";
        cout << "============================================\n";
        cout << "1. Registrasi User Baru\n";
        cout << "2. Login User\n";
        cout << "3. Login Admin\n";
        cout << "0. Keluar Program\n";
        cout << "Pilih menu: ";
        
        menu = getValidInt(0, 3);

        if (menu == 1) {
            if (jumlahUser >= 50) {
                cout << "Kapasitas user penuh!\n";
                continue;
            }
            string uname, pass, nama;
            cout << "Masukkan Username: "; getline(cin, uname);
            cout << "Masukkan Password: "; getline(cin, pass);
            cout << "Masukkan Nama Lengkap: "; getline(cin, nama);
            
            bool exist = false;
            for (int i = 0; i < jumlahUser; i++) {
                if (users[i].getUsername() == uname) {
                    exist = true; break;
                }
            }
            if (exist) {
                cout << "Username sudah terdaftar! Gunakan yang lain.\n";
            } else {
                users[jumlahUser++] = User(uname, pass, nama);
                cout << "Registrasi berhasil! Silahkan login.\n";
            }
        } 
        else if (menu == 2) {
            string uname, pass;
            cout << "Username: "; getline(cin, uname);
            cout << "Password: "; getline(cin, pass);
            
            User* loggedInUser = nullptr;
            for (int i = 0; i < jumlahUser; i++) {
                if (users[i].getUsername() == uname && users[i].getPassword() == pass) {
                    loggedInUser = &users[i];
                    break;
                }
            }
            
            if (loggedInUser != nullptr) {
                menuUser(loggedInUser);
            } else {
                cout << "Username atau Password salah!\n";
            }
        }
        else if (menu == 3) {
            string pass;
            cout << "Masukkan Password Admin: "; getline(cin, pass);
            if (pass == "admin123") { 
                menuAdmin();
            } else {
                cout << "Password Admin salah!\n";
            }
        }

    } while (menu != 0);

    cout << "Terima kasih telah menggunakan layanan GlowUp Beauty Store!\n";

    for (int i = 0; i < jumlahProduk; i++) delete katalog[i];
    for (int i = 0; i < jumlahTransaksi; i++) delete semuaTransaksi[i];

    return 0;
}