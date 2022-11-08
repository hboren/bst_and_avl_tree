#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
/// Calculates the height of the tree if it is balanced. Otherwise returns -1.
/// @param root The root of the tree to calculate height of
/// @return the height of the tree if its balanced, otherwise -1
int calculateEqualPaths(Node* root) {
	// Base case: an empty tree is always balanced and has a height of 0
	if (root == nullptr) return 0;

	// TODO: handle the cases here
	if(root->left == nullptr && root->right == nullptr){
		return 1;
	}    
    
	int left = calculateEqualPaths(root->left);
	int right = calculateEqualPaths(root->right);

    if(left == -1 || right == -1){
        return -1;
    }

    if(root->left != nullptr && root->right == nullptr){
		return left + 1;
	}
	if(root->left == nullptr && root->right != nullptr){
		return right + 1;
	}   
	
    //need a case to handle if they both don't exist
    if(root->left == nullptr && root->right != nullptr){
        return right + 1;
    }


	if(left != right){
		return -1;
	}
	else{
		if(left >= right){
            return left + 1;
        }
        else{
            return right + 1;
        }
	}
	
}

bool equalPaths(Node * root)
{
    // Add your code below
    if(root == nullptr){
        return true;
    }
    if(root->left == nullptr && root->right == nullptr){
        return true;
    }
    int height = calculateEqualPaths(root);

    if(height == -1){
        return false;
    }
    else{
        return true;
    }

}

