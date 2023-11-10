#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cuidador{
    int disponibilidade;
    char nome[50];
    long int cpf;
    char cidade[30];
    char dia[15];
    char horario[30];
    char telefone[20];
} Cuidador;

void mudaDisponibilidade(Cuidador* servicos);

int preencheSelecao(int* selecao, int maximo){
    scanf("%d", selecao);

    if(*selecao == 0)
        return -1;
    
    if(*selecao <= maximo)
        return *selecao;
    
    else {
        printf("Selecione uma opção válida!\n");
        preencheSelecao(selecao, maximo); // recursão OK
    }
}

int countServicos(){
    FILE* arquivo;
    arquivo = fopen("./arquivos/cuidadores.txt", "r");

    int qtdServicos = 1;
    char c;
    do{
        c = fgetc(arquivo);
        if(c == '\n')
            qtdServicos++;
    }while(c != EOF);
    fclose(arquivo);
    return qtdServicos;
}

Cuidador* getServicos(){
    FILE* arq_cuidadores;
    arq_cuidadores = fopen("./arquivos/cuidadores.txt", "r");

    int qtdServicos = countServicos();
    Cuidador* servicos = (Cuidador*) malloc((qtdServicos-1)*(sizeof(Cuidador)));
    
    if(servicos == NULL){
        printf("Erro na alocação de memória!\n");
        exit(1);
    }

    int i = 0;

    char infoServico[200];

    while(fgets(infoServico, 200, arq_cuidadores) != NULL){
        sscanf(infoServico, "%d %[^/]/%[^/]/%[^/]/%[^/]/%[^#] # %ld", &servicos[i].disponibilidade, servicos[i].nome, servicos[i].cidade, servicos[i].dia, servicos[i].horario, servicos[i].telefone, &servicos[i].cpf);
        i++;
    }

    fclose(arq_cuidadores);
    return servicos;
}

int countDisponiveis(Cuidador* servicos){

    int qtdServicos = countServicos();

    int disponiveis = 0;
    for(int i = 0; i < qtdServicos; i++){
        if(servicos[i].disponibilidade == 1)
            disponiveis++;
    }
    return disponiveis;
}

void listServicos(Cuidador* servicos){

    int qtdServicos = countServicos();
    int indiceServicos = 1;

    for(int i = 0; i < qtdServicos-1; i++){
        if(servicos[i].disponibilidade == 1){
            printf("%d - %50s\t%30s\t%15s\t%30s\t%20s\n", indiceServicos, servicos[i].nome, servicos[i].cidade, servicos[i].dia, servicos[i].horario, servicos[i].telefone);
            indiceServicos++;
        }
    }
}

void selecionouServico(int selecao, Cuidador* servicos){

    Cuidador cuidadorSelecionado;

    int indiceServico = 1;
    int i = 0;
    while(1){
        if(servicos[i].disponibilidade == 1){
            if(indiceServico == selecao){
                cuidadorSelecionado = servicos[i];
                servicos[i].disponibilidade = 0;
                break;
            }
            indiceServico++;  
        }
        i++;
    }

    char filePath[60];
    sprintf(filePath, "./arquivos/trabalhosCuidadores/%ld.txt", cuidadorSelecionado.cpf);
    
    FILE* trabalhosCuidador;
    trabalhosCuidador = fopen(filePath, "a");

    char nome[50];
    char raca[30];
    char porte[15];

    getchar();
    printf("Qual seu nome:\n");
    fgets(nome, 50, stdin);
    nome[strlen(nome) - 1] = '\0';
    printf("Qual a raça do seu cachorro:\n");
    fgets(raca, 30, stdin);
    raca[strlen(raca) - 1] = '\0';
    printf("Qual o porte do seu cachorro:\n");
    fgets(porte, 15, stdin);
    porte[strlen(porte) - 1] = '\0';

    fprintf(trabalhosCuidador, "#%s, %s, %s\nNome: %s\tRaça do cachorro: %s\tPorte do cachorro: %s\n", cuidadorSelecionado.cidade, cuidadorSelecionado.dia, cuidadorSelecionado.horario, nome, raca, porte);

    mudaDisponibilidade(servicos);
    
    printf("Você contratou o serviço %d\n", selecao);
    printf("Entre em contato com o dog sitter %s pelo telefone %s\n", cuidadorSelecionado.nome, cuidadorSelecionado.telefone);
}

void mudaDisponibilidade(Cuidador* servicos){
    FILE* arq_cuidadores;
    arq_cuidadores = fopen("./arquivos/cuidadores.txt", "r+");

    if (arq_cuidadores != NULL) {
        int qtdServicos = countServicos();

        for(int i = 0; i < qtdServicos - 1; i++){
            fprintf(arq_cuidadores, "%d %s/%s/%s/%s/%s # %ld\n", servicos[i].disponibilidade, servicos[i].nome, servicos[i].cidade, servicos[i].dia, servicos[i].horario, servicos[i].telefone, servicos[i].cpf);
        }

        fclose(arq_cuidadores);
    } else {
        printf("Erro ao abrir o arquivo de cuidadores.\n");
        exit(1);
    }
}

void cadastrarCuidador(char* nome, long int cpf, char* cidade, char* dia, char* horario, char* telefone){
    FILE* arq_cuidadores;
    arq_cuidadores = fopen("./arquivos/cuidadores.txt", "a");
    if(arq_cuidadores != NULL)
        fprintf(arq_cuidadores, "1 %s/%s/%s/%s/%s # %ld\n", nome, cidade, dia, horario, telefone, cpf);
    else{
        printf("Erro ao abrir o arquivo de cuidadores!\n");
        exit(1);
    }
    fclose(arq_cuidadores);

    char filePath[50];
    FILE* trabalhosCuidador;
    sprintf(filePath, "./arquivos/trabalhosCuidadores/%ld.txt", cpf);
    trabalhosCuidador = fopen(filePath, "a");
    fclose(trabalhosCuidador);
}

char* buscarCPF(long int* cpf) {
    scanf("%ld", cpf);
    getchar();

    if (*cpf == 0) {
        return NULL;
    }

    char* filePath = (char*) malloc(60*sizeof(char));
    sprintf(filePath, "./arquivos/trabalhosCuidadores/%ld.txt", *cpf);

    FILE* trabalho = fopen(filePath, "r");

    if (trabalho != NULL) {
        fclose(trabalho);
        return filePath;
    } else {
        printf("CPF inexistente ou digitado incorretamente!\n");
        buscarCPF(cpf);
    }
}


void consultarTrabalhos(char* path){
    system("clear");
    printf("Seus trabalhos: \n\n");
    FILE* trabalhos;

    trabalhos = fopen(path, "r");
    int qtdTrabalhos = 1;

    if(trabalhos != NULL){
        char linha[150];
        while(fgets(linha, 150, trabalhos) != NULL){
            for(int i = 0; i < strlen(linha); i++){
                if(linha[i] != '#'){
                    printf("%c", linha[i]);
                }
                else{
                    printf("%d - ", qtdTrabalhos);
                    qtdTrabalhos++;
                }
            }
        }
        fclose(trabalhos);
    }
    else{
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
   
}