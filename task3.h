#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct last8TeamsType {
    char *name8Team;
    float points8Team;
    struct last8TeamsType *next8Team;
};

typedef struct last8TeamsType last8Teams;

struct treeType {
    last8Teams *treeTeam;
    struct treeType *left;
    struct treeType *right;
};

struct AVLType {
    last8Teams *AVLTeam;
    int height;
    struct AVLType *leftAVL;
    struct AVLType *rightAVL;
};

typedef struct AVLType AVL;

typedef struct treeType tree;

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

void createTop8 (last8Teams **top8, stackTeams **winnerTeams);

void writeWinnerTeams (FILE *fileWrite, stackTeams **winnerTeams, queue **queuMatches, int numberRound, int numberTeams, last8Teams **top8);

void eliminateLoserTeams (stackTeams **loserTeams);

void lastTwoTeams(FILE *fileWrite, queue *queueMatches, stackTeams *winnerTeams, stackTeams *loserTeams, int numberRound, last8Teams **top8);

void placingTeams (FILE *fileWrite, int *numberTeams, team *allTeams, queue *queueMatches, last8Teams **top8);

void task3(FILE *fileWrite, int numberTeams, team *allTeams, last8Teams **top8);

void addTeamAtEnd (last8Teams **top8, last8Teams *newTop8Team);

tree* newRoot(last8Teams *teamTop);

tree* insert(tree* root, last8Teams *teamTop);

void placeIordine(FILE *fileWrite, last8Teams **top8, tree *root);

void placeIordine1(FILE *fileWrite, last8Teams **top8, tree *root);

void task4(FILE *fileWrite, last8Teams **top8);

int max (int val1, int val2);

int heightAVL (AVL *rootAVL);

void deleteTree(tree *root);

void printLevel2 (FILE *fileWrite,AVL *rootAVl);

AVL *rRotation(AVL* teamAVL);

AVL *pushAVL(AVL *rootAVL, last8Teams *top8TeamAVL);

AVL *createAVL(last8Teams *top8);

void deleteAVL (AVL *rootAVL);

void task5(FILE *fileWrite, last8Teams *top8);