#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;
struct Node // вузол дерева
{
	Node* left,
		* right;
	int info;
};
struct Elem // елемент стеку,
{ // в якому зберігаються
	Elem* link; // батьківські вузли
	Node* info;
};
Node* CreateTree(int nodeCount);
void PrintTree(Node* root, int level);
void SaveToFile(fstream& f, Node* root);
void LoadFromFile(fstream& f, Node*& root);
void RightRotation(Node*& root);
void LeftRotation(Node*& root);
int Height(Node* root);
int BFactor(Node* root);
void BalanceHeight(Node*& root);
int CountLevels(Node* root);
std::vector<int> sumOfLevels(Node* root);
int help(Node* root);
int sumLeftSubtree(Node* root);
int sumRightSubtree(Node* root);

void Push(Elem*& top, Node* node);
Node* Pop(Elem*& top);

int main()
{
	
	Node* root;
	fstream f;
	
	f.open("C:/Student/tree.txt", ios::in);
	LoadFromFile(f, root);
	f.close();
	BalanceHeight(root);
	PrintTree(root, 0);
	int k = CountLevels(root);
	cout << "amount of tree levels: " << k << endl;
	vector<int> sums = sumOfLevels(root);

	// Print level sums
	cout << "Level sums: ";
	for (int sum : sums) {
		cout << sum << " ";
	}
	cout << endl;

	int m = sumRightSubtree(root);
	cout << "Sum of right subtree: ";
	cout << m << " ";
	cout << endl;

	int n = sumLeftSubtree(root);
	cout << "Sum of left subtree: ";
	cout << n << " ";
	cout << endl;

	return 0;
}
Node* CreateTree(int nodeCount)
{
	if (nodeCount == 0)
		return NULL;
	else
	{
		Node* newNode = new Node;
		cout << " Enter node value: ";
		cin >> newNode->info;

		int leftCount = nodeCount / 2;
		int rightCount = nodeCount - leftCount - 1;
		newNode->left = CreateTree(leftCount);
		newNode->right = CreateTree(rightCount);
		return newNode;
	}
}
void PrintTree(Node* root, int level)
{
	if (root != NULL)
	{
		PrintTree(root->right, level + 1);
		for (int i = 1; i <= level; i++)
			cout << " ";
		cout << root->info << endl;
		PrintTree(root->left, level + 1);
	}
}
void SaveToFile(fstream& f, Node* root)
{
	if (root != NULL)
	{
		f << root->info << endl;
		SaveToFile(f, root->left);
		SaveToFile(f, root->right);
	}
	else
		f << "<END>" << endl;
}
void LoadFromFile(fstream& f, Node*& root)
{
	Node* newNode, * current;
	Elem* top = NULL;
	int c;
	if (!(f >> c)) // 1
	{
		root = NULL;
		return;
	}
	current = new Node; // 2
	current->info = c;
	current->left = NULL;
	current->right = NULL;
	root = current; // 2.1

	Push(top, current); // 2.2
	do
	{
			while (f >> c && c != NULL) // 3 
			{
				newNode = new Node;
				newNode->info = c;
				newNode->left = NULL;
				newNode->right = NULL;
				current->left = newNode; // 3.1
				current = current->left; // 3.2

				Push(top, current); // 3.3
			}

		while (f >> c)
			if (c == NULL) // 4
			{
				if (top != NULL)
					current = Pop(top); // 4.1
			}
			else
				break;
		if (f.eof()) break;
		if (top != NULL) // 5
		{
			current = Pop(top); // 5.1
			newNode = new Node;
			newNode->info = c;
			newNode->left = NULL;
			newNode->right = NULL;
			current->right = newNode; // 5.2
			current = current->right; // 5.3
			Push(top, current); // 5.4
		}
	} while (!f.eof()); // 6
}
void Push(Elem*& top, Node* node)
{
	Elem* tmp = new Elem;
	tmp->info = node;
	tmp->link = top;
	top = tmp;
}
Node* Pop(Elem*& top)
{
	Elem* tmp = top->link;
	Node* node = top->info;
	delete top;
	top = tmp;
	return node;
}
void RightRotation(Node*& root)
{
	Node* tmp1 = root->left;
	Node* tmp2 = tmp1->right;
	tmp1->right = root; //1
	root->left = tmp2; //2
	root = tmp1; //3
}
void LeftRotation(Node*& root)
{
	Node* tmp1 = root->right;
	Node* tmp2 = tmp1->left;
	tmp1->left = root; //1
	root->right = tmp2; //2
	root = tmp1; //3
}
int Height(Node* root)
{
	if (root == NULL)
		return 0;
	int hL = Height(root->left);
	int hR = Height(root->right);
	return (hL > hR ? hL : hR) + 1;
}
int BFactor(Node* root)
{
	return Height(root->right) - Height(root->left);
}

