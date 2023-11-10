typedef struct cuidador{
    int disponibilidade;
    char nome[50];
    int cpf;
    char cidade[30];
    char dia[15];
    char horario[30];
    char telefone[16];
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
    arquivo = fopen("cuidadores.txt", "r");

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
    arq_cuidadores = fopen("cuidadores.txt", "r");

    int qtdServicos = countServicos();
    Cuidador* servicos = malloc(qtdServicos*(sizeof(Cuidador)));
    
    if(servicos == NULL){
        printf("Erro na alocação de memória!\n");
        exit(1);
    }

    int i = 0;

    char infoServico[200];

    while(fgets(infoServico, 200, arq_cuidadores) != NULL){
        sscanf(infoServico, "%d %[^/]/%[^/]/%[^/]/%[^/]/%[^#] # %d", &servicos[i].disponibilidade, servicos[i].nome, servicos[i].cidade, servicos[i].dia, servicos[i].horario, servicos[i].telefone, &servicos[i].cpf);
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

    for(int i = 0; i < qtdServicos; i++){
        if(servicos[i].disponibilidade == 1){
            printf("%d - Nome: %s Cidade: %s Dia: %s Horario: %s Telefone: %s\n", indiceServicos, servicos[i].nome, servicos[i].cidade, servicos[i].dia, servicos[i].horario, servicos[i].telefone);
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

    mudaDisponibilidade(servicos);

    char fileName[15];
    sprintf(fileName, "%d.txt", cuidadorSelecionado.cpf);
    
    FILE* trabalhosCuidador;
    trabalhosCuidador = fopen(fileName, "a");

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

    fprintf(trabalhosCuidador, "Nome: %s Raça: %s Porte: %s\n", nome, raca, porte);

    printf("Você contratou o serviço %d.\n", selecao);
    printf("Entre em contato com o dog sitter %s pelo telefone %s.\n", cuidadorSelecionado.nome, cuidadorSelecionado.telefone);
}

void mudaDisponibilidade(Cuidador* servicos){
    FILE* arq_cuidadores;
    arq_cuidadores = fopen("cuidadores.txt", "w");

    int qtdServicos = countServicos(servicos);

    for(int i = 0; i < qtdServicos; i++){
        fprintf(arq_cuidadores, "%d %s/%s/%s/%s/%s # %d\n", servicos[i].disponibilidade, servicos[i].nome, servicos[i].cidade, servicos[i].dia, servicos[i].horario, servicos[i].telefone, servicos[i].cpf);
    }

    fclose(arq_cuidadores);
}

void cadastrarCuidador(char* nome, int cpf, char* cidade, char* dia, char* horario, char* telefone){
    FILE* arq_cuidadores;
    arq_cuidadores = fopen("cuidadores.txt", "a");
}