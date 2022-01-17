#include <iostream>
#include <cmath>
using namespace std;

bool issafe(int i, int que[8]) { // col = que[row]
	for(int k = 0; k < i; k++) {
		if(que[k] == que[i] || abs(que[i] - que[k]) == abs(i - k))
			return false;
	}
	return true;
}

void queen(int i, int que[8], int& cnt) {
    int chess[8][8] = {0};
	if(i == 8) {
		cout << "方案" << ++cnt << "：";
		for(int k = 0; k < 8; ++k) {
			cout << que[k] << " ";
            chess[k][que[k]] = 1;
		}   
		cout << endl;
        for(int m = 0; m < 8; m++) {
            for(int n = 0; n < 8; n++) {
                cout << chess[m][n] << " ";
            }
        cout << endl;
        }
		//return;
	}
	for(int k = 0; k < 8; k++) {
		que[i] = k;
		if(issafe(i, que)) queen(i + 1, que, cnt);
	}

    //cout << i << "  ";
}

int main() {
	int que[8];
	int cnt = 0;

	freopen("out1.txt", "w", stdout);
    cout << "1为皇后所在位置" << endl;
	queen(0, que, cnt);
	fclose(stdout);
	return 0;
}

