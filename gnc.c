
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

Point p0;

Point nextToTop(Point *S, int *top) {
    return S[*top - 1];
}

void swap(Point *p1, Point *p2) {
    Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    return (val == 0) ? 0 : (val > 0 ? 1 : 2);
}

int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1, *p2 = (Point *)vp2;
    int o = orientation(p0, *p1, *p2);
    if (o == 0) return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;
    return (o == 2) ? -1 : 1;
}

void convexHull(Point *points, int n) {
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < ymin) || (ymin == points[i].y && points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    swap(&points[0], &points[min]);
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m++] = points[i];
    }

    if (m < 3) return;

    Point *S = malloc(m * sizeof(Point));
    int top = -1;
    S[++top] = points[0];
    S[++top] = points[1];
    S[++top] = points[2];

    for (int i = 3; i < m; i++) {
        while (top > 0 && orientation(S[top - 1], S[top], points[i]) != 2)
            top--;
        S[++top] = points[i];
    }

    for (int i = 0; i <= top; i++)
        printf("(%d, %d)\n", S[i].x, S[i].y);

    free(S);
}

int main() {
    Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                      {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n = sizeof(points) / sizeof(points[0]);
    convexHull(points, n);
    return 0;
}
