#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

// Global variables for the coordinates
int x1, startY, x2, endY;

// Function to draw a pixel at (x, y) with a specified color
void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    cout << "(" << x << ", " << y << ")" << endl; // Print coordinates
}

// Bresenham Line Drawing Algorithm
void drawLine(int x1, int startY, int x2, int endY) {
    int dx = abs(x2 - x1);
    int dy = abs(endY - startY);
    int sx = (x2 > x1) ? 1 : -1;
    int sy = (endY > startY) ? 1 : -1;
    int g;
    int x = x1, y = startY;

    cout << "Drawing line from (" << x1 << ", " << startY << ") to (" << x2 << ", " << endY << ")" << endl;

    if (dx >= dy) {
        g = 2 * dy - dx;
        while (x != x2) {
            drawPixel(x, y);
            if (g >= 0) {
                y += sy;
                g -= 2 * dx;
            }
            x += sx;
            g += 2 * dy;
        }
    } else {
        g = 2 * dx - dy;
        while (y != endY) {
            drawPixel(x, y);
            if (g >= 0) {
                x += sx;
                g -= 2 * dy;
            }
            y += sy;
            g += 2 * dx;
        }
    }
    drawPixel(x, y); // Draw the last pixel
}

// OpenGL display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawLine(x1, startY, x2, endY);
    glFlush();
}

// OpenGL initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(4.0);
    glOrtho(0.0, 500.0, 0.0, 500.0, -1.0, 1.0);
}

// Main function
int main(int argc, char** argv) {
    cout << "Enter the starting point (x1, startY): ";
    cin >> x1 >> startY;
    cout << "Enter the ending point (x2, endY): ";
    cin >> x2 >> endY;

    if (x1 < 0 || x1 > 500 || startY < 0 || startY > 500 || x2 < 0 || x2 > 500 || endY < 0 || endY > 500) {
        cout << "Error: Coordinates must be between 0 and 500." << endl;
        return 1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line Drawing Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

