#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct point {
    float x, y;
};

struct rectangle {
    struct point top_left, bottom_right;
    char color[20];   // Changed to string instead of single char
};

int intersection(struct rectangle *p1, struct rectangle *p2);
int max_area(int N, struct rectangle ptr[], char *cl);
int max_perim(int N, struct rectangle ptr[], char *cl);

int main()
{
    int i, N, choice;
    struct rectangle *ptr;
    char cl[20];
    FILE *fp;
    char line[256];

    /* --- Open file --- */
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("Trouble opening the file\n");
        return 1;
    }

    /* --- Read number of rectangles --- */
    fscanf(fp, "%d", &N);
    fgetc(fp); // consume newline

    /* --- Allocate memory for rectangles --- */
    ptr = (struct rectangle*)malloc(N * sizeof(struct rectangle));
    if (!ptr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    /* --- Read rectangles from file --- */
    for (i = 0; i < N; i++) {
        fgets(line, 256, fp);
        sscanf(line, "%f %f %f %f %s",
                &ptr[i].top_left.x,
                &ptr[i].top_left.y,
                &ptr[i].bottom_right.x,
                &ptr[i].bottom_right.y,
                ptr[i].color);
    }

    fclose(fp);

    /* --- Program runs repeatedly until user enters STOP --- */
    while (1) {
        printf("Pick color (or STOP): ");
        scanf("%s", cl);

        if (strcmp(cl, "STOP") == 0)
            break;

        printf("1. Intersection\n2. Max Area\n3. Max Perimeter\n");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                /* Example: show intersection of first two */
                if (intersection(&ptr[0], &ptr[1])) {
                    printf("Intersection area: (%f,%f) to (%f,%f)\n",
                           ptr[0].top_left.x, ptr[0].top_left.y,
                           ptr[0].bottom_right.x, ptr[0].bottom_right.y);
                } else {
                    printf("No intersection found.\n");
                }
                break;
            }

            case 2: {
                int pos = max_area(N, ptr, cl);
                printf("Max area rect index: %d\n", pos);
                break;
            }

            case 3: {
                int pos = max_perim(N, ptr, cl);
                printf("Max perimeter rect index: %d\n", pos);
                break;
            }

            default:
                printf("Invalid input\n");
        }
    }

    free(ptr);
    return 0;
}

/*-------------------------------------------------------------
  intersection(): Checks rectangle overlap.
-------------------------------------------------------------*/
int intersection(struct rectangle *p1, struct rectangle *p2)
{
    // If rectangles do NOT overlap
    if (p1->top_left.x > p2->bottom_right.x ||
        p1->bottom_right.x < p2->top_left.x ||
        p1->top_left.y < p2->bottom_right.y ||
        p1->bottom_right.y > p2->top_left.y) {

        // Set rectangle p1 to empty
        p1->top_left.x = p1->top_left.y = 0;
        p1->bottom_right.x = p1->bottom_right.y = 0;
        return 0;
    }

    // Intersection rectangle boundaries
    p1->top_left.x = (p1->top_left.x > p2->top_left.x ? p1->top_left.x : p2->top_left.x);
    p1->top_left.y = (p1->top_left.y < p2->top_left.y ? p1->top_left.y : p2->top_left.y);
    p1->bottom_right.x = (p1->bottom_right.x < p2->bottom_right.x ? p1->bottom_right.x : p2->bottom_right.x);
    p1->bottom_right.y = (p1->bottom_right.y > p2->bottom_right.y ? p1->bottom_right.y : p2->bottom_right.y);

    return 1;
}

/*-------------------------------------------------------------
  max_area(): Returns index of rectangle with largest area
              that matches a given color.
-------------------------------------------------------------*/
int max_area(int N, struct rectangle ptr[], char *cl)
{
    int pos = -1;
    float max_area = -1;

    for (int i = 0; i < N; i++) {
        if (strcmp(ptr[i].color, cl) == 0) {
            float area = (ptr[i].bottom_right.x - ptr[i].top_left.x) *
                         (ptr[i].top_left.y - ptr[i].bottom_right.y);

            if (area > max_area) {
                max_area = area;
                pos = i;
            }
        }
    }
    return pos;
}

/*-------------------------------------------------------------
  max_perim(): Returns index of rectangle with largest perimeter
               matching the given color.
-------------------------------------------------------------*/
int max_perim(int N, struct rectangle ptr[], char *cl)
{
    int pos = -1;
    float max_p = -1;

    for (int i = 0; i < N; i++) {
        if (strcmp(ptr[i].color, cl) == 0) {
            float width = (ptr[i].bottom_right.x - ptr[i].top_left.x);
            float height = (ptr[i].top_left.y - ptr[i].bottom_right.y);
            float perim = 2 * (width + height);

            if (perim > max_p) {
                max_p = perim;
                pos = i;
            }
        }
    }
    return pos;
}
