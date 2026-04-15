#include <iostream>

using namespace std;
template <class T>
class TreeNode
{
public:
    int data;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode(T data =T(), TreeNode<T> *left = NULL, TreeNode<T> *right = NULL)
        : data(data), left(left), right(right) {}
};
enum MOD
{
    PREORDER,
    INORDER,
    POSTORDER
};

template <class T>
class BinarySearchTree
{
    TreeNode<T> *root;
    TreeNode<T> *insert(TreeNode<T> *start, T data)
    {
        if (start)
        {
            if (data < start->data)
            {
                start->left = insert(start->left, data);
            }
            else
            {
                start->right = insert(start->right, data);
            }
        }
        else
        {
            return new TreeNode<T>(data);
        }
        return start;
    }
    TreeNode<T> *mirror(TreeNode<T> *start)
    {
        if (start)
        {
            mirror(start->left);
            mirror(start->right);
            TreeNode<T> *temp = start->left;
            start->left = start->right;
            start->right = temp;
        }

        return start;
    }

    TreeNode<T> *find(TreeNode<T> *start, T data)
    {
        if (start)
        {
            if (data < start->data)
            {
                return find(start->left, data);
            }
            else if (start->data < data)
            {
                return find(start->right, data);
            }
        }

        return start;
    }

    void clear(TreeNode<T> start){
        if(start){
            clear(start.left)
        }
    }

public:
    BinarySearchTree(TreeNode<T> *root = NULL) : root(root) {}
    bool isEmpty() const { return root == NULL; }
    TreeNode<T> *getRoot() const { return root; }

    TreeNode<T> *find(T data, bool last = false)
    {
        TreeNode<T> *before = find(root, data);
        TreeNode<T> *after = before;
        if (last)
        {
            while (before && (before == find(before->right, data)))
            {
                after = before;
            }
        }
        return after;
    }

    void insert(T data)
    {
        root = insert(root, data);
    }
    TreeNode<T> * getMin(TreeNode<T> *start)
    {
        while (start && start->left)
        {
            start = start->left;
        }
        return start;
    }

    TreeNode<T> *getMin()
    {
        return getMin(root);
    }

    TreeNode<T> *getMax(TreeNode<T> *start)
    {
        while (start && start->right)
        {
            start = start->right;
        }
        return start;
    }

    TreeNode<T> *getMax()
    {
        return getMax(root);
    }

    int height(TreeNode<T> *node)
    {
        if (node)
        {
            int left = height(node->left);
            int right = height(node->right);
            return 1 + max(left, right);
        }
        else
        {
            return -1;
        }
    }

    TreeNode<T> *remove(TreeNode<T> *start, TreeNode<T> *deleted)
    {
        if (start)
        {
            if (deleted->data < start->data)
            {
                start->left = remove(start->left, deleted);
            }
            else if (start->data < deleted->data)
            {
                start->right = remove(start->right, deleted);
            }
            else if (start == deleted)
            {

                TreeNode<T> *temp = NULL;
                if (start->left && start->right)
                {
                    temp = getMin(start->right);
                    remove(start, temp);
                    temp->left = start->left;
                    temp->right = start->right;
                }
                else if (start->left)
                {
                    temp = start->left;
                }
                else if (start->right)
                {
                    temp = start->right;
                }
                return temp;
            }
            else
            {

                start->right = remove(start->right, deleted);
            }

            return start;
        }
    }

    void remove(TreeNode<T> *node)
    {
        if (node)
        {
            root = remove(root, node);
            delete node;
        }
    }

    void remove(T data, bool last = false)
    {
        remove(find(data, last));
    }

    int height()
    {
        return height(root);
    }

    int depth(TreeNode<T> *start, TreeNode<T> *finish)
    {
        if (start)
        {
            if (start == finish)
            {
                return 0;
            }
            int left = depth(start->left, finish);
            int right = depth(start->right, finish);
            return 1 + max(left, right);
        }
        else
        {
            return INT_MIN;
        }
    }

    int depth(TreeNode<T> *finish)
    {
        return depth(root, finish);
    }

    void preOrder(TreeNode<T> *start)
    {
        if (start)
        {
            cout << start->data << " ";
            preOrder(start->left);
            preOrder(start->right);
        }
    }

    void inOrder(TreeNode<T> *start)
    {
        if (start)
        {
            inOrder(start->left);
            cout << start->data << " ";
            inOrder(start->right);
        }
    }

    void postOrder(TreeNode<T> *start)
    {
        if (start)
        {
            postOrder(start->left);
            postOrder(start->right);
            cout << start->data << " ";
        }
    }

    void print(MOD mod)
    {
        switch (mod)
        {
        case PREORDER:
            preOrder(root);
            break;
        case INORDER:
            inOrder(root);
            break;
        case POSTORDER:
            postOrder(root);
            break;
        }

        if (!isEmpty())
        {
            cout << endl;
        }
    }

    void mirror()
    {
        root = mirror(root);
    }

    bool isBalanced(TreeNode<T>*  start){
        if(!start) return true;

        int leftH=height(start->left);
        int rightH=height(start->right);

        if(abs(leftH-rightH)<=1 && isBalanced(start->left)&&isBalanced(start->right)){
            return true;
        }

        return false;

    }

    bool isBlanced(){return isBalanced(root);}


    bool isFull(TreeNode<T>* start){
        if(!start) return true;

        if(!start->left && !start->right) return true;

        if(start->left && start->right){
            return isFull(start->left) && isFull(start->right);
        }

        return false;
    }

    bool isFull(){return isFull(root)};
};

int main()
{

    BinarySearchTree <int> bst;
    bst.insert(20);
    bst.insert(5);
    bst.insert(10);
    bst.insert(15);
    bst.insert(3);
    bst.insert(37);
    bst.insert(30);
    bst.insert(50);
    bst.insert(1);

    bst.print(PREORDER);
    bst.print(INORDER);
    bst.print(POSTORDER);

    cout << endl;

    cout << "mirror" << endl;

    bst.mirror();
    cout << endl;

    bst.print(PREORDER);
    bst.print(INORDER);
    bst.print(POSTORDER);

    return 0;
}
