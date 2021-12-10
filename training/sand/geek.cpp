/** C++ implementation for
Red-Black Tree Insertion
This code is adopted from
the code provided by
Dinesh Khandelwal in comments **/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using pll=pair<ll, ll>;
#define rep(i,n) for (ll i=0; i<n; ++i)
#define all(c) begin(c),end(c)

enum Color {RED, BLACK};

struct Node
{
	int data;
	bool color;
	Node *left, *right, *parent;

	// Constructor
	Node(int data)
	{
	this->data = data;
	left = right = parent = NULL;
	this->color = RED;
	}
};

// Class to represent Red-Black Tree
class RBTree
{
private:
	Node *root;
protected:
	void rotateLeft(Node *&, Node *&);
	void rotateRight(Node *&, Node *&);
	void fixViolation(Node *&, Node *&);
public:
	// Constructor
	RBTree() { root = NULL; }
	void insert(const int &n);
	void inorder();
	void levelOrder();
	void debug();
};

void dfs(Node *r, string path){
	if(r->left) dfs(r->left, path+'l');
	if(r->right) dfs(r->right, path+'r');
	reverse(all(path));
	cout << "M[" << r->data << "]:";
	if(r->color) cout << "B";
	else cout << "R";
	cout << " " << path << endl;
}

void RBTree::debug(){
	dfs(root, "");
}

// A recursive function to do inorder traversal
void inorderHelper(Node *root)
{
	if (root == NULL)
		return;

	inorderHelper(root->left);
	cout << root->data << " ";
	inorderHelper(root->right);
}

/* A utility function to insert
	a new node with given key


/*
           DUMMY(R): 0x7ffe5ab13d08
             +       |     right: 7
             |       +     left: 1
     [ROOT] 2(B): 0x1892500
              right: 4
              left: 1
             /       \
   1(B): 0x18924d0     4(R): 0x1892560
     right: 0            right: 6
     left: 0             left: 3
                         /      \
             3(B): 0x1892530     6(B): 0x18925c0
              right: 0             right: 7
              left: 0              left: 5
                                  /       \
                        5(R): 0x1892590    7(R): 0x18925f0
                          right: 0            right: 0
                          left: 0             left: 0


4.5を入れるとしたら？
root=2
4.5>2 

root=4
4.5>4

root=6
4.5<6

root=5
4.5<5

root=NULL

(root=5) // かわるのはここだけ。
5->left = 4.5 (NULL->4.5)
4.5->parent = 5

(root=6)
6->left = 5 (5->5)
5->parent = 6 (6->6)

...

insert(7)
insert(6)
root:7 pt:6
insert(5)
root:7 pt:5
root:6 pt:5
insert(3)
root:6 pt:3
root:5 pt:3
insert(2)
root:6 pt:2
root:5 pt:2
root:3 pt:2
insert(1)
root:6 pt:1
root:3 pt:1
root:2 pt:1
insert(4)
root:6 pt:4
root:3 pt:4
root:5 pt:4
in BST */
Node* BSTInsert(Node* root, Node *pt)
{
	/* If the tree is empty, return a new node */
	if (root == NULL)
	return pt;

//	cout << "root:" << root->data << " pt:" << pt->data << endl;
	/* Otherwise, recur down the tree */
	if (pt->data < root->data)
	{
		root->left = BSTInsert(root->left, pt);
		root->left->parent = root;
	}
	else if (pt->data > root->data)
	{
		root->right = BSTInsert(root->right, pt);
		root->right->parent = root;
	}

	/* return the (unchanged) node pointer */
	return root;
}

// Utility function to do level order traversal
void levelOrderHelper(Node *root)
{
	if (root == NULL)
		return;

	std::queue<Node *> q;
	q.push(root);

	while (!q.empty())
	{
		Node *temp = q.front();
		cout << temp->data << " ";
		q.pop();

		if (temp->left != NULL)
			q.push(temp->left);

		if (temp->right != NULL)
			q.push(temp->right);
	}
}

void RBTree::rotateLeft(Node *&root, Node *&pt)
{
	Node *pt_right = pt->right;

	pt->right = pt_right->left;

	if (pt->right != NULL)
		pt->right->parent = pt;

	pt_right->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_right;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;

	else
		pt->parent->right = pt_right;

	pt_right->left = pt;
	pt->parent = pt_right;
}

void RBTree::rotateRight(Node *&root, Node *&pt)
{
	Node *pt_left = pt->left;

	pt->left = pt_left->right;

	if (pt->left != NULL)
		pt->left->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_left;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;

	else
		pt->parent->right = pt_left;

	pt_left->right = pt;
	pt->parent = pt_left;
}

// This function fixes violations
// caused by BST insertion
void RBTree::fixViolation(Node *&root, Node *&pt)
{
	Node *parent_pt = NULL;
	Node *grand_parent_pt = NULL;

	while ((pt != root) && (pt->color != BLACK) &&
		(pt->parent->color == RED)) // 根っこじゃない、かつ赤赤が続いてる
	{
		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		/*
		   Case : A
			Parent of pt is left child of Grand-parent of pt
			ptの親はptの祖父母の左の子になります
              B grand_parent
		     /
            R parent
		    |
            R
		*/
		if (parent_pt == grand_parent_pt->left)
		{

			Node *uncle_pt = grand_parent_pt->right;

			/* Case : 1
			The uncle of pt is also red
			Only Recoloring required
			
			叔父も赤なら、色を変えるだけ
              B grand_parent
		     / \
     Parent R   R uncle
		    |
	        R
			*/
			if (uncle_pt != NULL && uncle_pt->color == RED) {
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else
			{
				/* Case : 2
				pt is right child of its parent
				Left-rotation require
				いったんptを左につけかえる

                      B grand_parent
        		     / \
             Parent R   B uncle
        		     \
        	          R
				*/
				if (pt == parent_pt->right)
				{
					rotateLeft(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				pt is left child of its parent
				Right-rotation required */
				rotateRight(root, grand_parent_pt);
				swap(parent_pt->color,
						grand_parent_pt->color);
				pt = parent_pt;
			}
		}

		/* Case : B
		Parent of pt is right child
		of Grand-parent of pt */
		else
		{
			Node *uncle_pt = grand_parent_pt->left;

			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if ((uncle_pt != NULL) && (uncle_pt->color ==
													RED))
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else
			{
				/* Case : 2
				pt is left child of its parent
				Right-rotation required */
				if (pt == parent_pt->left)
				{
					rotateRight(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				pt is right child of its parent
				Left-rotation required */
				rotateLeft(root, grand_parent_pt);
				swap(parent_pt->color,
						grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}

	root->color = BLACK;
}

// Function to insert a new node with given data
void RBTree::insert(const int &data)
{
	cout << "insert(" << data << ")" << endl;
	// nodeを作る
	Node *pt = new Node(data);

	// Do a normal BST insert
	root = BSTInsert(root, pt);

	// fix Red Black Tree violations
	fixViolation(root, pt);
}

// Function to do inorder and level order traversals
void RBTree::inorder()	 { inorderHelper(root);}
void RBTree::levelOrder() { levelOrderHelper(root); }

// Driver Code
int main()
{
	RBTree tree;

	rep(i, 7){
		tree.insert(i+1);
		tree.debug();
	}

	cout << "Inorder Traversal of Created Tree\n";
	tree.inorder();

	cout << "\n\nLevel Order Traversal of Created Tree\n";
	tree.levelOrder();

	return 0;
}
