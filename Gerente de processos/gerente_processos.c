#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DESCR 50
#define MAX 100

/* Aluno: Zeus Moreira de Lima Pereira */
/* Disciplina: Prog 2 , Programa: Gerente de processos */
/* Ultima ed: 07:26, 05/10/2020 */

/* Cabeçalho */

/* Armazena um horário de chegada */
typedef struct{
    int hh;
    int mm;
    int ss;
} horario;

/* Armazena informações de um processo */
typedef struct{
    int prior;
    horario chegada;
    char descricao[MAX_DESCR+1];
} celula;

void mergesort();
 /* Fim do cabeçalho */

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Função "add" que adiciona uma tarefa ao gerenciador de tarefas */
void add(celula inicio,celula vet[MAX],int tamanho){
    int i;
    for(i = tamanho; i <= tamanho ; i++){
        vet[i].prior = inicio.prior;
        vet[i].chegada = inicio.chegada;
        strcpy(vet[i].descricao,inicio.descricao);
    }
}

/* Função "exec que ja executa o processo com maior prioridade de acordo com -p ou -t escolhidos */
void exec(char exe[3],int tamanho,int p,celula vet[MAX]){
    int m;
    mergesort(p,tamanho,vet,exe);
    for (m = 0; m < tamanho-1;m++)
        vet[m] = vet[m+1];
}

/* Função "next" que mostra qual a proxima tarefa a ser realizada, podendo ser por -t ou -p*/
void next(char exe[3],int tamanho,celula vet[MAX],int p){
    mergesort(p,tamanho,vet,exe);
    printf("%02d %02d:%02d:%02d %s\n",vet[0].prior,vet[0].chegada.hh, vet[0].chegada.mm, vet[0].chegada.ss, vet[0].descricao);
 }

/* Função "Change" para o parâmetro prioridade (-p), mudando a prioridade de execução da tarefa */
void change(celula vet[MAX],int novo, int anterior,int tamanho ){
    int i;
    for (i=0; i < tamanho; i++){
        if (vet[i].prior == anterior){
            vet[i].prior = novo;
            break;
        }
    }
}

/* Função "Change2" para o parâmetro tempo (-t), mudando o horario de execução da tarefa*/
void change2(celula vet[MAX],horario nova, horario antes,int tamanho){
    int i;
    for (i=0; i < tamanho; i++){
        if((antes.hh == vet[i].chegada.hh) && (antes.mm == vet[i].chegada.mm) && (antes.ss == vet[i].chegada.ss)){
            vet[i].chegada.hh = nova.hh;
            vet[i].chegada.mm = nova.mm;
            vet[i].chegada.ss = nova.ss;
            break;
        }
    }
}

