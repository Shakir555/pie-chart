// Libraries
#include <GL/glut.h>
#include <math.h>
#include "pie_chart.h"

// Pie Chart Main Function
int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    // Enable double buffering and depth buffer                                
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // Initial Window Size 
    glutInitWindowSize(600, 600);                         
    // Initial Window Position
    glutInitWindowPosition(100, 100);                     
    // Create Window with Title
    glutCreateWindow("3D Pie Chart in OpenGL");
    // Call Custom Initialization
    pie_chart_init();                      // Call custom initialization
    // Register Pie Chart Display callback
    glutDisplayFunc(pie_chart_disp);
    // Register Pie Chart Reshape Callback
    glutReshapeFunc(pie_chart_reshape);
    // Register Pie Chart Idle Callback for animation
    glutIdleFunc(pie_chart_idle);
    // Enter the GLUT event Loop
    glutMainLoop();                            
}
