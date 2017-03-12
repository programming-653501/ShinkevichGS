/* Программа создает два бинарных дерева поиска, которые юзер заполняет целыми числами
	и сливает их в одно, исключая повторяющиеся элементы */
/* Обход деревьев осуществляется симметричным способом */
/* version 1.0 */


#include <iostream>
using namespace std;

void keep_window_open()
{
	cin.clear();
	cin.ignore(0xFFFFFFFF, '\n');
	cin.get();
}

struct Node
{
	int data;
	Node *left;
	Node *right;
};

Node* AddNode(int data)
{
	Node* newNode = new Node();
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

bool Search(Node* root, int data)
{
	if (root == NULL)
		return false;
	else if (root->data == data)
		return true;
	else if (data <= root->data)
		return Search(root->left, data);
	else
		return Search(root->right, data);

}

Node* Insert(Node* root, int data)
{
	if (Search(root, data) == false)
	{
		if (root == NULL)
			root = AddNode(data);
		else if (data <= root->data)
			root->left = Insert(root->left, data);
		else
			root->right = Insert(root->right, data);
	}
		return root;
}

void Inorder(Node* root)
{
	if (root == NULL)
		return;
	Inorder(root->left);
	cout << root->data << " ";
	Inorder(root->right);
}

void Merge(Node *&root1, Node *&root2)
{
	if (root1->left != NULL)
		Merge(root1->left, root2);
	if (root1->right != NULL)
		Merge(root1->right, root2);
	if (Search(root2, root1->data) == false)
	{
		Insert(root2, root1->data);
	}
	delete root1;
	root1 = NULL;

}

int main()
{
	Node* root1 = NULL;
	Node* root2 = NULL;

	cout << "Fill the first binary tree with integers ('s' to stop filling): ";
	int num1;
	while (cin >> num1)
		root1 = Insert(root1, num1);

	cin.clear();
	cin.ignore(0xFFFFFFFF, '\n');

	cout << "Fill the second binary tree with integers ('s' to stop filling): ";
	int num2;
	while (cin >> num2)
		root2 = Insert(root2, num2);

	if (root1 != NULL && root2 != NULL)
	{
		cout << "First tree: ";
		Inorder(root1);
		cout << endl;

		cout << "Second tree: ";
		Inorder(root2);
		cout << endl;

		Merge(root1, root2);
		cout << "Merged tree: ";
		Inorder(root2);
		cout << endl;
	}
	else
		cout << "Empty tree was detected!" << endl;

	keep_window_open();
	return 0;
}
