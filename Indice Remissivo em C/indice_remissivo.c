#include <stdio.h>
#include <string.h>  /* Biblioteca necessária para manipulação de strings */
#include <stdlib.h>  /* Biblioteca que permite a alocação de memória */
#include <ctype.h>   /* Biblioteca que facilita o trabalho de definir palavras */
#define MAX 10001


/* Aluno: Zeus Moreira de Lima Pereira */
/* Disciplina: Prog 2 , Programa: Indice remissivo */
/* Ultima ed: 13:26, 21/11/2020 */

/* Cabeçalho */
typedef struct first first;    /* O formato de cada célula da nossa lista principal */
typedef struct second second;  /* O formato de cada célula da nossa lista secundária */
struct second{
    int pg;        // Paragráfo em que uma determinada palavra está
    int ln;        // Linha
    int cl;        // Coluna
    second *prox;  // Permite a ligação dentre células da lista secundária
};
struct first{
    char *termo;    // Palavra a qual deseja-se informação
    int casos;      // Quantas vezes essa palavra ocorre
    second *inicio; // Permite a ligação da lista secundária a uma célula da lista primária
    second *fim;    // Conecta-se ao final da lista secundária
    first *prox;    // Permite a ligação dentre células da lista primária
};
/* Fim do cabeçalho */


////////////////////////////////////////////////////////////////////////////////// FUNÇÕES ///////////////////////////////////////////////////////////////////////////////////
/* Função que verifica quantas palavras há no texto */
int word(char *texto){
    int i=0,palavra=0;
    while (texto[i] != '\0')
    {
        if (texto[i] == ' ' || texto[i] == '\n' || (texto[i] == '@' && (!isspace(texto[i-1]))))
            palavra++;
        if ((texto[i] == '\n' && texto[i+1] == '\n') || (ispunct(texto[i]) && isspace(texto[i-1]) && (isspace(texto[i+1]) || ispunct(texto[i+1]))))
            palavra--;
        i++;
    }

    return palavra;
}
/* Função que verifica quantas linhas há no texto */
int line(char *texto){
    int i=0,linha=0;
    while (texto[i] != '\0')
    {
        if (texto[i] == '\n')
            linha++;
        else if (texto[i] == '@' && texto[i-1] != '\n')
            linha++;

        i++;
    }
    return linha;
}
/* Função que verifica quantos paragráfos há no texto */
int parag(char *texto){
    int i=0,graph=0;
    while (texto[i] != '\0')
    {
        if (texto[i] == '\n' && (texto[i+1] == '\n' || texto[i+1] == '@'))
            graph++;
        else if (texto[i] == '@' && texto[i-1] != '\n')
            graph++;

        i++;
    }
    return graph;
}
/* Função que fornece a verificação do menor primo maior que n */
int primo(int n){
    if (n == 1)
        return 0;

    for(int i=2; i<n; i++){
        if(n==2)
            return 1;
        if (n%i!=0)
            continue;
        else
            return 0;
    }
    return 1;
}
/* Função que fornece a quantidade de vezes que uma palavra o ocorreu no texto */
int ocorrencia(char *texto, char *string){

    char *achei = strstr(texto,string);
    int oc = 0;
    while (achei != NULL)
    {
        if (((ispunct(*(achei-1)) || isspace(*(achei-1))) && *(achei-1) != '-')  &&  ((ispunct(*(achei+strlen(string))) || isspace(*(achei+strlen(string)))) && *(achei+strlen(string)) != '-'))
            oc++;
        achei += strlen(string);
        achei = strstr(achei,string);
    }

    return oc;
}
/* Função que coloca a palavra no indice correto do vetor tab */
int apropriado(char *string,int tam){
    int i,x=0;
    for(i=0; i < tam; i++)
        x += string[i];
    return x;
}
/* Função que verifica em qual paragráfo está uma certa palavra */
int pag(char *texto, char *rst){
    char *help = texto;
    int prf=1;
    while (help < rst)
    {
        if (*(help) == '\n' && *(help+1) == '\n')
            prf++;
        help++;
    }
    return prf;
}
/* Função que verifica em qual coluna está uma certa palavra */
int col(char *texto, char *rst){
    char *help = texto;
    int cln = 1;
    while (help < rst)
    {
        if (*(help) == '\n')
            cln = 1;
        else
            cln++;
        help++;
    }
    return cln;
}
/* Função que verifica em qual linha está uma certa palavra */
int lin(char *texto, char *rst){
    char *help = texto;
    int lne=1;
    while (help < rst)
    {
        if (*(help) == '\n')
            lne++;
        if(*(help) == '\n' && *(help+1) == '\n')
            lne = 0;

        help++;
    }
    return lne;
}
/* Função que adiciona uma célula a lista primária */
void adiciona(first *tab, first *nova){
    first *aux = tab;
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = nova;
    nova->prox = NULL;
}
/* Função que adiciona uma célula a lista secundária */
void adiciona2(first *header,second *begin){
    second *bora = header->inicio;
    while (bora->prox != NULL)
        bora = bora->prox;
    bora->prox = begin;
    header->fim = begin;
    begin->prox = NULL;
}
/* Função que aloca a cabeça pra cada indice do vetor de ponteiros tab */
void tabv(first *tab[], int n){
    int l;
    for (l=0; l < n; l++)
    {
        first *pointer = malloc(sizeof(first));
        pointer->prox = NULL;
        tab[l] = pointer;
    }
}
/* Função que preenche uma célula da lista principal */
void preencherF(first *nova, char *str, int ocor,second *head){

    nova->termo = str;
    nova->casos = ocor;
    nova->inicio = head;
    nova->fim = head;

}
/* Função que preenche uma célula da lista principal */
void preencherS(second *begin,int a,int b, int c){
    begin->pg = a;
    begin->cl = b;
    begin->ln = c;
}
/* Funçao que libera todas as células de uma lista secundária de uma certa célula da lista primária */
void free_s(second *ini){
    if (ini->prox == NULL)
        free(ini);

    else{
        while (ini != NULL)
        {
            second *tmp = ini;
            ini = ini->prox;
            free(tmp);
        }
    }
}
/* Funçao que libera todas as células de uma lista primária de um indice do vetor tab */
void free_f(first *tab){

    if (tab->prox == NULL)
        free(tab);

    else{
        while (tab != NULL)
        {
            first *tmp = tab;
            tab = tab->prox;
            free(tmp);
        }
    }
}
/* Função que limpa o buffer para permitir a leitura correta de uma string ou de um char */
void limpabuffer(){
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}
////////////////////////////////////////////////////////////////////////////////// FIM ////////////////////////////////////////////////////////////////////////////////////////


