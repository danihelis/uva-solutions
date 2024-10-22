/* 11239
 * Open Source
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_STUDENTS 10000
#define MAX_PROJECTS 100
#define MAX_STRING 100

typedef char string_t[MAX_STRING];

typedef struct {
    string_t name;
    int students;
} project_t, *project_p;

typedef struct {
    string_t name;
    project_p project;
} student_t, *student_p;

project_t project[MAX_PROJECTS];
project_p proj_index[MAX_PROJECTS];
int num_projects;

student_t student[MAX_STUDENTS];
student_p stud_index[MAX_STUDENTS];
int num_students;

/* Insert a new student in a project, or remove it if he is present */
void insert(string_t *name, project_p proj) {
    int start = 0, end = num_students;
    while (start < end) {
        int middle, comp;
        middle = (start + end) / 2;
        comp = strcmp(stud_index[middle]->name, *name);
        if (comp == 0) {
            if (stud_index[middle]->project == proj) {
                return;
            }
            else if (stud_index[middle]->project != NULL) {
                stud_index[middle]->project->students--;
            }
            stud_index[middle]->project = NULL;
            return;
        }
        else if (comp < 0) {
            start = middle + 1;
        }
        else {
            end = middle;
        }
    }
    for (end = num_students; end > start; end--) {
        stud_index[end] = stud_index[end - 1];
    }
    stud_index[start] = &student[num_students];
    strcpy(student[num_students].name, *name);
    student[num_students].project = proj;
    proj->students++;
    num_students++;
}

/* Compare two projects in order to sort it */
int compare_project(const void *a, const void *b) {
    project_p x = *((project_p *) a), y = *((project_p *) b);
    if (x->students != y->students) {
        return y->students - x->students;
    }
    return strcmp(x->name, y->name);
}

/* Main function */
int main() {
    string_t input;
    while (scanf(" %[^\n]", input) != EOF && *input != '0') {
        int i;
        num_projects = 0, num_students = 0;
        while (*input != '1') {
            assert(isupper(*input));
            strcpy(project[num_projects].name, input);
            project[num_projects].students = 0;
            proj_index[num_projects] = &project[num_projects];
            while (scanf(" %[^\n]", input) != EOF && islower(*input)) {
                insert(&input, proj_index[num_projects]);
            }
            num_projects++;
        }
        qsort(proj_index, num_projects, sizeof (project_p), compare_project);
        for (i = 0; i < num_projects; i++) {
            printf("%s %d\n", proj_index[i]->name, proj_index[i]->students);
        }
    }
    return 0;
}
