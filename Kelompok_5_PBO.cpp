#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

string toLower(string str) {
    for (int i = 0; i < (int)str.length(); i++)
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
    return str;
}

int getValidInt(int minVal, int maxVal = 999999) {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Input tidak valid! Harap masukkan angka: ";
        } else if (input < minVal || input > maxVal) {
            cin.ignore(10000, '\n');
            cout << "Pilihan di luar jangkauan (" << minVal;
            if (maxVal != 999999) cout << " - " << maxVal;
            cout << "). Coba lagi: ";
        } else { cin.ignore(10000, '\n'); return input; }
    }
}

double getValidDouble(double minVal) {
    double input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Input tidak valid! Harap masukkan angka: ";
        } else if (input < minVal) {
            cin.ignore(10000, '\n');
            cout << "Angka tidak boleh kurang dari " << minVal << ". Coba lagi: ";
        } else { cin.ignore(10000, '\n'); return input; }
    }
}

class Produk {
protected:
    string nama, merk, kategori;
    double harga;
    int stok;
public:
    Produk(string n, string m, double h, int s, string k)
        : nama(n), merk(m), harga(h), stok(s), kategori(k) {}
    virtual ~Produk() {}
    virtual void tampilkanInfo(int id) = 0;
    string getNama()     { return nama; }
    string getMerk()     { return merk; }
    double getHarga()    { return harga; }
    int    getStok()     { return stok; }
    string getKategori() { return kategori; }
    void setStok(int s)  { stok = s; }
    void tambahStok(int tambahan) { stok += tambahan; }
};

class ProdukFisik : public Produk {
private:
    double berat;
public:
    ProdukFisik(string n, string m, double h, int s, string k, double b)
        : Produk(n, m, h, s, k), berat(b) {}
    void tampilkanInfo(int id) override {
        cout << left << setw(4) << id
            << "| " << setw(35) << nama << "| " << setw(15) << merk
            << "| " << setw(12) << kategori << "| Rp " << setw(9) << harga
            << "| " << setw(5) << stok << "| " << berat << "g" << endl;
    }
    double getBerat() { return berat; }
};

class ProdukParfum : public Produk {
private:
    double volume;
public:
    ProdukParfum(string n, string m, double h, int s, double vol)
        : Produk(n, m, h, s, "Parfum"), volume(vol) {}
    void tampilkanInfo(int id) override {
        cout << left << setw(4) << id
            << "| " << setw(35) << nama << "| " << setw(15) << merk
            << "| " << setw(12) << kategori << "| Rp " << setw(9) << harga
            << "| " << setw(5) << stok << "| " << volume << "ml" << endl;
    }
    double getVolume() { return volume; }
};

struct ItemKeranjang { Produk* produk; int qty; };

class Transaksi {
private:
    int idTransaksi, itemCount;
    string username, metodeBayar, status;
    ItemKeranjang items[50];
    double totalHarga;
public:
    Transaksi(int id, string uname, ItemKeranjang keranjang[], int count, double total, string metode)
        : idTransaksi(id), username(uname), itemCount(count), totalHarga(total), metodeBayar(metode) {
        for (int i = 0; i < count; i++) items[i] = keranjang[i];
        status = "Menunggu Pembayaran";
    }
    int    getId()       { return idTransaksi; }
    string getUsername() { return username; }
    string getStatus()   { return status; }
    void setStatus(string s) { status = s; }
    void tampilkanInvoice() {
        cout << "\n  ┌──────────────────────────────────────────────────────────┐\n"
            << "  │                  INVOICE TRANSAKSI                       │\n"
            << "  ├──────────────────────────────────────────────────────────┤\n"
            << "  │  ID Transaksi  : #" << left << setw(40) << idTransaksi << "│\n"
            << "  │  Username      : "  << left << setw(41) << username    << "│\n"
            << "  │  Metode Bayar  : "  << left << setw(41) << metodeBayar << "│\n"
            << "  │  Status        : "  << left << setw(41) << status      << "│\n"
            << "  ├──────────────────────────────────────────────────────────┤\n";
        for (int i = 0; i < itemCount; i++) {
            int    qty  = items[i].qty;
            double hSat = items[i].produk->getHarga();
            string hTotStr = to_string(qty) + " x Rp " + to_string((int)hSat)
                           + " = Rp " + to_string((int)(hSat * qty));
            cout << "  │  Nama Produk   : " << left << setw(41) << items[i].produk->getNama()      << "│\n"
                << "  │  Merk          : " << left << setw(41) << items[i].produk->getMerk()      << "│\n"
                << "  │  Kategori      : " << left << setw(41) << items[i].produk->getKategori()  << "│\n"
                << "  │  Jumlah        : " << left << setw(41) << qty                             << "│\n"
                << "  │  Harga Satuan  : Rp " << left << setw(38) << fixed << setprecision(0) << hSat << "│\n"
                << "  │  Harga Total   : " << left << setw(41) << hTotStr                        << "│\n";
            if (i < itemCount - 1)
                cout << "  │  - - - - - - - - - - - - - - - - - - - - - - - - - - - -│\n";
        }
        cout << "  ├──────────────────────────────────────────────────────────┤\n"
            << "  │  TOTAL         : Rp " << left << setw(38) << fixed << setprecision(0) << totalHarga << "│\n"
            << "  └──────────────────────────────────────────────────────────┘\n";
    }
};

