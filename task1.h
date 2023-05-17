#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PlayerStruct {
    char *firstName;
    char *secondName;
    int points;
};

typedef struct PlayerStruct player;

struct ListPlayersStruct {
    player playerMember;
    struct ListPlayersStruct *nextPlayer;
};

typedef struct ListPlayersStruct listPlayers;

struct TeamStruct {
    char *name;
    float points;
    int numberMembers;
    listPlayers list;
    struct TeamStruct *nextTeam;
};

typedef struct TeamStruct team;

void modifyString (char **string);

listPlayers readAllMembers(FILE *fileReadValues, team **currentTeam, int numberMembers);

void readValues(FILE *fileReadValues, int *numberTeams, team **allTeams);

void task1 (FILE* fileReadValues, FILE* fileWrite, int *numberTeams, team **allTeams);