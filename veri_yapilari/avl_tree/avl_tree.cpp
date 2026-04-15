#include <iostream>


using namespace std;

template <class T>
class AVLNode {
public:
    T data;
    AVLNode<T> *left;
    AVLNode<T> *right;

    AVLNode(T data = T(), AVLNode<T> *left = NULL, AVLNode<T> *right = NULL)
        : data(data), left(left), right(right) {}
};

template <class T>
class AVL {
private:
    AVLNode<T> *root;

    int height(AVLNode<T> *node) const {
        if (node == NULL) return 0;
        return max(height(node->left), height(node->right)) + 1;
    }

    int getBalanceFactor(AVLNode<T> *node) const {
        if (node == NULL) return 0;
        return height(node->left) - height(node->right);
    }

    AVLNode<T>* ll_rotate(AVLNode<T>* node) {
        AVLNode<T>* tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        return tmp;
    }

    AVLNode<T>* rr_rotate(AVLNode<T>* node) {
        AVLNode<T>* tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        return tmp;
    }

    AVLNode<T>* lr_rotate(AVLNode<T>* node) {
        node->left = rr_rotate(node->left);
        return ll_rotate(node);
    }

    AVLNode<T>* rl_rotate(AVLNode<T>* node) {
        node->right = ll_rotate(node->right);
        return rr_rotate(node);
    }

    AVLNode<T>* getMin(AVLNode<T>* node) {
        AVLNode<T>* current = node;
        while (current->left != NULL) current = current->left;
        return current;
    }

    AVLNode<T>* insert(AVLNode<T>* node, T data) {
        if (node == NULL) return new AVLNode<T>(data);

        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);
        else
            return node;

        int balance = getBalanceFactor(node);

        if (balance > 1 && data < node->left->data)
            return ll_rotate(node);

        if (balance < -1 && data > node->right->data)
            return rr_rotate(node);

        if (balance > 1 && data > node->left->data)
            return lr_rotate(node);

        if (balance < -1 && data < node->right->data)
            return rl_rotate(node);

        return node;
    }

    AVLNode<T>* remove(AVLNode<T>* node, T data) {
        if (node == NULL) return node;

        if (data < node->data)
            node->left = remove(node->left, data);
        else if (data > node->data)
            node->right = remove(node->right, data);
        else {
            if ((node->left == NULL) || (node->right == NULL)) {
                AVLNode<T> *temp = node->left ? node->left : node->right;
                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                } else
                    *node = *temp;
                delete temp;
            } else {
                AVLNode<T>* temp = getMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }

        if (node == NULL) return node;

        int balance = getBalanceFactor(node);

        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return ll_rotate(node);

        if (balance > 1 && getBalanceFactor(node->left) < 0)
            return lr_rotate(node);

        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return rr_rotate(node);

        if (balance < -1 && getBalanceFactor(node->right) > 0)
            return rl_rotate(node);

        return node;
    }

    AVLNode<T>* find(AVLNode<T>* node, T data) const {
        if (node == NULL || node->data == data) return node;
        if (data < node->data) return find(node->left, data);
        return find(node->right, data);
    }

    void clear(AVLNode<T>* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void inOrder(AVLNode<T>* node) const {
        if (node) {
            inOrder(node->left);
            cout << node->data << " ";
            inOrder(node->right);
        }
    }

public:
    AVL() : root(NULL) {}

    ~AVL() {
        clear(root);
    }

    void insert(T data) {
        root = insert(root, data);
    }

    void remove(T data) {
        root = remove(root, data);
    }

    bool find(T data) const {
        return find(root, data) != NULL;
    }

    int height() const {
        return height(root);
    }

    void print() const {
        inOrder(root);
        cout << endl;
    }
};

int main() {
   
    return 0;
}