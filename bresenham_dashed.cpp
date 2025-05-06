#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int x_start, y_start, x_end, y_end; // Avoid conflict with math.h

// Plot a point if count is within dash interval
void plot(int x, int y, int count) {
    // Create dashed effect: plot only for part of the cycle (e.g., 5 on, 5 off)
    if (count % 10 < 5) {
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
    }
}

// Bresenham's Line Drawing Algorithm (Dashed)
void bresenham_dashed() {
    int dx = abs(x_end - x_start);
    int dy = abs(y_end - y_start);
    int sx = (x_start < x_end) ? 1 : -1;
    int sy = (y_start < y_end) ? 1 : -1;
    int err = dx - dy;

    int x = x_start;
    int y = y_start;
    int count = 0;

    while (true) {
        plot(x, y, count);
        if (x == x_end && y == y_end) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }

        count++;
    }
}

// OpenGL setup
void init() {
    glClearColor(1, 1, 1, 0);             // White background
    glColor3f(0, 0, 1);                   // Blue dashed line
    gluOrtho2D(-320, 320, -240, 240);     // Coordinate system
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw coordinate axes
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(320, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 240);
    glEnd();

    glColor3f(0, 0, 1); // Reset to blue for dashed line
}

int main(int argc, char **argv) {
    cout << "Enter start point (x y): ";
    cin >> x_start >> y_start;
    cout << "Enter end point (x y): ";
    cin >> x_end >> y_end;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham Dashed Line");
    init();
    glutDisplayFunc(bresenham_dashed);
    glutMainLoop();
    return 0;
}
