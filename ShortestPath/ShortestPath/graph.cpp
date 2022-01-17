//
//  graph.cpp
//  ShortestPath
//
//  Created by HaoyuLu on 2021/11/19.
//

#include "graph.hpp"
#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;

/*
Vertex::Vertex() {
    data = 0;
    Firstin = NULL;
    Firstout = NULL;
}

Edge::Edge() {
    mark = 0;
    weight = NULL;
    vertex1 = -1;
    vertex2 = -1;
    Path1 = NULL;
    Path2 = NULL;
}

void Edge::Set(int ed[2]) {
    mark = 0;
    weight = NULL;
    vertex1 = ed[0];
    vertex2 = ed[1];
    Path1 = NULL;
    Path2 = NULL;
}



AdjacentMultilist::AdjacentMultilist(int v[], int ed[][2], int n, int e) {
    numVertices = n;
    numEdges = e;
//    int i, j, k;
    int fin[numVertices], fout[numVertices]; //记录各节点第一条入边/出边的序号
    Edge edg[numEdges];
    for(int i = 0; i < numEdges; i++) {
        edg[i].vertex1 = ed[i][0];
        edg[i].vertex2 = ed[i][1];
    }
    for(int i = 0; i < numEdges; i++) {
        for(int j = 0; j < numEdges; j++) {
            if(edg[i].vertex1 == edg[j].vertex1) { // 连接头节点相同的边
                if(i == j) continue;
                else if(i < j) edg[i].Path1 = &edg[j];
                else edg[j].Path1 = &edg[i];
                
                fin[edg[i].vertex1] = min(i, j);
            }
            if(edg[i].vertex2 == edg[j].vertex2) { // 连接尾节点相同的边
                if(i == j) continue;
                else if(i < j) edg[i].Path2 = &edg[j];
                else edg[j].Path2 = &edg[j];
                
                fout[edg[i].vertex2] = min(i, j);
            }
        }
    }
    
    for(int i = 0; i < numVertices; i++) { // 连接头尾相同的边链域
        VertexList[i].data = v[i];
        VertexList[i].Firstin = &edg[fin[i]];
        VertexList[i].Firstout = &edg[fout[i]];
    }
}

void AdjacentMultilist::ShortestPath(int city, int dist[], int path[]) {
    int n = numVertices;
    int sp[numVertices];
//    int i, j, k;
    int weight, minn;
//    dist[city] = 0;

    queue<Vertex> q;
    q.push(VertexList[city]);
    VertexList[city].mark = 1;
    while(!q.empty()) {
        Vertex tmp = q.back();
        q.pop();
        for(Vertex v = VertexList[tmp.Firstout->vertex1];v.Firstout != NULL;v = VertexList[v.Firstout->vertex1]) {
            if(!v.mark) {
                v.mark = 1;
                q.push(v);
            }
            // 应该是city结点到i结点的权
            if(v.Firstout->vertex1 == city) dist[v.data] = v.Firstout->weight;
            else if (v.Firstin->vertex2 == city) dist[v.data] = v.Firstin->weight;
            else dist[v.data] = INT_MAX;
            
            sp[v.data] = 0;
            if(dist[v.data] < INT_MAX) path[v.data] = city;
            else path[v.data] = -1;
        } //for
        
        dist[city] = 0;
        sp[city] = 1;
        
    }
    for(int i = 0; i < n - 1; i++) {
        minn = INT_MAX;
        Vertex u = VertexList[city];
        for(int j = 0; j < n; j++)
            if(!sp[j] && dist[j] < minn) {
                u = VertexList[j];
                minn = dist[j];
            }
        sp[u.data] = 1; //顶点u加入最短路集合sp
        
        for(int k = 0; k < n; k++) {
            // 应该是u到k的权
            if(u.Firstout->vertex1 == k) weight = u.Firstout->weight;
            else if(u.Firstin->vertex2 == k) weight = u.Firstin->weight;
            else weight = INT_MAX;
            
            if(!sp[k] && weight < INT_MAX && dist[u.data] + weight < dist[k]) {
                dist[k] = dist[u.data] + weight;
                path[k] = u.data;
            }
        }
    }
}


void AdjacentMultilist::print_SP(int city, int *dist, int *path) {
    
}

*/
