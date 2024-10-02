#include <iostream>
#include <string>
using namespace std;

struct BahanBaku {
    string namaBahan;
    int jumlahStok;
    string satuan;
    BahanBaku* next;  
};

class LinkedList {
private:
    BahanBaku* head; 

public:
    LinkedList() : head(nullptr) {}

    void tambahBahan(const string& namaBahan, int stok, const string& satuan) {
        BahanBaku* newBahan = new BahanBaku{namaBahan, stok, satuan, nullptr};
        
        if (!head) {
            head = newBahan;
        } else {
            BahanBaku* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newBahan;
        }
        cout << "Bahan baku \"" << namaBahan << "\" berhasil ditambahkan!\n";
    }

    void tampilkanBahan() {
        if (!head) {
            cout << "Saat ini tidak ada bahan baku yang terdaftar.\n";
            return;
        }
        
        BahanBaku* temp = head;
        cout << "Daftar Bahan Baku:\n";
        int index = 1;
        while (temp) {
            cout << index++ << ". " << temp->namaBahan 
                 << " - Stok: " << temp->jumlahStok 
                 << " " << temp->satuan << endl;
            temp = temp->next;
        }
    }

    BahanBaku* cariBahan(const string& namaBahan) {
        BahanBaku* temp = head;
        while (temp) {
            if (temp->namaBahan == namaBahan) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void updateStok(const string& namaBahan, int stokBaru) {
        BahanBaku* bahan = cariBahan(namaBahan);
        if (bahan) {
            bahan->jumlahStok = stokBaru;
            cout << "Stok bahan \"" << namaBahan << "\" telah diperbarui menjadi " 
                 << stokBaru << " " << bahan->satuan << endl;
        } else {
            cout << "Maaf, bahan \"" << namaBahan << "\" tidak ditemukan.\n";
        }
    }

    void hapusBahan(const string& namaBahan) {
        if (!head) {
            cout << "Tidak ada bahan untuk dihapus.\n";
            return;
        }
        
        if (head->namaBahan == namaBahan) {
            BahanBaku* temp = head;
            head = head->next;
            delete temp;
            cout << "Bahan baku \"" << namaBahan << "\" berhasil dihapus.\n";
            return;
        }

        BahanBaku* temp = head;
        while (temp->next && temp->next->namaBahan != namaBahan) {
            temp = temp->next;
        }
        
        if (temp->next) {
            BahanBaku* bahanToDelete = temp->next;
            temp->next = bahanToDelete->next;
            delete bahanToDelete;
            cout << "Bahan baku \"" << namaBahan << "\" berhasil dihapus.\n";
        } else {
            cout << "Bahan baku \"" << namaBahan << "\" tidak ditemukan.\n";
        }
    }
};

int main() {
    LinkedList daftarBahan;
    int pilihan;

    do {
        cout << "\n=== Program Pengelolaan Bahan Baku Restoran (Linked List) ===\n";
        cout << "1. Tambah Bahan Baku\n";
        cout << "2. Tampilkan Semua Bahan Baku\n";
        cout << "3. Ubah Stok Bahan Baku\n";
        cout << "4. Hapus Bahan Baku\n";
        cout << "5. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
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
                daftarBahan.tambahBahan(namaBahan, stok, satuan);
                break;
            }
            case 2:
                daftarBahan.tampilkanBahan();
                break;
            case 3: {
                string namaBahan;
                int stokBaru;
                cout << "Masukkan nama bahan yang ingin diubah: ";
                cin.ignore();
                getline(cin, namaBahan);
                cout << "Masukkan jumlah stok baru: ";
                cin >> stokBaru;
                daftarBahan.updateStok(namaBahan, stokBaru);
                break;
            }
            case 4: {
                string namaBahan;
                cout << "Masukkan nama bahan yang ingin dihapus: ";
                cin.ignore();
                getline(cin, namaBahan);
                daftarBahan.hapusBahan(namaBahan);
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
