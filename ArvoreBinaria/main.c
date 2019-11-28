#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

int main(int argc, char const *argv[])
{
    ArvBin* raiz = cria_ArvBin();

    int altura =  AlturaArvBin(raiz);
    int total_nos = TotalNos(raiz);
    return 0;


}
