//main.cpp
#include "SetList.h"
#include <iostream>
using namespace std;

int main() {
    linklist A,B,C;
    init(A);
    init(B);
    init(C);
    
	cout << "Initialize Aggregation A：" << endl;
	cout << "Please enter an integer as the limit on the size of A：" << endl;
	int enda;
	cin >> enda;
	build(A, enda);
	
	cout << "Initialize Aggregation B：" << endl;
	cout << "Please enter an integer as the limit on the size of B：" << endl;
	int endb;
	cin >> endb;
	build(B, endb);
	
	cout << "Please choose the operation below：1-search，2-insert，3-delete，0-end: " << endl;
	int key;
	cin >> key;
	
	while(key) {
        switch(key) {
            case 1: {
                cout << "Choose the aggregation you want to search elements in，1-A,2-B:" << endl;
                int m;
                cin >> m;
                cout << "enter the value you want to search" << endl;
                int n;
                cin >> n;
                if(m == 1) {
                    if(find(A,n)==-1)
                        cout << "Search failed！" << endl;
                    else
                        cout << "Its position is：" << find(A,n) << endl; 
                } 
                else {
                    if(find(B,n)==-1)
                        cout << "Search failed！" << endl;
                    else
                        cout << "Its position is：" << find(B,n) << endl; 
                } 
                break;
            }
            case 2: {
                cout << "Choose the aggregation you want to insert elements in，1-A,2-B:" << endl;
                int m;
                cin >> m;
                cout << "Enter the element you want to insert: " << endl;
                int n;
                cin >> n;
                cout << "Enter the position you want to insert in" << endl;
                int k;
                cin >> k;
                if(m == 1)
                    insert(A,k,n);
                else
                    insert(B,k,n);
                break;
            }
            case 3: {
                cout << "Choose the aggregation you want to remove elements from，1-A,2-B:"<<"\n";
                int m;
                cin >> m;
                cout << "Choose the position to remove: " << endl;
                int k;
                cin >> k;
                if(m == 1)
                    remove(A, k);
                else
                    remove(B, k);
                break;
            }

            default :break;
        }
	cout << "Please choose the operation below：1-search，2-insert，3-delete，0-end: " << endl;
	cin >> key;
	}
    //Comment the other 2 code blocks which you don't want to run, and don't run the 3 code blocks or any 2 of them below simultaneously
    
	cout << "C："; 
	bing(A, B, C);
	print(C);
    /*
	cout << "C："; 
    jiao(A, B, C);
    print(C);
    
	cout << "C："; 
    cha(A, B, C);
    print(C);
*/
    return 0;
}

