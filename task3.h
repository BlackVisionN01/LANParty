#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MatchType {
    team *teamNO1;
    team *teamNO2;
    struct MatchType *nextMatch;
};

typedef struct MatchType match;

struct QueueType {
    match *first, *rear;
};

typedef struct QueueType queue;

struct StackTeamsType {
    team *Elem;
    struct StackTeamsType *nextTeamStack;
};

typedef struct StackTeamsType stackTeams;

void popTeam (stackTeams **teamGroup);

void pushTeam (stackTeams **teamGroup, team *currentTeam);

void enQueue (queue **queueMatches, team *currentTeam1, team *currentTeam2);

queue *deQueue (queue *queueMatches);

void splitTeams (FILE *fileWrite, queue **queueMatches, stackTeams **winnerTeams, stackTeams **loserTeams);

void writeWinnerTeams (FILE *fileWrite, stackTeams **winnerTeams, queue **queuMatches, int numberRound);

void eliminateLoserTeams (stackTeams **loserTeams);

void lastTwoTeams(FILE *fileWrite, queue *queueMatches, stackTeams *winnerTeams, stackTeams *loserTeams, int numberRound);

void placingTeams (FILE *fileWrite, int *numberTeams, team *allTeams, queue *queueMatches);

void task3(FILE *fileWrite, int numberTeams, team *allTeams, stackTeams **top8);