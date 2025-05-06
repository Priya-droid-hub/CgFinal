#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

float x[3] = {100, 200, 150}; // Triangle X coordinates
float y[3] = {100, 100, 200}; // Triangle Y coordinates

int choice;
float sx = 1.0, sy = 1.0;
float angle = 0.0, cx = 0.0, cy = 0.0;
char axis;

void drawTriangle(float x[], float y[], float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++)
        glVertex2f(x[i], y[i]);
    glEnd();
}

void applyScaling(float x_new[], float y_new[]) {
    for (int i = 0; i < 3; i++) {
        x_new[i] = x[i] * sx;
        y_new[i] = y[i] * sy;
    }
}

void applyRotation(float x_new[], float y_new[]) {
    float rad = angle * M_PI / 180.0;
    for (int i = 0; i < 3; i++) {
        x_new[i] = (x[i] - cx) * cos(rad) - (y[i] - cy) * sin(rad) + cx;
        y_new[i] = (x[i] - cx) * sin(rad) + (y[i] - cy) * cos(rad) + cy;
    }
}

void applyReflection(float x_new[], float y_new[]) {
    for (int i = 0; i < 3; i++) {
        x_new[i] = (axis == 'y' || axis == 'Y') ? 400 - x[i] : x[i];
        y_new[i] = (axis == 'x' || axis == 'X') ? 400 - y[i] : y[i];
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawTriangle(x, y, 1, 0, 0); // Draw original in red

    float x_new[3], y_new[3];

    switch (choice) {
        case 1:
            applyScaling(x_new, y_new);
            drawTriangle(x_new, y_new, 0, 0, 1); // Blue scaled
            break;
        case 2:
            applyRotation(x_new, y_new);
            drawTriangle(x_new, y_new, 0, 1, 0); // Green rotated
            break;
        case 3:
            applyReflection(x_new, y_new);
            drawTriangle(x_new, y_new, 1, 0, 1); // Magenta reflected
            break;
        default:
            break;
    }

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 400, 0, 400);
}

int main(int argc, char** argv) {
    cout << "Select Transformation:\n";
    cout << "1) Scaling\n";
    cout << "2) Rotation about arbitrary point\n";
    cout << "3) Reflection (about x or y axis)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter scaling factors sx and sy: ";
        cin >> sx >> sy;
    } else if (choice == 2) {
        cout << "Enter center of rotation (cx, cy): ";
        cin >> cx >> cy;
        cout << "Enter angle in degrees: ";
        cin >> angle;
    } else if (choice == 3) {
        cout << "Enter axis for reflection (x or y): ";
        cin >> axis;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformations - Scaling, Rotation, Reflection");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}