class Keranjang {
private:
    ItemKeranjang items[50];
    int itemCount;
public:
    Keranjang() : itemCount(0) {}
    void tambahProduk(Produk* p, int qty) {
        if (itemCount >= 50) { cout << "  Error: Keranjang penuh!\n"; return; }
        items[itemCount++] = {p, qty};
        cout << "  Produk berhasil ditambahkan ke keranjang!\n";
    }
    double hitungTotal() {
        double total = 0;
        for (int i = 0; i < itemCount; i++) total += items[i].produk->getHarga() * items[i].qty;
        return total;
    }
    // Overload 1: tampilkan semua
    void tampilkan() {
        if (itemCount == 0) { cout << "  Keranjang masih kosong.\n"; return; }
        cout << "\n  ┌──────────────────────────────────────────────────────────┐\n"
            << "  │                    ISI KERANJANG                         │\n"
            << "  ├──────────────────────────────────────────────────────────┤\n";
        for (int i = 0; i < itemCount; i++) {
            int qty = items[i].qty; double hSat = items[i].produk->getHarga();
            cout << "  │  " << left << setw(58) << (to_string(i+1) + ". " + items[i].produk->getNama()) << "│\n"
                << "  │  " << left << setw(58) << ("   x" + to_string(qty) + " @ Rp " + to_string((int)hSat) + "  =  Rp " + to_string((int)(hSat*qty))) << "│\n";
            if (i < itemCount - 1)
                cout << "  │                                                          │\n";
        }
        cout << "  ├──────────────────────────────────────────────────────────┤\n"
            << "  │  " << left << setw(58) << ("Total Belanja : Rp " + to_string((int)hitungTotal())) << "│\n"
            << "  └──────────────────────────────────────────────────────────┘\n";
    }
    // Overload 2: tampilkan filter per kategori
    void tampilkan(string kategori) {
        double sub = 0; bool ada = false; int nomor = 1;
        cout << "\n  ┌──────────────────────────────────────────────────────────┐\n"
            << "  │           ISI KERANJANG [" << left << setw(32) << kategori << "]│\n"
            << "  ├──────────────────────────────────────────────────────────┤\n";
        for (int i = 0; i < itemCount; i++) {
            if (items[i].produk->getKategori() != kategori) continue;
            ada = true;
            int qty = items[i].qty; double hSat = items[i].produk->getHarga(); double tot = hSat * qty;
            sub += tot;
            cout << "  │  " << left << setw(58) << (to_string(nomor++) + ". " + items[i].produk->getNama()) << "│\n"
                << "  │  " << left << setw(58) << ("   x" + to_string(qty) + " @ Rp " + to_string((int)hSat) + "  =  Rp " + to_string((int)tot)) << "│\n"
                << "  │                                                          │\n";
        }
        if (!ada) cout << "  │  " << left << setw(58) << "Tidak ada produk kategori ini di keranjang." << "│\n";
        cout << "  ├──────────────────────────────────────────────────────────┤\n"
            << "  │  " << left << setw(58) << ("Total [" + kategori + "] : Rp " + to_string((int)sub)) << "│\n"
            << "  └──────────────────────────────────────────────────────────┘\n";
    }
    void clear()              { itemCount = 0; }
    int getCount()            { return itemCount; }
    ItemKeranjang* getItems() { return items; }
};

