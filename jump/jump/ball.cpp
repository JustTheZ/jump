#include "ball.h"
#include"public.h"

const int num = 20;
GLfloat black[] = { 0.0f, 0.0f, 0.0f };
char* over = (char*)" Game Over! ";
char* o;

#define textureSize 256
GLubyte textureImage[textureSize][textureSize][3];
static GLuint texName;
int justOne = 1;

void makeTextureImage(void) {
    int i, j;

    for (i = 0; i < textureSize; i++) {
        for (j = 0; j < textureSize; j++) {
            textureImage[i][j][0] = (GLubyte)(i % 256);
            textureImage[i][j][1] = (GLubyte)(j % 256);
            textureImage[i][j][2] = (GLubyte)255;
        }
    }
}

void textureInit()
{
    makeTextureImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //像素存储模式：每个像素按一个字节行对齐

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texName);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 当纹理像素映射到小于或等于一个纹理元素的区域时，使用纹理放大函数
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //边界处采用纹理边缘的颜色，与线框无关
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // 分辨率（mipmap） 图像纹理单元 纹理图像的宽度 高度 边框宽度 纹理图像数据的格式 数据类型 纹理图像数据
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, textureSize, textureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, textureSize, textureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, textureSize, textureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, textureSize, textureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, textureSize, textureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, textureSize, textureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage);
}

Ball::Ball() {  }

Ball::Ball(int r, float* c, double x, double y, double z) :
	radius(r), color(c), bx(x), by(y), bz(z), direction(1) {  }

void Ball::creatTextureBall()
{
    if(justOne++ == 1)
        textureInit();
    glPushMatrix();
    glTranslated(bx, by, bz);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texName);
    glutSolidSphere(radius, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Ball::creatBall()
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glTranslated(bx, by, bz);
    glutSolidSphere(radius, 50, 50);
    glPopMatrix();
}

void Ball::creatHighJumper(int angle) 
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glTranslated(bx, by, bz);
    glutSolidSphere(radius, 50, 50);
    glTranslated(3, 0, -1);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
    glPushMatrix();
    glRotated(angle, 0, 0, 1);
    glScalef(0.01f, 1.0f, 0.01f);
    glutSolidCube(6);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glRotated(angle, 0, 0, 1);
    glTranslated(-0.7, 1, 0);
    glutSolidSphere(0.5, 100, 100);  
    glPopMatrix();
}

void Ball::colorRandom()
{
    for (int i = 0; i < 3; i++)
        color[i] = rand() % 51 / (float)100; // 0~0.5

}

void Ball::selfJump(int &sj)
{
    by += direction * 0.15;
    if (by > 3) {
        by = 3;
        direction = -1;
    }
    else if (by < radius) {
        by = radius;
        direction = 1;
        sj = 0;
    }
}

double Ball::getBx() { return bx; }

double Ball::getBy() { return by; }

double Ball::getBz() { return bz; }

double Ball::jump(double time, double x, double z, int circulate)
{
    double a, b, y;
    a = (x - 7) * 0.3 + 2.1;
    b = x / num * circulate;
    if (fabs(a - time) <= 0.15 )
    {
        y = (-0.3) * b * b + a * b;
        bx += x/num;
        by = 2 + y/2;
        bz += z/num;
    }
    else
    {
        bz += (6 + time)/num;
        by += direction * 0.4;
        if (by >= 3) {
            by = 3;
            direction = -1;
        }
    }

    if (by <= 0)
    {
        glRasterPos3f(bx, by, bz + 5);
        for (o = over; *o != '\0'; o++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *o);
    }

    if (by <= -3) 
    {
        Beep(750, 300);
        Sleep(1000);
        exit(0);
    }
    return 0; 
}
