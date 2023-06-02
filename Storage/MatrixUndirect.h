#ifndef GRAPH_MATRIXUNUndirECT_H
#define GRAPH_MATRIXUNUndirECT_H

#include "cstdio"
#include "fstream"
#include "iostream"
#include "cstring"

using namespace std;
#define DEFAULT_SIZE 100
#define DEFAULT_FILL -1

class MatrixUndirect {
public:
    MatrixUndirect(int setVertexMaxNum = DEFAULT_SIZE);

    MatrixUndirect(const string &file, int setVertexMaxNum = DEFAULT_SIZE);

    ~MatrixUndirect();

    void display();

    int getEdge(int vertexStart, int vertexEnd);

    int update(int vertexStart, int vertexEnd, int weight);

    bool addEdge(int vertexStart, int vertexEnd, int weight);

    bool delEdge(int vertexStart, int vertexEnd);

private:
    int **matrix;
    int vertexMaxNum = DEFAULT_SIZE;
    int minVertexStart = INT32_MAX, maxVertexStart = 0, minVertexEnd = INT32_MAX, maxVertexEnd = 0;

    void promptInfo(int kind);

    bool setEdge(int vertexStart, int vertexEnd, int weight);
};

MatrixUndirect::MatrixUndirect(int setVertexMaxNum) {
    vertexMaxNum = setVertexMaxNum + 1;
    matrix = new int *[vertexMaxNum];
    for (int i = 0; i < vertexMaxNum; i++) {
        matrix[i] = new int[vertexMaxNum];
        for (int j = 0; j < vertexMaxNum; j++) {
            matrix[i][j] = DEFAULT_FILL;
        }
    }
}

MatrixUndirect::MatrixUndirect(const string &file, int setVertexMaxNum) {
    vertexMaxNum = setVertexMaxNum + 1;
    matrix = new int *[vertexMaxNum];
    for (int i = 0; i < vertexMaxNum; i++) {
        matrix[i] = new int[vertexMaxNum];
        for (int j = 0; j < vertexMaxNum; j++) {
            matrix[i][j] = DEFAULT_FILL;
        }
    }
    fstream f;
    f.open(file, ios::in);
    char buf[1024] = {0};
    while (f.getline(buf, sizeof(buf))) {
        int pos1 = -1, pos2 = -1;
        for (int i = 0; buf[i] != '\0'; i++) {
            if (buf[i] == ' ') {
                if (pos1 < 0) pos1 = i;
                else pos2 = i;
            }
        }
        // 从文件中获取对应的数据
        string start = string(buf, 0, pos1);
        string end = string(buf, pos1 + 1, pos2 - pos1);
        string val = string(buf, pos2 + 1, strlen(buf) - pos2);
        // 将数据拷贝至数据区域
        addEdge(stol(start), stoi(end), stoi(val));
    }
    f.close();
}

MatrixUndirect::~MatrixUndirect() {
    if (matrix != NULL) {
        delete matrix;
    }
}

void MatrixUndirect::display() {
    printf("\n 行\\列");
    for (int j = minVertexEnd; j <= maxVertexEnd; j++) {
        printf("%4d", j);
    }
    for (int i = minVertexStart; i <= maxVertexStart; i++) {
        printf("\n%4d  ", i);
        for (int j = minVertexEnd; j <= maxVertexEnd; j++) {
            if (matrix[i][j] == DEFAULT_FILL) {
                printf("    ");
            } else {
                printf("%4d", matrix[i][j]);
            }
        }
    }
}

int MatrixUndirect::getEdge(int vertexStart, int vertexEnd) {
    if (vertexStart > vertexMaxNum || vertexEnd > vertexMaxNum) {
        promptInfo(1);
        return -2;
    }
    return matrix[vertexStart][vertexEnd];
}

bool MatrixUndirect::setEdge(int vertexStart, int vertexEnd, int weight) {
    matrix[vertexStart][vertexEnd] = weight;
    matrix[vertexEnd][vertexStart] = weight;
    return true;
}

int MatrixUndirect::update(int vertexStart, int vertexEnd, int weight) {
    if (vertexStart > vertexMaxNum || vertexEnd > vertexMaxNum) {
        promptInfo(1);
        return -2;
    }
    int preWeight = getEdge(vertexStart, vertexEnd);
    setEdge(vertexStart, vertexEnd, weight);
    return preWeight;
}

bool MatrixUndirect::addEdge(int vertexStart, int vertexEnd, int weight) {
    if (vertexStart > vertexMaxNum || vertexEnd > vertexMaxNum) {
        promptInfo(1);
        return false;
    }
    int minTemp = vertexStart < vertexEnd ? vertexStart : vertexEnd;
    int maxTemp = vertexStart > vertexEnd ? vertexStart : vertexEnd;
    if (minTemp < minVertexStart) {
        minVertexStart = minTemp;
        minVertexEnd = minTemp;
    }
    if (maxTemp > maxVertexEnd) {
        maxVertexStart = maxTemp;
        maxVertexEnd = maxTemp;
    }
    if (matrix[vertexStart][vertexEnd] == DEFAULT_FILL) {
        setEdge(vertexStart, vertexEnd, weight);
        return true;
    }
    return false;
}

bool MatrixUndirect::delEdge(int vertexStart, int vertexEnd) {
    if (vertexStart > vertexMaxNum || vertexEnd > vertexMaxNum) {
        promptInfo(1);
        return false;
    }
    if (matrix[vertexStart][vertexEnd] != DEFAULT_FILL) {
        setEdge(vertexStart, vertexEnd, DEFAULT_FILL);
        return true;
    }
    return false;
}

void MatrixUndirect::promptInfo(int kind) {
    switch (kind) {
        case 1:
            cout << "\n[Info]存在异常信息，点最大为" << vertexMaxNum << endl;
            break;
    }
}

#endif