void BalanceHeight(Node*& root)
{
	if (root != NULL)
	{
		while (BFactor(root) >= 2)
		{
			if (BFactor(root->right) < 0)
				RightRotation(root->right);
			LeftRotation(root);
		}
		while (BFactor(root) <= -2)
		{
			if (BFactor(root->left) > 0)
				LeftRotation(root->left);
			RightRotation(root);
		}
		BalanceHeight(root->left);
		BalanceHeight(root->right);
	}
}

int CountLevels(Node* root) {

	if (root == nullptr) {
		return 0;  // Empty tree has 0 levels
	}

	std::queue<Node*> q;
	q.push(root);
	int levelCount = 0;

	while (!q.empty()) {
		int nodeCount = q.size();

		// Process all nodes at the current level
		while (nodeCount > 0) {
			Node* node = q.front();
			q.pop();

			if (node->left != nullptr) {
				q.push(node->left);
			}

			if (node->right != nullptr) {
				q.push(node->right);
			}

			nodeCount--;
		}

		levelCount++;
	}

	return levelCount;
}

vector<int> sumOfLevels(Node* root) {
	vector<int> levelSums;
	if (root == nullptr) {
		return levelSums;
	}

	queue<Node*> nodeQueue;
	nodeQueue.push(root);

	while (!nodeQueue.empty()) {
		int currentLevelSize = nodeQueue.size();
		int levelSum = 0;

		for (int i = 0; i < currentLevelSize; i++) {
			Node* currentNode = nodeQueue.front();
			nodeQueue.pop();
			levelSum += currentNode->info;

			if (currentNode->left != nullptr) {
				nodeQueue.push(currentNode->left);
			}

			if (currentNode->right != nullptr) {
				nodeQueue.push(currentNode->right);
			}
		}

		levelSums.push_back(levelSum);
	}

	return levelSums;
}

int help(Node* root) {
	if (root == nullptr) {
		return 0;
	}

	int sum = 0;

	if (root->right != nullptr) {
		sum += root->right->info;  // Add the value of the current node if it has a right child
	}

	
	sum += help(root->left);
	sum += help(root->right); 
	//sum += sumRightSubtree(root);

	return sum;
}

int sumLeftSubtree(Node* root) {
	if (root == nullptr) {
		return 0;
	}

	int sum = 0;

	if (root->left != nullptr) {
		sum += root->left->info;  // Add the value of the current node if it has a right child
	}

	sum += help(root);
	sum += help(root->right);   // Recursively sum up the right subtree of the left child
	sum += help(root->left);  // Recursively sum up the right subtree of the right child

	return sum;
}

int sumRightSubtree(Node* root) {

	if (root == nullptr) {
		return 0;
	}

	int sum = -1;

	if (root->right != nullptr) {
		sum += root->right->info;  // Add the value of the current node if it has a right child
	}

	sum += help(root);
	//sum += help(root->left);   // Recursively sum up the right subtree of the left child
	sum += help(root->right);  // Recursively sum up the right subtree of the right child

	return sum;
}
