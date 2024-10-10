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
        cout << "Bahan baku \"" << namaBahan << "\" berhasil ditambahkan dengan stok " 
             << stok << " " << satuan << "!\n";
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

class Stack {
private:
    struct Node {
        BahanBaku data;
        Node* next;
    };
    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(const BahanBaku& bahan) {
        Node* newNode = new Node{bahan, top};
        top = newNode;
        cout << bahan.namaBahan << " dengan stok " << bahan.jumlahStok << " " 
             << bahan.satuan << " berada di posisi teratas stackk\n";
    }

    void pop() {
        if (top == nullptr) {
            cout << "Stack gak ada\n";
            return;
        }
        cout << top->data.namaBahan << " dengan stok " << top->data.jumlahStok 
             << " " << top->data.satuan << " dihapus dari stack\n";
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    void peek() {
        if (top == nullptr) {
            cout << "Stack kosong\n";
        } else {
            cout << "Bahan teratas: " << top->data.namaBahan
                 << " - Stok: " << top->data.jumlahStok
                 << " " << top->data.satuan << endl;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

class Queue {
private:
    struct Node {
        BahanBaku data;
        Node* next;
    };
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(const BahanBaku& bahan) {
        Node* newNode = new Node{bahan, nullptr};
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << bahan.namaBahan << " dengan stok " << bahan.jumlahStok << " " 
             << bahan.satuan << " enqueued into queue\n";
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "Queue gak ada\n";
            return;
        }
        cout << front->data.namaBahan << " dengan stok " << front->data.jumlahStok 
             << " " << front->data.satuan << " dihapus dari queue\n";
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    void peek() {
        if (front == nullptr) {
            cout << "Queue kosong\n";
        } else {
            cout << "Bahan terdepan: " << front->data.namaBahan
                 << " - Stok: " << front->data.jumlahStok
                 << " " << front->data.satuan << endl;
        }
    }
};

int main() {
    LinkedList daftarBahan;
    Stack stackBahan;
    Queue queueBahan;
    int pilihan;

    do {
        cout << "\n=== Program Pengelolaan Bahan Baku Restoran ===\n";
        cout << "1. Tambah Bahan Baku\n";
        cout << "2. Tampilkan Semua Bahan Baku\n";
        cout << "3. Ubah Stok Bahan Baku\n";
        cout << "4. Hapus Bahan Baku\n";
        cout << "5. Tambah Bahan ke Stack\n";
        cout << "6. Hapus Bahan dari Stack\n";
        cout << "7. Lihat Bahan Teratas (Stack)\n";
        cout << "8. Tambah Bahan ke Queue\n";
        cout << "9. Hapus Bahan dari Queue\n";
        cout << "10. Lihat Bahan Terdepan (Queue)\n";
        cout << "11. Keluar\n";
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
            case 5: {
                string namaBahan;
                int stok;
                string satuan;
                cout << "Masukkan nama bahan untuk stack: ";
                cin.ignore();
                getline(cin, namaBahan);
                cout << "Masukkan jumlah stok: ";
                cin >> stok;
                cout << "Masukkan satuan: ";
                cin >> satuan;
                stackBahan.push({namaBahan, stok, satuan});
                break;
            }
           
            case 6:
                stackBahan.pop();
                break;
            case 7:
                stackBahan.peek();
                break;
            case 8: {
                string namaBahan;
                int stok;
                string satuan;
                cout << "Masukkan nama bahan untuk queue: ";
                cin.ignore();
                getline(cin, namaBahan);
                cout << "Masukkan jumlah stok: ";
                cin >> stok;
                cout << "Masukkan satuan: ";
                cin >> satuan;
                queueBahan.enqueue({namaBahan, stok, satuan});
                break;
            }
            case 9:
                queueBahan.dequeue();
                break;
            case 10:
                queueBahan.peek();
                break;
            case 11:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
    } while (pilihan != 11);

    return 0;
}
