#ifndef PENDULUM_H_INCLUDED
#define PENDULUM_H_INCLUDED

#include "vmath.h"

#define GRAVITY 9.82

class Pendulum
{
private:
    //Vinkelrelaterade variabler.
    float theta, initTheta;
    float velocity;
    float omega;

    //Massa och replängd och höjd
    float mass;
    float height;
    float initHeight;
    float ropeLength;
    float airDrag;
    float radius;

    bool play;
    float rcolor;
    float gcolor;
    float bcolor;

    //Coefficients of restitution
    static const float CORsteel = 0.9f; //steel on steel collision
    static const float CORwood = 0.65f; //wood on wood collision
    static const float CORglass = 0.96; //glass on glass collision

    //Tidssteg för Euler
    static const float timeStep = 0.1f;

    //Pendelns position
    Vector3f position;
    Vector3f prevPos;

    float nr;

public:
    Pendulum();

    Pendulum(float theX, float theY, float theZ, int theNr, float theAngle);

    void calculatePosition();
    void draw();

    Vector3f getPosition() const {return position;};
    float getXpos() const {return position.x;};
    float getTheta() const {return theta;};
    float getRadius() const{return radius;};
    float getOmega() const  {return omega;};

    //Hämta vilket material som används
    float getCOR(int material) const
    {
        if(material == 1)
            return CORsteel;

        else if(material == 2)
            return CORwood;

        else if(material == 3)
            return CORglass;
    };



    void insertNewOmega(float newOmega);
    void insertNewTheta(float newTheta);
    int calculateDirection();
    void setIndex(int theIndex);
    void setPlay(bool p);
    void setActive(float r, float g, float b);
};


#endif // PENDULUM_H_INCLUDED
