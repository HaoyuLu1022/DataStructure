#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

typedef struct eightqueen {
	int que[100];
	int top;
}eightqueen;
 
void init(eightqueen *s) {
	s->top = -1;
}
 
bool isempty(eightqueen *s) {
	return s->top == -1;
}
 
int size(eightqueen *s) {
	return s->top + 1;
}
 
void pop(eightqueen *s) {
	if(!isempty(s))
		s->top--;
}
 
void push(eightqueen *s, int data) {
	s->que[++s->top] = data;
}
 
int get(eightqueen *s, int index) {
	return s->que[index];
}
 
int top(eightqueen *s) {
	return s->que[s->top];
}
 
bool issafe(int i, eightqueen *s) {
	if(isempty(s))
		return false;
	int state = -1;
	for(int j = 0; j < size(s); ++j) {
		state = get(s, j);
		if(i == state || abs(size(s) - j) == abs(i - state)) {
			return true;
		}
	}
	return false;
}

void queen(int i, eightqueen *eightque, int& cnt) {		
	while(i < 8 || !isempty(eightque)) {
		if(size(eightque) == 8) {
			int chess[8][8] = {0};
			cout << "方案" << cnt + 1 << "：";
			for(int k = 0; k < 8; ++k) {
				cout << get(eightque, k) << " ";
				chess[k][get(eightque, k)] = 1;
			}
			cout << endl;

			for(int m = 0; m < 8; m++) {
            for(int n = 0; n < 8; n++) {
                cout << chess[m][n] << " ";
            }
        	cout << endl;
        	}
			
			cnt++;
			pop(eightque);
			i = top(eightque) + 1; 
			pop(eightque);
		}
		else if(i == 8) {
			i = top(eightque) + 1;
			pop(eightque);
		} 
		else if(issafe(i, eightque)) {
			++i;
		}  
		else {
			push(eightque, i);
			i = 0;
		}
	}
	//cout << cnt << endl;	
}
 
int main() {
	eightqueen *eightque = (eightqueen* )malloc(sizeof(eightqueen));
	init(eightque);
	int i, cnt = 0;

    freopen("out2.txt", "w", stdout);
	queen(0, eightque, cnt);
    fclose(stdout);
	free(eightque);
    return 0;
}

