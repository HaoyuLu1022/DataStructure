#include <iostream>
#include <limits.h>
#include <string>
#include <cstring>
using namespace std;

typedef struct TreeNode {
    char ch;
    int weight;
    TreeNode* left;
    TreeNode* right;
}HuffmanNode, *HuffmanTree;

typedef struct Heap {
    HuffmanTree* tree;
    int size; //当前元素个数
    int capacity; //最大容量
}Heap, *MinHeap;

HuffmanTree newHuffmanNode() {
    HuffmanTree t = new HuffmanNode;
    t->weight = 0;
    t->left = NULL;
    t->right = NULL;

    return t;
}

MinHeap createMinHeap(int maxsize) {
    MinHeap h = new Heap;
    h->tree = (HuffmanTree *)malloc((maxsize + 1) * sizeof(HuffmanTree));
    h->size = 0;
    h->capacity = maxsize;
    HuffmanTree t = newHuffmanNode();
    t->ch = '\0';
    t->weight = INT_MIN;
    h->tree[0] = t;

    return h;
}

bool InsertHeap(MinHeap& h, HuffmanTree& t) { //插入新增结点
    int i;
    if(h->size == h->capacity) {
        cout << "The heap is full." << endl;
        return 0;
    }

    i = ++h->size;
    for(; h->tree[i / 2]->weight > t->weight; i /= 2) h->tree[i] = h->tree[i / 2];
    h->tree[i] = t;

    return 1;
}

HuffmanTree GetMin(MinHeap& h) { //取最小堆的根
    int parent, child;
    HuffmanTree MinTree, tmp = NULL;

    if(h->size == 0) {
        cout << "The heap is empty." << endl;
        return NULL;
    }
    MinTree = h->tree[1];
    tmp = h->tree[h->size--];
    for(parent = 1; parent * 2 <= h->size; parent = child) {
        child = parent * 2;
        if(child != h->size && h->tree[child]->weight > h->tree[child + 1]->weight) {
            child++; //child: 左右子结点较小者
        }
        if(tmp->weight > h->tree[child]->weight) {
            h->tree[parent] = h->tree[child]; //tmp下移到child位置
        }
        else break;
    }
    h->tree[parent] = tmp;

    return MinTree;
}

MinHeap BuildMinHeap(MinHeap& h) { //调整使满足有序性
    int parent, child;
    HuffmanTree tmp;
    for(int i = h->size / 2; i > 0; i--) {
        tmp = h->tree[i];
        for(parent = i; parent * 2 <= h->size; parent = child) { //向下过滤
            child = parent * 2;
            if(child != h->size && h->tree[child]->weight > h->tree[child + 1]->weight) {
                child++; 
            }
            if(tmp->weight > h->tree[child]->weight) {
                h->tree[parent] = h->tree[child]; //parent下移到child
            }
            else break;
        }
        h->tree[parent] = tmp;
    }

    return h;
}

HuffmanTree Huffman(MinHeap &h) { //构造哈夫曼树
    int cnt = h->size;
    HuffmanTree t;

    BuildMinHeap(h);
    for(int i = 1; i < cnt; i++) {
        t = newHuffmanNode();
        t->left = GetMin(h);
        t->right = GetMin(h);
        t->weight = t->left->weight + t->right->weight;
        InsertHeap(h, t);
    }
    t = GetMin(h);

    return t;
}

void HuffmanCode(HuffmanTree& t, int depth) { //depth当前结点深度
    static int code[10];
    if(t) {
        if(t->left == NULL && t->right == NULL) { //叶结点
            cout << "The weight " << t->weight << " of corresponding char " << t->ch << " is ";
            for(int i = 0; i < depth; i++) {
                cout << code[i];
            }
            cout << endl;
        }
        else {
            code[depth] = 0; //左子树编码0
            HuffmanCode(t->left, depth + 1);
            code[depth] = 1; //右子树编码1
            HuffmanCode(t->right, depth + 1);
        }
    }
}

void HuffmanDecode(char ch[], HuffmanTree& t) {
    int code = 0;
    string decode = "";
    HuffmanTree tmp = t;
    for(int i = 0; i < strlen(ch); i++) {
        while(tmp->left != NULL && tmp->right != NULL) {
            code = ch[i] - '0';
            if(code == 0) {
                tmp = tmp->left;
            }
            else tmp = tmp->right;
            i++;
        }
        i--;
        decode += tmp->ch;
        tmp = t;
    }
    cout << decode << endl;
}

void PreOrder(HuffmanTree& t) {
    if(t) {
        cout << t->weight << " ";
        PreOrder(t->left);
        PreOrder(t->right);
    }
}

int main() {
    int i, leaf;
    MinHeap h;
    HuffmanTree t;
    HuffmanTree bt = NULL;

    cout << "Please input the number of leaf nodes: ";
    cin >> leaf;
    h = createMinHeap(2 * leaf);
    cout << "Please input the weights of the leaves: ";
    for(int i = 1; i <= leaf; i++) {
        t = newHuffmanNode();
        cin >> t->weight;
        h->tree[++(h->size)] = t;
    }
    char s[50];
    cout << "Please input the char for each leaf correspondingly: ";
    getchar();
    gets(s);
   
    for(int i = 1; i <= h->size; i++) {
        h->tree[i]->ch = s[i - 1];
    }
    
    bt = Huffman(h);
    cout << "The weights in pre-order: ";
    PreOrder(bt);
    cout << endl;

    HuffmanCode(bt, 0);
    cout << "Please input binary code to be decoded: ";
    char c[100];
    gets(c);
    cout << "result: ";
    HuffmanDecode(c, bt);

    return 0;
}
