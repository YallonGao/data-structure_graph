#include "MatrixUndirect.h"
#include "MatrixDirect.h"

void testMatrixUndirect() {
    cout<<"\n----------\n无向图临接矩阵，自定义图"<<endl;
    MatrixUndirect graph(100);
    graph.addEdge(1, 5, 100);
    graph.addEdge(2, 3, 9);
    graph.addEdge(1, 3, 4);
    graph.addEdge(4, 3, 11);
    graph.update(1, 5, 8);
    graph.delEdge(2, 3);
    graph.display();
}

void testMatrixDirect() {
    cout<<"\n----------\n有向图临接矩阵，自定义图"<<endl;
    MatrixDirect graph(100);
    graph.addEdge(1, 5, 100);
    graph.addEdge(2, 399, 9);
    graph.addEdge(4, 3, 11);
    graph.update(1, 5, 8);
    graph.delEdge(2, 3);
    graph.display();
}

void testMatrixUndirectFromFile() {
    cout<<"\n----------\n无向图临接矩阵，从文件导入数据"<<endl;
    MatrixUndirect graph("../resources/data.txt");
    graph.display();
}

void testMatrixDirectFromFile() {
    cout<<"\n----------\n有向图临接矩阵，从文件导入数据"<<endl;
    MatrixDirect graph("../resources/data.txt");
    graph.display();
}

int main() {
    testMatrixUndirect();
    testMatrixDirect();
    testMatrixUndirectFromFile();
    testMatrixDirectFromFile();
    return 0;
}
