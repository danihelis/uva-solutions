/* 10194
 * Football (aka Soccer)
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_NAME 50
#define MAX_TEAMS 30
#define MAX_INPUT 200

typedef struct {
    char name[MAX_NAME], upper_name[MAX_NAME];
    int goals_scored, goals_against, goals_points;
    int games, wins, ties, losses;
    int points;
} team_t, *team_p;

team_t team[MAX_TEAMS];
team_p index[MAX_TEAMS];
int num_teams;

/* Compare teams by name */
int compare_name(const void *a, const void *b) {
    team_p x = *((team_p *) a), y = *((team_p *) b);
    return strcmp(x->name, y->name);
}

/* Compare teams by game results */
#define COMPARE(p) if (x->p != y->p) return (y->p - x->p)
int compare_team(const void *a, const void *b) {
    team_p x = *((team_p *) a), y = *((team_p *) b);
    COMPARE(points);
    COMPARE(wins);
    COMPARE(goals_points);
    COMPARE(goals_scored);
    COMPARE(games) * -1;
    return strcmp(x->upper_name, y->upper_name);
}

/* Main function */
#define ADD_DATA(t, gs, ga) \
    (t)->games++; \
    (t)->wins += (gs > ga ? 1 : 0); \
    (t)->ties += (gs == ga ? 1 : 0); \
    (t)->losses += (gs < ga ? 1 : 0); \
    (t)->goals_scored += gs; \
    (t)->goals_against += ga; \
    (t)->goals_points += (gs - ga); \
    (t)->points += (gs > ga ? 3 : gs == ga ? 1 : 0)
   
int main() {
    char input[MAX_INPUT];
    int i = -1, games, tests;

    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        assert(scanf(" %[^\n]", input) != EOF);
        printf("%s%s\n", (i >= 0 ? "\n" : ""), input);

        assert(scanf(" %d", &num_teams) != EOF);
        memset(team, 0, num_teams * sizeof (team_t));
        for (i = 0; i < num_teams; i++) {
            char *symbol;
            assert(scanf(" %[^\n]", team[i].name) != EOF);
            for (symbol = team[i].name; *symbol != 0; symbol++) {
                team[i].upper_name[symbol - team[i].name] = (isalpha(*symbol) ? toupper(*symbol) :
                        *symbol);
            }
            index[i] = &team[i];
        }
        qsort(index, num_teams, sizeof (team_p), compare_name);
        
        assert(scanf(" %d", &games) != EOF);
        for (i = 0; i < games; i++) {
            team_t key_team;
            team_p key = &key_team, *result;
            assert(scanf(" %[^#]#%d@%d#", key_team.name, &key_team.goals_scored,
                        &key_team.goals_against) != EOF);
            result = bsearch(&key, index, num_teams, sizeof (team_p), compare_name);
            assert(result != NULL);
            ADD_DATA(*result, key_team.goals_scored, key_team.goals_against);
            assert(scanf("%[^\n]", key_team.name) != EOF);
            result = bsearch(&key, index, num_teams, sizeof (team_p), compare_name);
            assert(result != NULL);
            ADD_DATA(*result, key_team.goals_against, key_team.goals_scored);
        }
        qsort(index, num_teams, sizeof (team_p), compare_team);

        for (i = 0; i < num_teams; i++) {
            team_p t = index[i];
            printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n", i + 1, t->name, t->points,
                    t->games, t->wins, t->ties, t->losses, t->goals_points, t->goals_scored,
                    t->goals_against);
        }
    }
    return 0;
}
