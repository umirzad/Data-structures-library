#include <iostream>
using namespace std;

template <class T>
class StackNode
{
public:
    T data;
    StackNode<T> *next;
    StackNode(const T &data = T(), StackNode<T> *next = NULL) : data(data), next(next) {}
};

template <class T>
class Stack
{
    StackNode<T> *root;
    int length;
    void makeEmpty()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

public:
    Stack() : root(NULL), length(0) {}
    Stack(const Stack<T> &rhs) : Stack()
    {
        *this = rhs;
    }
    ~Stack()
    {
        makeEmpty();
    }
    StackNode<T> *begin() const { return root; }
    StackNode<T> *end() const { return NULL; }
    bool isEmpty() const
    {
        return begin() == end();
    }

    Stack<T> &operator=(const Stack<T> &rhs)
    {
        return assign(rhs);
    }
    Stack<T> &assign(const Stack<T> &rhs)
    {
        if (this == &rhs)
            return *this;

        makeEmpty();
        length = 0;

        if (!rhs.isEmpty())
        {
            root = new StackNode<T>(rhs.top());
            length = 1;

            StackNode<T> *rhsTmp = rhs.begin()->next;
            StackNode<T> *lhsTmp = root;

            while (rhsTmp != rhs.end())
            {
                lhsTmp->next = new StackNode<T>(rhsTmp->data);
                lhsTmp = lhsTmp->next;
                rhsTmp = rhsTmp->next;
                length++;
            }
        }
        return *this;
    }

    void push(const T &value)
    {
        StackNode<T> *tmp = new StackNode<T>(value, root);
        root = tmp;
        length++;
    }

    T top() const
    {
        if (isEmpty())
        {
            throw "Error : Stack is empty";
        }

        return begin()->data;
    }

    int size() const
    {
        return length;
    }

    void pop()
    {
        if (isEmpty())
        {
            throw "Error: Stack is empty";
        }
        StackNode<T> *tmp = root;
        root = root->next;
        delete tmp;
        length--;
    }

    void print() const
    {
        StackNode<T> *tmp = begin();
        while (tmp != end())
        {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
};

int main()
{
    Stack<int> s1;
    s1.push(10);
    s1.push(11);
    s1.push(12);
    s1.print();

    Stack<int> s2 = s1;

    cout << "s1 begin:" << s1.begin() << endl;
    cout << "s2 begin:" << s2.begin() << endl;

    s1.begin()->data = 5;

    s1.print();
    s2.print();

    return 0;
}