class User {
private:
    string username, password, namaLengkap;
    Keranjang keranjang;
    Transaksi* riwayat[50];
    int riwayatCount;
public:
    User() : riwayatCount(0) {}
    User(string u, string p, string n) : username(u), password(p), namaLengkap(n), riwayatCount(0) {}
    string     getUsername()  { return username; }
    string     getPassword()  { return password; }
    string     getNama()      { return namaLengkap; }
    Keranjang* getKeranjang() { return &keranjang; }
    void tambahRiwayat(Transaksi* t) { if (riwayatCount < 50) riwayat[riwayatCount++] = t; }
    void tampilkanRiwayat() {
        if (riwayatCount == 0) { cout << "  Belum ada riwayat transaksi.\n"; return; }
        for (int i = 0; i < riwayatCount; i++) riwayat[i]->tampilkanInvoice();
    }
};

Produk*    katalog[100];
int        jumlahProduk = 0;
User       users[50];
int        jumlahUser = 0;
Transaksi* semuaTransaksi[100];
int        jumlahTransaksi = 0, idTransaksiGlobal = 1001;

void inisialisasiDataDummy() {
    katalog[jumlahProduk++] = new ProdukFisik("Somethinc Niacinamide Serum",   "Somethinc",    115000, 50, "Skincare",  50);
    katalog[jumlahProduk++] = new ProdukFisik("Skintific 5X Ceramide Gel",     "Skintific",    135000, 40, "Skincare",  80);
    katalog[jumlahProduk++] = new ProdukFisik("Wardah UV Shield Sunscreen",    "Wardah",        35000,100, "Skincare",  45);
    katalog[jumlahProduk++] = new ProdukFisik("Azarine Hydrasoothe Sunscreen", "Azarine",       65000, 75, "Skincare",  60);
    katalog[jumlahProduk++] = new ProdukFisik("Wardah Colorfit Cushion",       "Wardah",       105000, 30, "Makeup",   150);
    katalog[jumlahProduk++] = new ProdukFisik("Maybelline Sky High Mascara",   "Maybelline",   120000, 45, "Makeup",    30);
    katalog[jumlahProduk++] = new ProdukFisik("Implora Lip Cream Matte",       "Implora",       24000,200, "Makeup",    15);
    katalog[jumlahProduk++] = new ProdukParfum("HMNS Orgasm",                  "HMNS",         315000, 15, 100);
    katalog[jumlahProduk++] = new ProdukParfum("Carl & Claire Black Dahlia",   "Carl & Claire",275000, 20, 100);
    katalog[jumlahProduk++] = new ProdukParfum("Kahf Revered Oud",             "Kahf",          75000, 60,  50);
    katalog[jumlahProduk++] = new ProdukFisik("Scarlett Whitening Lotion",     "Scarlett",      75000, 85, "Body Care",350);
    katalog[jumlahProduk++] = new ProdukFisik("Vaseline Healthy Bright",       "Vaseline",      45000,110, "Body Care",300);
    katalog[jumlahProduk++] = new ProdukFisik("Lifebuoy Body Wash",            "Lifebuoy",      35000,200, "Body Care",500);
}

void cetakHeaderKatalog() {
    cout << left << setw(4) << "ID"
        << "| " << setw(35) << "Nama Produk" << "| " << setw(15) << "Merk"
        << "| " << setw(12) << "Kategori"    << "| " << setw(12) << "Harga"
        << "| " << setw(5)  << "Stok"        << "| Ukuran" << endl;
    cout << "--------------------------------------------------------------------------------------------------\n";
}

