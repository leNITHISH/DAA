
#include <stdio.h>
#include <stdlib.h>

// 🎯 Structure to represent a point in 2D space
typedef struct {
    int x, y;  // Coordinates (x, y)
} Point;

// This will store the first (lowest) point globally for sorting
Point p0;

/**
 * Returns the second-to-top element from a manually implemented stack.
 * @param S: Stack (array) of Points.
 * @param top: Pointer to the current top index.
 */
Point nextToTop(Point *S, int *top) {
    return S[*top - 1];  // The element below the top one
}

/**
 * Swaps two points.
 * @param p1: Pointer to first point.
 * @param p2: Pointer to second point.
 */
void swap(Point *p1, Point *p2) {
    Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

/**
 * Calculates the squared distance between two points (avoiding float operations).
 * @param p1: First point.
 * @param p2: Second point.
 * @return Squared distance between p1 and p2.
 */
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

/**
 * Determines the orientation of the triplet (p, q, r).
 * - 0: Collinear (all on a straight line)
 * - 1: Clockwise turn
 * - 2: Counterclockwise turn (this is what we want for the hull)
 */
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    return (val == 0) ? 0 : (val > 0 ? 1 : 2);
}

/**
 * Comparison function for sorting points based on their polar angle with p0.
 * - Sorts in increasing angle order.
 * - If two points have the same angle, the farther one comes last.
 */
int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1, *p2 = (Point *)vp2;
    int o = orientation(p0, *p1, *p2);
    
    // If collinear, keep the farthest point last
    if (o == 0) return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;
    
    return (o == 2) ? -1 : 1;  // Counterclockwise first
}

/**
 * Finds and prints the convex hull using Graham's scan algorithm.
 * @param points: Array of points.
 * @param n: Number of points.
 */
void convexHull(Point *points, int n) {
    // ✅ Step 1: Find the lowest point (smallest y, or smallest x if tie)
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < ymin) || (ymin == points[i].y && points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    // Move this lowest point to the front
    swap(&points[0], &points[min]);

    // ✅ Step 2: Sort points based on polar angle with `p0`
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // ✅ Step 3: Remove duplicate angles, keeping only the farthest one
    int m = 1;  // Size of the cleaned-up array
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;  // Skip all but the farthest point in the same direction

        points[m++] = points[i];  // Store the useful point
    }

    // If we don’t have at least 3 points left, convex hull is impossible
    if (m < 3) return;

    // ✅ Step 4: Build the convex hull using a manual stack
    Point *S = malloc(m * sizeof(Point));
    int top = -1;

    // Push first 3 points to stack
    S[++top] = points[0];
    S[++top] = points[1];
    S[++top] = points[2];

    // Process remaining points
    for (int i = 3; i < m; i++) {
        // Remove top while it doesn't form a counterclockwise turn
        while (top > 0 && orientation(nextToTop(S, &top), S[top], points[i]) != 2)
            top--;

        // Push current point to stack
        S[++top] = points[i];
    }

    // ✅ Step 5: Print final hull
    for (int i = 0; i <= top; i++)
        printf("(%d, %d)\n", S[i].x, S[i].y);

    free(S);  // Free dynamically allocated memory
}

/**
 * Main function - Entry point of the program.
 */
int main() {
    // Example input points
    Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                      {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n = sizeof(points) / sizeof(points[0]);  // Calculate number of points

    convexHull(points, n);  // Compute and print the convex hull
    return 0;
}
