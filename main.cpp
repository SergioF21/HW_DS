#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template<typename T>
struct Node{
    int parent;
    int rank;
    T data;
};

class DisjoinSet
{
public:
    virtual ~DisjoinSet(){};
    virtual void MakeSet(int x)=0;
    virtual int Find(int x)=0;
    virtual void Union(int x, int y)=0;

    virtual bool isConnected(int x, int y)=0;
};

template<typename T>
class DisjoinSetTree : public DisjoinSet{
private:
    Node<T>*nodes;
    int size;
public:
    DisjoinSetTree(T* data, int n){
        size=n;
        nodes= new Node<T>[size];
        for(int i=0; i<size; i++){
            MakeSet(i);
            nodes[i].data=data[i];
        }
    }
    ~DisjoinSetTree() override{
        delete[] nodes;
    };
    void MakeSet(int x) override {
        nodes[x].parent=x;
        nodes[x].rank=0;
    }
    int Find(int x) override{
        if(x==nodes[x].parent)
            return x;
        else
            return Find(nodes[x].parent);
    }
    void Union(int x, int y) override{
        int xRoot=Find(x);
        int yRoot=Find(y);

        if(xRoot == yRoot){
            return;
        }
       if(nodes[xRoot].rank > nodes[yRoot].rank)
            nodes[yRoot].parent=xRoot;
       else if((nodes[xRoot].rank) < (nodes[yRoot].rank))
            nodes[xRoot].parent=yRoot;
        else
        {
            nodes[yRoot].parent=xRoot;
            nodes[xRoot].rank++;
        }

    };
    bool isConnected(int x, int y) override{
        return Find(x)==Find(y);
    };
};

template <typename T>
class DisjoinSetArray: public DisjoinSet{
private:

    int* parents;
    int* ranks;
    T* data;
    int size;
public:
    DisjoinSetArray(T* data, int n){
        size = n;
        parents = new int[size];
        ranks = new int[size];
        this->data = new T[size];
        for(int i=0; i<size; i++){
            MakeSet(i);
            this->data[i]=data[i];
        }
    };
    ~DisjoinSetArray() override{
        delete[] parents;
    };
    void MakeSet(int x) override{
        parents[x]=x;
        ranks[x]=0;
    }
    int Find(int x) override{
        if(x==parents[x]){
            return x;
        }
        else{
            return Find(parents[x]);
        }
    }
    void Union(int x, int y) override{
        int xRoot=Find(x);
        int yRoot=Find(y);

        if(xRoot==yRoot){
            return;
        }
        if(ranks[xRoot] < ranks[yRoot])
            parents[xRoot] = yRoot;
        else if(ranks[xRoot] > ranks[yRoot])
            parents[yRoot] = xRoot;
        else{
            parents[yRoot]=xRoot;
            ranks[xRoot]++;
        }
    }
    bool isConnected(int x, int y) override{
        return Find(x)==Find(y);
    }
};

void test(){

  int n = 5;
  int data[] = {1, 2, 3, 4, 5};

  DisjoinSetTree<int> treeSet(data, n);
  DisjoinSetArray<int> arraySet(data, n);

  treeSet.Union(0, 1);
  treeSet.Union(1, 2);
  treeSet.Union(3, 4);

  arraySet.Union(0, 1);
  arraySet.Union(1, 2);
  arraySet.Union(3, 4);

  assert(treeSet.isConnected(0, 2) == true);
  assert(treeSet.isConnected(3, 4) == true);
  assert(arraySet.isConnected(0, 2) == true);
  assert(arraySet.isConnected(3, 4) == true);
}

int main() {
  test();
  return 0;
}
