#include <iostream>
using namespace std;

// 1. Düğüm yapısını şablon hale getirdik
template<class T>
class Node {
public:
    Node(const T &data = T(), Node<T> *next = NULL) : data(data), next(next) {}
    T data;
    Node<T> *next;
};

// 2. Liste sınıfını şablon hale getirdik
template<class T>
class list {
    Node<T>* root;
    Node<T>* tail;
    int length;

    Node<T>* findPrev(Node<T>* pos) {
        Node<T>* tmp = root;
        Node<T>* stop = end();
        while (tmp != stop && tmp->next != pos) {
            tmp = tmp->next;
        }
        return tmp;
    }

public:
    list() {
        length = 0;
        root = new Node<T>();
        tail = root;
        tail->next = new Node<T>();
    }

    // Parametreleri T tipine çevirdik
    list(int n, const T& value = T()) : list() {
        insert(end(), n, value);
    }

    list(Node<T>* first, Node<T>* last) : list() {
        while (first != last) {
            insert(end(), first->data);
            first = first->next;
        }
    }

    list(const list<T>& rhs) : list(rhs.begin(), rhs.end()) {}

    ~list() {
        clear();
        delete tail->next;
        delete tail;
    }

    list<T>& operator=(const list<T>& rhs) {
        return assign(rhs);
    }

    list<T>& assign(const list<T>& rhs) {
        clear();
        Node<T>* tmp = rhs.begin();
        while (tmp != rhs.end()) {
            push_back(tmp->data);
            tmp = tmp->next;
        }
        return *this;
    }

    Node<T>* begin() const { return root->next; }
    Node<T>* end() const { return tail->next; }

    bool isEmpty() const { return begin() == end(); }
    int size() const { return length; }

    // int olan tüm veri girişlerini T yaptık
    void push_back(const T& value) {
        insert(end(), value);
    }

    void push_front(const T& value) {
        insert(begin(), value);
    }

    void insert(Node<T>* pos, const T& value) {
        if (pos == end()) {
            tail->next = new Node<T>(value, end());
            tail = tail->next;
        } else {
            Node<T>* tmp = findPrev(pos);
            if (tmp == end()) {
                throw "Error";
            }
            tmp->next = new Node<T>(value, tmp->next);
        }
        length++;
    }

    void insert(Node<T>* pos, int n, const T& value) {
        for (int i = 0; i < n; i++) {
            insert(pos, value);
        }
    }

    void insert(Node<T>* pos, Node<T>* first, Node<T>* last) {
        while (first != last) {
            insert(pos, first->data);
            first = first->next;
        }
    }

    void erase(Node<T>* pos) {
        if (isEmpty()) throw "Error: List is empty";
        Node<T>* prev = root;
        if (pos == end() || pos == tail) {
            pos = tail;
            prev = findPrev(pos);
            prev->next = pos->next;
            tail = prev;
        } else {
            prev = findPrev(pos);
            if (prev == end()) throw "Error";
            prev->next = pos->next;
        }
        delete pos;
        length--;
    }

    void erase(Node<T>* first, Node<T>* last) {
        Node<T>* tmp;
        while (first != last) {
            tmp = first;
            first = first->next;
            erase(tmp);
        }
    }

    void clear() {
        erase(begin(), end());
    }

    Node<T>* find(const T& value) const {
        return find(begin(), value);
    }

    Node<T>* find(Node<T>* pos, const T& value) const {
        Node<T>* tmp = pos;
        Node<T>* stop = end();
        while (tmp != stop && tmp->data != value) {
            tmp = tmp->next;
        }
        return tmp;
    }

    void print() {
        Node<T>* tmp = begin();
        while (tmp != end()) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }

    T front() const {
        if (isEmpty()) throw "Error: front() empty";
        return begin()->data;
    }

    T back() const {
        if (isEmpty()) throw "Error: back() empty";
        return tail->data;
    }
};

int main() {
    // Liste artık int tipiyle çalışacak şekilde tanımlandı
    list<int> l; 
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(10);
    l.push_back(40);
    l.push_back(10);
    l.print();

    // Node<T> yerine Node<int> kullanıyoruz
    Node<int>* aranan = l.begin();
    Node<int>* tmp;
    
    while ((aranan = l.find(aranan, 10)) != l.end()) {
        tmp = aranan;
        aranan = aranan->next;
        cout << tmp << ":" << tmp->data << endl;
        l.erase(tmp);
    }
    l.print();

    return 0;
}