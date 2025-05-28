#include <iostream>
#include <vector>
#include <string>


class graphs{
private:
int largura, altura;

public:
 graphs::graphs(int l, int a){
    largura = l;
    altura = a;
}
int getAltura();
int getLargura();
};