#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

float x1, y_start, x2, y_end; // Renamed y1 to y_start and y2 to y_end

void plot(float x, float y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void DDA_staircase_line() {
    float dx = x2 - x1;
    float dy = y_end - y_start;
    float steps;
    
    if (abs(dx) > abs(dy)) {
        steps = abs(dx);  // Move along x axis more
    } else {
        steps = abs(dy);  // Move along y axis more
    }
    
    float x = x1, y = y_start;
    
    // Determine whether to step in x or y direction for staircase effect
    if (abs(dx) > abs(dy)) {  // Horizontal movement is larger
        for (int i = 0; i <= steps; i++) {
            plot(round(x), round(y));  // Round to nearest pixel
            x += (dx / steps);
            if (i % 2 == 0) {  // Alternate stepping vertically
                y += (dy / steps);
            }
        }
    } else {  // Vertical movement is larger
        for (int i = 0; i <= steps; i++) {
            plot(round(x), round(y));  // Round to nearest pixel
            y += (dy / steps);
            if (i % 2 == 0) {  // Alternate stepping horizontally
                x += (dx / steps);
            }
        }
    }
}

void init() {
    glClearColor(1, 1, 1, 0);
    glColor3f(1, 0, 0);
    gluOrtho2D(-320, 320, -240, 240); // Divide screen into 4 quadrants
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw coordinate axes
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(320, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 240);
    glEnd();
    
    glColor3f(1, 0, 0); // Reset color to red for line
}

int main(int argc, char **argv) {
    cout << "Enter start point (x1 y_start): ";
    cin >> x1 >> y_start;
    cout << "Enter end point (x2 y_end): ";
    cin >> x2 >> y_end;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Staircase Line - DDA Algorithm");
    init();
    glutDisplayFunc(DDA_staircase_line);
    glutMainLoop();
    return 0;
}
