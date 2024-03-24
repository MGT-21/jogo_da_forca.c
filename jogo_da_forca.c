#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.h"

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;
int mododejogoescolhido;

void mododejogo(){
    
    printf("Escolha um modo de jogo:\n");
    printf("(1)-Frutas\n(2)-Objetos\n(3)-Esportes\nresposta: ");
    scanf("%d", &mododejogoescolhido);

}

int letraexiste(char letra) {

    for(int j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }

    return 0;
}

int chuteserrados() {
    int erros = 0;

    for(int i = 0; i < chutesdados; i++) {

        if(!letraexiste(chutes[i])) {
            erros++;
        }
    }

    return erros;
}

int enforcou() {
    return chuteserrados() >= 5;
}

int ganhou() {
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}


void abertura() {
    printf("\n\n**********************************************\n");
    printf("*********** Bem vindo ao Jogo de Forca ***********\n");
    printf("**************************************************\n\n");
    printf("para garantir que o programa funcione corretamente:\n"); 
    printf("ative a tecla CapsLock!\n\n");
}

void chuta() {
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    if(letraexiste(chute)) {
        printf("Voce acertou: a palavra tem a letra %c\n\n", chute);
    } else {
        printf("\nVoce errou: a palavra NÃO tem a letra %c\n\n", chute);
    }

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra) {
    int achou = 0;
    for(int j = 0; j < chutesdados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaforca() {

    int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(int i = 0; i < strlen(palavrasecreta); i++) {

        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");

}

void escolhepalavra() {
    FILE* f;

    //lugar que tem que entrar a escolha do arquivo
    
    if (mododejogoescolhido == 1){
        f = fopen("frutas.txt", "r");
    }else if(mododejogoescolhido == 2) {
        f = fopen("objetos.txt", "r");
    }else if (mododejogoescolhido == 3){
        f = fopen("esportes.txt", "r");
    }
    
    if(f == 0) {
        printf("Banco de dados de palavras nao disponivel\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

//função não utilizada
void adicionapalavra() {
    char quer;

    printf("Voce deseja adicionar uma nova palavra no jogo (S/N)? ");
    scanf(" %c", &quer);

    if(quer == 'S') {
        char novapalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra, em letras maiúsculas: ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0) {
            printf("Banco de dados de palavras não disponível\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);

    }
}

int main() {
    
    while(1){


        abertura();
        mododejogo();
        escolhepalavra();

        do {

            desenhaforca();
            chuta();

        } while (!ganhou() && !enforcou());

        if(ganhou()) {

            printf("\nParabens, voce ganhou!\n\n");

            printf("       ___________      \n");
            printf("      '._==_==_=_.'     \n");
            printf("      .-\\:      /-.    \n");
            printf("     | (|:.     |) |    \n");
            printf("      '-|:.     |-'     \n");
            printf("        \\::.    /      \n");
            printf("         '::. .'        \n");
            printf("           ) (          \n");
            printf("         _.' '._        \n");
            printf("        '-------'       \n\n");

        } else {
            printf("\nPuxa, você foi enforcado!\n");
            printf("A palavra era **%s**\n\n", palavrasecreta);

            printf("    _______________         \n");
            printf("   /               \\       \n"); 
            printf("  /                 \\      \n");
            printf("//                   \\/\\  \n");
            printf("\\|   XXXX     XXXX   | /   \n");
            printf(" |   XXXX     XXXX   |/     \n");
            printf(" |   XXX       XXX   |      \n");
            printf(" |                   |      \n");
            printf(" \\__      XXX      __/     \n");
            printf("   |\\     XXX     /|       \n");
            printf("   | |           | |        \n");
            printf("   | I I I I I I I |        \n");
            printf("   |  I I I I I I  |        \n");
            printf("   \\_             _/       \n");
            printf("     \\_         _/         \n");
            printf("       \\_______/           \n");
        }

        //adicionapalavra();

        char resposta;

        printf("gostaria de jogar novamente? S/N ");
        scanf(" %c", &resposta);
            
        if(resposta == 'S'){
            
            chutesdados = 0;
            continue;

        }else {
            break;
        }   
    }
}
