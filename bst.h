#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.
		static Node<Key, Value>* successor(Node<Key, Value>* current);

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
		int calculateHeightIfBalanced(Node<Key, Value>* node) const;
		void noChildRemove(Node<Key, Value>* goal);
		void oneChildRemove(Node<Key, Value>* goal, int sideIndicate);
		void clearHelper(Node<Key, Value> *node);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
	current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
		current_ = NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
		return this->current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
		return this->current_ != rhs.current_;

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
		//find successor of current item
		iterator it =  iterator(BinarySearchTree<Key, Value>::successor(current_));
		*this = it;
		return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
		//call clear function to delete all nodes
		clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
		//if the tree is empty, set root to be the new key and value pair
		if(root_ == NULL){
			root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
			return;
		}
		//if the root is the only thing in the tree, insert
		//the new node as the right or left child appropriately
		if(root_->getLeft() == NULL && root_->getRight() == NULL){
			//if the new key is greater than the root_, right child
			if(keyValuePair.first > root_->getKey()){
				Node<Key, Value> *newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
				root_->setRight(newNode);
				newNode->setParent(root_);
			}
			//if the new key is less than the root_, left child
			if(keyValuePair.first < root_->getKey()){
				Node<Key, Value> *newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
				root_->setLeft(newNode);
				newNode->setParent(root_);
			}
			//if already in the tree, set the root's value to the new value
			if(keyValuePair.first == root_->getKey()){
				root_->setValue(keyValuePair.second);
			}
			return;
		}
		//if it is not the root, create a temp variable to store current loc
		Node<Key, Value> *temp = root_;
		Node<Key, Value>* potentialParent = temp;
		//while we haven't reached the end of the tree
		while(temp!=NULL){
			//if the new item is greater than the current node
			if(keyValuePair.first > temp->getKey()){
				//advance temp to its right child, advance parent to temp
				potentialParent = temp;
				temp = temp->getRight();
				//if temp was a leaf node (aka is null when it is advanced)
				//insert the new node as the right child of the leaf node
				if(temp == NULL){
					Node<Key, Value> *rightChild = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
					potentialParent->setRight(rightChild);
					rightChild->setParent(potentialParent);
					return;
				}
			}
			//if the new item is less than the current node
			else if(keyValuePair.first < temp->getKey()){
				//advance temp to its left child, advance parent to temp
				potentialParent = temp;
				temp = temp->getLeft();
				//if temp was a leaf node (aka is null when it is advanced)
				//insert the new node as the left child of the leaf node				
				if(temp == NULL){
					Node<Key, Value> *leftChild = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
					potentialParent->setLeft(leftChild);
					leftChild->setParent(potentialParent);
					return;
				}
			}
			//if already in tree, replace current value with new value
			else if(keyValuePair.first == temp->getKey()){
				temp->setValue(keyValuePair.second);
				return;
			}
		}
		return;


}

//helper function for 0 child remove case
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::noChildRemove(Node<Key, Value>* goal){
		Node<Key, Value> *goalParent = goal->getParent();
		Node<Key, Value> *goalrChild = goalParent->getRight();
		Node<Key, Value> *goallChild = goalParent->getLeft();
		//if node to be deleted is right child, set parent right to null
		if(goalrChild == goal){
			goalParent->setRight(NULL);
		}
		//if node to be deleted is left child, set parent left to null
		else if(goallChild == goal){
			goalParent->setLeft(NULL);
		}
		//delete and null node
		delete goal;
		goal = NULL;
		return;
}

