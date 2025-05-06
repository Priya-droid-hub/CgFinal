#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

// Window coordinates
int x1, y_start, x2, y_end;  // Line endpoints
int xmin = -100, ymin = -100, xmax = 100, ymax = 100;  // Clipping window

// Region codes
const int INSIDE = 0;  // 0000
const int LEFT = 1;    // 0001
const int RIGHT = 2;   // 0010
const int BOTTOM = 4;  // 0100
const int TOP = 8;     // 1000

int computeCode(int x, int y) {
    int code = INSIDE;
    
    if (x < xmin)
        code |= LEFT;
    else if (x > xmax)
        code |= RIGHT;
    
    if (y < ymin)
        code |= BOTTOM;
    else if (y > ymax)
        code |= TOP;
    
    return code;
}

void cohenSutherlandClip() {
    int code1 = computeCode(x1, y_start);
    int code2 = computeCode(x2, y_end);
    bool accept = false;
    
    while (true) {
        if (!(code1 | code2)) {  // Both endpoints inside window
            accept = true;
            break;
        }
        else if (code1 & code2) {  // Both endpoints outside window
            break;
        }
        else {
            int code_out = code1 ? code1 : code2;
            int x, y;
            
            // Find intersection point
            if (code_out & TOP) {
                x = x1 + (x2 - x1) * (ymax - y_start) / (y_end - y_start);
                y = ymax;
            }
            else if (code_out & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y_start) / (y_end - y_start);
                y = ymin;
            }
            else if (code_out & RIGHT) {
                y = y_start + (y_end - y_start) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }
            else if (code_out & LEFT) {
                y = y_start + (y_end - y_start) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }
            
            // Replace outside point with intersection point
            if (code_out == code1) {
                x1 = x;
                y_start = y;
                code1 = computeCode(x1, y_start);
            }
            else {
                x2 = x;
                y_end = y;
                code2 = computeCode(x2, y_end);
            }
        }
    }
    
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);  // Draw clipping window
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();
    
    if (accept) {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2i(x1, y_start);
        glVertex2i(x2, y_end);
        glEnd();
    }
    
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(xmin - 20, xmax + 20, ymin - 20, ymax + 20); // Adjust window view
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv) {
    cout << "Enter line coordinates (x1 y_start x2 y_end): ";
    cin >> x1 >> y_start >> x2 >> y_end;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    init();
    glutDisplayFunc(cohenSutherlandClip);
    glutMainLoop();
    return 0;
}
