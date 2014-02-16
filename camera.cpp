#include <windows.h>
#include <math.h>
#include "camera.h"


#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Camera::Camera()
{
    xpos = -15;
    ypos = -10;
    zpos = 25;
    xrot = 0;
    yrot = 22;
}

void Camera::movement (void)
{
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
}


Vector3f Camera::getPosition()
{
    return Vector3f(xpos, ypos, zpos);
}


