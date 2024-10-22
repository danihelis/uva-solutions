/* 11308
 * Bankrupt Baker
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STRING 100
#define MAX_INGREDIENTS 100
#define MAX_RECIPES 100

typedef char string_t[MAX_STRING];

typedef struct {
    string_t name;
    int cost;
} ingredient_t, *ingredient_p, recipe_t, *recipe_p;

ingredient_t ingredient[MAX_INGREDIENTS];
ingredient_p index_ingredient[MAX_INGREDIENTS];
int num_ingredients;

recipe_t recipe[MAX_RECIPES];
recipe_p index_recipe[MAX_RECIPES];
int num_recipes;

/* Compare two ingredients in order to sort them */
int compare_ingredient(const void *a, const void *b) {
    ingredient_p x = *((ingredient_p *) a), y = *((ingredient_p *) b);
    return strcmp(x->name, y->name);
}

/* Compare two recipies in order to sort them */
int compare_recipe(const void *a, const void *b) {
    recipe_p x = *((recipe_p *) a), y = *((recipe_p *) b);
    if (x->cost != y->cost) {
        return x->cost - y->cost;
    }
    return strcmp(x->name, y->name);
}

/* Main function */
int main() {
    int tests;
    assert(scanf("%d", &tests) != EOF);
    for (; tests > 0; tests--) {
        string_t title;
        char *symbol;
        int i, budget;
        assert(scanf(" %[^\n] %d %d %d", title, &num_ingredients, &num_recipes, &budget) != EOF);
        for (symbol = title; *symbol != 0; symbol++) {
            printf("%c", toupper(*symbol));
        }
        printf("\n");
        for (i = 0; i < num_ingredients; i++) {
            assert(scanf(" %s %d", ingredient[i].name, &ingredient[i].cost) != EOF);
            index_ingredient[i] = &ingredient[i];
        }
        qsort(index_ingredient, num_ingredients, sizeof (ingredient_p), compare_ingredient);
        for (i = 0; i < num_recipes; i++) {
            int num_entries, j;
            assert(scanf(" %[^\n] %d", recipe[i].name, &num_entries) != EOF);
            recipe[i].cost = 0;
            index_recipe[i] = &recipe[i];
            for (j = 0; j < num_entries; j++) {
                ingredient_t key_struct;
                ingredient_p key = &key_struct, *result;
                assert(scanf(" %s %d", key_struct.name, &key_struct.cost) != EOF);
                result = (ingredient_p *) bsearch(&key, index_ingredient, num_ingredients, 
                        sizeof (ingredient_p), compare_ingredient);
                assert(result != NULL);
                recipe[i].cost += (*result)->cost * key_struct.cost;
            }
        }
        qsort(index_recipe, num_recipes, sizeof (recipe_p), compare_recipe);
        if (index_recipe[0]->cost > budget) {
            printf("Too expensive!\n");
        }
        else {
            for (i = 0; i < num_recipes && index_recipe[i]->cost <= budget; i++) {
                printf("%s\n", index_recipe[i]->name);
            }
        }
        printf("\n");
    }

    return 0;
}
