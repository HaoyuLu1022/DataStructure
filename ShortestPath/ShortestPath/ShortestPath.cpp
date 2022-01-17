//
//  ShortestPath.cpp
//  ShortestPath
//
//  Created by HaoyuLu on 2021/11/19.
//

#include <iostream>
#include <limits.h>
using namespace std;

const int numEdges = 16;
const int numVertices = 8;
int head[numVertices] = {-1, -1, -1, -1, -1, -1, -1, -1};
int visited[numVertices] = {0, 0, 0, 0, 0, 0, 0, 0};
int sp[numVertices] = {0, 0, 0, 0, 0, 0, 0, 0}; // the set for shortest paths

struct Edge {
    int from, to, next, weight; // array "next" stores the next edge with the same starting point as edge.from, in a reverse order
    int price, transfer, s_hour, s_minute, e_hour, e_minute; // prepared for multiple types of weights
};

struct Vertex {
    int order;
    string name;
};

void ShortestPath(Edge e[], int city, int dist[], int path[]) { // path: the last vertex to reach the destination
    int w = INT_MAX, minn;

    for(int i = 0; i < numVertices; i++) { // Initialize
        for(int j = head[city]; j != -1; j = e[j].next) {
            if(e[j].to == i) {
                dist[i] = e[j].weight; // every vertex that is not reachable from the starting point has weight of INT_MAX
                sp[i] = 0;
                if(i != city && dist[i] < INT_MAX)
                    path[i] = city;
            }
        }
    }
    
    sp[city] = 1;
    dist[city] = 0;
    for(int i = 0; i < numVertices - 1; i++) {
        minn = INT_MAX;
        int tmp = city;
        for(int j = 0; j < numVertices; j++) {
            if(!sp[j] && dist[j] < minn) {
                tmp = j;
                minn = dist[j];
            }
        } // for_j
        sp[tmp] = 1;
        for(int k = 0; k < numVertices; k++) {
            for(int m = head[tmp]; m != -1; m = e[m].next) {
                if(e[m].to == k) {
                    w = e[m].weight;
                    if(!sp[k] && w < INT_MAX && dist[tmp] + w < dist[k]) {
                        dist[k] = dist[tmp] + w; // update the weight
                        path[k] = tmp;
                    }
                }
            }// for_m
        }// for_k
    }
}


void GetWeight(Edge e[numEdges]) {
    int choice;
    cout << "Please choose the weight (1--price, 2--flight time, 3--total time, 4--transferring times): ";
    cin >> choice;
    switch (choice) {
        case 1:
            for(int i = 0; i < numEdges; i++) {
                e[i].weight = e[i].price; // price as weight
            }
            break;
        case 2:
            for(int i = 0; i < numEdges; i++) {
                e[i].weight = e[i].e_hour * 60 + e[i].e_minute - e[i].s_hour * 60 - e[i].s_minute; // flying time as weight
            }
            break;
        case 3: // if e[i].from is not the starting point, the weight should be defined as the end time - start time, otherwise it needs correction
            for(int i = 0; i < numEdges; i++) {
                for(int j = 0; j < numEdges; j++) {
                    if(e[j].to == e[i].from && e[j].from != e[i].to) {
                        if(e[j].e_hour * 60 + e[j].e_minute <= e[i].s_hour * 60 + e[i].s_minute)
                            e[i].weight = e[i].e_hour * 60 + e[i].e_minute - e[j].e_hour * 60 - e[j].e_minute; // total time as weight
                        else e[i].weight = e[i].e_hour * 60 + e[i].e_minute + 24 * 60 - e[j].e_hour * 60 - e[j].e_minute;
                    }
                }
            }
            break;
        case 4:
            for(int i = 0; i < numEdges; i++) {
                e[i].weight = e[i].transfer;
            }
            break;
        default:
            break;
    }
}


int main(int argc, const char * argv[]) {
    Edge ed[numEdges];
    Vertex v[numVertices];
    int dist[numVertices] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX};
    int path[numVertices] = {-1, -1, -1, -1, -1, -1, -1, -1};
    
    string n[8] = {"bj", "sh", "wl", "xa", "gz", "ls", "km", "wh"};
    int x[16] = {0, 1, 0, 2, 0, 3, 3, 4, 5, 6, 5, 7, 2, 6, 7, 4};
    int y[16] = {1, 0, 2, 0, 3, 0, 4, 3, 6, 5, 7, 5, 6, 2, 4, 7};
    int price[16] = {680, 680, 1150, 1150, 930, 930, 1320, 1320, 830, 830, 890, 890, 1480, 1480, 810, 810};
    int starth[16] = {16, 18, 8, 10, 15, 12, 7, 10, 10, 12, 14, 16, 9, 13, 7, 11};
    int startm[16] = {20, 0, 0, 45, 25, 35, 15, 15, 20, 35, 15, 25, 30, 5, 5, 25};
    int endh[16] = {17, 19, 9, 11, 17, 14, 9, 11, 11, 14, 15, 17, 12, 15, 8, 13};
    int endm[16] = {25, 5, 55, 40, 0, 15, 35, 35, 45, 0, 45, 55, 15, 50, 45, 5};
    int transfer[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    for(int i = 0; i < numVertices; i++) {
        v[i].order = i;
        v[i].name = n[i];
    }
    for(int i = 0; i < numEdges; i++) {
        ed[i].from = x[i];
        ed[i].to = y[i];
        ed[i].next = -1;
        ed[i].price = price[i];
        ed[i].transfer = transfer[i];
        ed[i].s_hour = starth[i];
        ed[i].s_minute = startm[i];
        ed[i].e_hour = endh[i];
        ed[i].e_minute = endm[i];
    }
    
    for(int i = 0; i < numEdges; i++) {
        ed[i].next = head[ed[i].from];
        head[ed[i].from] = i;
    }

    GetWeight(ed); // obtain the weights
    int city = 6;
    cout << "Please choose a city as your start place (0--Beijing, 1--Shanghai, 2--Wulumuqi, 3--Xian, 4--Guangzhou, 5--Lasa, 6--Kunming, 7--Wuhan): ";
    cin >> city;
    
    for(int i = numEdges - 1; i >= 0; i--) { // The total time for the starting point weight initialization should be corrected
        if(ed[i].from == city) {
            ed[i].weight = ed[i].e_hour * 60 + ed[i].e_minute - ed[i].s_hour * 60 - ed[i].s_minute;
            for(int j = ed[i].next; j != -1; j = ed[j].next) { // traverse the edges with "city" as the starting point
                ed[j].weight = ed[j].e_hour * 60 + ed[j].e_minute - ed[j].s_hour * 60 - ed[j].s_minute;
            }
            break;
        }
    }
    
    ShortestPath(ed, city, dist, path); // Dijkstra
    
    cout << "the cost from city " << v[city].name << " to other cities: " << endl;
    int d[10];
    for(int i = 0; i < numVertices; i++)
        if(i != city) {
            int j = i;
            int k = 0;
            while(j != city) {
                d[k++] = j;
                j = path[j];
            }
            d[k++] = city;
            cout << "The least cost to city " << v[i].name << ": ";
            while(k > 0)
                cout << v[d[--k]].name << " ";
            cout << endl << "The cost: " << dist[i] << endl;
        }
    return 0;
}
