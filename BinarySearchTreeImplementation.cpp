#include<iostream>
using namespace std;
class node{
public:
int data;
node* right;
node* left;
node(int value){
data=value;
right=NULL;
left=NULL;
}
};
class BinarySearchTree{
public:
void insert(node* &root,int data){
node* n = new node(data);
node* temp = root;
if(root==NULL){
    root=n;
}
else{
while(temp!=NULL){
    if(temp->data<data){
        if(temp->right==NULL){
            temp->right=n;
            return;
        }
        temp=temp->right;
    }
if(temp->data>data){
if(temp->left==NULL){
    temp->left=n;
    return;
}
temp=temp->left;
}
}
}
}
void display(node* root)
{
   
    if (root != NULL)
     {
        display(root->left);
        cout<<root->data<<" ";
        display(root->right);
    }
}
void lookUp(node* root,int key)
{
if(root==NULL){
    cout<<"Nothing to search";
}
node* temp=root;
if(key==temp->data){
    cout<<"Found";
    return;
}
else{

    while(temp){
        if(key>temp->data){
            temp=temp->right;
            if(key==temp->data){
                cout<<"found";
                return;
                
            }
        }
        if(key<temp->data){
            temp=temp->left;
            if(key==temp->data){
                cout<<"found";
                return;
            }
        }

    }
}

}
};
int main()
{
 BinarySearchTree bst;
 node* root=NULL;
 bst.insert(root,4);
  bst.insert(root,5);
 bst.insert(root,6);
 bst.insert(root,7);
 bst.insert(root,8);
 bst.insert(root,2);

 bst.display(root);
 bst.lookUp(root,8);
  return 0;
}