void tampilkanKatalog() {
    cout << "\n==================================================================================================\n"
        << "                                KATALOG PRODUK BEAUTY STORE                                     \n"
        << "==================================================================================================\n";
    cetakHeaderKatalog();
    for (int i = 0; i < jumlahProduk; i++) katalog[i]->tampilkanInfo(i + 1);
    cout << "==================================================================================================\n";
}

void tampilkanKatalogKategori(string kategori) {
    cout << "\n  Produk dalam kategori [" << kategori << "]:\n"
        << "--------------------------------------------------------------------------------------------------\n";
    cetakHeaderKatalog();
    bool ada = false;
    for (int i = 0; i < jumlahProduk; i++)
        if (katalog[i]->getKategori() == kategori) { katalog[i]->tampilkanInfo(i + 1); ada = true; }
    cout << "--------------------------------------------------------------------------------------------------\n";
    if (!ada) cout << "  Tidak ada produk dalam kategori ini.\n";
}

void fiturKeranjang(User* userLogin) {
    while (true) {
        cout << "\n  ┌─────────────────────────────────────────┐\n"
            << "  │           PILIH KATEGORI                │\n"
            << "  ├─────────────────────────────────────────┤\n"
            << "  │   1. Skincare   2. Makeup               │\n"
            << "  │   3. Parfum     4. Body Care            │\n"
            << "  ├─────────────────────────────────────────┤\n"
            << "  │   0. Batal                              │\n"
            << "  └─────────────────────────────────────────┘\n"
            << "  Pilih kategori: ";
        int pilihanKat = getValidInt(0, 4);
        if (pilihanKat == 0) return;

        string katList[] = {"", "Skincare", "Makeup", "Parfum", "Body Care"};
        string kategoriDipilih = katList[pilihanKat];
        tampilkanKatalogKategori(kategoriDipilih);

        cout << "  Masukkan ID produk (atau 0 untuk cari nama): ";
        int pilihanId = getValidInt(0);
        int id = -1;

        if (pilihanId != 0) {
            id = pilihanId;
        } else {
            string keyword;
            cout << "\n  Cari nama produk: "; getline(cin, keyword);
            keyword = toLower(keyword);
            cout << "\n  Hasil pencarian:\n--------------------------------------------------------------------------------------------------\n";
            cetakHeaderKatalog();
            bool found = false;
            for (int i = 0; i < jumlahProduk; i++)
                if (katalog[i]->getKategori() == kategoriDipilih &&
                    toLower(katalog[i]->getNama()).find(keyword) != string::npos)
                    { katalog[i]->tampilkanInfo(i + 1); found = true; }
            cout << "--------------------------------------------------------------------------------------------------\n";
            if (!found) { cout << "  Produk tidak ditemukan.\n"; continue; }
            cout << "  Masukkan ID Produk: "; id = getValidInt(1);
        }

        if (id > jumlahProduk) { cout << "  Error: ID tidak ditemukan!\n"; continue; }
        Produk* p = katalog[id - 1];
        if (p->getKategori() != kategoriDipilih) { cout << "  Error: Produk bukan kategori " << kategoriDipilih << "!\n"; continue; }
        if (p->getStok() == 0) { cout << "  Error: Stok produk habis!\n"; continue; }

        cout << "  Masukkan Jumlah (Min 1, Stok: " << p->getStok() << "): ";
        int qty = getValidInt(1);
        if (qty > p->getStok()) { cout << "  Error: Stok tidak mencukupi!\n"; continue; }

        double subtotal = p->getHarga() * qty;
        string subStr = to_string(qty) + " x Rp " + to_string((int)p->getHarga()) + " = Rp " + to_string((int)subtotal);
        cout << "\n  ┌──────────────────────────────────────────────────────────┐\n"
            << "  │                 RINGKASAN PRODUK                         │\n"
            << "  ├──────────────────────────────────────────────────────────┤\n"
            << "  │  Nama Produk  : " << left << setw(43) << p->getNama()     << "│\n"
            << "  │  Merk         : " << left << setw(43) << p->getMerk()     << "│\n"
            << "  │  Kategori     : " << left << setw(43) << p->getKategori() << "│\n"
            << "  │  Harga Satuan : Rp " << left << setw(40) << fixed << setprecision(0) << p->getHarga() << "│\n"
            << "  │  Jumlah       : " << left << setw(43) << qty              << "│\n"
            << "  │  Subtotal     : " << left << setw(43) << subStr           << "│\n"
            << "  └──────────────────────────────────────────────────────────┘\n"
            << "  Masukkan ke keranjang? (y/n): ";
        string konfirmasi; getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
            userLogin->getKeranjang()->tambahProduk(p, qty);
        else { cout << "  Dibatalkan.\n"; continue; }

        cout << "\n  Tambah produk dari kategori lain? (y/n): ";
        string lagi; getline(cin, lagi);
        if (lagi != "y" && lagi != "Y") break;
        cout << "  (Catatan: pilih kategori yang berbeda dari [" << kategoriDipilih << "])\n";
    }
}

