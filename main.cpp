#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159265f;
float slices[] = {0.2f, 0.3f, 0.1f, 0.4f};
float colors[][3] = {
    {1.0f, 0.6f, 0.0f}, // orange
    {0.0f, 1.0f, 0.0f}, // green
    {0.0f, 0.5f, 1.0f}, // blue
    {1.0f, 0.0f, 0.0f}  // red
};

float rotationAngle = 0.0f;

void drawPieSlice(float startAngle, float sweepAngle, float height, float r, float g, float b) {
    float radius = 1.0f;
    glColor3f(r, g, b);

    // Top face
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, height / 2, 0.0f);
    for (float angle = startAngle; angle <= startAngle + sweepAngle; angle += 1.0f) {
        float rad = angle * PI / 180.0f;
        glVertex3f(radius * cos(rad), height / 2, radius * sin(rad));
    }
    glEnd();

    // Bottom face
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, -height / 2, 0.0f);
    for (float angle = startAngle; angle <= startAngle + sweepAngle; angle += 1.0f) {
        float rad = angle * PI / 180.0f;
        glVertex3f(radius * cos(rad), -height / 2, radius * sin(rad));
    }
    glEnd();

    // Side wall
    glBegin(GL_QUAD_STRIP);
    for (float angle = startAngle; angle <= startAngle + sweepAngle; angle += 1.0f) {
        float rad = angle * PI / 180.0f;
        float x = radius * cos(rad);
        float z = radius * sin(rad);
        glVertex3f(x, height / 2, z);
        glVertex3f(x, -height / 2, z);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 1.5, 3.0, 0, 0, 0, 0, 1, 0);

    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    float startAngle = 0.0f;
    float height = 0.2f;

    for (int i = 0; i < 4; ++i) {
        float sweepAngle = slices[i] * 360.0f;
        drawPieSlice(startAngle, sweepAngle, height, colors[i][0], colors[i][1], colors[i][2]);
        startAngle += sweepAngle;
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
}

void idle() {
    rotationAngle += 0.2f;
    if (rotationAngle > 360) rotationAngle -= 360;
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0); // white background

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Pie Chart in OpenGL");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle); // for auto-rotation

    glutMainLoop();
    return 0;
}
