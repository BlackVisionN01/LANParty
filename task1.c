#include <stdio.h>

#include "task1.h"

void modifyString (char **string) {
    string[0][strlen(*string) - 2] = '\0';
    *string = (char *)realloc(*string, strlen(*string) * sizeof(char));
}

listPlayers readAllMembers(FILE *fileReadValues, team **currentTeam, int numberMembers) {
    listPlayers newList;
    newList.nextPlayer = NULL;
    float averagePoints = 0.0;

    for (int i = 0; i < numberMembers; i++) {
        player newPlayer;

        newPlayer.firstName = (char *)malloc(100 * sizeof(char));
        fscanf(fileReadValues, "%s", newPlayer.firstName);
        modifyString(&newPlayer.firstName);
        fgetc(fileReadValues);

        newPlayer.secondName = (char *)malloc(100 * sizeof(char));
        fscanf(fileReadValues, "%s", newPlayer.secondName);
        modifyString(&newPlayer.secondName);
        fgetc(fileReadValues);

        fscanf(fileReadValues, "%d", &newPlayer.points);
        averagePoints = averagePoints + newPlayer.points;

        listPlayers newEntity;
        newEntity.playerMember = newPlayer;
        newEntity.nextPlayer = newList.nextPlayer;
        newList.nextPlayer = &newEntity;
    }
    (*currentTeam)->teamPoints = averagePoints / numberMembers;
    return newList;
}


void readValues(FILE *fileReadValues, int *numberTeams, team **allTeams) {
    fscanf(fileReadValues, "%d", numberTeams);
    for (int i = 0; i < *numberTeams; i++) {
        
        team *newTeam = (team *)malloc(sizeof(team));

        fscanf(fileReadValues, "%d", &newTeam->numberMembers);

        fgetc(fileReadValues);
        newTeam->name = (char *)malloc(100 * sizeof(char));
    
        // se alege o valoare mai mare pentru malloc ca sa fim siguri
        // ca nu pierdem niciun caracter important
        //aplicam pentru toate citirile de siruri de caractere

        fgets(newTeam->name, 100, fileReadValues);
        
        modifyString(&newTeam->name);
        newTeam->list = readAllMembers(fileReadValues, &newTeam, newTeam->numberMembers);

        newTeam->nextTeam = *allTeams;
        *allTeams = newTeam;
    }
}

void writeTeams(FILE *fileWrite, team **allTeams) {
    //aici trebuie sa faci o copie la allTeams ca sa nu pierzi adresa de inceput a listei
    //dar nu trebuie sa faci copii >:C
    team *iter = *allTeams;
    if (iter != NULL) {
        while(iter != NULL) {
            fprintf(fileWrite, "%s\n", iter->name);
            iter = iter->nextTeam;
        }
    }
    free(iter);
}

void task1 (FILE *fileReadValues, FILE *fileWrite, int *numberTeams, team **allTeams) {
    readValues(fileReadValues, numberTeams, allTeams);
    fclose(fileReadValues);
}