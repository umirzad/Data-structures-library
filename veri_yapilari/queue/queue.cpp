#include <iostream>
using namespace std;

template <class T>

class QueueNode{
    public: 
      T data;
      QueueNode<T>* next;
      QueueNode(const T& data=T(),QueueNode* next=NULL):data(data),next(next){  }


};

template<class T>
class Queue{
    QueueNode<T>* root;
    QueueNode<T>* tail;
    void makeEmpty(){
        while(!isEmpty()){
            dequeue();
        }
    }
    int length;
    public:
      Queue():root(NULL),tail(NULL),length(0){   }
      Queue(const Queue<T>& rhs):Queue<T>(){*this=rhs;}
      ~Queue(){
        makeEmpty();
      }
      Queue<T>& operator=(const Queue<T>& rhs){
        return assign(rhs);

      }
      Queue<T>& assign(const Queue<T>& rhs){
        makeEmpty();
        QueueNode<T>* tmp=rhs.root;
        while(tmp!=NULL){
            enqueue(tmp->data);
            tmp=tmp->next;
        }

        return *this;
      }

      bool isEmpty()const{return root==NULL;}
      void enqueue(const T& value){
        if(isEmpty()){
            root=new QueueNode<T>(value);
            tail=root;
        }else{
            tail->next=new QueueNode<T>(value);
            tail=tail->next;
        }
        length++;
      }

      void dequeue(){
        if(isEmpty()){
            throw "Error: Queue is empty";
        }
        QueueNode<T>* tmp=root;
        if(root==tail){
            tail=tmp->next;
        }
        root=root->next;
        delete tmp;
        length--;


      }

      int size()const{
        if(isEmpty()){
            throw "Error : Queue is empty";
        }
        return length;
      }


      T front()const{
        if(isEmpty()){
            throw "Error: Queue is empty";
        }
        return root->data;
      }


      T back()const{
        return tail->data;
      }
        


      void print()const{
        QueueNode<T>* tmp=root;
        while(tmp!=NULL){
            cout<<tmp->data<<" ";
            tmp=tmp->next;
        }
        cout<<endl;
      }
};





int main(){

    Queue <int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    Queue <int>q2;
    q2=q;
    q.dequeue();
    q.print();
    q2.print();
    






    return 0;
}