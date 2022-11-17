#include <iostream>
#include <fstream>
#include <queue>
#include "ArgumentManager.h"
using namespace std;

int max(int a, int b) {
    if (a < b)
        return b;
    else
        return a;
}

struct node {
    int data;
    node* left;
    node* right;
    int height;
    node(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

class avlTree {
private:
  node* root;

public:
  avlTree() { root = nullptr; }

  void add(int data) { root = insert(root, data); }

  node* getRoot() { return root; }

    node* insert(node* t, int x) {
        if (t == nullptr)
            t = new node(x);
        else if (x < t->data) {
            t->left = insert(t->left, x);
            if (bFactor(t) == 2) {
                if (x < t->left->data)
                    t = singleRight(t);
                else
                    t = leftRight(t);
            }
        }
        else if (x > t->data) {
            t->right = insert(t->right, x);
            if (bFactor(t) == -2) {
                if (x > t->right->data)
                    t = singleLeft(t);
                else
                    t = rightLeft(t);
            }
        }
        t->height = max(height(t->left), height(t->right)) + 1;
        return t;
    }

    node* singleRight(node* t) {
        node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(u->left), height(u->right)) + 1;
        return u;
    }

    node* singleLeft(node* t) {
        node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->right), height(t->left)) + 1;
        u->height = max(height(u->right), height(u->left)) + 1;
        return u;
    }

    node* leftRight(node* t) {
        t->left = singleLeft(t->left);
        return singleRight(t);
    }

    node* rightLeft(node* t) {
        t->right = singleRight(t->right);
        return singleLeft(t);
    }

    int height(node* cu) {
        if (cu == nullptr)
            return -1;
        else
            return cu->height;
    }

    int bFactor(node* cu) {
        return (height(cu->left) - height(cu->right));
    }
    void levelOrder(ofstream &out, node* n){
      if(n != nullptr){
        queue<node*> q;
        q.push(n);
        while(!q.empty()){
          int levelSize = q.size();
          for(int i = 0; i < levelSize; i++){
            node* cu = q.front();
            q.pop();
            out << cu->data << " ";
            if(cu->left != nullptr)
              q.push(cu->left);
            if(cu->right != nullptr)
              q.push(cu->right);
          }
        }
      }
    }
};

int main(int argc, char *argv[]) {
  
  ArgumentManager am(argc, argv);
  ifstream in(am.get("input"));
  ofstream out(am.get("output"));
  /*
  ifstream input("input1.txt");
  ofstream out("output.txt");
  */
  int num,count;
  in >> count;
  avlTree new_tree;   

  while (count>0){
    in >> num;
    new_tree.add(num);
    count--;
  }

  new_tree.levelOrder(out, new_tree.getRoot());
  
  return 0;
}