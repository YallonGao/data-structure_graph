#ifndef GRAPH_MATRIXDIRECT_H
#define GRAPH_MATRIXDIRECT_H

#include "cstdio"
#include "fstream"
#include "iostream"
#include "cstring"

using namespace std;
#define DEFAULT_SIZE 10
#define DEFAULT_FILL -1

class MatrixDirect {
public:
    MatrixDirect(int setVertexMaxNum = DEFAULT_SIZE);

    MatrixDirect(const string &file, int setVertexMaxNum = DEFAULT_SIZE);

    ~MatrixDirect();

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

MatrixDirect::MatrixDirect(int setVertexMaxNum) {
    vertexMaxNum = setVertexMaxNum + 1;
    matrix = new int *[vertexMaxNum];
    for (int i = 0; i < vertexMaxNum; i++) {
        matrix[i] = new int[vertexMaxNum];
        for (int j = 0; j < vertexMaxNum; j++) {
            matrix[i][j] = DEFAULT_FILL;
        }
    }
}

MatrixDirect::MatrixDirect(const string &file, int setVertexMaxNum) {
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

MatrixDirect::~MatrixDirect() {
    if (matrix != NULL) {
        delete matrix;
    }
}

void MatrixDirect::display() {
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

int MatrixDirect::getEdge(int vertexStart, int vertexEnd) {
    if (vertexStart > vertexMaxNum || vertexEnd > vertexMaxNum) {
        promptInfo(1);
        return -2;
    }
    return matrix[vertexStart][vertexEnd];
}

bool MatrixDirect::setEdge(int vertexStart, int vertexEnd, int weight) {
    matrix[vertexStart][vertexEnd] = weight;
    return true;
}

int MatrixDirect::update(int vertexStart, int vertexEnd, int weight) {
    if (vertexStart > vertexMaxNum || vertexEnd > vertexMaxNum) {
        promptInfo(1);
        return -2;
    }
    int preWeight = getEdge(vertexStart, vertexEnd);
    setEdge(vertexStart, vertexEnd, weight);
    return preWeight;
}

bool MatrixDirect::addEdge(int vertexStart, int vertexEnd, int weight) {
    if (vertexStart > vertexMaxNum || vertexEnd > vertexMaxNum) {
        promptInfo(1);
        return false;
    }
    if (vertexStart < minVertexStart) minVertexStart = vertexStart;
    if (vertexStart > maxVertexStart) maxVertexStart = vertexStart;
    if (vertexEnd < minVertexEnd) minVertexEnd = vertexEnd;
    if (vertexEnd > maxVertexEnd) maxVertexEnd = vertexEnd;
    if (matrix[vertexStart][vertexEnd] == DEFAULT_FILL) {
        setEdge(vertexStart, vertexEnd, weight);
        return true;
    }
    return false;
}

bool MatrixDirect::delEdge(int vertexStart, int vertexEnd) {
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

void MatrixDirect::promptInfo(int kind) {
    switch (kind) {
        case 1:
            cout << "\n[Info]存在异常信息，点最大为" << vertexMaxNum << endl;
            break;
    }
}

#endif
