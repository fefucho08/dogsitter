#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"

void menuPrincipal();
void areaContratarServico();
void areaCuidador();
void telaCadastroCuidador();
void telaTrabalhosCuidador();

int main() {

    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    system("clear");
    int selecao = 0;

    printf("Bem vindo ao sistema de Dog Sitter!\n");
    printf("Selecione uma opção:\n\n\n");
    printf("1 - Contratar um serviço\n2 - Área do cuidador\n\n\n0- Sair\n");

    selecao = preencheSelecao(&selecao, 2);
    if(selecao == -1){
        exit(0);
    }

    if(selecao == 1){
        areaContratarServico();
    }
    if(selecao == 2){
        areaCuidador();
    }
}

void areaContratarServico(){
    system("clear");
    int selecao = 0;

    FILE* arq_cuidadores;
    arq_cuidadores = fopen("cuidadores.txt", "r");

    int indiceServico = 1;
    char infoServico[250];

    printf("\n");
    printf("Digite um número de serviço para contratar:\n");
    printf("\n\n");
    
    Cuidador* servicos = getServicos();

    listServicos(servicos);

    printf("\n\n");
    printf("Ou digite “0” para voltar ao menu principal.\n");

    int servicosDisponiveis = countDisponiveis(servicos);

    selecao = preencheSelecao(&selecao, servicosDisponiveis);
    if(selecao == -1)
        menuPrincipal();
    else
        selecionouServico(selecao, servicos);
    free(servicos);
}

void areaCuidador(){
    system("clear");

    int selecao = 0;

    printf("Bem vindo a área do cuidador!\n");
    printf("Selecione uma opção:\n");
    printf("1 - Cadastrar como cuidador.\n2 - Verificar seus trabalhos.\n\n\n3 - Sair\n");

    selecao = preencheSelecao(&selecao, 2);

    if(selecao == -1)
        menuPrincipal();
    if(selecao == 1)
        telaCadastroCuidador();
    if(selecao == 2)
        telaTrabalhosCuidador();
}

void telaCadastroCuidador(){
    system("clear");
    
    char nome[50];
    int cpf;
    char cidade[30];
    char dia[15];
    char horario[30];
    char telefone[16];

    printf("Insira suas informações!\n\n");
    printf("Digite seu nome:\n");
    fgets(nome, 50, stdin);
    nome[strlen(nome)-1] = '\0';
    printf("Digite seu CPF:\n");
    scanf("%11d", &cpf);
    printf("Digite a cidade:\n");
    fgets(cidade, 50, stdin);
    cidade[strlen(cidade)-1] = '\0';
    printf("Digite o dia da semana:\n");
    fgets(dia, 50, stdin);
    dia[strlen(dia)-1] = '\0';
    printf("Digite o horario:\n");
    fgets(horario, 50, stdin);
    horario[strlen(horario)-1] = '\0';
    printf("Digite seu telefone:\n");
    fgets(telefone, 50, stdin);
    telefone[strlen(telefone)-1] = '\0';

    cadastrarCuidador(nome, cpf, cidade, dia, horario, telefone);
}

void telaTrabalhosCuidador(){
    system("clear");
    printf("trabalhos");
}