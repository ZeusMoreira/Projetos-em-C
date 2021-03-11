#include <stdio.h>
#define MAX 1000

// Criptografia URI
// Criado por Zeus Moreira 16/01/2020
/* Programa que criptografa uma mensagem de acordo com padrões estabelecidos */

int main()
{
    char codigo[MAX];               /* String que recebe a mensagem à ser criptografada */
    int n,i,g;                      /* n = numero de testes, i = indice do ciclo teste, g = indice do ciclo para emitir a mensagem criptografada */
    int j,l;                        /* j = usado como tamanho da string e seu indice, l = usado como indice da string */
    char aux;                       /* Usado para inverter a linha na segunda passagem */

    scanf("%d ",&n);
    for(i=0; i < n; i++)           /* Ciclo de numero de teste */
    {
        scanf(" %[^\n]",codigo);    /* Leitura da string incluindo o ' ' */
        j=0;
        while(codigo[j] != '\0')    /* Ciclo que verifica o tamanho da string e altera 3 posições à direita os caracteres letra minuscula e maiuscula */
        {
            if((codigo[j] >= 65 && codigo[j] <= 90) || (codigo[j] >= 97 && codigo[j] <= 122))
                    codigo[j] = codigo[j] + 3;
            j++;
        }

        l=0;
        while(l < j / 2)   /* Ciclo que inverte a string */
        {
            aux = codigo[l];           /* aux recebe o primeiro elemento da string para poder fazer a inversão */
            codigo[l] = codigo[j-1-l]; /* O elemento 0 recebe o ultimo elemento da string */
            codigo[j-1-l] = aux;       /* O ultimo elemento recebe o elemento 0  da string */
            l++;                       /* Valor que varia para poder varrer string elemento à elemento invertendo as "pontas" da string até o meio */
        }

        for(g = l; g < j; g++)  /* Ciclo responsável por mudar a segunda metade da string um elemento a esquerda */
            codigo[g] = codigo[g] - 1;

        printf("%s",codigo);    /* Mensagem criptografada */
        printf("\n");
    }
    return 0;
}