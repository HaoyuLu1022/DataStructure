//SetList.h
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef struct node {                                        
    int data;                                          
    struct node *link;                                      
}node, *linklist;  
                                      
void init(linklist& S) { //初始化                             
    S = (node *)malloc(sizeof(node));             
    S->link = NULL;                                 
}

void build(linklist& first, int end) {//尾插法构建链表 
    int val;  
    node *s, *rear = first;
    while (end--) {
        s = (node *)malloc(sizeof(node));
        cout << "Please enter an integer：" << "\n";
        cin >> s->data;  		
        rear->link = s;   
        rear = s;	 
    }
    rear->link = NULL;		
} 

int find(linklist& first, int x) {//寻找
	int i=1;
    node *p = first->link;        
    while (p!= NULL)  {
        if(p->data == x)  return i;
	    p = p->link;
        i++;
	}
    return 0;     
}


void print(linklist& first ) {	//输出链表
    first = first->link;
	while(first) {
        cout << first->data << " ";
        first = first->link ;
		}
    cout << "\n";
}

void insert(linklist& first, int i, int x ) {//插入
	if(i<1) cout << "Insertion failed." << "\n"; 
    node *newnode;
    newnode = (node *) malloc(sizeof(node));
	newnode->data = x;
    node *p = first, *pr;   
    int k = 0;
    while (p != NULL && k < i-1) { 
        pr = p;  
        p = p->link;  
        k++; 
        } 
	if (p == NULL && first != NULL) 
		p = pr;
    newnode->link = p->link;
    p->link = newnode;

    cout << "Insertion success." << "\n"; 						
} 

bool remove(linklist& first, int i) {//删除
    node *p, *q;   
    int k;
    if (i == 0) return false;    
    else {			     
        p = first;  int k = 0;        
        while (p != NULL && k < i-1) { 
            p = p->link; 
            k++; 
        }
		if (p == NULL || p->link == NULL)  {
            cout << "the position to remove is invalid." << endl;
            return false;	    
      	}
      	else {                         	    
            q = p->link;       	    
            p->link = q->link;        
      	}
        free(q);   
    }

    return true; 
}

void insertA(linklist& first , int x) {//在结尾插入
	node *newnode;
    newnode = (node *)malloc(sizeof(node));
	newnode->data = x;
    node *p = first, *pr;   
    while (p != NULL) { 
        pr = p;  
        p = p->link; 
    } 
	if (p == NULL && first != NULL) 
		p = pr;
    newnode->link = p->link;
    p->link = newnode;
}
/*
void bing(linklist& a, linklist& b, linklist &c) {//并 
	a = a->link;
	b = b->link;
	while (a) {
		if (!find(c, a->data)) {
			insertA(c, a->data);
		}
		a = a->link;
	}
	while (b) {
		if (!find(c, b->data)) {
			insertA(c, b->data);
		}
		b = b->link;
	}
}
*/
void bing(linklist &L1, linklist &L2, linklist &L3) { //并
    linklist p1 = L1->link;
    linklist p2 = L2->link;
    L1->link = NULL;
    L3 = L1;
    linklist p3;
    while(p1 && p2) {
        if(p1->data < p2->data){
            p3 = p1->link;
            p1->link = NULL;
            L1->link = p1;
            L1 = L1->link;
            p1 = p3;
        }
        else if(p1->data == p2->data){
            p3 = p1->link;
            p1->link = NULL;
            L1->link = p1;
            L1 = L1->link;
            p1 = p3;
            p2 = p2->link;
        }
        else{
            p3 = p2->link;
            p2->link = NULL;
            L1->link = p2;
            L1 = L1->link;
            p2 = p3;
        }
    }
    if(p2) p1 = p2;
    while(p1){
        p3 = p1->link;
        p1->link = NULL;
        L1->link = p1;
        L1 = L1->link;
        p1 = p3;
    }
    free(L2);
}

void cha (linklist &L1, linklist &L2, linklist &L3) { //差
    L3 = (linklist)malloc(sizeof(node));
    L3->link = NULL;
    linklist a = L1->link, b = L2->link, c = L3, s;
    if(a->link == NULL) exit(0);
    while(a != NULL && b != NULL){
        if(a->data != b->data){
            if(a->data > b->data){
                while(a->data > b->data) b = b->link;
                if(a->data == b->data) continue;
            }
            s = (linklist)malloc(sizeof(node));
            s->data = a->data;
            s->link = NULL;
            c->link = s;
            c = s;
            a = a->link;
        }
        else{
            a = a->link;
            b = b->link;
        }
    }
    while(a != NULL){
        s = (linklist)malloc(sizeof(node));
        s->data = a->data;
        s->link = NULL;
        c->link = s;
        c = s;
        a = a->link;
    }
}

void jiao(linklist &L1, linklist &L2, linklist &L3) { //交
    linklist a = L1->link, b = L2->link, s;
    L3 = (linklist)malloc(sizeof(node));
    L3->link = NULL;
    linklist c = L3;
    if(a == NULL || b == NULL) exit(0);
    while(a != NULL){
        while(b != NULL){
            if(b->data == a->data){
                s = (linklist)malloc(sizeof(node));
                s->data = a->data;
                s->link = NULL;
                c->link = s;
                c = s;
            }
            if(b->data > a->data) break;
            b = b->link;
        }
        a = a->link;
    }
}