/* Função "print" que mostra,de acordo com a escolha (-p) ou (-t), a sequencia da lista de tarefas ordenada */
void print(char exe[3],int tamanho,celula vet[MAX],int p){
    int m = 0;
    mergesort(p,tamanho,vet,exe);
    for (m = 0; m < tamanho; m++){
        printf("%02d %02d:%02d:%02d %s",vet[m].prior,vet[m].chegada.hh,vet[m].chegada.mm,vet[m].chegada.ss, vet[m].descricao);
        printf("\n");
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Função que converte a data inserida em segundos para calcular a precedencia */
int converte_segundos(celula vet[MAX],int y){
    return vet[y].chegada.hh * 3600 + vet[y].chegada.mm * 60 + vet[y].chegada.ss;
}

/* Aqui começa o desenvolvimento do mergesort para ordenarmos quais tarefas serão realizadas primeiro */
void intercala(int p, int q, int tamanho,celula vet[MAX],char exe[3])
{
    int i, j, k;
    celula w[MAX];
    i = p; j = q; k = 0;

    while (i < q && j < tamanho) {
        /* Caso a prioridade seja o principal parametro */
        if (strcmp(exe,"-p") == 0){
            if (vet[i].prior > vet[j].prior) {
                w[k].prior = vet[i].prior;
                w[k].chegada = vet[i].chegada;
                strcpy(w[k].descricao,vet[i].descricao);
                i++;
            }
            else {
                w[k].prior = vet[j].prior;
                w[k].chegada = vet[j].chegada;
                strcpy(w[k].descricao,vet[j].descricao);
                j++;
            }
        }
        /* Caso o tempo seja o principal parâmetro */
        else if (strcmp(exe,"-t") == 0){
            if (converte_segundos(vet,i) < converte_segundos(vet,j)) {
                w[k].prior = vet[i].prior;
                w[k].chegada = vet[i].chegada;
                strcpy(w[k].descricao,vet[i].descricao);
                i++;
            }
            else {
                w[k].prior = vet[j].prior;
                w[k].chegada = vet[j].chegada;
                strcpy(w[k].descricao,vet[j].descricao);
                j++;
            }
        }
    k++;
    }
    /* Agora inicia o preenchimento dos elementos que sobraram na intercalação */
    while (i < q) {
        w[k].prior = vet[i].prior;
        w[k].chegada = vet[i].chegada;
        strcpy(w[k].descricao,vet[i].descricao);
        i++;
        k++;
    }

    while (j < tamanho) {
        w[k].prior = vet[j].prior;
        w[k].chegada = vet[j].chegada;
        strcpy(w[k].descricao,vet[j].descricao);
        j++;
        k++;
    }

    for (i = p; i < tamanho; i++){
        vet[i].prior = w[i-p].prior;
        vet[i].chegada = w[i-p].chegada;
        strcpy(vet[i].descricao,w[i-p].descricao);
    }
}

void mergesort(int p,int tamanho,celula vet[MAX],char exe[3]){
    int q;
    if (p < tamanho-1) {
        q = (p + tamanho) / 2;
        mergesort(p, q, vet,exe);
        mergesort(q, tamanho, vet,exe);
        intercala(p, q, tamanho, vet,exe);
    }
}
/* Fim do mergesort */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Main */
int main()
{
    int tamanho=0;
    while(1){
        char instrucao[7];   /* String que contém a instrução desejada */
        celula vet[MAX];     /* Um vetor do tipo "celula" utilizado para manipular as tarefas */
        celula inicio;       /* Adiciona uma nova tarefa ao celula vet[MAX] */
        horario hora;        /* Preenchimento da hora que a tarefa do celula inicio foi adicionada */
        int novo,anterior;   /* Quando a função change for requisitada com a opção -p */
        char exe[3];         /* Comandos -p e -t */
        int p = 0;           /* Indice do primeiro elemento das tarefas */
        horario antes,nova;  /* Quando a função change2 for necessaria com a opção -t */

        scanf("%s",instrucao);
        /* Quando o comando digitado seja "quit" */
        if(strcmp(instrucao,"quit") == 0)
            return 0;

        /* Quando o comando digitado seja "add" */
        else if(strcmp(instrucao,"add") == 0){
            scanf("%d %d:%d:%d %[^\n]",&inicio.prior,&hora.hh,&hora.mm,&hora.ss,inicio.descricao);
            inicio.chegada = hora;
            add(inicio,vet,tamanho);
            tamanho++;
        }

        /* Quando o comando digitado seja "exec" */
        else if(strcmp(instrucao,"exec") == 0){
            scanf("%s",exe);
            exec(exe,tamanho,p,vet);
            tamanho--;
        }

        /* Quando o vetor digitado é o "next" */
        else if(strcmp(instrucao,"next") == 0){
           scanf("%s",exe);
           next(exe,tamanho,vet,p);
        }

         /* Quando o vetor digitado é o "opcao" */
        else if(strcmp(instrucao,"print") == 0){
           scanf("%s",exe);
           print(exe,tamanho,vet,p);
        }

        /* Quando o vetor digitado é o "change" */
        else if(strcmp(instrucao,"change") == 0){
           scanf("%s",exe);
           if (strcmp(exe,"-p") == 0){
                scanf("%d|%d",&novo,&anterior);
                change(vet,anterior,novo,tamanho);
           }
           else if (strcmp(exe,"-t") == 0){
                scanf("%d:%d:%d|%d:%d:%d",&antes.hh,&antes.mm,&antes.ss,&nova.hh,&nova.mm,&nova.ss);
                change2(vet,nova,antes,tamanho);
           }
        }
    }
    return 0;
}