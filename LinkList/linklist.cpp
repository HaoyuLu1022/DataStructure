#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <limits.h>
#include <algorithm>
using namespace std;

typedef struct list{
    int *element;
    int length;
}list;

list Initialize(int length) {
    list l;
    l.length = length;
    
    l.element = (int*)malloc(l.length * (sizeof(int)));
    if(!l.element) {
        printf("Allocation failed.\n");
        exit(0);
    }
    
    return l;
}


int find(list& l, int x) {
    int i;
    for(i = 0; i < l.length; i++) {
        if(l.element[i] == x) {
            return i + 1;
        }
    }
    return -1;
}

list DelMinList (list& l) {
    int mark, minn = INT_MAX;
    if(l.length != 0) {
        for(int i = 0; i < l.length; i++) {
            if(l.element[i] < minn) {
                minn = l.element[i];
                mark = i;
            }
        }
        l.element[mark] = l.element[l.length - 1];
        l.length--;

        return l;
    }
    else {
        exit(0);
    }
}

list DelIndex(list& l, int index) {
    if(l.length != 0) {
        for(int i = index - 1; i < l.length; i++) {
            l.element[i] = l.element[i + 1];
        }
        l.length--;

        return l;
    }
    else {
        exit(0);
    }
}

list DelValue(list &l, int value) {
    for (int i = 0; i < l.length; i++) {
        if(l.element[i] == value) {
            l.element[i] = l.element[i + 1];
            l.length--;
        }
    } 
    return l;
} 

list DelSection(list &l, int s, int t) {
    if(l.length == 0 || s <= 0 || t > l.length || s >= t) {
        printf("The sequential list is empty or the section of value you choose to delete exceeds the section where the values in the list is included.\n");
        exit(0);
    }
    else {
        for(int i = 0; i < l.length; i++) {
            if (l.element[i] >= s && l.element[i] <= t) {
                DelIndex(l, i);
                }
                l.length--;
            }
        }
        //l.element = (int*)realloc(l.element, l.length*sizeof(int));
        return l;
}

list DelRepeated(list &l) {
    for(int i = 0; i < l.length; i++) {
        for(int j = 0; j < l.length; j++) {
            if (i == j) continue;
            else {
                if(l.element[i] == l.element[j]) {
                    int mark;
                    if(i > j) {
                        mark = i;
                        for(int k = mark; k <l.length; k++) {
                            l.element[k] = l.element[k + 1];
                            }
                        }
                    else {
                        mark = j;
                        for(int k = mark; k <l.length; k++) {
                            l.element[k] = l.element[k + 1];
                        }
                    }
                l.length--;
                }
            }
        }
    }
    return l;
}

list AddList(list& l, int n, int order) {
    if(order > l.length + 1 || order < 1) {
        printf("The position doesn't exist.\n");
        exit(0);
    }

    l.element = (int*)realloc(l.element, (l.length + 1) * (sizeof(int)));
    for(int i = l.length - 1;i >= order - 1; i--) {
        l.element[i + 1] = l.element[i];
    }
    l.element[order - 1] = n;

    l.length++;

    return l;
}

list DelSectionSeq(list& l, int s, int t) {
    if(l.length == 0 || s <= 0 || t > l.length || s >= t) {
        printf("The sequential list is empty or the section of value you choose to delete exceeds the section where the values in the list is included.\n");
        exit(0);
    }
    else {
        sort(l.element, l.element + l.length);
        int start, end;
        for (int i = 0; i < l.length; i++) {
            if(l.element[i] >= s) {
                start = i;
                break;
            }
        }
        for(int i = start; i < l.length; i++) {
            if(l.element[i] <= t) {
                end = i;
                break;
            }
        }
        for(int i = end + 1 ; i < l.length; i++) {
            l.element[i - (end - start + 1)] = l.element[i];
        }
        l.length -= (end - start + 1);
        //l.element = (int*)realloc(l.element, sizeof(int));
    }

    return l;
}

list CombineList(list& l1, list& l2, list& newlist) {
    int i = 0, j = 0, k = 0;
    while(i < l1.length && j < l2.length) {
        if(l1.element[i] < l2.element[j]) {
            newlist.element[k++] = l1.element[i++];
        }
        else {
            newlist.element[k++] = l2.element[j++];
        }
    }

    while(i < l1.length) {
        newlist.element[k++] = l1.element[i++];
    }
    while(j < l2.length) {
        newlist.element[k++] = l2.element[j++];
    }
    newlist.length = k;
    sort(newlist.element, newlist.element + newlist.length);
    return newlist;
}

int main() {
    int length1, length2;
    cin >> length1 >> length2;
    list l1 = Initialize(length1);
    list l2 = Initialize(length2);
    
    for(int i = 0; i < l1.length; i++) {
        scanf("%d", &l1.element[i]);
    }

    for(int i = 0; i < l2.length; i++) {
        cin >> l2.element[i];
    }

    l1 = DelMinList(l1);
    for(int i = 0; i < l1.length; i++) {
        printf("%d ", l1.element[i]);
    }


    printf("\n");
    
    //l1 = DelIndex(l1, 2);
    //l1 = DelValue(l2, 1);
    
    //l1 = DelRepeated(l1);
    /*
    int s, t;
    cin >> s >> t;
    l1 = DelSection(l1, s, t);
    

    for(int i = 0; i < l1.length; i++) {
        printf("%d ", l1.element[i]);
    }

    printf("\n");
    */
    
    //printf("%d\n", find(l1, 1));
/*
    l1 = AddList(l1, 10, 2);
    
    for(int i = 0; i < l1.length; i++) {
        printf("%d ", l1.element[i]);
    }

    printf("\n");

    sort(l1.element, l1.element + l1.length);
    for(int i = 0; i < l1.length; i++) {
        printf("%d ", l1.element[i]);
    }
    cout << endl;
    */
    list newl = Initialize(length1 + length2);
    CombineList(l1, l2, newl);
    for(int i = 0; i < newl.length; i++) {
        cout << newl.element[i] << " ";
    }
    return 0;
}

