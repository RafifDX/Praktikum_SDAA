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

    // Fungsi untuk memecah linked list menjadi dua bagian
    BahanBaku* split(BahanBaku* head) {
        BahanBaku* fast = head->next;
        BahanBaku* slow = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        BahanBaku* temp = slow->next;
        slow->next = nullptr;
        return temp;
    }

    // Fungsi untuk menggabungkan dua linked list yang sudah terurut
    BahanBaku* merge(BahanBaku* left, BahanBaku* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->jumlahStok < right->jumlahStok) {
            left->next = merge(left->next, right);
            return left;
        } else {
            right->next = merge(left, right->next);
            return right;
        }
    }

    // Fungsi utama untuk merge sort (ascending)
    BahanBaku* mergeSort(BahanBaku* head) {
        if (!head || !head->next) {
            return head;
        }

        BahanBaku* middle = split(head);
        BahanBaku* left = mergeSort(head);
        BahanBaku* right = mergeSort(middle);
        
        return merge(left, right);
    }

    void sortAscending() {
        head = mergeSort(head);
        cout << "Daftar bahan baku telah diurutkan secara ascending berdasarkan jumlah stok.\n";
    }

    // Fungsi untuk menemukan node terakhir dari linked list
    BahanBaku* getTail(BahanBaku* cur) {
        while (cur != nullptr && cur->next != nullptr)
            cur = cur->next;
        return cur;
    }

    // Fungsi partisi untuk quicksort
    BahanBaku* partition(BahanBaku* head, BahanBaku* end, BahanBaku** newHead, BahanBaku** newEnd) {
        BahanBaku* pivot = end;
        BahanBaku* prev = nullptr, *cur = head, *tail = pivot;

        while (cur != pivot) {
            if (cur->jumlahStok > pivot->jumlahStok) { // Sorting descending
                if (*newHead == nullptr) {
                    *newHead = cur;
                }
                prev = cur;
                cur = cur->next;
            } else {
                if (prev) prev->next = cur->next;
                BahanBaku* temp = cur->next;
                cur->next = nullptr;
                tail->next = cur;
                tail = cur;
                cur = temp;
            }
        }

        if (*newHead == nullptr)
            *newHead = pivot;

        *newEnd = tail;
        return pivot;
    }

    // Fungsi utama untuk quick sort (descending)
    BahanBaku* quickSortRecur(BahanBaku* head, BahanBaku* end) {
        if (!head || head == end) {
            return head;
        }

        BahanBaku *newHead = nullptr, *newEnd = nullptr;
        BahanBaku* pivot = partition(head, end, &newHead, &newEnd);

        if (newHead != pivot) {
            BahanBaku* temp = newHead;
            while (temp->next != pivot)
                temp = temp->next;
            temp->next = nullptr;

            newHead = quickSortRecur(newHead, temp);
            temp = getTail(newHead);
            temp->next = pivot;
        }

        pivot->next = quickSortRecur(pivot->next, newEnd);

        return newHead;
    }

    void sortDescending() {
        head = quickSortRecur(head, getTail(head));
        cout << "Daftar bahan baku telah diurutkan secara descending berdasarkan jumlah stok.\n";
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
             << bahan.satuan << " berada di posisi teratas stack\n";
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
        cout << bahan.namaBahan << " dengan stok " << bahan.jumlahStok 
             << " " << bahan.satuan << " ditambahkan ke queue\n";
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "Queue kosong\n";
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

    bool isEmpty() {
        return front == nullptr;
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
        cout << "11. Urutkan Bahan Ascending (Merge Sort)\n";
        cout << "12. Urutkan Bahan Descending (Quick Sort)\n";
        cout << "13. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string namaBahan, satuan;
                int stok;
                cout << "Masukkan nama bahan: ";
                cin >> namaBahan;
                cout << "Masukkan stok: ";
                cin >> stok;
                cout << "Masukkan satuan: ";
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
                cout << "Masukkan nama bahan yang stoknya ingin diubah: ";
                cin >> namaBahan;
                cout << "Masukkan stok baru: ";
                cin >> stokBaru;
                daftarBahan.updateStok(namaBahan, stokBaru);
                break;
            }
            case 4: {
                string namaBahan;
                cout << "Masukkan nama bahan yang ingin dihapus: ";
                cin >> namaBahan;
                daftarBahan.hapusBahan(namaBahan);
                break;
            }
            case 5: {
                string namaBahan, satuan;
                int stok;
                cout << "Masukkan nama bahan untuk stack: ";
                cin >> namaBahan;
                cout << "Masukkan stok: ";
                cin >> stok;
                cout << "Masukkan satuan: ";
                cin >> satuan;
                BahanBaku bahan = {namaBahan, stok, satuan, nullptr};
                stackBahan.push(bahan);
                break;
            }
            case 6:
                stackBahan.pop();
                break;
            case 7:
                stackBahan.peek();
                break;
            case 8: {
                string namaBahan, satuan;
                int stok;
                cout << "Masukkan nama bahan untuk queue: ";
                cin >> namaBahan;
                cout << "Masukkan stok: ";
                cin >> stok;
                cout << "Masukkan satuan: ";
                cin >> satuan;
                BahanBaku bahan = {namaBahan, stok, satuan, nullptr};
                queueBahan.enqueue(bahan);
                break;
            }
            case 9:
                queueBahan.dequeue();
                break;
            case 10:
                queueBahan.peek();
                break;
            case 11:
                daftarBahan.sortAscending();
                break;
            case 12:
                daftarBahan.sortDescending();
                break;
            case 13:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
    } while (pilihan != 13);

    return 0;
}
