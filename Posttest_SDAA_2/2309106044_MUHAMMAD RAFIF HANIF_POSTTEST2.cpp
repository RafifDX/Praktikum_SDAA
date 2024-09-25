#include <iostream>
#include <string>
using namespace std;

const int MAX_BAHAN = 9999;

struct BahanBaku 
{
    string namaBahan;
    int jumlahStok;
    string satuan;
};

bool tambahBahan(BahanBaku* daftarBahan, int& jumlahBahan, const string& namaBahan, int stok, const string& satuan) 
{
    if (jumlahBahan < MAX_BAHAN) 
    {
        daftarBahan[jumlahBahan].namaBahan = namaBahan;
        daftarBahan[jumlahBahan].jumlahStok = stok;
        daftarBahan[jumlahBahan].satuan = satuan;
        jumlahBahan++;
        cout << "Bahan baku \"" << namaBahan << "\" berhasil ditambahkan!\n";
        return true; 
    } else 
    {
        cout << "Kapasitas bahan baku penuh! Tidak bisa menambah lagi.\n";
        return false;
    }
}

bool tampilkanBahan(BahanBaku* daftarBahan, int jumlahBahan) 
{
    if (jumlahBahan == 0) 
    {
        cout << "Saat ini tidak ada bahan baku yang terdaftar.\n";
        return false;
    } else {
        cout << "Daftar Bahan Baku:\n";
        for (int i = 0; i < jumlahBahan; i++) 
        {
            cout << i + 1 << ". " << daftarBahan[i].namaBahan 
                 << " - Stok: " << daftarBahan[i].jumlahStok 
                 << " " << daftarBahan[i].satuan << endl;
        }
        return true;
    }
}

int cariBahan(BahanBaku* daftarBahan, int jumlahBahan, const string& namaBahan) 
{
    for (int i = 0; i < jumlahBahan; i++) 
    {
        if (daftarBahan[i].namaBahan == namaBahan) 
        {
            return i;
        }
    }
    return -1;
}

void updateStok(BahanBaku* daftarBahan, int jumlahBahan, const string& namaBahan, int stokBaru) 
{
    int indeks = cariBahan(daftarBahan, jumlahBahan, namaBahan);
    if (indeks != -1) 
    {
        daftarBahan[indeks].jumlahStok = stokBaru;
        cout << "Stok bahan \"" << namaBahan << "\" telah diperbarui menjadi " << stokBaru << " " << daftarBahan[indeks].satuan << endl;
    } else 
    {
        cout << "Maaf, bahan \"" << namaBahan << "\" tidak ditemukan.\n";
    }
}

void hapusBahan(BahanBaku* daftarBahan, int& jumlahBahan, const string& namaBahan) 
{
    int indeks = cariBahan(daftarBahan, jumlahBahan, namaBahan);
    if (indeks != -1) 
    {
        for (int i = indeks; i < jumlahBahan - 1; i++) 
        {
            daftarBahan[i] = daftarBahan[i + 1];
        }
        jumlahBahan--;
        cout << "Bahan baku \"" << namaBahan << "\" berhasil dihapus.\n";
    } else 
    {
        cout << "Bahan baku \"" << namaBahan << "\" tidak ditemukan.\n";
    }
}

int main() 
{
    BahanBaku daftarBahan[MAX_BAHAN]; 
    int jumlahBahan = 0; 
    int pilihan;
    do 
    {
        cout << "\n=== Program Pengelolaan Bahan Baku Restoran ===\n";
        cout << "1. Tambah Bahan Baku\n";
        cout << "2. Tampilkan Semua Bahan Baku\n";
        cout << "3. Ubah Stok Bahan Baku\n";
        cout << "4. Hapus Bahan Baku\n";
        cout << "5. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) 
        {
            case 1: 
            {
                string namaBahan;
                int stok;
                string satuan;
                cout << "Masukkan nama bahan: ";
                cin.ignore();
                getline(cin, namaBahan);
                cout << "Masukkan jumlah stok: ";
                cin >> stok;
                cout << "Masukkan satuan (kg, liter, dll.): ";
                cin >> satuan;
                if (tambahBahan(daftarBahan, jumlahBahan, namaBahan, stok, satuan)) 
                {
                    cout << "Bahan baku ditambahkan dengan sukses!\n";
                }
                break;
            }
            case 2:
                tampilkanBahan(daftarBahan, jumlahBahan);
                break;
            case 3: 
            {
                string namaBahan;
                int stokBaru;
                cout << "Masukkan nama bahan yang ingin diubah: ";
                cin.ignore();
                getline(cin, namaBahan);
                cout << "Masukkan jumlah stok baru: ";
                cin >> stokBaru;
                updateStok(daftarBahan, jumlahBahan, namaBahan, stokBaru);
                break;
            }
            case 4: 
            {
                string namaBahan;
                cout << "Masukkan nama bahan yang ingin dihapus: ";
                cin.ignore();
                getline(cin, namaBahan);
                hapusBahan(daftarBahan, jumlahBahan, namaBahan);
                break;
            }
            case 5:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
    } while (pilihan != 5);

    return 0;
}
