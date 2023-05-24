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

void createTop8 (last8Teams **top8, stackTeams **winnerTeams) {
    last8Teams *newTop8Team1 = (last8Teams *)malloc(sizeof(last8Teams));
    newTop8Team1->name8Team = (*winnerTeams)->Elem->name;
    newTop8Team1->points8Team = (*winnerTeams)->Elem->teamPoints;
    newTop8Team1->next8Team = *top8;
    *top8 = newTop8Team1;
    popTeam(winnerTeams);

    last8Teams *newTop8Team2 = (last8Teams *)malloc(sizeof(last8Teams));
    newTop8Team2->name8Team = (*winnerTeams)->Elem->name;
    newTop8Team2->points8Team = (*winnerTeams)->Elem->teamPoints;
    newTop8Team2->next8Team = *top8;
    *top8 = newTop8Team2;
    popTeam(winnerTeams);
}

void writeWinnerTeams (FILE *fileWrite, stackTeams **winnerTeams, queue **queuMatches, int numberRound, int numberTeams, last8Teams **top8) {

    fprintf(fileWrite, "\nWINNERS OF ROUND NO:%d", numberRound);
    while (*winnerTeams != NULL) {
        
        if((*winnerTeams)->nextTeamStack != NULL) {

            (*winnerTeams)->Elem->teamPoints++;
            fprintf(fileWrite,"\n%-33s -  %0.2f", (*winnerTeams)->Elem->name, (*winnerTeams)->Elem->teamPoints);
            
            (*winnerTeams)->nextTeamStack->Elem->teamPoints++;
            fprintf(fileWrite,"\n%-33s -  %0.2f", (*winnerTeams)->nextTeamStack->Elem->name, (*winnerTeams)->nextTeamStack->Elem->teamPoints);
            enQueue(queuMatches, (*winnerTeams)->Elem, (*winnerTeams)->nextTeamStack->Elem);
            
            if (numberTeams / 2 == 8) {
                createTop8(top8, winnerTeams);
            }
            else {
                popTeam(winnerTeams);
                popTeam(winnerTeams);
            }

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

void lastTwoTeams(FILE *fileWrite, queue *queueMatches, stackTeams *winnerTeams, stackTeams *loserTeams, int numberRound, last8Teams **top8) {
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
    writeWinnerTeams(fileWrite, &winnerTeams, &queueMatches, numberRound, 1, top8);
    eliminateLoserTeams(&loserTeams);
}

void placingTeams (FILE *fileWrite, int *numberTeams, team *allTeams, queue *queueMatches, last8Teams **top8) {
    stackTeams *winnerTeams = NULL;
    stackTeams *loserTeams = NULL;
    int numberRound = 1;
    
    while (*numberTeams / 2 != 1) {
        
        fprintf(fileWrite, "\n--- ROUND NO:%d", numberRound);

        splitTeams(fileWrite, &queueMatches, &winnerTeams, &loserTeams);
        
        writeWinnerTeams(fileWrite, &winnerTeams, &queueMatches, numberRound, *numberTeams, top8);
        
        eliminateLoserTeams(&loserTeams);
        
        numberRound++;
        (*numberTeams) = (*numberTeams) / 2;
    }

    fprintf(fileWrite, "\n--- ROUND NO:%d", numberRound);
    lastTwoTeams(fileWrite, queueMatches, winnerTeams, loserTeams, numberRound, top8);
}

void task3(FILE *fileWrite, int numberTeams, team *allTeams, last8Teams **top8) {
    queue *queueMatches = (queue *)malloc(sizeof(queue));
    queueMatches->first = queueMatches->rear = NULL;

    for (int i = 0; i < numberTeams / 2; i++) {
        enQueue(&queueMatches, allTeams, allTeams->nextTeam);
        allTeams = allTeams->nextTeam->nextTeam;
    }
    free(allTeams);

    placingTeams(fileWrite, &numberTeams, allTeams, queueMatches, top8);
}

tree* newRoot(last8Teams *teamTop) {
    tree *root = (tree*)malloc(sizeof(tree));
    root->treeTeam = teamTop;
    root->left = root->right = NULL;
    return root;
}

tree* insert(tree* root, last8Teams *teamTop) {
    if (root == NULL) {
        return newRoot(teamTop);
    }
    if (teamTop->points8Team < root->treeTeam->points8Team) {
        root->left = insert(root->left, teamTop);
    }
    else if (teamTop->points8Team > root->treeTeam->points8Team) {
         root->right = insert(root->right, teamTop);
     }
    else {
        if(strcmp(teamTop->name8Team, root->treeTeam->name8Team) < 0) {
            root->left = insert(root->left, teamTop);
        }
        else if (strcmp(teamTop->name8Team, root->treeTeam->name8Team) > 0) {
            root->right = insert(root->right, teamTop);
        }
    }
    return root;
}

void writeIordine(FILE *fileWrite,tree *root) {
    if(root == NULL) return ;
    
        writeIordine(fileWrite, root->right);
        fprintf(fileWrite, "\n%-33s -  %.2f",root->treeTeam->name8Team, root->treeTeam->points8Team);
        writeIordine(fileWrite, root->left);
}

void task4(FILE *fileWrite, last8Teams *top8) {
    tree *root = NULL;
    int numberTopTeams = 8;
    for (int i = 0; i < numberTopTeams; i++) {
        root = insert(root, top8);
        top8 = top8->next8Team;
    }
    fprintf(fileWrite, "\nTOP 8 TEAMS:");
    writeIordine(fileWrite, root);
}