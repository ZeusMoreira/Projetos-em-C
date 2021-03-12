#include <stdio.h>
#define MAX 60
/* Código implementado por Zeus Moreira */
/* Fibonacci em C URI */

int main()
{
    unsigned long long int fib[MAX];            /* Variavel apropriada de acordo com o que foi pedido no problema */         
    int i,n,j,a;                                /* i = contador do ciclo de leitura do fib desejado, n = numero de testes */
                                                /* j = Fib desejado pelo usuário, a = definição dos valores do Fibonacci */
                                            
    fib[0] = 0;                                 /* Casos base do Fibonacci */
    fib[1] = 1;

    for(a=2; a <= MAX; a++)                     /* Ciclo que atribui valor ao fib apartir dos valores da base */
        fib[a] = fib[a-1] + fib[a-2];           /* Definição do Fibonacci */

    scanf("%d",&n);
    for(i=0; i < n; i++)                        /* Ciclo que lê o fib desejado e imprime o seu valor */
    {
        scanf("%d",&j);
        printf("Fib(%d) = %llu\n",j,fib[j]);
    }

    return 0;
}