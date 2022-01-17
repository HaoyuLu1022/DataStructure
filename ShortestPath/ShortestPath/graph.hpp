//
//  graph.hpp
//  ShortestPath
//
//  Created by HaoyuLu on 2021/11/19.
//

#ifndef graph_hpp
#define graph_hpp

#include <iostream>
using namespace std;
static int cnt = 0;
static int head[8];
/*
class Edge {
    friend class AdjacentMultilist;
public:
    Edge();
    Edge(int ed[2]);
    void Set(int ed[2]);
protected:
    int mark;
    int weight;
    int vertex1, vertex2; // 边的头尾顶点
    Edge* Path1; //头相同的边的链域
    Edge* Path2; //尾相同的边的链域
};

class Vertex {
    friend class AdjacentMultilist;
    friend class Edge;
public:
    Vertex();
protected:
    int mark, data; //mark记录是否被访问, data记录序号
    Edge* Firstin; // 第一条入边
    Edge* Firstout; // 第一条出边
};


class AdjacentMultilist {
public:
    AdjacentMultilist(int v[], int ed[][2], int n, int e);
    void ShortestPath(int city, int dist[], int path[]);
    void print_SP(int city, int dist[], int path[]);
protected:
    int numVertices, numEdges;
    Vertex VertexList[8]; // 顶点表
};
*/

class Edge {
public:
    int from, to, next, weight;
    Edge();
};

class Vertex {
public:
    int order, s_hour, s_minute, e_hour, e_minute;
};

void AddEdge(Edge e[], int i, int j, int w) {
    e[cnt].from = i;
    e[cnt].to = j;
    e[cnt].weight = w;
    e[cnt].next = head[e[cnt].from];
    head[e[cnt].from] = cnt++;
}

void AddVertex(Vertex v[], int s1, int s2, int e1, int e2) {
    
}
#endif /* graph_hpp */
