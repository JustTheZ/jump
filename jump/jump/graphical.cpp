#include "graphical.h"
#include "public.h"

GLfloat silver[] = { 0.8f, 0.8f, 0.8f };

Graphical::Graphical()
{
    gx = 0;
    gy = 0;
    gz = 0;
    num = 2;
    color[0] = 0.8f;
    color[1] = 0.8f;
    color[2] = 0.8f;
}

void Graphical::theThree(double x, double z)
{
    gx = x;
    gy = 0;
    gz = z;
}

void Graphical::positionRandom()
{
    double a, angle;
    for (int i = 0; i < 3; i++)
        color[i] = rand() % 51 / (float)100; // 0~0.5
    num = rand() % 4 + 1; // 1~4的随机数
    a = rand() % 4 + 8; // 8~11的随机数
    angle = rand()%61 - 30; // 角度：-30°~30°
    gx += a * cos(angle * PI /180);
    gy = 0;
    gz += a * sin(angle * PI / 180);
}

double Graphical::getGx() { return gx; };

double Graphical::getGz() { return gz; };

void Graphical::circular()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 50; i++)
        glVertex3d(gx + 3 * cos(2 * PI * i / 50), 0, gz + 3 * sin(2 * PI * i / 50));
    glEnd();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, silver);
    glBegin(GL_LINES);
    glVertex3d(gx - 3, 0, gz);
    glVertex3d(gx - 3, -4, gz);

    glVertex3d(gx, 0, gz + 3);
    glVertex3d(gx, -4, gz + 3);
    glEnd();
}

void Graphical::triangle()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glBegin(GL_TRIANGLES);
    glVertex3d(gx, 0, gz - 4);
    glVertex3d(gx - 3, 0, gz + 2);
    glVertex3d(gx + 3, 0, gz + 2);
    glEnd();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, silver);
    glBegin(GL_LINES);
    glVertex3d(gx, 0, gz - 4);
    glVertex3d(gx, -2, gz - 4);

    glVertex3d(gx - 3, 0, gz + 2);
    glVertex3d(gx - 3, -2, gz + 2);

    glVertex3d(gx + 3, 0, gz + 2);
    glVertex3d(gx + 3, -2, gz + 2);
    glEnd();
}

void Graphical::square()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glBegin(GL_QUADS);
    glVertex3d(gx - 2.5, 0, gz - 2.5);
    glVertex3d(gx - 2.5, 0, gz + 2.5);
    glVertex3d(gx + 2.5, 0, gz + 2.5);
    glVertex3d(gx + 2.5, 0, gz - 2.5);
    glEnd();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, silver);
    glBegin(GL_LINES);
    glVertex3d(gx - 2.5, 0, gz - 2.5);
    glVertex3d(gx - 2.5, -6, gz - 2.5);

    glVertex3d(gx - 2.5, 0, gz + 2.5);
    glVertex3d(gx - 2.5, -6, gz + 2.5);

    glVertex3d(gx + 2.5, 0, gz + 2.5);
    glVertex3d(gx + 2.5, -6, gz + 2.5);

    glVertex3d(gx + 2.5, 0, gz - 2.5);
    glVertex3d(gx + 2.5, -6, gz - 2.5);
    glEnd();
}

void Graphical::rectangle()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glBegin(GL_QUADS);
    glVertex3d(gx - 3, 0, gz - 2.5);
    glVertex3d(gx - 3, 0, gz + 2.5);
    glVertex3d(gx + 3, 0, gz + 2.5);
    glVertex3d(gx + 3, 0, gz - 2.5);
    glEnd();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, silver);
    glBegin(GL_LINES);
    glVertex3d(gx - 3, 0, gz - 2.5);
    glVertex3d(gx - 3, -8, gz - 2.5);

    glVertex3d(gx - 3, 0, gz + 2.5);
    glVertex3d(gx - 3, -8, gz + 2.5);

    glVertex3d(gx + 3, 0, gz + 2.5);
    glVertex3d(gx + 3, -8, gz + 2.5);

    glVertex3d(gx + 3, 0, gz - 2.5);
    glVertex3d(gx + 3, -8, gz - 2.5);
    glEnd();
}

void Graphical::changeModel(Graphical* p) 
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
            p[i].color[j] = p[i+1].color[j];
        p[i].gx = p[i+1].gx;
        p[i].gy = p[i+1].gy;
        p[i].gz = p[i+1].gz;
        p[i].num = p[i+1].num;
    }
    
    p[4].positionRandom();
}

void Graphical::exchange(Graphical* p, Graphical* q)
{
    for (int i = 0; i < 5; i++)
    {
        q[i].gx = p[i].gx;
        q[i].gy = p[i].gy;
        q[i].gz = p[i].gz - 20;
        q[i].num = p[i].num;
        for (int j = 0; j < 3; j++)
            q[i].color[j] = p[i].color[j];
    }
}

int Graphical::build()
{
    switch (num)
    {
        case 1:
            rectangle();
            break;

        case 2:
            square();
            break;

        case 3:
            circular();
            break;

        case 4:
            triangle();
            break;

        default:
            break;
    }
    return num;
}