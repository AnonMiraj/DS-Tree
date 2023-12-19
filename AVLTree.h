#include<iostream>
#include <queue>


template<class T>
struct AVLNode
{
	T data;
	AVLNode* left;
	AVLNode* right;
	int height;
};
template<class T>
class AVLTree {
public:
	AVLNode<T>* root = NULL;
	// Unit of help functions for insertion and deletion
	int GetHight(AVLNode<T>* p) {
		int hl, hr;
		hl = (p && p->left) ? p->left->height : 0;
		hr = (p && p->right) ? p->right->height : 0;

		return hl > hr ? hl + 1 : hr + 1;

		// Note we get the hight by calc the backwards hights make the max and + 1 to the new level
	}
	int getbalance(AVLNode<T>* node) {
		int hl, hr;
		hl = node && node->left ? node->left->height : 0;
		hr = node && node->right ? node->right->height : 0;

		return hl - hr;

	}
	int max(int a, int b)
	{
		return (a > b) ? a : b;
	}
	   

	//help functions on deletions
	AVLNode<T>* InPre(AVLNode<T>* p) {
		while (p && p->right != nullptr) {
			p = p->right;
		}
		return p;
	}
	AVLNode<T>* InSucc(AVLNode<T>* p) {
		while (p && p->left != nullptr) {
			p = p->left;
		}
		return p;
	}

	// For rotations
	AVLNode<T>* LLRotation(AVLNode<T>* p) {
		// p is a node that is impalance
		AVLNode<T>* left_p = p->left; // this node will be the parent "root" 
		AVLNode<T>* right_left_p = p->left->right; // will be the left of p"root"

		p->left = right_left_p;
		left_p->right = p;

		// then modify the hights
		// right_left_p its hight not changed
		p->height = GetHight(p);
		left_p->height = GetHight(left_p);

		if (root == p)
			root = left_p;

		return left_p; // new root
	}
	AVLNode<T>* LRRotation(AVLNode<T>* p)
	{
		// 4 assin links should be done 
		int lbf, rbf;

		AVLNode<T>* pl = p->left;
		AVLNode<T>* plr = pl->right;

		p->left = plr->right;
		pl->right = plr->left;

		plr->left = pl;
		plr->right = p;

		// modify hights
		pl->height = GetHight(pl);
		p->height = GetHight(p);
		plr->height = GetHight(plr);

		if (p == root)root = plr;
		return plr;
	}

	AVLNode<T>* RRRotation(AVLNode<T>* p) {
		AVLNode<T>* pr = p->right;
		AVLNode<T>* prl = pr->left;

		pr->left = p;
		p->right = prl;

		// Update height
		p->height = GetHight(p);
		pr->height = GetHight(pr);

		// Update root
		if (root == p) {
			root = pr;
		}
		return pr;
	}
	AVLNode<T>* RLRotation(AVLNode<T>* p) {
		AVLNode<T>* pr = p->right;
		AVLNode<T>* prl = pr->left;

		pr->left = prl->right;
		p->right = prl->left;

		prl->right = pr;
		prl->left = p;

		// Update height
		pr->height = GetHight(pr);
		p->height = GetHight(p);
		prl->height = GetHight(prl);

		// Update root
		if (root == p) {
			root = prl;
		}
		return prl;
	}



	// For Display
	void preOrder(AVLNode<T>* root)
	{
		if (root != NULL)
		{
			std::cout << root->data << " ";
			preOrder(root->left);
			preOrder(root->right);
		}
	}
	void Levelorder(AVLNode<T>* p) {
		std::queue<AVLNode<T>*> q;
		std::cout << p->data << " ";
		q.push(p);
		while (!q.empty()) {
			p = q.front();
			q.pop();
			if (p->left) {
				std::cout << p->left->data << " ";
				q.push(p->left);
			}
			if (p->right) {
				std::cout << p->right->data << " ";
				q.push(p->right);
			}

		}
	}
	void Inorder(AVLNode<T>* p) {
		if (p) {
			Inorder(p->left);
			std::cout << p->data << ", ";
			Inorder(p->right);
		}
	}