void menuUser(User* userLogin) {
    int pilihan;
    do {
        cout << "\n  ╔═════════════════════════════════════════╗\n"
            << "  ║         GLOWUP BEAUTY STORE             ║\n"
            << "  ╚═════════════════════════════════════════╝\n"
            << "\n  ┌─────────────────────────────────────────┐\n"
            << "  │           MENU PENGGUNA                 │\n"
            << "  │  Halo, " << left << setw(33) << userLogin->getNama() << "│\n"
            << "  ├─────────────────────────────────────────┤\n"
            << "  │   1. Lihat Semua Katalog                │\n"
            << "  │   2. Masukkan ke Keranjang              │\n"
            << "  │   3. Lihat Keranjang & Checkout         │\n"
            << "  │   4. Lihat Riwayat Transaksi            │\n"
            << "  ├─────────────────────────────────────────┤\n"
            << "  │   0. Logout                             │\n"
            << "  └─────────────────────────────────────────┘\n"
            << "  Pilih menu: ";
        pilihan = getValidInt(0, 4);

        if (pilihan == 1) { tampilkanKatalog(); }
        else if (pilihan == 2) { fiturKeranjang(userLogin); }
        else if (pilihan == 3) {
            cout << "\n  ┌─────────────────────────────────────────┐\n"
                << "  │        TAMPILKAN KERANJANG              │\n"
                << "  ├─────────────────────────────────────────┤\n"
                << "  │   1. Semua Produk                       │\n"
                << "  │   2. Filter per Kategori                │\n"
                << "  └─────────────────────────────────────────┘\n"
                << "  Pilih: ";
            int pil = getValidInt(1, 2);
            if (pil == 1) {
                userLogin->getKeranjang()->tampilkan();
            } else {
                cout << "\n  ┌─────────────────────────────────────────┐\n"
                    << "  │           PILIH KATEGORI                │\n"
                    << "  ├─────────────────────────────────────────┤\n"
                    << "  │   1. Skincare   2. Makeup               │\n"
                    << "  │   3. Parfum     4. Body Care            │\n"
                    << "  └─────────────────────────────────────────┘\n"
                    << "  Pilih kategori: ";
                int katPil = getValidInt(1, 4);
                string katList[] = {"", "Skincare", "Makeup", "Parfum", "Body Care"};
                userLogin->getKeranjang()->tampilkan(katList[katPil]);
            }

            if (userLogin->getKeranjang()->getCount() > 0) {
                string pil2; cout << "\n  Lanjut Checkout? (y/n): "; getline(cin, pil2);
                if (pil2 == "y" || pil2 == "Y") {
                    bool valid = true;
                    ItemKeranjang* items = userLogin->getKeranjang()->getItems();
                    int count = userLogin->getKeranjang()->getCount();
                    for (int i = 0; i < count; i++)
                        if (items[i].produk->getStok() < items[i].qty)
                            { cout << "  Maaf, stok " << items[i].produk->getNama() << " habis/kurang.\n"; valid = false; break; }
                    if (valid) {
                        double total = userLogin->getKeranjang()->hitungTotal();
                        cout << "\n  ┌─────────────────────────────────────────┐\n"
                            << "  │       PILIH METODE PEMBAYARAN           │\n"
                            << "  ├─────────────────────────────────────────┤\n"
                            << "  │   1. COD (Bayar di Tempat)              │\n"
                            << "  │   2. Transfer Bank                      │\n"
                            << "  └─────────────────────────────────────────┘\n"
                            << "  Pilih metode: ";
                        int metode = getValidInt(1, 2);
                        string m = (metode == 1) ? "COD" : "Transfer Bank";
                        if (metode == 2) {
                            cout << "\n  Total yang harus dibayar : Rp " << fixed << setprecision(0) << total << "\n"
                                << "  Konfirmasi pembayaran transfer? (y/n): ";
                            string konfTrf; getline(cin, konfTrf);
                            if (konfTrf != "y" && konfTrf != "Y") { cout << "  Pembayaran dibatalkan.\n"; continue; }
                        }
                        for (int i = 0; i < count; i++)
                            items[i].produk->setStok(items[i].produk->getStok() - items[i].qty);
                        Transaksi* trxBaru = new Transaksi(idTransaksiGlobal++, userLogin->getUsername(), items, count, total, m);
                        semuaTransaksi[jumlahTransaksi++] = trxBaru;
                        userLogin->tambahRiwayat(trxBaru);
                        userLogin->getKeranjang()->clear();
                        cout << "\n  " << (metode == 2 ? "Pembayaran" : "Checkout") << " berhasil! Pesanan sedang diproses.\n";
                    }
                }
            }
        }
        else if (pilihan == 4) { userLogin->tampilkanRiwayat(); }
    } while (pilihan != 0);
}

