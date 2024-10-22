/* 908
 * Re-connecting Computer Sites
 * by Daniel Donadon
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define MAX_SITES 1000000

struct site_s;

typedef struct {
    struct site_s *pair[2];
    int cost;
} link_t, *link_p;

link_t link[MAX_SITES];

typedef struct site_s {
    link_p *link;
    int num_links, max_links;
    link_p path;
} site_t, *site_p;

site_t site[MAX_SITES];
int num_sites;

/* Add new link in a site */
void add_link(site_p site, link_p link) {
    if (site->num_links >= site->max_links) {
        site->max_links += 2;
        site->link = (link_p *) realloc(site->link, site->max_links * sizeof (link_p));
    }
    site->link[site->num_links++] = link;    
}

/* Remove a link from a site */
void remove_link(site_p site, link_p link) {
    int i;
    for (i = 0; i < site->num_links && site->link[i] != link; i++)
        ;
    assert(i < site->num_links);
    site->link[i] = site->link[site->num_links - 1];
    site->num_links--;
}

/* Get costlier link */
link_p get_costlier_link(site_p from_site, site_p to_site, link_p new_link) {
    site_p queue[MAX_SITES];
    int i, front, size;
    link_p costlier, current;
    for (i = 0; i < num_sites; i++) {
        site[i].path = NULL;
    }
    front = 0, size = 1, queue[0] = from_site, from_site->path = new_link;
    while (front < size && to_site->path == NULL) {
        site_p current = queue[front++];
        for (i = 0; i < current->num_links; i++) {
            site_p next = current->link[i]->pair[(current->link[i]->pair[0] == current ? 1 : 0)];
            if (next->path == NULL) {
                next->path = current->link[i];
                queue[size++] = next;
            }
        }
    }
    assert(to_site->path != NULL);
    costlier = new_link, current = to_site->path; 
    while (current != new_link) {
        if (current->cost > costlier->cost) {
            costlier = current;
        }
        to_site = current->pair[(current->pair[0] == to_site ? 1 : 0)];
        current = to_site->path;
    }
    return costlier;
}

/* Deallocate all memory */
void free_sites() {
    int i;
    for (i = 0; i < num_sites; i++) {
        if (site[i].max_links > 0) {
            free(site[i].link);
        }
    }
}

/* Main function */
int main() {
    int first = 1;
    while (scanf("%d", &num_sites) != EOF) {
        int i, total_cost, num_links;
        (first ? first = 0 : printf("\n"));
        memset(site, 0, num_sites * sizeof (site_t));
        for (i = 0, total_cost = 0; i < num_sites - 1; i++) {
            int a, b;
            assert(scanf("%d %d %d", &a, &b, &link[i].cost) != EOF);
            add_link(&site[--a], &link[i]);
            add_link(&site[--b], &link[i]);
            link[i].pair[0] = &site[a], link[i].pair[1] = &site[b];
            total_cost += link[i].cost;
        }
        printf("%d\n", total_cost);
        assert(scanf("%d", &num_links) != EOF);
        for (i = 0; i < num_links; i++) {
            int a, b;
            link_t new_link;
            link_p costlier;
            assert(scanf("%d %d %d", &a, &b, &new_link.cost) != EOF);
            new_link.pair[0] = &site[--a], new_link.pair[1] = &site[--b];
            costlier = get_costlier_link(&site[a], &site[b], &new_link);
            if (costlier != &new_link) {
                total_cost += new_link.cost - costlier->cost;
                remove_link(costlier->pair[0], costlier);
                remove_link(costlier->pair[1], costlier);
                costlier->pair[0] = new_link.pair[0], costlier->pair[1] = new_link.pair[1],
                    costlier->cost = new_link.cost;
                add_link(&site[a], costlier);
                add_link(&site[b], costlier);
            }
        }
        printf("%d\n", total_cost);
        assert(scanf("%d", &num_links) != EOF);
        for (i = 0; i < num_links; i++) {
            assert(scanf("%*d %*d %*d") != EOF);
        }
        free_sites();
    }
    return 0;
}
