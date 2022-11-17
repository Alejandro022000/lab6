#include <iostream>
#include <fstream>
#include <queue>
#include "ArgumentManager.h"
using namespace std;

int find_max(int a, int b) {
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
        t->height = find_max(height(t->left), height(t->right)) + 1;
        return t;
    }

    node* singleRight(node* t) {
        node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = find_max(height(t->left), height(t->right)) + 1;
        u->height = find_max(height(u->left), height(u->right)) + 1;
        return u;
    }

    node* singleLeft(node* t) {
        node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = find_max(height(t->right), height(t->left)) + 1;
        u->height = find_max(height(u->right), height(u->left)) + 1;
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
    void levelOrder(ofstream &out, node* my_node){
      if(my_node == nullptr)
        return;      
      queue<node*> q;
      q.push(my_node);//enqueue
      while(q.empty()==false){
        int size = q.size();
        for(int i = 0; i < size; i++){
          node* temp = q.front();
          q.pop();
          if(temp==root){
          //cout << temp->data << " ";
          out << temp->data << " ";
          if(temp->left != NULL)//left child
            q.push(temp->left);
          if(temp->right != NULL)//right child
            q.push(temp->right);
          }
          else{
            out << " " << temp->data;
            if(temp->left != nullptr){
                q.push(temp->left);
            }
            if(temp->right != nullptr){
                q.push(temp->right);
            }
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