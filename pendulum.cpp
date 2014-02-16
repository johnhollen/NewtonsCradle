#include "pendulum.h"

#include "windows.h"
#include "vmath.h"

#include <math.h>
#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Pendulum::Pendulum()//DefaultKonstruktor
{
    play = false;

    initTheta = -90.0; theta = initTheta; //Angle

    omega = 0; //Angular Velocity

    rcolor = 0.5;
    gcolor = 0.5;
    bcolor = 0.5;

    velocity = 0;
    position.x = 0; position.y = 0; position.z = 0;
    prevPos.x = 0; prevPos.y = 0; prevPos.z = 0;

    ropeLength = 15;
    radius = 1.2f;
    mass = 10.0;

    airDrag = (0.47/(2*mass))*0.0011839*M_PI*(radius*radius)*ropeLength; //0.47 = dragCoefficient f�r sf�r, 0.0011839 �r densiteten f�r luft vid 25Celcius

    initHeight = ropeLength*(1-cos(DEG2RAD(theta)));
    height = 0;

    nr = 0.0;

}

Pendulum::Pendulum(float theX, float theY, float theZ, int theNr, float theAngle)//Konstruktor
{
    play = false;

    rcolor = 0.5;
    gcolor = 0.5;
    bcolor = 0.5;

    initTheta = theAngle; theta = initTheta; //Angle

    omega = 0; //Angular Velocity

    velocity = 0;
    position.x = theX; position.y = theY; position.z = theZ;
    prevPos.x = theX; prevPos.y = theY; prevPos.z = theZ;

    ropeLength = 15;
    radius = 1.2f;
    mass = 10.0;

    airDrag = (0.47/(2*mass))*0.0011839*M_PI*(radius*radius)*ropeLength; //0.47 = dragCoefficient of sphere, 0.0011839 density of air at 25Celcius



    initHeight = ropeLength*(1-cos(DEG2RAD(theta)));
    height = 0;

    nr = theNr;
}

//H�r r�knas EulerL�sningen ut f�r varje frame
void Pendulum::calculatePosition()
{

    prevPos.x = position.x;
    prevPos.y = position.y;

    //EulerL�sning fr�n matlab
    //R�kna ut omega och theta
    //R�kna ut VinkelHastighetet och Vinkeln och nu senast med luftmotst�nd tillagt :D

    if(play)
    {
        //F�r sm� theta approximeras sin(theta) med theta.
        if(theta < 0.05 && theta > -0.05)
            omega -= timeStep*(((GRAVITY/ropeLength)*theta) + airDrag*omega*abs(omega));

        else
            omega -= timeStep*((GRAVITY/ropeLength)*sin(DEG2RAD(theta)) + airDrag*omega*abs(omega));


        theta += timeStep*omega;
    }

    //R�kna ut h�jden

    height = ropeLength*(1-cos(DEG2RAD(theta)));

    //R�kna ut hastighet
    velocity = sqrt(2*GRAVITY*(initHeight-height)); //v = sqrt(2g*deltaH)


    //Uppdatera positionen av pendeln
    position.y = -ropeLength*cos(DEG2RAD(theta));
    position.x = (ropeLength*sin(DEG2RAD(theta)) + (radius*nr));
}

//Funktion f�r att rita ut pendlarna.
//Uppdatera klotet med positionerna vi f�r fr�n calculatePosition, och rotera sn�ret med kulan s� det ser ut som att den sitter fast i det.
void Pendulum::draw()
{

    calculatePosition();

    glPushMatrix();
    glColor3f(rcolor, gcolor, bcolor);
    glTranslatef(prevPos.x,prevPos.y, 0.0);
    glRotatef(theta, 0.0, 0.0, 1.0);
    glutSolidSphere(radius, 30.0f, 30.0f);

    glRotatef(-70.0f,1.0f,0.0f,0.0f);
    glTranslatef(0.0, 0.0, 0.0);
    glColor3f(0.9f, 0.9f, 0.8f);
    glutSolidCone(0.05f, ropeLength, 15.0f, 15.0f);


    glRotatef(-45.0f,1.0f,0.0f,0.0f);
    glTranslatef(0.0, 0.0, 0.0);
    glColor3f(0.9f, 0.9f, 0.8f);
    glutSolidCone(0.05f, ropeLength, 15.0f, 15.0f);

    glPopMatrix();
}

//S�tta in ny vinkelhastighet, anv�nds vid kollisionerna.
void Pendulum::insertNewOmega(float newOmega)
{
    omega = newOmega;
}

//S�tta in ny vinkel, anv�nds vid translatering och n�r man v�ljer initialvinkel.
void Pendulum::insertNewTheta(float newTheta)
{
    theta = newTheta;
}

//Funktion f�r att hitta vilket h�ll pendeln r�r sig �t.
//Approximerat p� en gr�ns vid 0.3, d� vinkelhastigheten n�stan aldrig blir 0. Fungerar b�ttre s�.
int Pendulum::calculateDirection()
{
    if(omega < -0.3)
    {
        return -1;
    }
    else if(omega > 0.3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Pendlarna uppdaterar inte sin position s�l�nge som play = false; M�ste vara true. Blir true n�r man trycker p� play.
void Pendulum::setPlay(bool p)
{
    play = p;
}

//Funktion f�r att �ndra f�rg p� pendlarna. Heter setActive f�r att det �r en rest fr�n ett gammalt tankes�tt.
void Pendulum::setActive(float r, float g, float b)
{
    rcolor = r;
    gcolor = g;
    bcolor = b;
}
