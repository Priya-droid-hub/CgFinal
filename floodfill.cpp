#include <GL/glut.h>
#include <iostream>
#include <stack>
#include <cmath> // For fabs

using namespace std;

int winWidth = 640, winHeight = 480;
float fillColor[3] = {0.0, 1.0, 0.0};   // Fill color (Green)
float borderColor[3] = {0.0, 0.0, 0.0}; // Border color (Black)
float bgColor[3] = {1.0, 1.0, 1.0};     // Background color (White)

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// Triangle
Point poly[] = {{150, 150}, {300, 350}, {450, 150}};
int polySize = 3;

void drawPoly() {
    glColor3fv(borderColor);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < polySize; i++)
        glVertex2i(poly[i].x, poly[i].y);
    glEnd();
    glFlush();
}

void getPixelColor(int x, int y, float* color) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

void setPixelColor(int x, int y, float* color) {
    glColor3fv(color);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

bool compareColor(float* c1, float* c2) {
    return (fabs(c1[0] - c2[0]) < 0.01 &&
            fabs(c1[1] - c2[1]) < 0.01 &&
            fabs(c1[2] - c2[2]) < 0.01);
}

void floodFill(int x, int y, float* oldColor) {
    stack<Point> pixels;
    pixels.push(Point(x, y));

    while (!pixels.empty()) {
        Point p = pixels.top();
        pixels.pop();

        float color[3];
        getPixelColor(p.x, p.y, color);

        if (compareColor(color, oldColor)) {
            setPixelColor(p.x, p.y, fillColor);
            pixels.push(Point(p.x + 1, p.y));
            pixels.push(Point(p.x - 1, p.y));
            pixels.push(Point(p.x, p.y + 1));
            pixels.push(Point(p.x, p.y - 1));
        }
    }
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = winHeight - y; // Convert to OpenGL coordinate system
        float color[3];
        getPixelColor(x, y, color);
        floodFill(x, y, color);
    }
}

void menuFunc(int option) {
    switch (option) {
        case 1: fillColor[0] = 0.0; fillColor[1] = 1.0; fillColor[2] = 0.0; break; // Green
        case 2: fillColor[0] = 1.0; fillColor[1] = 0.0; fillColor[2] = 0.0; break; // Red
        case 3: fillColor[0] = 0.0; fillColor[1] = 0.0; fillColor[2] = 1.0; break; // Blue
        case 4: glClear(GL_COLOR_BUFFER_BIT); drawPoly(); break;
        case 5: exit(0);
    }
    glFlush();
}

void display() {
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawPoly();
    glFlush();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, winWidth, 0, winHeight);
    glPointSize(1.0);
    glDisable(GL_POINT_SMOOTH); // Avoid anti-aliasing artifacts
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Flood Fill Algorithm - OpenGL");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);

    int menu = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Fill Green", 1);
    glutAddMenuEntry("Fill Red", 2);
    glutAddMenuEntry("Fill Blue", 3);
    glutAddMenuEntry("Clear", 4);
    glutAddMenuEntry("Exit", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
