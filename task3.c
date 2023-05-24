#include <stdio.h>

#include "task1.h"
#include "task2.h"
#include "task3.h"

void popTeam (stackTeams **teamGroup) {
    if (*teamGroup != NULL) {
        stackTeams *temp = (*teamGroup);
        *teamGroup = (*teamGroup)->nextTeamStack;
        free(temp);
    }
}

void pushTeam (stackTeams **teamGroup, team *currentTeam) {
    stackTeams *newTeam = (stackTeams *)malloc(sizeof(stackTeams));
    newTeam->Elem = currentTeam;
    newTeam->nextTeamStack = *teamGroup;
    *teamGroup = newTeam;
}

void enQueue (queue **queueMatches, team *currentTeam1, team *currentTeam2) {
    match *newMatch = (match *)malloc(sizeof(match));

    newMatch->teamNO1 = currentTeam1;
    newMatch->teamNO2 = currentTeam2;
    
    newMatch->nextMatch = NULL;
    
    if ((*queueMatches)->rear == NULL) {
        (*queueMatches)->rear = newMatch;
    }
    else {
        ((*queueMatches)->rear)->nextMatch = newMatch;
        (*queueMatches)->rear = newMatch;
    }
    
    if ((*queueMatches)->first == NULL) {
        (*queueMatches)->first = (*queueMatches)->rear;
    }
}

queue *deQueue (queue *queueMatches) {
    if (queueMatches->first != NULL) {
        match *aux = queueMatches->first;
        queueMatches->first = (queueMatches)->first->nextMatch;
        free(aux);
    }
    return queueMatches;
}

void splitTeams (FILE *fileWrite, queue **queueMatches, stackTeams **winnerTeams, stackTeams **loserTeams) {
    while ((*queueMatches)->first != NULL) {
        team *teamNO1Match = (*queueMatches)->first->teamNO1;
        team *teamNO2Match = (*queueMatches)->first->teamNO2;
        
        fprintf(fileWrite, "\n%-32s - %32s", teamNO1Match->name, teamNO2Match->name);
        
        if (teamNO1Match->teamPoints > teamNO2Match->teamPoints) {
            pushTeam(winnerTeams, teamNO1Match);
            pushTeam(loserTeams, teamNO2Match);
            
        }
        else {
            pushTeam(winnerTeams, teamNO2Match);
            pushTeam(loserTeams, teamNO1Match);
        }
        (*queueMatches) = deQueue(*queueMatches);
    }
    fprintf(fileWrite, "\n");
}

void writeWinnerTeams (FILE *fileWrite, stackTeams **winnerTeams, queue **queuMatches, int numberRound) {

    fprintf(fileWrite, "\nWINNERS OF ROUND NO:%d", numberRound);
    while (*winnerTeams != NULL) {
        
        if((*winnerTeams)->nextTeamStack != NULL) {
            
            (*winnerTeams)->Elem->teamPoints++;
            fprintf(fileWrite,"\n%-33s -  %0.2f", (*winnerTeams)->Elem->name, (*winnerTeams)->Elem->teamPoints);
            
            (*winnerTeams)->nextTeamStack->Elem->teamPoints++;
            fprintf(fileWrite,"\n%-33s -  %0.2f", (*winnerTeams)->nextTeamStack->Elem->name, (*winnerTeams)->nextTeamStack->Elem->teamPoints);
            enQueue(queuMatches, (*winnerTeams)->Elem, (*winnerTeams)->nextTeamStack->Elem);
            
            popTeam(winnerTeams);
            popTeam(winnerTeams);
        }
        else {
            
            (*winnerTeams)->Elem->teamPoints++;
            fprintf(fileWrite,"\n%-33s -  %0.2f", (*winnerTeams)->Elem->name, (*winnerTeams)->Elem->teamPoints);
            popTeam(winnerTeams);
        }
    }
    
    fprintf(fileWrite, "\n");
}

void eliminateLoserTeams (stackTeams **loserTeams) {
    while (*loserTeams != NULL) {
        popTeam(loserTeams);
    }
}

void lastTwoTeams(FILE *fileWrite, queue *queueMatches, stackTeams *winnerTeams, stackTeams *loserTeams, int numberRound) {
    team *teamNO1Match = queueMatches->first->teamNO1;
    team *teamNO2Match = queueMatches->first->teamNO2;

    fprintf(fileWrite, "\n%-32s - %32s", teamNO1Match->name, teamNO2Match->name);

    if (teamNO1Match->teamPoints > teamNO2Match->teamPoints) {
        pushTeam(&winnerTeams, teamNO1Match);
        pushTeam(&loserTeams, teamNO2Match);
    }
    else {
        pushTeam(&winnerTeams, teamNO2Match);
        pushTeam(&loserTeams, teamNO1Match);
    }

    deQueue(queueMatches);
    queueMatches = NULL;

    fprintf(fileWrite, "\n");
    writeWinnerTeams(fileWrite, &winnerTeams, &queueMatches, numberRound);
    eliminateLoserTeams(&loserTeams);
}

void placingTeams (FILE *fileWrite, int *numberTeams, team *allTeams, queue *queueMatches) {
    stackTeams *winnerTeams = NULL;
    stackTeams *loserTeams = NULL;
    int numberRound = 1;
    
    while (*numberTeams / 2 != 1) {
        
        fprintf(fileWrite, "\n--- ROUND NO:%d", numberRound);

        splitTeams(fileWrite, &queueMatches, &winnerTeams, &loserTeams);
        
        writeWinnerTeams(fileWrite, &winnerTeams, &queueMatches, numberRound);
        
        eliminateLoserTeams(&loserTeams);
        
        numberRound++;

        (*numberTeams) = (*numberTeams) / 2;
    }

    fprintf(fileWrite, "\n--- ROUND NO:%d", numberRound);
    lastTwoTeams(fileWrite, queueMatches, winnerTeams, loserTeams, numberRound);
}

void task3(FILE *fileWrite, int numberTeams, team *allTeams, stackTeams **top8) {
    queue *queueMatches = (queue *)malloc(sizeof(queue));
    queueMatches->first = queueMatches->rear = NULL;

    for (int i = 0; i < numberTeams / 2; i++) {
        enQueue(&queueMatches, allTeams, allTeams->nextTeam);
        allTeams = allTeams->nextTeam->nextTeam;
    }
    free(allTeams);

    placingTeams(fileWrite, &numberTeams, allTeams, queueMatches);
}