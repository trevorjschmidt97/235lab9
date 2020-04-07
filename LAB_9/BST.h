#ifndef BST_H
#define BST_H
//#include "BSTInterface.h"
#include <string>
#include <sstream>

using namespace std;

/** A binary tree node with data, left and right child pointers */
template<typename T>
class BST
{
private:

	struct BstNode
	{
		T data;
		BstNode* left;
		BstNode* right;

		BstNode(T d) : data(d), left(NULL), right(NULL) {}
	};
	BstNode* root = NULL;

	size_t size = 0;

	void infix(BstNode* localNode, stringstream& ss)
	{
		if (localNode == NULL)
		{
			return;
		}
		infix(localNode->left, ss);
		ss << localNode->data << ",";
		infix(localNode->right, ss);
	}

	bool treeContains(BstNode* localRoot, const T& item) {
		// Return true if item is one of the items in the binary
		// sort tree to which root points.   Return false if not.
		if (localRoot == NULL) {
			// Tree is empty, so it certainly doesn't contain item.
			return false;
		}
		else if (item == localRoot->data) {
			// Yes, the item has been found in the root node.
			return true;
		}
		else if (item < localRoot->data) {
			// If the item occurs, it must be in the left subtree.
			return treeContains(localRoot->left, item);
		}
		else {
			// If the item occurs, it must be in the right subtree.
			return treeContains(localRoot->right, item);
		}
	}  // end treeContains()

	bool insert(BstNode*& localRoot, const T& item)
	{
		if (localRoot == NULL)
		{
			++size;
			localRoot = new BstNode(item);
			
			return true;
		}
		else
		{
			if (item < localRoot->data)
			{
				return insert(localRoot->left, item);
			}
			else if (localRoot->data < item)
			{
				return insert(localRoot->right, item);
			}
			else
			{
				return false;
			}
		}
	}

	bool remove(BstNode*& localRoot, const T& item)
	{
		if (localRoot == NULL) // if the root is NULL
		{
			return false; // The item is not in tree - return NULL.
		}

		else // Compare the item to the data at the local root
		{
			if (item < localRoot->data) // if the item is less than the data at the local root
			{
				return remove(localRoot->left, item); // Return the result of deleting from the left subtree.
			}
			else if (localRoot->data < item) // Else if the item is greater than the local root.
			{
				return remove(localRoot->right, item); // Return the result of deleting from the right subtree
			}
			else // The item is in the local root
			{
				if (localRoot->right == NULL && localRoot->left == NULL) // if the local root has no children
				{
					--size;
					delete localRoot;
					localRoot = NULL; // Set the parent of the local root to reference NULL.
					return true;
				}
				else if (localRoot->right != NULL && localRoot->left == NULL) //else if the local root has right child and no left
				{
					BstNode* temp = localRoot;
					localRoot = localRoot->right;
					--size;
					delete temp; //Set the parent of the local root to reference that child
					return true;
				}
				else // else if there's a left child (find the inorder predecessor)
				{
					if (localRoot->left->right == NULL) //if the left child has no right child,
					{                                   //it is the inorder predecessor
						BstNode* temp = localRoot;
						localRoot = localRoot->left;
						localRoot->right = temp->right;
						--size;
						delete temp; //Set the parent of the local root to reference the left child.
					}
					else //Else
					{
						BstNode* inOrderPredParent = localRoot->left;
						while (inOrderPredParent->right->right != NULL) //Find the righmost node in the right subtree of the left child.
						{
							inOrderPredParent = inOrderPredParent->right;
						}
						localRoot->data = inOrderPredParent->right->data; //Copy its data into the local root's data

						BstNode* temp = inOrderPredParent->right; // and remove it by setting its parent to reference the local root's left child.
						inOrderPredParent->right = inOrderPredParent->right->left;

						--size;
						delete temp;
					}
					return true;
				}
			}
		}
	}

	bool outLevel(BstNode* localRoot, int level, stringstream& out) const
	{
		if (localRoot == NULL) return false;
		if (level == 0)
		{
			out << " " << localRoot->data;
			if ((localRoot->left != NULL) || (localRoot->right != NULL)) return true;
			return false;
		}
		if ((level == 1) && localRoot->left == NULL && localRoot->right != NULL) out << " _";
		bool left = outLevel(localRoot->left, level - 1, out);
		bool right = outLevel(localRoot->right, level - 1, out);
		if ((level == 1) && localRoot->left != NULL && localRoot->right == NULL) out << " _";
		return left || right;
	}

public:
	BST(void)
	{
		root = NULL;
	}
	~BST(void) 
	{
		clearTree();
	}

	/** Return true if node added to BST, else false */
	bool addNode(const T& item)
	{
		return insert(this->root, item);
	}

	/** Return true if node removed from BST, else false */
	bool removeNode(const T& item)
	{
		return remove(this->root, item);
	}

	/** Return true if BST cleared of all nodes, else false */
	bool clearTree()
	{
		while (root != NULL)
		{
			remove(this->root, this->root->data);
		}
		size = 0;
		return true;
	}

	size_t findNode(const T& item)
	{
		if (treeContains(this->root, item))
		{
			return 0;
		}
		return 1;
	}

	string iterTree() const
	{
		if (size == 0)
		{
			return "empty";
		}

		return "Finish tree thing";
	}

	/** Return a level order traversal of a BST as a string */
	string toString()
	{
		stringstream ss;

		infix(root, ss);
		string line = ss.str();

		int length = line.length();

		return line.substr(0, length - 1);
	}

	size_t getSize()
	{
		return size;
	}

}; // End BST_H

template<typename T>
ostream& operator<<(ostream& out, const BST<T>& tree)
{
	return out << tree.toString();
}

#endif	

