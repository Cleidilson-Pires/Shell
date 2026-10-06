#include<stdio.h>
#include <stdlib.h>
#include <string.h>

struct commandNode;
typedef struct commandNode* CommandNode;
// Estrutura para organizar sequencias de comandos, por exemplo ls -all: ls->all. Estará organizado
// para a leitura do shell

struct commandNode{
    char* command;
    CommandNode NextCommand;
};

typedef CommandNode commandHead;
CommandNode newCommand(char* command) {
    CommandNode newNode= malloc(sizeof(struct commandNode));
    newNode->command= malloc(strlen(command)+1);
    strcpy(newNode->command,command);
    newNode->NextCommand= NULL;
    return newNode;
}

void defineNextNode(CommandNode previousNode, CommandNode nextNode) {
    previousNode->NextCommand= nextNode;
}

CommandNode goToNextNode(CommandNode previousNode) {
    return previousNode->NextCommand;
}

void deleteNode(CommandNode node) {
    free(node->command);
    free(node);
}

void cleanCommandNode(CommandNode Head) {
    if(Head->NextCommand!=NULL) {
        CommandNode Proximo= Head->NextCommand;
        CommandNode delete= Head;
        deleteNode(delete);
        while(Proximo!=NULL) {
            delete= Proximo;
            Proximo= goToNextNode(Proximo);
            deleteNode(delete);
        }
    }
    else {
        deleteNode(Head);
    }
}

int main(){
    char comando[100];
    while(strcmp(comando,"exit")!=0){
        printf("$ :");
        gets(comando);
        printf("\n");
        printf(comando);
    }
    return 0;
}