void menuAdmin() {
    int pilihan;
    do {
        cout << "\n  ╔═════════════════════════════════════════╗\n"
            << "  ║         GLOWUP BEAUTY STORE             ║\n"
            << "  ╚═════════════════════════════════════════╝\n"
            << "\n  ┌─────────────────────────────────────────┐\n"
            << "  │          MENU ADMINISTRATOR             │\n"
            << "  ├─────────────────────────────────────────┤\n"
            << "  │   1. Lihat Katalog Produk               │\n"
            << "  │   2. Tambah Produk Baru                 │\n"
            << "  │   3. Restock Produk                     │\n"
            << "  │   4. Lihat Semua Transaksi User         │\n"
            << "  ├─────────────────────────────────────────┤\n"
            << "  │   0. Logout                             │\n"
            << "  └─────────────────────────────────────────┘\n"
            << "  Pilih menu: ";
        pilihan = getValidInt(0, 4);

        if (pilihan == 1) { tampilkanKatalog(); }
        else if (pilihan == 2) {
            if (jumlahProduk >= 100) { cout << "  Kapasitas katalog penuh!\n"; continue; }
            string n, m, k;
            cout << "  Nama Produk : "; getline(cin, n);
            cout << "  Merk        : "; getline(cin, m);
            cout << "  Kategori    : "; getline(cin, k);
            cout << "  Harga       : "; double h = getValidDouble(0);
            cout << "  Stok Awal   : "; int s = getValidInt(0);
            if (k == "Parfum") {
                cout << "  Volume (ml) : "; double vol = getValidDouble(0);
                katalog[jumlahProduk++] = new ProdukParfum(n, m, h, s, vol);
            } else {
                cout << "  Berat (g)   : "; double b = getValidDouble(0);
                katalog[jumlahProduk++] = new ProdukFisik(n, m, h, s, k, b);
            }
            cout << "  Produk baru berhasil ditambahkan!\n";
        }
        else if (pilihan == 3) {
            tampilkanKatalog();
            cout << "  Masukkan ID Produk untuk Restock: "; int id = getValidInt(1);
            if (id > jumlahProduk) { cout << "  Error: ID Produk tidak ditemukan!\n"; continue; }
            cout << "  Jumlah Restock (Min 1): "; int qty = getValidInt(1);
            katalog[id - 1]->tambahStok(qty);
            cout << "  Stok berhasil ditambah sebanyak " << qty << " unit.\n"
                << "  Detail: ID " << id << " | " << katalog[id-1]->getNama()
                << " | " << katalog[id-1]->getMerk() << " | " << katalog[id-1]->getKategori() << "\n";
        }
        else if (pilihan == 4) {
            if (jumlahTransaksi == 0) { cout << "  Belum ada pesanan masuk.\n"; continue; }
            for (int i = 0; i < jumlahTransaksi; i++) semuaTransaksi[i]->tampilkanInvoice();
            cout << "\n  Ubah status pesanan? (y/n): ";
            string jawab; getline(cin, jawab);
            if (jawab != "y" && jawab != "Y") continue;
            cout << "  Masukkan ID Transaksi: "; int idTrx = getValidInt(1000);
            bool found = false;
            for (int i = 0; i < jumlahTransaksi; i++) {
                if (semuaTransaksi[i]->getId() == idTrx) {
                    found = true;
                    cout << "  Status saat ini: " << semuaTransaksi[i]->getStatus() << "\n"
                        << "\n  ┌─────────────────────────────────────────┐\n"
                        << "  │         PILIH STATUS BARU               │\n"
                        << "  ├─────────────────────────────────────────┤\n"
                        << "  │   1. Diproses  2. Dikirim  3. Selesai  │\n"
                        << "  └─────────────────────────────────────────┘\n"
                        << "  Pilih: ";
                    int st = getValidInt(1, 3);
                    string statusList[] = {"", "Diproses", "Dikirim", "Selesai"};
                    semuaTransaksi[i]->setStatus(statusList[st]);
                    cout << "  Status berhasil diperbarui!\n"; break;
                }
            }
            if (!found) cout << "  Error: ID Transaksi tidak ditemukan.\n";
        }
    } while (pilihan != 0);
}

