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

    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}; // pares pra mover, segui a imagem que eu tinha feito
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    while (!fila.empty()) {
    auto [x, y] = fila.front(); // pega o ponto atual
    fila.pop();
    char altura = grid[x][y]; //altura desse ponto
    if (altura == 'S') altura = 'a'; // S = a

    for (int d = 0; d < 8; ++d) { // verifica os vizinhos, usa o esquema que eu desenhei
        int vx = x + dx[d]; //pega o (x,y) do que estamos testando e soma com cada um dos pares (x,y) que servem pra achar os vizinhos
        int vy = y + dy[d];

        if (vx >= 0 && vx < linhas && vy >= 0 && vy < colunas) {
                char AlturadoVizinho = grid[vx][vy]; // pega a altura do vizinho pra comparar se pode ir ou não
            if (AlturadoVizinho == 'S') AlturadoVizinho = 'a';

            if (dist[vx][vy] == GPC && (AlturadoVizinho <= altura + 1)) { // confere se ele ainda não foi visitado e se pode ir nele
                    dist[vx][vy] = dist[x][y] + 1;
                    fila.push({vx, vy});
                }
            }
        }
    }

    int menorCaminho = GPC; // começa com um numero g.p.c e passa por todos em busca do menor caminho existente pra algum z, ele vai chechar todos os z
    for (int i = 0; i < linhas; ++i) { 
        for (int j = 0; j < colunas; ++j) {
            if (grid[i][j] == 'z') {
                if (dist[i][j] < menorCaminho) {
                    menorCaminho = dist[i][j];
                }
            }
        }
    }

    return ((menorCaminho == GPC )? -1 : menorCaminho);
}

int main(){ //fiz isso pra ficar mais facil de rodar todos os testes
        string filename;
        char enable_start = 0;
        cout << "Digite o nome do arquivo: ";
        cin >> filename;
        int resultado = floodFill(filename);
        cout << "Resultado: " << resultado << endl;
        return 0;
     }