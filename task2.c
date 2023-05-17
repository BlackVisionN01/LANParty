#include <stdio.h>

#include "task1.h"
#include "task2.h"

void eliminateTeamTask2(team ***allTeams) {
    float minPoints = (**allTeams)->teamPoints;
    team *minPosition = (**allTeams);
    team *minPositionPrev = minPosition;
    team *iter = (**allTeams)->nextTeam;
    team *iterPrev = (**allTeams);
    
    while (iter != NULL) {
        if (minPoints > iter->teamPoints) {
            minPoints = iter->teamPoints;
            minPosition = iter;
            minPositionPrev = iterPrev;
        }
        iter = iter->nextTeam;
        iterPrev = iterPrev->nextTeam;
    }
    if (minPosition == minPositionPrev) {
        **allTeams = (**allTeams)->nextTeam;
    }
    else if (minPosition->nextTeam == NULL) {
        minPositionPrev->nextTeam = NULL;
    }
    else {
        minPositionPrev->nextTeam = minPosition->nextTeam;
    }
}

void task2(FILE *fileWrite, int *numberTeams, team **allTeams) {
    int newNumberTeams = 1;
    while (newNumberTeams * 2 < *numberTeams) {
        newNumberTeams = newNumberTeams * 2;
    }
    while (*numberTeams > newNumberTeams) {
        eliminateTeamTask2(&allTeams);
        (*numberTeams)--;
    }
}