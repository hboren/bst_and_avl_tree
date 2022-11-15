#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    virtual void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node);
    virtual void removeFix(AVLNode<Key, Value>* node, int diff); 
		virtual void rotateRight(AVLNode<Key, Value>* origParent);
		virtual void rotateLeft(AVLNode<Key, Value>* origParent);
		AVLNode<Key, Value>* internalFind(const Key& k) const;
		void noChildRemove(AVLNode<Key, Value> *node);
		void oneChildRemove(AVLNode<Key, Value> *node, int sideIndicate);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
		//if the root is null, insert the new node as the root
    if(this->root_ == NULL){
        AVLNode<Key, Value> *node = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        this->root_ = node;
        return;
    }
		AVLNode<Key, Value> *temp = static_cast<AVLNode<Key, Value>*>(this->root_);
		AVLNode<Key, Value>* potentialParent = temp;
		//otherwise, while we haven't reached the end of the tree
		while(temp!=NULL){
			//if the new item is greater than the current node
			if(new_item.first > temp->getKey()){
				//advance temp to its right child, advance parent to temp
				potentialParent = temp;
				temp = temp->getRight();
				//if temp was a leaf node (aka is null when it is advanced)
				//insert the new node as the right child of the leaf node
				//and update the balances appropriately
				if(temp == NULL){
					AVLNode<Key, Value> *rightChild = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
					potentialParent->setRight(rightChild);
					rightChild->setParent(potentialParent);
					if(potentialParent->getBalance() == -1)
						potentialParent->setBalance(0);
					else if(potentialParent->getBalance() == 1)
						potentialParent->setBalance(0);
					else if(potentialParent->getBalance() == 0){
						potentialParent->setBalance(1);
						insertFix(potentialParent, rightChild);
					}
					return;
				}
			}
			//otherise if the new item is less than the current node
			else if(new_item.first < temp->getKey()){
				//advance temp to its left child, advance parent to temp
				potentialParent = temp;
				temp = temp->getLeft();
				//if temp was a leaf node (aka is null when it is advanced)
				//insert the new node as the left child of the leaf node	
				//and update the balances appropriately			
				if(temp == NULL){
					AVLNode<Key, Value> *leftChild = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
					potentialParent->setLeft(leftChild);
					leftChild->setParent(potentialParent);
					if(potentialParent->getBalance() == -1)
						potentialParent->setBalance(0);
					else if(potentialParent->getBalance() == 1)
						potentialParent->setBalance(0);
					else if(potentialParent->getBalance() == 0){
						potentialParent->setBalance(-1);
						insertFix(potentialParent, leftChild);
					}
					return;
				}
			}
			//else if already in tree, replace current value with new value
			else if(new_item.first == temp->getKey()){
				temp->setValue(new_item.second);
				return;
			}
		}
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
  AVLNode<Key, Value> *target = internalFind(key);
	//if target node not found, return
  if(target == NULL){
    return;
  }
	AVLNode<Key, Value> *parent = target->getParent();
	AVLNode<Key, Value> *pred = NULL;
	int diff = 0;
	//calculate difference (aka what balance change will be depending on
	//whether a left node or right node is being removed)
	if(parent != NULL){
		AVLNode<Key, Value> *parentLeft = parent->getLeft();
		AVLNode<Key, Value> *parentRight = parent->getRight();
		//if target is a left child
		if(parentLeft == target){
			diff = 1;
		}
		else if(parentRight == target){
			diff = -1;
		}
	}
	//target has zero children case
	//if the target is the root, delete and set the root to null
	if(target->getLeft() == NULL && target->getRight() == NULL){
		if(target == this->root_){
			delete target;
			this->root_ = NULL;
		}
		//otherwise call helper
		else{
			noChildRemove(target);
		}
	}
	//target has one children, check and call helper
	//if right child but no left child,
	else if(target->getLeft() == NULL && target->getRight() != NULL){
		oneChildRemove(target, 1);
	}
	//if left child but no right child
	else if(target->getLeft() != NULL && target->getRight() == NULL){
		oneChildRemove(target, 0);
	}
	//target has two children
	else if(target->getLeft() != NULL && target->getRight() != NULL){
			//get predecessor
			pred = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(target));
			//if no predecessor, make the root the predecessor
			if(pred == NULL){
				pred = static_cast<AVLNode<Key, Value>*>(this->root_);
			}
			//swap target with predecessor
			nodeSwap(target, pred);
			parent = target->getParent();
			//calculate difference for next call depending on if right or left child
			if(parent != NULL){
				AVLNode<Key, Value> *swapLeft = parent->getLeft();
				AVLNode<Key, Value> *swapRight = parent->getRight();
				//if target is a left child
				if(swapLeft == target){
					diff = 1;
				}
				else if(swapRight == target){
					diff = -1;
				}
			}

			//if no children, call noChild helper
			if(target->getLeft() == NULL && target->getRight() == NULL){
				noChildRemove(target);
			}
			//if right child but no left child, call one child helper
			else if(target->getLeft() == NULL && target->getRight() != NULL){
				oneChildRemove(target, 1);
			}
			//if left child but no right child, call one child helper
			else if(target->getLeft() != NULL && target->getRight() == NULL){
				oneChildRemove(target, 0);
			}
	}
	//if the target node had a parent, aka not the root, call removeFix
	//with the parent
	if(parent != NULL){
		removeFix(parent, diff);
	}
	//otherwise if it was the root and there was a predecessor 
	//(aka target was not the only node) call removeFix with predecessor
	else if(pred != NULL){
		removeFix(pred, 1);
	}

}
	 


