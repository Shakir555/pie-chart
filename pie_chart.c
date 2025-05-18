// Libraries
#include <GL/glut.h>
#include <math.h>
#include "pie_chart.h"

// Pie Chart Definition
#define PI 3.14159265f
// Pie Chart proportions and colors
float slices[] = {0.2f, 0.3f, 0.1f, 0.4f};
float colors[][3] = {
    // Orange Colors
    {1.0f, 0.6f, 0.0f},
    // Green Colors
    {0.0f, 1.0f, 0.0f},
    // Blue Colors
    {0.0f, 0.5f, 1.0f},
    // Red Colors
    {1.0f, 0.0f, 0.0f}
};
// Pie Chart Rotation Angle (Start for animation)
float rotationAngle = 0.0f;
// Pie Chart Radius
float radius = 1.0f;

// Pie Chart Draw
void pie_slice_draw(float startAngle, float sweepAngle, float height,
                    float r, float g, float b)
{
    // RGB Colour
    glColor3f(r, g, b);
    // Pie Chart Top Surface
    glBegin(GL_TRIANGLE_FAN);
    // Center vertex of top circle
    glVertex3f(0.0f, height / 2, 0.0f);
    // Start Angle and keep on sweep angle
    for (float angle = startAngle; angle <= startAngle + sweepAngle; angle += 1.0f)
    {
        // Convert angle to radians
        float rad = angle *PI / 180.0f;
        // Perimeter Point
        glVertex3f(radius * cos(rad), height / 2, radius * sin(rad));
    }
    glEnd();

    // Pie Chart Botton Surface
    glBegin(GL_TRIANGLE_FAN);
    // Center of bottom face
    glVertex3f(0.0f, -height / 2, 0.0f);
    // Start Angle and keep on sweep angle
    for (float angle = startAngle; angle <= startAngle + sweepAngle; angle += 1.0f)
    {
        float rad = angle * PI / 180.0f;
        glVertex3f(radius * cos(rad), -height / 2, radius * sin(rad));
    }
    glEnd();

    // Pie Chart Side Wall
    glBegin(GL_QUAD_STRIP);
    // Draw the vertical side walls using a quad strip
    for (float angle = startAngle; angle <= startAngle + sweepAngle; angle += 1.0f)
    {
        float rad = angle * PI / 180.0f;
        float x = radius * cos(rad);
        float z = radius * sin(rad);
        // Top Point
        glVertex3f(x, height / 2, z);
        glVertex3f(x, -height / 2, z);
    }
    glEnd();
}

// Pie Chart Display
void pie_chart_disp()
{
    // Pie Chart Initial Start Angle
    float startAngle = 0.0f;
    // Height (thickness) of the pie chart
    float height = 0.2f;
    // Pie Chart Clear Display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Position the camera: eyeX, eyeY, eyeZ, 
    // centerX, centerY, centerZ, 
    // upX, upY, upZ
    gluLookAt(0.0, 1.5, 3.0,    // Camera position
              0, 0, 0,          // Look-at target
              0, 1, 0);         // Up direction
    // Apply rotation for animation
    // Rotate around Y-axis
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    
    // 4 Pie Slices draw all
    for (int i = 0; i < 4; i++)
    {
        // Convert proportion to degrees
        float sweepAngle = slices[i] * 360.0f;
        pie_slice_draw(startAngle, sweepAngle, height,
                       colors[i][0], colors[i][1], colors[i][2]);
        // Move to next slice starting angle
        startAngle += sweepAngle;
    }
    // Swap the back buffer with the front buffer (double buffering)
    glutSwapBuffers();
}

// Pie Chart Window Resize Callback
void pie_chart_reshape(int w, int h)
{
    // Avoid division by zero
    if (h == 0) h = 1;
    // Aspect ratio of the window
    float aspect = (float)w / h;
    // Switch to projection matrix
    glMatrixMode(GL_PROJECTION);
    // Reset projection matrix
    glLoadIdentity();
    // Set perspective projection
    gluPerspective(45.0, aspect, 1.0, 10.0);
    // Switch back to modelview matrix
    glMatrixMode(GL_MODELVIEW);
}

// Pie Chart Idle Callback (animation)
void pie_chart_idle()
{
    // Increment the angle to rotate the pie chart
    rotationAngle += 0.2f;
    // Keep the angle in 0-360 degrees range
    if (rotationAngle > 360)
    {
        rotationAngle -=360;
    }
    // Request to redraw the screen
    glutPostRedisplay();
}

// Pie Chart Initialization
void pie_chart_init()
{
    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);
    // Set the background color to white
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // Set the background color to black
    //glClearColor(0.0, 0.0, 0.0, 0.1);
    // Set matrix mode to projection
    glMatrixMode(GL_PROJECTION);
    // Reset projection matrix
    glLoadIdentity(); 
    // Default perspective setup
    gluPerspective(45.0, 1.0, 1.0, 10.0);
    // Set matrix mode back to modelview
    glMatrixMode(GL_MODELVIEW);
}