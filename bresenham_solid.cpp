#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int x_start, y_start, x_end, y_end; // Renamed to avoid math.h conflict

// Plot a point
void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Bresenham's Line Drawing Algorithm
void bresenham_line() {
    int dx = abs(x_end - x_start);
    int dy = abs(y_end - y_start);
    int sx = (x_start < x_end) ? 1 : -1;
    int sy = (y_start < y_end) ? 1 : -1;
    int err = dx - dy;

    int x = x_start;
    int y = y_start;

    while (true) {
        plot(x, y);
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
    }
}

// OpenGL setup
void init() {
    glClearColor(1, 1, 1, 0);             // White background
    glColor3f(1, 0, 0);                   // Red line color
    gluOrtho2D(-320, 320, -240, 240);     // 4 quadrants
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw coordinate axes
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(320, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 240);
    glEnd();

    glColor3f(1, 0, 0); // Reset color to red
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
    glutCreateWindow("Bresenham Solid Line");
    init();
    glutDisplayFunc(bresenham_line);
    glutMainLoop();
    return 0;
}
