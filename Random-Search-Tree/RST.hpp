#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include <iostream>
#include <cstdlib>


using namespace std;

template <typename Data>
class RST : public BST<Data> {



public:

  /* Insert new data into the RST if it is not already present.
   * Input
   *    item - the data to insert.
   *    return - true if the item was inserted. If the item was already contained in
   *       the tree then return false.
   */
  virtual bool insert(const Data& item) {
    // TODO: Implement this function!
    //Call insert function in BST to insert item
    BSTNode<Data>* itemInserted = RSTinsert(item);
      //srand(time(0));
    itemInserted->priority = rand();
    // cout<<itemInserted->data<<"priority"<<itemInserted->priority<<endl;
      if (itemInserted == 0){
          cout<< "this node has been in the tree"<<endl;
          return false;
      }
      if (itemInserted->parent==0){//if itemInserted is root, return true

          //cout<<"Root inserted"<<endl;
          return true;
      }
      BSTNode<Data>* par = itemInserted->parent;// Because itemInserted is a leaf, we should get the parent of itemInserted and compare their priority
      
    while(par!=0 && itemInserted->priority > par->priority) {
        //cout<<"Rotation called"<<endl;
          if (itemInserted==par->left){
         	rotateRight(par,itemInserted);
          }
          else{
              rotateLeft(par,itemInserted);
          }
          par=itemInserted->parent;
      }

    
    return true;
  }

private:

  /* Perform a 'right rotation' that changes the structure of the tree without
   * interfering with the size, data content, and left->right order of nodes in the RST.
   * This rotation is done by changing the 'left', 'right', and/or 'parent' pointers
   * of a subset of nodes without changing their 'priority' values.
   *
   * Input
   *    par - a parent node in the RST with a left child
   *    child - the left child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order but switched
   *   in level, meaning 'par' will effectively become the right-child of 'child'.
   *
   */
  void rotateRight( BSTNode<Data>* par, BSTNode<Data>* child ) {
      
      BSTNode<Data>* ppar=par->parent; //record the parent of x

      int LOR=0; //initialize LeftOrRight
      if (ppar!=0){ // find the par is leftchild or rightchild
          if (par==ppar->left){ // if par is the left child of its parent
              LOR=1; //set LOR ==1, record the information that par is the left child of its parent
          }
          else{
              LOR=2;
          }
      }

    BSTNode<Data> * rightTree = child->right; //Get right subtree of *child
    child->right = par; //*par is the right child of *child
    par->parent = child; //*child is the parent of *par
    par->left = rightTree;//Reattach the right subtree as the left child of *par


      if (rightTree != 0){
          rightTree->parent = par;
      }//*par is the parent of *rightTree
       
      child->parent=ppar;
      
      if (LOR==1){// if original par is the left child of its parent
          ppar->left=child;// set current par which is the original child as the left child of the original par's parent
      }
      if (LOR==2){
          ppar->right=child;
      }
      if (LOR==0){
          BST<Data>::root=child;
      }

  }
  /* Perform a 'left rotation' that changes the structure of the tree without
   * interfering with the size, data content, and left->right order of nodes in the RST.
   * This rotation is done by changing the 'left', 'right', and/or 'parent' pointers
   * of a subset of nodes without changing their 'priority' values.
   *
   * Input
   *    par - a parent node in the RST with a right child
   *    child - the right child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order but switched
   *   in level, meaning 'par' will effectively become the left-child of 'child'.
   *
   */
  void rotateLeft( BSTNode<Data>* par, BSTNode<Data>* child ) {
    BSTNode<Data>* ppar=par->parent; //record the parent of x
      int LOR=0;
      if (ppar){
          if (par==par->parent->left){ // find the par is leftchild or rightchild
              LOR=1;
          }
          else{
              LOR=2;
          }
      }

    BSTNode<Data> * leftTree = child->left; //Get left subtree of *child
    child->left = par; //*par is the left child of *child
    par->parent = child; //*child is the parent of *par
    par->right = leftTree; //Reattach left subtree as the right child of *par

      
    if ( leftTree != 0)
	leftTree->parent = par; //*par is the parent of *leftTree

      child->parent=ppar;//if ppar is None, it's ok
      if (LOR==0){
          BST<Data>::root=child;
      }
      if (LOR==1){
          ppar->left=child;
      }
      if (LOR==2){
          ppar->right=child;
      }
  }

public:

  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   *
   * Calls BST::insert so we can add data to test rotateRight and rotateLeft before
   * implementing the fully correct version of RST::insert.
   *
   */
  bool BSTinsert(const Data& item) {

    return BST<Data>::insert(item);

  }


  BSTNode<Data>* RSTinsert(const Data& item) {

      if (RST<Data>::root== 0) {
    RST<Data>::root= new BSTNode<Data>(item);
          //cout<<"ROOOOOT"<<endl;
      return RST<Data>::root;
    }
    else {
      BSTNode<Data>* current = RST<Data>::root;
      BSTNode<Data>* last = 0;
      while ( current != 0 ) {
	if ( item < current->data ) {
	  last = current;
	  current = current->left;
	}
	else if ( current->data < item ) {
	  last = current;
	  current = current->right;
	}
	else {  // already in the tree
	  return 0;
	}
      }
      BSTNode<Data>* newNode = new BSTNode<Data>(item);
      if ( item < last->data ) {
	last->left = newNode;
	newNode->parent = last;
      }
      else {
	last->right = newNode;
	newNode->parent = last;
      }
      return newNode;
	
    }
  }

  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   *
   * Locates the node for an item and rotates it left or right without changing the
   * left->right order of nodes in the RST
   * Input
   *    item - the Data item to rotate.
   *    leftOrRight - if true then rotateLeft, otherwise rotateRight
   *    output - 0 if item could be found and had a child to rotate with, 1 if not. -1 if
   *         rotation failed for other reasons
   */
  int findAndRotate(const Data& item, bool leftOrRight) {

     BSTNode<Data>* current = RST<Data>::root;
     while ( current != 0 ) {
       if ( item < current->data ) {
         current = current->left;
       }
       else if ( current->data < item ) {
         current = current->right;
       }
       else {  // already in the tree
         break;
       }
     }

     if (current == 0 or current->data != item) {
       return 1;
     }

     if (leftOrRight) {
       if (current->right == 0) {
         return 1;
       }
       BSTNode<Data>* right = current->right;
       rotateLeft(current, current->right);

       // make sure we actually do a rotation
       if (current->right == right) {
         return -1;
       }

     } else {
       if (current->left == 0) {
         return 1;
       }
       BSTNode<Data>* left = current->left;
       rotateRight(current, current->left);

       // make sure we actually do a rotation
       if (current->left == left) {
         return -1;
       }
     }
     return 0;
  }
};
#endif // RST_HPP