int main() {
    system("chcp 65001");
    inisialisasiDataDummy();
    int menu;
    do {
        cout << "\n  ╔═════════════════════════════════════════╗\n"
            << "  ║         GLOWUP BEAUTY STORE             ║\n"
            << "  ╚═════════════════════════════════════════╝\n"
            << "\n  ┌─────────────────────────────────────────┐\n"
            << "  │              MENU UTAMA                 │\n"
            << "  ├─────────────────────────────────────────┤\n"
            << "  │   1. Registrasi User Baru               │\n"
            << "  │   2. Login User                         │\n"
            << "  │   3. Login Admin                        │\n"
            << "  ├─────────────────────────────────────────┤\n"
            << "  │   0. Keluar Program                     │\n"
            << "  └─────────────────────────────────────────┘\n"
            << "  Pilih menu: ";
        menu = getValidInt(0, 3);

        if (menu == 1) {
            if (jumlahUser >= 50) { cout << "  Kapasitas user penuh!\n"; continue; }
            string uname, pass, nama;
            cout << "  Masukkan Username     : "; getline(cin, uname);
            cout << "  Masukkan Password     : "; getline(cin, pass);
            cout << "  Masukkan Nama Lengkap : "; getline(cin, nama);
            bool exist = false;
            for (int i = 0; i < jumlahUser; i++)
                if (users[i].getUsername() == uname) { exist = true; break; }
            if (exist) cout << "  Username sudah terdaftar! Gunakan yang lain.\n";
            else { users[jumlahUser++] = User(uname, pass, nama); cout << "  Registrasi berhasil! Silahkan login.\n"; }
        }
        else if (menu == 2) {
            string uname, pass;
            cout << "  Username : "; getline(cin, uname);
            cout << "  Password : "; getline(cin, pass);
            User* loggedInUser = nullptr;
            for (int i = 0; i < jumlahUser; i++)
                if (users[i].getUsername() == uname && users[i].getPassword() == pass)
                    { loggedInUser = &users[i]; break; }
            if (loggedInUser) menuUser(loggedInUser);
            else cout << "  Username atau Password salah!\n";
        }
        else if (menu == 3) {
            string pass; cout << "  Password Admin: "; getline(cin, pass);
            if (pass == "admin123") menuAdmin();
            else cout << "  Password Admin salah!\n";
        }
    } while (menu != 0);

    cout << "\n  Terima kasih telah menggunakan layanan GlowUp Beauty Store!\n";
    for (int i = 0; i < jumlahProduk;    i++) delete katalog[i];
    for (int i = 0; i < jumlahTransaksi; i++) delete semuaTransaksi[i];
    return 0;
}