//helper function for 1 child remove case
// 0 refers to a left child, 1 refers to a right child
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::oneChildRemove(Node<Key, Value>* goal, int sideIndicate){
		
		//if the node to remove is the root and it has a left child but no right
		if(goal->getKey() == root_->getKey() && sideIndicate == 0){
			//set the left child to be the new root and delete and null the old root
			root_ = root_->getLeft();
			root_->setParent(NULL);
			delete goal;
			goal = NULL;
			return;
		}
		//if the node to remove is the root and it has a right child but no left
		if(goal->getKey() == root_->getKey() && sideIndicate == 1){
			//set the right child to be the new root and delete and null the old root
			root_ = root_->getRight();
			root_->setParent(NULL);
			delete goal;
			goal = NULL;
			return;
		}
		
		Node<Key, Value> *goalChild;
		//if child is left, set goalChild left
		if(sideIndicate == 0){
			goalChild = goal->getLeft();
		}
		//if child is right, set goalChild right
		if(sideIndicate == 1){
			goalChild = goal->getRight();
		}

		//get goals parent, delete goal, promote goal node child to where goal used to be
		Node<Key, Value> *goalParent = goal->getParent();
		delete goal;
		goal = NULL;
		goalChild->setParent(goalParent);
		if(goalParent->getKey() < goalChild->getKey()){
			goalParent->setRight(goalChild);
		}
		else if(goalParent->getKey() > goalChild->getKey()){
			goalParent->setLeft(goalChild);
		}
		return;
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
		//if tree is empty return
		if(root_ == NULL){
			return;
		}
		//use internal find to look for 
		Node<Key, Value> *goal = internalFind(key);

		//if key is not in the tree, return
		if(goal == NULL){
			return;
		}
		//case 1, 0 children, delete node, null parent pointers
		if(goal->getLeft() == NULL && goal->getRight() == NULL){
			//if the node to be removed is the root
			if(goal->getKey() == root_->getKey()){
				root_ = NULL;
				delete goal;
				return;
			}
			else{
				noChildRemove(goal);
				return;
			}
		}
		//case 2, 1 child, promote its child to its position (promote NOT swap)
		//so delete intended node and set the orig parent pointer to child
		
		//if right child but no left child
		if(goal->getLeft() == NULL && goal->getRight() != NULL){
			oneChildRemove(goal, 1);
			return;
		}
		//if left child but no right child
		if(goal->getLeft() != NULL && goal->getRight() == NULL){
			oneChildRemove(goal, 0);
			return;
		}

		//case 3, 2 children, swap with predecessor, then do 0 or 1 child case
		if(goal->getLeft() != NULL && goal->getRight() != NULL){
			Node<Key, Value> *pred =  BinarySearchTree<Key, Value>::predecessor(goal);
			//if no predecessor, make the root the predecessor
			if(pred == NULL){
				pred = root_;
			}
			nodeSwap(goal, pred);

			//if no children, call noChild helper
			if(goal->getLeft() == NULL && goal->getRight() == NULL){
				noChildRemove(goal);
			}
			//if right child but no left child, call one child helper
			else if(goal->getLeft() == NULL && goal->getRight() != NULL){
				oneChildRemove(goal, 1);
			}
			//if left child but no right child, call one child helper
			else if(goal->getLeft() != NULL && goal->getRight() == NULL){
				oneChildRemove(goal, 0);
			}
			return;
		}

}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
		/*If left child exists, predecessor is the
		right most node of the left subtree
		• Else walk up the ancestor chain until you
		traverse the first right child pointer (find
		the first node who is a right child of his
		parent…that parent is the predecessor)
		– If you get to the root w/o finding a node
		who is a right child, there is no predecessor*/
	Node<Key, Value> *temp = current;

	//if empty, return null
	if(temp == NULL){
		return NULL;
	}
	//if left child exists, predecessor is right most node of left subtree
	if(temp->getLeft() != NULL){
		temp = temp->getLeft();
		while(temp->getRight() != NULL){
			temp = temp->getRight();
		}
		return temp;
	}
	//otherwise, walk up until you traverse right child pointer
	//aka where child is greater than parent
	else if(temp->getLeft() == NULL){
		while(temp->getParent() != NULL){
			//right child link
			if((temp->getParent())->getKey() < temp->getKey()){
				temp = temp->getParent();
				return temp;
			}
		}
	}
	return NULL;

}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
		/*If right child exists, successor is the
		left most node of the right subtree
		• Else walk up the ancestor chain until
		you traverse the first left child pointer
		(find the first node who is a left child
		of his parent…that parent is the
		successor)
		– If you get to the root w/o finding a node
		who is a left child, there is no successor*/
	Node<Key, Value> *temp = current;
	//if empty, return null
	if(temp == NULL){
		return NULL;
	}
	//if right child exist, successor is left most node of right subtree
	if(temp->getRight() != NULL){
		temp = temp->getRight();
		while(temp->getLeft() != NULL){
			temp = temp->getLeft();
		}
		return temp;
	}
	//otherwise walk up until you find a left child link
	//aka the child is smaller than the parent
	else if(temp->getRight() == NULL){
		while(temp->getParent() != NULL){
			//left child link
			if((temp->getParent())->getKey() > temp->getKey()){
				temp = temp->getParent();
				return temp;
			}
			temp = temp->getParent();
		}
	}
	return NULL;

}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value> *node){
	//base case, return when reach leaf node
	if(node == NULL){
		return;
	}
	
	//post order traversal, go to leaf nodes
	clearHelper(node->getLeft());
	clearHelper(node->getRight());

	//delete and null all nodes
	delete node;
	node = NULL;
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{	
		//call clearHelper function
		clearHelper(root_);

		root_ = NULL;

}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
		Node<Key, Value> *temp = root_;
		//if empty, return NULL
		if(temp == NULL){
			return NULL;
		}
		//otherwise go to the left most node of the tree which would be the smallest
		while(temp->getLeft() != NULL){
			temp = temp->getLeft();
		}
		return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
		//if empty, return
		if(root_ == NULL){
			return NULL;
		}
		//if the node to find is the root, return the root
		if(root_->getKey() == key){
			return root_;
		}
		Node<Key, Value> *temp = root_;
		//while we haven't reached the end of the tree
		while(temp != NULL){
			//if the key we want is greater than the current node, go right
			if(key > temp->getKey()){
				temp = temp->getRight();
			}
			// else if the key we want is less than the current node, go left
			else if(key < temp->getKey()){
				temp = temp->getLeft();
			}
			//else if the key is equal to the current node, return the current node
			else if(key == temp->getKey()){
				return temp;
			}
		}
		//if never found, return null
		return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	Node<Key, Value> *temp = root_;
	//call balance check helper that returns -1 if not balanced and height otherwise
  int height = calculateHeightIfBalanced(temp);
	//if returns -1, unbalanced, otherwise balanced
	if(height == -1){
		return false;
	}
	else{
		return true;
	}
}


template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::calculateHeightIfBalanced(Node<Key, Value>* node) const
{
  // Base case: an empty tree is always balanced and has a height of 0
	Node<Key, Value> *temp = node;
	if (temp == NULL) return 0;

	//if just a root node, height of 1
	if(temp->getLeft() == NULL && temp->getRight() == NULL){
		return 1;
	}
	//recurse left and right til hit base case
	int left = calculateHeightIfBalanced(temp->getLeft());
	int right = calculateHeightIfBalanced(temp->getRight());

	//if have returned -1 (aka unbalanced) previously, ensure continue to 
	//return -1 to signal unbalanced
	if(left == -1 || right == -1){
    return -1;
  }
	
	//if left and right subtree differ by more than one, not balanced, otherwise add
	//1 to the taller height to sum up height
	if(std::abs(left - right) > 1){
		return -1;
	}
	else{
		return std::max(left, right) + 1;
	}
}





template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
