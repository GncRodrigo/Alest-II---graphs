#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

scruct posicao{
    int x, y;
};

int floodFill(string filename) {  
    ifstream arquivo(filename);

    if (!arquivo.is_open()) {
        cerr << "Nao foi possivel localizar o arquivo" << endl;
        return -1;
    }
    int linhas, colunas;
    arquivo >> linhas >> colunas;

    vector<string> malha(linhas);
    for (int i = 0; i < linhas; ++i) {
        arquivo >> malha[i];
    }
    arquivo.close();


    const int GPC = 1000000000; 
    int inicialX = 0, inicialY = 0; 

    vector<vector<int>> dist(linhas, vector<int>(colunas, GPC));
    queue<Pos> fila;
    
    dist[inicialX][inicialY] = 0; 
    fila.push({inicialX, startY});


}