	AVLNode<T>* insert(AVLNode<T>* node, T key)
	{
		/*normal BST insertion*/
		AVLNode<T>* t = NULL;
		if (node == NULL) {
			t = new AVLNode;
			t->data = key;
			t->height = 1;
			t->left = t->right = NULL;
			return t; // return the created node to assign the suit position 
		}
		if (key < node->data) {
			// go to the left
			//cout << key << "   ";
			node->left = insert(node->left, key);
		}
		else if (key > node->data) {
			// right 
			// note : insert rerurn an created new node :
			node->right = insert(node->right, key);
		}
		else { // Equal keys are not allowed in BST  
			return node;
		}

		// here after insert each node its hight will be changed so i should update hight 
		// max bett hl , hr ,,, get the hight of node by taking the max (hight of its child) + 1
		node->height = GetHight(node);// +1 the cuurent node


		//after we get all nodes hight updated we calc the balance factor of each node at return time
		int balanceFactor = getbalance(node);
		/* after get the balance factor of current node we must chcek balanced
		 4 cases (LL,RR,LR,RL)
		 1 . LL


			Rotations only applied on 3 nodes
			suppose we have 3 nodes and sign of node 1 + "left", and node 2 + it mean we insert at left of node 2
			" then it LL rotation "

			node 1 + , node 2 - => LR rotation (mean we insert at the right of the node 2)
			conclusion :
				BF > 1 ,left is bigger
				BF < -1 , right branch is bigger
		*/
		if (balanceFactor > 1) {
			// mean this node what i stand on it "impalance"
			if (key < node->left->data) {
				// we can do it (balance factor(node) == 2 && balance factor(node->left) == 1)
				// LL case 
				return LLRotation(node);
			}
			else if (key > node->left->data) {
				// LR case
				return LRRotation(node);
			}
		}
		else if (balanceFactor < -1) {
			if (key > node->right->data) {
				//RR case 
				return RRRotation(node);
			}
			else if (key < node->right->data) {
				//RL case
				//return RLRotation();
			}
		}
		return node;
	}
	AVLNode<T>* Delete(AVLNode<T>* p, T key) {
		if (p == nullptr) {
			return nullptr;
		}
		// this is normal bst deletion 
		if (p->left == nullptr && p->right == nullptr) {
			// no child
			if (p == root) {
				// if this node is the tree root
				root = nullptr;
			}
			delete p;
			return nullptr;
		}
		if (key < p->data) {
			p->left = Delete(p->left, key);
		}
		else if (key > p->data) {
			p->right = Delete(p->right, key);
		}
		// untill here we dont found the key
		else { // oh we found the node which be deleted 
			// the avl tree work start from here 
			AVLNode<T>* q;
			if (GetHight(p->left) > GetHight(p->right)) {
				q = InPre(p->left);
				p->data = q->data;
				p->left = Delete(p->left, q->data);
			}
			else {
				q = InSucc(p->right);
				p->data = q->data;
				p->right = Delete(p->right, q->data);
			}
		}

		// Update height
		p->height = GetHight(p);

		// after update the hight and delete the node we should look for if the deleted node 
		// cause imbalance in the tree and rotate if true (the same in inserting) GH :)
		
		int balanceFactor = getbalance(p);//for each node in return time
			

		if (balanceFactor > 1) {
			// mean this node what i stand on it "impalance"
			if (key < p->left->data) {
				// we can do it (balance factor(node) == 2 && balance factor(node->left) == 1)
				// LL case 
				return LLRotation(p);
			}
			else if (key > p->left->data) {
				// LR case
				return LRRotation(p);
			}
		}
		else if (balanceFactor < -1) {
			if (key > p->right->data) {
				//RR case 
				return RRRotation(p);
			}
			else if (key < p->right->data) {
				//RL case
				return RLRotation(p);
			}
		}
		return p;
	}
	AVLNode<T>* search(AVLNode<T>* root, T key)
	{
		if (root == NULL || root->data == key)
			return root;

		if (root->data < key)
			return search(root->right, key);

		// Key is smaller than root's key
		return search(root->left, key);
	}
};
