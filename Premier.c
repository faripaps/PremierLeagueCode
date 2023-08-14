#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEAMS 20

// Structure to store team details
typedef struct {
    char name[20];
    int wins;
    int draws;
    int losses;
    int goalsFor;
    int goalsAgainst;
    int points;
} Team;

// Function to update team statistics
void updateTeamStats(Team* team, int goalsFor, int goalsAgainst, int result) {
    team->goalsFor += goalsFor;
    team->goalsAgainst += goalsAgainst;
    
    if (result == 1) {
        team->wins += 1;
        team->points += 3;
    } else if (result == 0) {
        team->draws += 1;
        team->points += 1;
    } else {
        team->losses += 1;
    }
}

// Function to compare teams for sorting based on points
int compareTeams(const void* a, const void* b) {
    Team* team1 = (Team*)a;
    Team* team2 = (Team*)b;
    
    if (team1->points != team2->points) {
        return team2->points - team1->points; // Sort descending by points
    } else {
        return (team2->goalsFor - team2->goalsAgainst) - (team1->goalsFor - team1->goalsAgainst); // Sort descending by goal difference
    }
}

int main() {
    Team teams[MAX_TEAMS];
    int numTeams;
    
    printf("Enter the number of teams: ");
    scanf("%d", &numTeams);
    
    if (numTeams < 2 || numTeams > MAX_TEAMS) {
        printf("Number of teams should be between 2 and %d.\n", MAX_TEAMS);
        return 0;
    }
    
    // Input team details
    for (int i = 0; i < numTeams; i++) {
        printf("\nEnter team %d name: ", i+1);
        scanf("%s", teams[i].name);
        
        teams[i].wins = 0;
        teams[i].draws = 0;
        teams[i].losses = 0;
        teams[i].goalsFor = 0;
        teams[i].goalsAgainst = 0;
        teams[i].points = 0;
    }
    
    // Input match results
    int numMatches = numTeams * (numTeams - 1);
    for (int i = 0; i < numMatches; i++) {
        char team1[20];
        char team2[20];
        int goals1, goals2;
        
        printf("\nEnter match %d details:\n", i+1);
        printf("Team 1: ");
        scanf("%s", team1);
        
        printf("Team 2: ");
        scanf("%s", team2);
        
        printf("Goals for Team 1: ");
        scanf("%d", &goals1);
        
        printf("Goals for Team 2: ");
        scanf("%d", &goals2);
        
        // Find the team indexes
        int index1, index2;
        for (int j = 0; j < numTeams; j++) {
            if (strcmp(teams[j].name, team1) == 0) {
                index1 = j;
            }
            if (strcmp(teams[j].name, team2) == 0) {
                index2 = j;
            }
        }
        
        // Update team statistics based on goals scored/against and result
        if (goals1 > goals2) {
            updateTeamStats(&teams[index1], goals1, goals2, 1);
            updateTeamStats(&teams[index2], goals2, goals1, -1);
        } else if (goals1 < goals2) {
            updateTeamStats(&teams[index1], goals1, goals2, -1);
            updateTeamStats(&teams[index2], goals2, goals1, 1);
        } else {
            updateTeamStats(&teams[index1], goals1, goals2, 0);
            updateTeamStats(&teams[index2], goals2, goals1, 0);
        }
    }
    
    // Sort teams based on points and goal differences
    qsort(teams, numTeams, sizeof(Team), compareTeams);
    
    // Display the standings
    printf("\nPremier League Standings:\n");
    printf("  Team\t\tWins\tDraws\tLosses\tGF\tGA\tPoints\n");
    
    for (int i = 0; i < numTeams; i++) {
        printf("%2d. %s", i+1, teams[i].name);
        int tabs = strlen(teams[i].name) < 8 ? 2 : 1; // Adjust tabs based on team name length
        for (int j = 0; j < tabs; j++) {
            printf("\t");
        }
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", teams[i].wins, teams[i].draws, teams[i].losses, 
               teams[i].goalsFor, teams[i].goalsAgainst, teams[i].points);
    }
    
    return 0;
}
