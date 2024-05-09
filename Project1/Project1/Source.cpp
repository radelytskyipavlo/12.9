#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef int Info;
struct Node
{
    Node* left,
        * right;
    Info info;
};

void AddNode(Node*& root, Info value);
Node* CreateSearchTree(int nodeCount);
void BalanceSearchTree(Node*& root);
void storeInorder(Node* root, vector<Node*>& nodes);
Node* buildBalancedTree(vector<Node*>& nodes, int start, int end);
void DeleteTree(Node*& root);

Node* CreateTree(int nodeCount)
{
    if (nodeCount == 0)
        return nullptr;
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
    if (root != nullptr)
    {
        PrintTree(root->right, level + 1);
        for (int i = 0; i < level; i++)
            cout << "   ";
        cout << root->info << endl;
        PrintTree(root->left, level + 1);
    }
}

Node* CreateSearchTree(int nodeCount)
{
    Node* root = nullptr;
    for (int i = 0; i < nodeCount; ++i) {
        Info value;
        cout << "Enter node value: ";
        cin >> value;
        AddNode(root, value);
    }
    return root;
}

void AddNode(Node*& root, Info value)
{
    if (root == nullptr) {
        root = new Node;
        root->info = value;
        root->left = root->right = nullptr;
    }
    else if (value < root->info) {
        AddNode(root->left, value);
    }
    else {
        AddNode(root->right, value);
    }
}

void BalanceSearchTree(Node*& root)
{
    if (root == nullptr)
        return;

    vector<Node*> nodes;
    storeInorder(root, nodes);
    root = buildBalancedTree(nodes, 0, nodes.size() - 1);
}

void storeInorder(Node* root, vector<Node*>& nodes)
{
    if (root == nullptr)
        return;

    storeInorder(root->left, nodes);
    nodes.push_back(root);
    storeInorder(root->right, nodes);
}

Node* buildBalancedTree(vector<Node*>& nodes, int start, int end)
{
    if (start > end)
        return nullptr;

    int mid = (start + end) / 2;
    Node* root = nodes[mid];
    root->left = buildBalancedTree(nodes, start, mid - 1);
    root->right = buildBalancedTree(nodes, mid + 1, end);
    return root;
}

void DeleteLeaf(Node*& root, Info value)
{
    if (root == nullptr)
        return;
    if (root->left != nullptr && root->left->info == value && root->left->left == nullptr && root->left->right == nullptr) {
        delete root->left;
        root->left = nullptr;
        return;
    }
    if (root->right != nullptr && root->right->info == value && root->right->left == nullptr && root->right->right == nullptr) {
        delete root->right;
        root->right = nullptr;
        return;
    }
    DeleteLeaf(root->left, value);
    DeleteLeaf(root->right, value);
}

void DeleteSingleNode(Node*& root, Info value)
{
    if (root == nullptr)
        return;
    if (root->left != nullptr && root->left->info == value && (root->left->left == nullptr || root->left->right == nullptr)) {
        Node* temp = root->left;
        root->left = (root->left->left != nullptr) ? root->left->left : root->left->right;
        delete temp;
        return;
    }
    if (root->right != nullptr && root->right->info == value && (root->right->left == nullptr || root->right->right == nullptr)) {
        Node* temp = root->right;
        root->right = (root->right->left != nullptr) ? root->right->left : root->right->right;
        delete temp;
        return;
    }
    DeleteSingleNode(root->left, value);
    DeleteSingleNode(root->right, value);
}

void DeleteDoubleNode(Node*& root, Info value)
{
    if (root == nullptr)
        return;
    if (root->info == value && root->left != nullptr && root->right != nullptr) {
        Node* minRight = root->right;
        while (minRight->left != nullptr)
            minRight = minRight->left;
        root->info = minRight->info;
        DeleteLeaf(root->right, minRight->info);
        return;
    }
    DeleteDoubleNode(root->left, value);
    DeleteDoubleNode(root->right, value);
}

void DeleteSubTree(Node*& root, Info value)
{
    if (root == nullptr)
        return;
    if (root->info == value) {
        DeleteTree(root);
        return;
    }
    DeleteSubTree(root->left, value);
    DeleteSubTree(root->right, value);
}

void DeleteTree(Node*& root)
{
    if (root == nullptr)
        return;
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
    root = nullptr;
}

int CountParents(Node* root, Info k)
{
    if (root == nullptr)
        return 0;

    int count = 0;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        if (curr->left != nullptr && curr->left->info == k)
            count++;
        if (curr->right != nullptr && curr->right->info == k)
            count++;
        if (curr->left != nullptr)
            q.push(curr->left);
        if (curr->right != nullptr)
            q.push(curr->right);
    }
    return count;
}

int main()
{
    int choice, N, k;
    Node* root = nullptr;
    cout << "Enter nodes count: ";
    cin >> N;
    root = CreateTree(N);

    do {
        cout << "\nMenu:\n";
        cout << "1. Print tree\n";
        cout << "2. Create search tree\n";
        cout << "3. Add node\n";
        cout << "4. Balance search tree\n";
        cout << "5. Delete leaf node\n";
        cout << "6. Delete single node\n";
        cout << "7. Delete double node\n";
        cout << "8. Delete subtree\n";
        cout << "9. Count parents with value k\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nPrinting tree:\n";
            PrintTree(root, 0);
            break;
        case 2:
            cout << "\nCreating search tree:\n";
            root = CreateSearchTree(N);
            break;
        case 3:
            Info newValue;
            cout << "Enter value to add: ";
            cin >> newValue;
            AddNode(root, newValue);
            break;
        case 4:
            cout << "\nBalancing search tree:\n";
            BalanceSearchTree(root);
            break;
        case 5:
            Info leafValue;
            cout << "Enter leaf node value to delete: ";
            cin >> leafValue;
            DeleteLeaf(root, leafValue);
            break;
        case 6:
            Info singleValue;
            cout << "Enter single node value to delete: ";
            cin >> singleValue;
            DeleteSingleNode(root, singleValue);
            break;
        case 7:
            Info doubleValue;
            cout << "Enter double node value to delete: ";
            cin >> doubleValue;
            DeleteDoubleNode(root, doubleValue);
            break;
        case 8:
            Info subtreeValue;
            cout << "Enter subtree root value to delete: ";
            cin >> subtreeValue;
            DeleteSubTree(root, subtreeValue);
            break;
        case 9:
            cout << "Enter value k: ";
            cin >> k;
            cout << "Number of parents with value " << k << ": " << CountParents(root, k) << endl;
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please enter again.\n";
        }
    } while (choice != 0);

    return 0;
}
