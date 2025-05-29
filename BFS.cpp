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
        cerr << "Nao foi possivel localizar o arquivo, confira se o nome do arquivo esta correto e se ele esta na mesma pasta." << endl;
        return -1;
    }

    int linhas, colunas;
    file >> linhas >> colunas; // >> é do fstream, pega uma palavra só, para no espaço se eu não me engano

    vector<string> grid(linhas); // gridzada dos guris

    for (int i = 0; i < linhas; ++i) { // vai preenchendo
        file >> grid[i];
    }
    file.close();// fecha pra não deixar abrido

    int startX = 0, startY = 0; // cords. do S

    const int GPC = 1000000000; // numero g.p.c
    vector<vector<int>> dist(linhas, vector<int>(colunas, GPC));
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
            int vx = x + dx[d]; //pega o (x,y) do que estamos testando e soma com cada um dos pares (x,y) que servem pra achar os vizinhos
            int vy = y + dy[d];

            if (vx >= 0 && vx < linhas && vy >= 0 && vy < colunas) {
                char alturaVizinho = grid[vx][vy]; // pega a altura do vizinho pra comparar se pode ir ou não
                if (alturaVizinho == 'S') alturaVizinho = 'a';

                if (dist[vx][vy] == GPC && (alturaVizinho <= altura + 1)) { // confere se ele ainda não foi visitado e se pode ir nele
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
        cout << "Solucao do T2 de Alest II - Feito por Lucas G. e Rodrigo M. " << endl
             << "Deseja comecar? (S/N)  ";
        cin >> enable_start;
        if( enable_start == 'S' || enable_start == 's'){
            for(int i = 0; i < 9; i++) {
                switch (i) {
                    case 0:
                        filename = "caso0050.txt";
                        cout << endl << "caso0050: " << floodFill(filename) << endl;
                        break;
                    case 1:
                        filename = "caso0100.txt";
                        cout << endl << "caso0100: " << floodFill(filename) << endl;
                        break;
                    case 2:
                        filename = "caso0200.txt";
                        cout << endl << "caso0200: " << floodFill(filename) << endl;
                        break;
                    case 3:
                        filename = "caso0400.txt";
                        cout << endl << "caso0400: " << floodFill(filename) << endl;
                        break;
                    case 4:
                        filename = "caso0800.txt";
                        cout << endl << "caso0800: " << floodFill(filename) << endl;
                        break;
                    case 5:
                        filename = "caso1000.txt";
                        cout << endl << "caso1000: " << floodFill(filename) << endl;
                        break;
                    case 6:
                        filename = "caso1500.txt";
                        cout << endl << "caso1500: " << floodFill(filename) << endl;
                        break;
                    case 7:
                        filename = "caso2000.txt";
                        cout << endl << "caso2000: " << floodFill(filename) << endl;
                        break;
                    default:
                        break;
                }   
            } 
        }  else cout << "Fim. "; 

}   
