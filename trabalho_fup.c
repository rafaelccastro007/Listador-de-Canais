#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    int id;
    char nome[100];
    float numero;
    char categoria[50];
}Canais;

void imprimir_lista(Canais *lista, int n) {
    if (n == 0) {
        printf("Nenhum programa cadastrado.\n");
    } else {
        printf("== Lista de Canais Cadastrados ===\n");

        for (int i = 0; i < n; i++) {
            printf("---------------------------\n");
            printf("ID: %d\n", lista[i].id);
            printf("Nome: %s\n", lista[i].nome);
            printf("Numero: %.2f\n", lista[i].numero);
            printf("Categoria: %s\n", lista[i].categoria);
            printf("---------------------------\n");
        }
    }
}


Canais* adiciona_canal(Canais *lista,int *n, Canais prog){
    lista = realloc(lista,(*n+1) * sizeof(Canais));
    if(lista == NULL){
        printf("Erro ao adicionar este programa!!!\n");
        return lista;
    }

    lista[*n] = prog;

    *n = *n+1;
    
    
    return lista;

}


void salvar_arquivo(Canais *lista,int n){
    FILE *arquivo;
    arquivo = fopen("Dados.txt","w");
    fprintf(arquivo,"%d\n",n);
    for(int i=0;i<n;i++){
        fprintf(arquivo,"%d\n",lista[i].id);
        fprintf(arquivo,"%s\n",lista[i].nome);
        fprintf(arquivo,"%f\n",lista[i].numero);
        fprintf(arquivo,"%s\n",lista[i].categoria);
    }
    fclose(arquivo);
}

Canais* ler_arquivo(int *n){
    FILE *arquivo;
    int qtd;
    arquivo = fopen("Dados.txt","r");
    if(arquivo == 0){
        printf("ERRO ao abrir o arquivo!\n");
        *n = 0;
        return NULL;
    }
     if(fscanf(arquivo,"%d", &qtd) != 1){
        fclose(arquivo);
        *n = 0;
        return NULL;
    }
    *n = qtd;
    printf("valor lido: %d\n", qtd);
    Canais *v = malloc(qtd*(sizeof(Canais)));
    for(int i = 0;i<qtd;i++){
        fscanf(arquivo,"%d", &v[i].id);
        fscanf(arquivo," %[^\n]",v[i].nome);
        fscanf(arquivo,"%f",&v[i].numero);
        fscanf(arquivo," %[^\n]", v[i].categoria);
    }
    fclose(arquivo);
    return v;
}

Canais* remover_canal(Canais *lista, int *n, int id){
    int rastreador = -1;
    for(int i=0;i<*n;i++){
        if(lista[i].id == id){
            rastreador = i;
            break;
        }
    }
    if(rastreador == -1){
        printf("Canal com o ID %d nao encontado.\n",id);
        return lista;
    }


    for(int i = rastreador;i < *n - 1;i++ ){
        lista[i] = lista[i+1];

    }
    *n = *n-1;
    lista = realloc(lista,(*n) * sizeof(Canais));
    printf("Canal com ID %d removido com sucesso.\n",id);
    salvar_arquivo(lista,*n);
    return lista;
}

void ordenarPorNome(Canais *lista, int n) {
    int i, j;
    Canais temp;
    for(i = 0; i < n-1; i++) {
        for(j = 0; j < n-i-1; j++) {
            if(strcasecmp(lista[j].nome, lista[j+1].nome) > 0) {
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

int main(){
    int n = 0;
    Canais *lista = ler_arquivo(&n);
    printf("\n\n");
    printf(" $$$$$$\\  $$\\        $$$$$$\\  $$$$$$$\\   $$$$$$\\     $$$$$$$$\\ $$\\    $$\\ \n");
    printf("$$  __$$\\ $$ |      $$  __$$\\ $$  __$$\\ $$  __$$\\    \\__$$  __|$$ |   $$ |\n");
    printf("$$ /  \\__|$$ |      $$ /  $$ |$$ |  $$ |$$ /  $$ |      $$ |   $$ |   $$ |\n");
    printf("$$ |      $$ |      $$$$$$$$ |$$$$$$$  |$$ |  $$ |      $$ |   \\$$\\  $$  |\n");
    printf("$$ |      $$ |      $$  __$$ |$$  __$$< $$ |  $$ |      $$ |    \\$$\\$$  / \n");
    printf("$$ |  $$\\ $$ |      $$ |  $$ |$$ |  $$ |$$ |  $$ |      $$ |     \\$$$  /  \n");
    printf("\\$$$$$$  |$$$$$$$$\\ $$ |  $$ |$$ |  $$ | $$$$$$  |      $$ |      \\$  /   \n");
    printf(" \\______/ \\________|\\__|  \\__|\\__|  \\__| \\______/$$$$$$\\\\__|       \\_/    \n");
    printf("                                                 \\______|                \n");
    
    printf("\n");
    while(1){
        printf("***************************************************************************************************************************************\n");
        printf("[1] - LISTAR TODOS OS CANAIS  ");
		printf("[2] - ADICIONAR UM CANAL A SUA LISTA  ");
		printf("[3] - REMOVER UM CANAL DA LISTA  ");
        printf("[4] - ORDENAR POR NOME  ");
		printf("[0] - SAIR\n");
        printf("***************************************************************************************************************************************\n");
        int op;
        scanf("%d",&op);
        switch (op){
        case 0:
            free(lista);
            return 0;
        case 1:
        imprimir_lista(lista,n);
        break;
        case 2:
        printf("\n\n");
        Canais prog;
        int novo_id = 1; 
        for (int i = 0; i < n; i++) {
            if (lista[i].id >= novo_id) {
                novo_id = lista[i].id + 1;
            }
        }
        prog.id = novo_id;

            printf("Digite o nome do canal que deseja adicionar:\n ");
            scanf(" %[^\n]", prog.nome);

            printf("Digite o numero do canal:\n ");
            scanf("%f",&prog.numero);
            
            printf("Digite a categoria deste canal:\n ");
            scanf(" %[^\n]",prog.categoria);
            
            lista = adiciona_canal(lista,&n,prog);
            salvar_arquivo(lista,n);
            break;
        case 3:
            printf("Diga o ID do canal para a remoção\n");
            int index;
            scanf("%d",&index);
            lista = remover_canal(lista,&n,index);
            break;
        case 4:
        ordenarPorNome(lista, n);
        printf("Canais ordenados sucesso!\n");
        salvar_arquivo(lista, n);
        break;
        }

    }
    free(lista);
    return 0;
}