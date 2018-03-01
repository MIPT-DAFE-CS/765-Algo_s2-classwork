/****************************************************************************
Задача 3_2. Порядковые статистики.

Дано число N и N строк. Каждая строка содержащит команду добавления или
удаления натуральных чисел, а также запрос на получение k-ой порядковой
статистики. Команда добавления числа A задается положительным числом A,
команда удаления числа A задается отрицательным числом "-A".
Запрос на получение k-ой порядковой статистики задается числом k.
Требуемая скорость выполнения запроса - O(log n).

  in    | out
  ----- | ---
  5     | 40
  40 0  | 40
  10 1  | 10
  4 1   | 4
  -10 0 | 50
  50 2  |

****************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    explicit Node(int key) : key(key) {}
    Node* left = nullptr;
    Node* right = nullptr;
    int key = 0;
    int height = 1;
    int size = 1;
};

int height(Node* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return (node->height);
    }
}

int size(Node* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return (node -> size);
    }
}

int diff(Node* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return (height(node-> left) - height(node->right));
    }
}

/** @pre height of node->left and node->right should be correct. */
void updateHeight(Node* node)  {
    node->height = 1 + max(height(node->left), height(node->right));
}

void updateSize(Node* node) {
    node->size = 1 + size(node->left) + size(node->right);
}

/** @pre diff(node) == -2 && ( diff(node->right) == 0 || diff(node->right) == -1 )
 @retval new node instead of @a node. */
Node * rotateLeft(Node * node) {
    Node * b = node->right;
    node->right = b->left;
    b->left = node;
    updateHeight(node);
    updateSize(node);
    updateHeight(b);
    updateSize(b);
    return b;
}

/** @pre diff(node) == 2 && ( diff(node->left) == 0 || diff(node->left) == 1 )
 *  @retval new node instead of @a node. */
Node * rotateRight(Node * node) {
    Node * b = node->left;
    node->left = b->right;
    b->right = node;
    updateHeight(node);
    updateSize(node);
    updateHeight(b);
    updateSize(b);
    return b;
}

/** @pre diff(node) == -2 && diff(node->right) == 1 && (diff(node->right->left) == 1
 *                                                      diff(node->right->left) == 0
 *                                                      diff(node->right->left) == -1)
 *  @retval new node instead of @a node. */
Node * rotateLeftBig(Node * node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

/** @pre diff(node) == 2 && diff(node->left) == -1 && (diff(node->left->right) == 1
 *                                                     diff(node->left->right) == 0
 *                                                     diff(node->left->right) == -1)
 *  @retval new node instead of @a node. */
Node * rotateRightBig(Node * node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

/** @pre node->left and node->right should be balanced
 *  @retval new node instead of @a node. */
Node * balance(Node * node) {
    updateHeight(node);
    updateSize(node);
    if(diff(node) == 2) {
        if( diff(node->left) < 0 ) {
            return rotateRightBig(node);
        } else {
            return rotateRight(node);
        }
    } else if(diff(node) == -2) {
        if( diff(node->right) > 0 ) {
            return rotateLeftBig(node);
        } else {
            return rotateLeft(node);
        }
    }
    return node;
}

Node * insert(Node * node, int key)
{
    if(node == nullptr) {
        return new Node(key);
    }
    if(node->key > key) {
        node->left = insert(node->left, key);
    } else {
        node->right = insert(node->right, key);
    }
    
    return balance(node);
}

Node * findMin(Node * node)
{
    if(node->left == nullptr)
    {
        return node;
    } else
    {
        return findMin(node->left);
    }
}

Node * deleteMin(Node * node)
{
    if(node->left == nullptr)
    {
        return node->right;
    }
    node->left = deleteMin(node->left);
    return balance(node);
}

Node * deleteNode(Node * node, int key)
{
    if(node->key == key)
    {
        // @todo: if node->right is null
        if(node -> right == nullptr)
        {
            Node * tmp = node->left;
            delete node;
            return tmp;
        } else
        {
            Node * min = findMin(node->right);
            node->right = deleteMin(node->right);
            min->left = node->left;
            min->right = node->right;
            delete node;
            return balance(min);
        }
    } else if(node->key > key)
    {
        node->left = deleteNode(node->left, key);
    } else {
        node->right = deleteNode(node->right, key);
    }
    return balance(node);
}

void getIndex(Node * node, int key, int & index) {
    int leftSize = index + size(node->left) + 1;
    if(node->key > key) {
        getIndex(node->left, key, index);
    } else if(node->key < key) {
        index = leftSize;
        getIndex(node->right, key, index);
    } else {
        index = leftSize;
    }
}

int getKey(Node * node, int index) {
    int leftSize = size(node->left) + 1;
    if(leftSize > index) {
        return getKey(node->left, index);
    } else if(leftSize < index) {
        return getKey(node->right, index-leftSize);
    } else {
        return node->key;
    }
}

int whatcom (int c) {
    return (c<0? 2 : 1);
}

int main(){
    int n;
    cin >> n;
    Node * root = nullptr;
    int key, index;
    int command;
    for (int i(0); i<n; ++i)
    {
        cin >> key;
        cin>>index;
        command = whatcom(key);
        key = abs(key);
        switch (command) {
            case 1 : {
                root = insert(root, key);
                cout << getKey (root,index+1) << endl;
                break;
            }
            case 2 : {
                root = deleteNode(root, key);
                cout << getKey (root,index+1) << endl;
                break;
            }
            default: break;
        }
    }
}