template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* origParent){
		//take a left child, make it the parent, 
		//make the original parent the new right child
		//store right subtree of new parent and make it the left subtree of 
		//original parent
		
		//if given node is null, return
		if(origParent == NULL)
			return;
		
		AVLNode<Key, Value> *grandparent = origParent->getParent();
		AVLNode<Key, Value> *grandLeft;
		AVLNode<Key, Value> *grandRight;

		//if there is a grandparent, get its left and right child
		if(grandparent != NULL){
			grandRight = grandparent->getRight();
			grandLeft = grandparent->getLeft();
		}

		AVLNode<Key, Value> *leftChild = origParent->getLeft();
		//if there is no left child, done, return, nothing to rotate with
		if(leftChild == NULL){
			return;
		}
		AVLNode<Key, Value> *temp = leftChild->getRight();
		//make left child the new parent, set pointers appropriately
		leftChild->setRight(origParent);
		leftChild->setParent(origParent->getParent());
		// if origParent was a right child, set the node we are rotating's parent's
		//right child to origParents left child
		if(leftChild->getParent() != NULL && (origParent == grandRight)){
			leftChild->getParent()->setRight(leftChild);
		}
		//otherwise do the same but for its left child link
		else if(leftChild->getParent() != NULL && (origParent == grandLeft)){
			leftChild->getParent()->setLeft(leftChild);
		}
		origParent->setParent(leftChild);
		origParent->setLeft(temp);
		//if temp, aka left childs right tree exists, set its parent to the
		//node we were rotating
		if(temp != NULL)
			temp->setParent(origParent);

}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* origParent){
		//TODO
		//take right child, make it the new parent, make original parent
		//the new left child, store the left subtree of new parent
		//make that the right subtree of the old parent
		
		//if given node is null, return
		if(origParent == NULL){
			return;
		}

		AVLNode<Key, Value> *grandparent = origParent->getParent();
		AVLNode<Key, Value> *grandLeft;
		AVLNode<Key, Value> *grandRight;

		//if there is a grandparent, get its left and right child
		if(grandparent != NULL){
			grandLeft = grandparent->getLeft();
			grandRight = grandparent->getRight();
		}

		//if there is no right child, done, return, nothing to rotate with
		AVLNode<Key, Value> *rightChild = origParent->getRight();
		if(rightChild == NULL){
			return;
		}
		//make right child the new parent, set pointers appropriately
		AVLNode<Key, Value> *temp = rightChild->getLeft();
		rightChild->setLeft(origParent);
		rightChild->setParent(origParent->getParent());
		// if origParent was a left child, set the node we are rotating's parent's
		//left child to origParents right child
		if(rightChild->getParent() != NULL && (origParent == grandLeft)){
			rightChild->getParent()->setLeft(rightChild);
		}
		//otherwise do the same but for its right child link
		else if(rightChild->getParent() != NULL && (origParent == grandRight)){
			rightChild->getParent()->setRight(rightChild);
		}
		origParent->setParent(rightChild);
		origParent->setRight(temp);
		//if temp, aka right childs left tree exists, set its parent to the
		//node we were rotating
		if(temp != NULL)
			temp->setParent(origParent);
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node){
		//if parent or grandparent is null, return
		if(parent == NULL || parent->getParent() == NULL){
			return;
		}
		AVLNode<Key, Value> *preserve_grandparent = parent->getParent();
		AVLNode<Key, Value> *grandparent = parent->getParent();
		AVLNode<Key, Value> *grandLeft = grandparent->getLeft();
		AVLNode<Key, Value> *grandRight = grandparent->getRight();
		AVLNode<Key, Value> *parentLeft = parent->getLeft();
		AVLNode<Key, Value> *parentRight = parent->getRight();
		//if parent is left child of grandparent
		if(grandLeft == parent){
			grandparent->updateBalance(-1);
			//case 1, grand balance is 0
			if(grandparent->getBalance() == 0)
				return;
			//case 2, grand balance is -1
			else if(grandparent->getBalance() == -1)
				insertFix(grandparent, parent);
			//case 3, grand balance is -2
			else if(grandparent->getBalance() == -2){
				//if zig zig (left left) rotate right on grandparent
				if(parentLeft == node){
					rotateRight(grandparent);
					grandparent->setBalance(0);
					parent->setBalance(0);
					if(this->root_ == preserve_grandparent){
						this->root_ = parent;
					}
				}
				//if zig zag (left right) rotate left on parent then right on grand
				else if(parentRight == node){
					rotateLeft(parent);
					rotateRight(grandparent);
					if(this->root_ == preserve_grandparent){
						this->root_ = node;
					}
					if(node->getBalance() == -1){
						grandparent->setBalance(1);
						parent->setBalance(0);
						node->setBalance(0);
					}
					else if(node->getBalance() == 0){
						grandparent->setBalance(0);
						parent->setBalance(0);
						node->setBalance(0);
					}
					else if(node->getBalance() == 1){
						grandparent->setBalance(0);
						parent->setBalance(-1);
						node->setBalance(0);
					}
				}
			}
		}
		//if parent is right child of grandparent
		if(grandRight == parent){
			grandparent->updateBalance(1);
			//case 1, grand balance is 0
			if(grandparent->getBalance() == 0)
				return;
			//case 2, grand balance is -1
			else if(grandparent->getBalance() == 1)
				insertFix(grandparent, parent);
			//case 3, grand balance is -2
			else if(grandparent->getBalance() == 2){
				//if zig zig (right right) rotate left on grandparent
				if(parentRight == node){
					rotateLeft(grandparent);
					grandparent->setBalance(0);
					parent->setBalance(0);
					if(this->root_ == preserve_grandparent){
						this->root_ = parent;
					}
				}
				//if zig zag (right left)	rotate right on parent then left on grand			
				else if(parentLeft == node){
					rotateRight(parent);
					rotateLeft(grandparent);
					if(this->root_ == preserve_grandparent){
						this->root_ = node;
					}
					if(node->getBalance() == 1){
						grandparent->setBalance(-1);
						parent->setBalance(0);
						node->setBalance(0);
					}
					else if(node->getBalance() == 0){
						grandparent->setBalance(0);
						parent->setBalance(0);
						node->setBalance(0);
					}
					else if(node->getBalance() == -1){
						grandparent->setBalance(0);
						parent->setBalance(1);
						node->setBalance(0);
					}
				}
			}
		}

}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node, int diff){
    //if input in null return
		if(node == NULL){
			return;
		}
		AVLNode<Key,Value> *parent = node->getParent();
		int ndiff = 0;
		//if there is a parent, get new diff based on if removed was left or right child
		if(parent != NULL){
			AVLNode<Key, Value> *parentLeft = parent->getLeft();
			if(node == parentLeft){
				ndiff = 1;
			}
			else{
				ndiff = -1;
			}
		}
		//case 1 left: if the balalnce is -2, aka left tree is larger
		if((node->getBalance() + diff) == -2){
			AVLNode<Key, Value>* child = node->getLeft();
			//case 1a: child balance is -1 zig-zig: rotate right on node
			//call removeFix with its parent
			if(child->getBalance() == -1){
				rotateRight(node);
				if(this->root_ == node){
					this->root_ = node->getParent();
				}
				node->setBalance(0);
				child->setBalance(0);
				removeFix(parent, ndiff);
			}
			//case 1b: child balance is 0 zig-zig: rotate right on node and return
			else if(child->getBalance() == 0){
				rotateRight(node);
				if(this->root_ == node){
					this->root_ = node->getParent();
				}
				node->setBalance(-1);
				child->setBalance(1);
				return;
			}
				//case 1c: child balance is 1 zig-zag: rotate left on child, right on 
				//parent, set pointers and balances appropriately, call removeFix on parent
			else if(child->getBalance() == 1){
				AVLNode<Key, Value>* grandchild = child->getRight();
				rotateLeft(child);
				rotateRight(node);
				if(this->root_ == node){
					this->root_ = grandchild;
				}
				if(grandchild->getBalance() == 1){
					node->setBalance(0);
					child->setBalance(-1);
					grandchild->setBalance(0);
				}
				else if(grandchild->getBalance() == 0){
					node->setBalance(0);
					child->setBalance(0);
					grandchild->setBalance(0);
				}
				else if(grandchild->getBalance() == -1){
					node->setBalance(1);
					child->setBalance(0);
					grandchild->setBalance(0);
				}
				removeFix(parent, ndiff);
			}
		}
		//case 2: b(n) + diff == -1: set balance to -1 and return
		else if((node->getBalance() + diff) == -1){
			node->setBalance(-1);
			return;
		}
		//case 3: b(n) + diff == 0: set balance to 0 and recurse with parent
		else if((node->getBalance() + diff) == 0){
			node->setBalance(0);
			removeFix(parent, ndiff);
		}
		//case 1 right: if the balalnce is 2, aka right tree is larger
		else if((node->getBalance() + diff) == 2){
			AVLNode<Key, Value>* child = node->getRight();
			//case 1a: child balance is 1 zig-zig, rotate left on node, recurse parent
			if(child->getBalance() == 1){
				rotateLeft(node);
				if(this->root_ == node){
					this->root_ = child;
				}
				node->setBalance(0);
				child->setBalance(0);
				removeFix(parent, ndiff);
			}
			//case 1b: child balance is 0 zig-zig, rotate left on node, return
			else if(child->getBalance() == 0){
				rotateLeft(node);
				if(this->root_ == node){
					this->root_ = child;
				}
				node->setBalance(1);
				child->setBalance(-1);
				return;
			}
			//case 1c: child balance is 1 zig-zag, rotate left child, right node
			//set balances appropriately, recurse with parent
			else if(child->getBalance() == -1){
				AVLNode<Key, Value>* grandchild = child->getLeft();
				rotateRight(child);
				rotateLeft(node);
				if(this->root_ == node){
					this->root_ = grandchild;
				}
				if(grandchild->getBalance() == -1){
					node->setBalance(0);
					child->setBalance(1);
					grandchild->setBalance(0);
				}
				else if(grandchild->getBalance() == 0){
					node->setBalance(0);
					child->setBalance(0);
					grandchild->setBalance(0);
				}
				else if(grandchild->getBalance() == 1){
					node->setBalance(-1);
					child->setBalance(0);
					grandchild->setBalance(0);
				}
				removeFix(parent, ndiff);
			}
		}
		//case 2: b(n) + diff == 1, set balance to 1 and return
		else if((node->getBalance() + diff) == 1){
			node->setBalance(1);
			return;
		}
		//set balance to 0 and recurse
		else if((node->getBalance() + diff) == 0){
			node->setBalance(0);
			removeFix(parent, ndiff);
		}


}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::internalFind(const Key& k) const{
		//if empty, return
		if(this->root_ == NULL){
			return NULL;
		}
		//if the node to find is the root, return the root
		if(this->root_->getKey() == k){
			return static_cast<AVLNode<Key, Value>*>(this->root_);
		}
		AVLNode<Key, Value> *temp = static_cast<AVLNode<Key, Value>*>(this->root_);
		//while we haven't reached the end of the tree
		while(temp != NULL){
			//if the key we want is greater than the current node, go right
			if(k > temp->getKey()){
				temp = temp->getRight();
			}
			// else if the key we want is less than the current node, go left
			else if(k < temp->getKey()){
				temp = temp->getLeft();
			}
			//else if the key is equal to the current node, return the current node
			else if(k == temp->getKey()){
				return static_cast<AVLNode<Key, Value>*>(temp);
			}
		}
		//if never found, return null
		return NULL;	
}

