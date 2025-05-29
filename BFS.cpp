#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Pos // mais fácil de guardar as cords. na fila
{
    int x, y;
};


int floodFill(string filename) { // não esquece de mandar com .txt, se achar ruim depois mudamos
    ifstream file(filename); 

    if (!file.is_open()) {
        cerr << "Não abriu" << endl;
        return -1;
    }

    int linhas, colunas;
    file >> linhas >> colunas; // >> é do fstream, pega uma palavra só, para no espaço se eu não me engano

    vector<string> grid(linhas); // gridzada dos guris

    for (int i = 0; i < linhas; ++i) { // vai preenchendo o labrinto
        file >> grid[i];
    }
    file.close();// fecha pra não deixar abrido

    int startX =0, startY = 0; // cords. do S

    const int INF = 1000000000; // numero g.p.c
    vector<vector<int>> dist(linhas, vector<int>(colunas, INF)); // distancias
    queue<Pos> fila;

    dist[startX][startY] = 0; 
    fila.push({startX, startY});

    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}; // pares pra mover, segui a imagem que eu tinha feito
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    while (!fila.empty()) {
        auto [x, y] = fila.front(); // pega o ponto atual
        fila.pop();

        char altura = grid[x][y]; //altura desse ponto
        if (altura == 'S') altura = 'a'; // S = a

        for (int d = 0; d < 8; ++d) { // verifica os vizinhos, usa o esquema que eu desenhei
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas) {
                char alturaVizinho = grid[nx][ny]; // pega a altura do vizinho pra comparar se pode ir ou não
                if (alturaVizinho == 'S') alturaVizinho = 'a';

                if (dist[nx][ny] == INF && (alturaVizinho <= altura + 1)) { // confere se ele ainda não foi visitado e se pode ir nele
                    dist[nx][ny] = dist[x][y] + 1;
                    fila.push({nx, ny});
                }
            }
        }
    }

    int menorCaminho = INF; // começa com um numero g.p.c e passa por todos em busca do menor caminho existente pra algum z, ele vai chechar todos os z
    for (int i = 0; i < linhas; ++i) { 
        for (int j = 0; j < colunas; ++j) {
            if (grid[i][j] == 'z') {
                if (dist[i][j] < menorCaminho) {
                    menorCaminho = dist[i][j];
                }
            }
        }
    }

    return ((menorCaminho == INF )? -1 : menorCaminho);
}

int main(){ //fiz isso pra ficar mais facil de rodar todos os testes
    cout << "qual o arquivo?" << endl;
    string filename;
    cin >> filename ;
    cout << endl <<"caso0050: "<< floodFill(filename) << endl;
}