/* Main */
int main()
{
    int k,i;
    scanf("%d",&k);
    limpabuffer();


    for (i=0; i < k; i++)
    {
        /* Leitura do texto,adequações e alocação. */
        char *texto,pula;
        scanf("%c",&pula);
        texto = malloc(sizeof(char)*MAX);
        if (texto == NULL)
            return 0;
        scanf("%[^@]",texto);
        texto[strlen(texto)] = '@';
        texto[strlen(texto)+1] = '\0';
        texto = realloc(texto,sizeof(char)*strlen(texto));
        if (texto == NULL)
            return 0;
        limpabuffer();
        scanf("%c",&pula);
        /* Fim */

        /* n = Numero de palavras do indice remissivo, aux = Salva o valor de n, j = contador */
        int n,aux,j;
        scanf("%d",&n);
        aux = n;

        /* Definição do menor primo maior que n */
        while (primo(n) == 0)
            n++;

        /* Declaração do vetor de listas tab e criação das n cabeças */
        first *tab[n];
        tabv(tab,n);
        limpabuffer();


        /* Ciclo 1: Lê as aux palavras desejadas, criação das celulas das duas listas e seu preenchimento */
        for (j=0; j < aux; j++)
        {

            /* Alocação da memória para as células das duas listas e da palavra desejada */
            int x,l,yes=1;
            char *str;
            str = malloc(sizeof(char));
            if (str == NULL)
                return 0;
            first *nova = malloc(sizeof(first));
            if (nova == NULL)
                return 0;
            second *head = malloc(sizeof(second));
            if (head == NULL)
                return 0;
            head->prox = NULL;
            /* Fim */

            /* Leitura da palavra e preenchimento da célula da lista primária e adição no indice correto de tab */
            scanf("%[^\n]",str);
            limpabuffer();
            preencherF(nova,str,ocorrencia(texto,str),head);
            x = apropriado(str,strlen(str))%n;
            adiciona(tab[x],nova);
            /* Fim */

            /* Ciclo auxiliar interno: preenche e adiciona a lista secundária na lista primária */
            char *result = strstr(texto,str);
            for (l=0; l < nova->casos; l++)
            {
                yes=1;
                while (yes){
                    if (((*(result) == texto[0] || ispunct(*(result-1)) || isspace(*(result-1))) && *(result-1) != '-')  &&  ((ispunct(*(result+strlen(str))) || isspace(*(result+strlen(str)))) && *(result+strlen(str)) != '-'))
                        yes = 0;
                    else{
                        result += strlen(str);
                        result = strstr(result,str);
                    }
                }
                second *begin = malloc(sizeof(second));
                if (begin == NULL)
                    return 0;
                preencherS(begin,pag(texto,result),col(texto,result),lin(texto,result));
                adiciona2(nova,begin);
                result += strlen(str);
                result = strstr(result,str);

            }
            /* Fim */
        }


        /* Impressão dos dados construídos */
        printf("Totais do texto %d:\n",i+1);
        printf("  Palavras: %d\n",word(texto));
        printf("  Linhas: %d\n",line(texto));
        printf("  Paragrafos: %d\n",parag(texto));
        printf("\nIndice remissivo:\n");

        int p;
        for (p = 0; p < n; p++)
        {
            first *f = tab[p]->prox;
            if(tab[p]->prox != NULL){

                while (f != NULL){
                    if (f->casos == 0)
                        printf("  %s nao ocorre no texto",f->termo);

                    else{
                        printf("  %s [%d]:",f->termo,f->casos);
                        second *s = f->inicio->prox;

                        int m = 0;
                        while (s != NULL){

                            if (m < f->casos-1)
                                printf(" (%d, %d, %d),",s->pg,s->ln,s->cl);
                            else
                                printf(" (%d, %d, %d)",s->pg,s->ln,s->cl);

                            m++;
                            s = s->prox;
                        }
                        free_s(f->inicio);
                    }

                    f = f->prox;
                    printf("\n");

                }

            }
        }
        printf("\n");
        /* Fim */

        /* Liberação da memória das células das listas principais */
        for (p = 0; p < n; p++)
            free_f(tab[p]);
        free(texto);
    }

    return 0;
}