template<class Key, class Value>
void AVLTree<Key, Value>::noChildRemove(AVLNode<Key, Value> *node){
		AVLNode<Key, Value> *goalParent = node->getParent();
		AVLNode<Key, Value> *goalrChild = goalParent->getRight();
		AVLNode<Key, Value> *goallChild = goalParent->getLeft();
		//if node to be deleted is right child, set parent right to null
		if(goalrChild == node){
			goalParent->setRight(NULL);
		}
		//if node to be deleted is left child, set parent left to null
		else if(goallChild == node){
			goalParent->setLeft(NULL);
		}
		//delete and null node
		delete node;
		node = NULL;
		return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::oneChildRemove(AVLNode<Key, Value> *node, int sideIndicate){
//if the node to remove is the root and it has a left child but no right
		if(node->getKey() == this->root_->getKey() && sideIndicate == 0){
			//set the left child to be the new root and delete and null the old root
			this->root_ = this->root_->getLeft();
			this->root_->setParent(NULL);
			delete node;
			node = NULL;
			return;
		}
		//if the node to remove is the root and it has a right child but no left
		if(node->getKey() == this->root_->getKey() && sideIndicate == 1){
			//set the right child to be the new root and delete and null the old root
			this->root_ = this->root_->getRight();
			this->root_->setParent(NULL);
			delete node;
			node = NULL;
			return;
		}
		
		AVLNode<Key, Value> *goalChild;
		//if child is left, set goalChild left
		if(sideIndicate == 0){
			goalChild = node->getLeft();
		}
		//if child is right, set goalChild right
		if(sideIndicate == 1){
			goalChild = node->getRight();
		}

		//get goals parent, delete goal, promote goal node child to where goal used to be
		AVLNode<Key, Value> *goalParent = node->getParent();
		delete node;
		node = NULL;
		goalChild->setParent(goalParent);
		if(goalParent->getKey() < goalChild->getKey()){
			goalParent->setRight(goalChild);
		}
		else if(goalParent->getKey() > goalChild->getKey()){
			goalParent->setLeft(goalChild);
		}
		return;
}




template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
