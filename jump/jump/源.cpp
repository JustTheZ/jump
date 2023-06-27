#include "public.h" 
#include "ball.h"
#include "camera.h"
#include "graphical.h"
#include "filebackground.h"

char* a = (char*)"Prompt:";
char* b = (char*)"Jump:";
char* c = (char*)"Score:";
char* change;

GLfloat smallWhite[] = { 0.7f, 0.7f, 0.7f };
GLfloat white[] = { 1.0f, 1.0f, 1.0f };
GLfloat smallBlack[] = { 0.3f, 0.3f, 0.3f };
const int sameNum = 20;
int background = 0;
int prompt = 1; //提示判断
double pt;
int view = 3;  // 默认第三视角
int sj = 0;  //  selfjump的判断
int j = 0, circulate = 1; // jump的判断 及 循环
double jumpTime = 1.8; //初始跳跃系数
double stillnessX = 0, stillnessZ = 0; //球禁止时的x，z坐标 
int score = 0;
int angle = 0;
int role = 0;
static GLint fogMode;

Ball ball(2, smallWhite, 0, 2, 0);
Camera camera;
Graphical graphical[5];
double windowWidth = 1900, windowHeigh = 800;

Ball ball2(2, smallBlack, 0, 2, -20);
Graphical graphical2[5];
int circulate2 = 1, distance1 = 0, distance2 = 0;
char* d = (char*)"You win";
char* e = (char*)"You lost";
int model = 0;
int theEnd = 0;
bool isFirstTime = true;
time_t startTime;
time_t endTime;
tm startTimeInfo;
tm endTimeInfo;

char* objname = (char*)"octaflower.obj";

void judgewin()
{
    if (distance1 - distance2 >= 4)
    {
        glRasterPos3f(ball.getBx() + 5, ball.getBy(), ball.getBz() + 5);
        for (change = d; *change != '\0'; change++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *change);
        theEnd++;
    }
    else if (distance1 - distance2 <= -4)
    {
        glRasterPos3f(ball.getBx() + 5, ball.getBy(), ball.getBz() + 5);
        for (change = e; *change != '\0'; change++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *change);
        theEnd++;
    }
}

void shadow()
{
    ball2.creatBall();
    for (int i = 0; i < 5; i++)
    {
        graphical2[i].build();
    }
    if (isFirstTime)
    {
        time(&startTime);
        time(&endTime);
    }
    else
    {
        time(&endTime);
    }

    isFirstTime = false;
    localtime_s(&startTimeInfo, &startTime);
    localtime_s(&endTimeInfo, &endTime);
    if (abs(endTimeInfo.tm_sec - startTimeInfo.tm_sec) >= 2)
    {
        double theShadow = ((graphical2 + 1)->getGx() - graphical2->getGx() - 7) * 0.3 + 2.1;
        if (circulate2 <= sameNum)
        {
            ball2.jump(theShadow, (graphical2 + 1)->getGx() - graphical2->getGx(), (graphical2 + 1)->getGz() - graphical2->getGz(), circulate2);
            circulate2++;
        }

        if (circulate2 == sameNum + 1)
        {
            isFirstTime = true;
            circulate2 = 1;
            distance2++;
            graphical2->changeModel(graphical2);
        }
    }
    judgewin();
}

//定义计时器函数
void timer(int t) {
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

void init()
{
    GLfloat LightPosition[] = { 100.0f, 100.0f, 100.0f, 1.0f };
    glEnable(GL_DEPTH_TEST);                  //启用深度测试
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE); //标准化

    glEnable(GL_TEXTURE_CUBE_MAP);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);

    graphical[1].positionRandom();
    for (int i = 2; i < 5; i++)
    {
        graphical[i].theThree(graphical[i - 1].getGx(), (graphical + i -1)->getGz());
        graphical[i].positionRandom();
    }
    
    Graphical::exchange(graphical, graphical2);
}

void display()
{
    if(background == 0)
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    else if(background == 1)
        glClearColor(0.8f, 0.7f, 0.6f, 0.0f);
    else if(background == 2)
    {
        glEnable(GL_FOG);
        GLfloat fogColor[4] = { 0.5,0.5,0.5,1.0 };

        fogMode = GL_LINEAR;
        glFogi(GL_FOG_MODE, fogMode);
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 0.5);
        glHint(GL_FOG_HINT, GL_DONT_CARE);
        glFogf(GL_FOG_START, 5.0);
        glFogf(GL_FOG_END, 40.0);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    }
    else
    {
        glDisable(GL_FOG);
        glClearColor(1.0f, 1.0f, 0.9f, 0.0f);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, windowWidth/windowHeigh, 1.0, 100.0);

    if (background == 3 && view == 3)
        drawFlower(-8, 2, -10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (view == 3)
    {
        camera.follow3(ball.getBx(), ball.getBy(), ball.getBz());
        gluLookAt(camera.getCx(), camera.getCy(), camera.getCz(), camera.getCx(), camera.getCy() - 8, camera.getCz() - 16, 0, 1, 0);
    }
    else
    {
        camera.follow1(ball.getBx(), ball.getBy(), ball.getBz());
        gluLookAt(camera.getCx(), camera.getCy(), camera.getCz(), camera.getCx() + 10, camera.getCy(), camera.getCz(), 0, 1, 0);
    }

    if (role == 0)
        ball.creatBall();
    else if (role == 1)
        ball.creatHighJumper(angle);
    else
        ball.creatTextureBall();
    for (int i = 0; i < 5; i++)
    {
        graphical[i].build();
    }

    if (model == 1)
        shadow();
  
    glRasterPos3f(ball.getBx() - 10, ball.getBy() + 7, ball.getBz());
    for (change = b; *change != '\0'; change++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *change);
    glRasterPos3f(ball.getBx() - 8, ball.getBy() + 7, ball.getBz());
    char jt[20];
    sprintf_s(jt, "%.2f", jumpTime);
    for (change = jt; *change != '\0'; change++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *change);

    glRasterPos3f(ball.getBx(), ball.getBy() + 8, ball.getBz());
    for (change = c; *change != '\0'; change++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *change);
    glRasterPos3f(ball.getBx() + 2, ball.getBy() + 8, ball.getBz());
    char sc[20];
    sprintf_s(sc, "%d", score);
    for (change = sc; *change != '\0'; change++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *change);
    
    pt = ((graphical + 1)->getGx() - stillnessX - 7) * 0.3 + 2.1;
    if (prompt == 1)
    {
        glRasterPos3f(ball.getBx() - 10, ball.getBy() + 8, ball.getBz());
        for(change = a; *change != '\0'; change++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *change);
        glRasterPos3f(ball.getBx() - 8, ball.getBy() + 8, ball.getBz());
        char digital[20];
        sprintf_s(digital, "%.2f", pt);
        for (change = digital; *change != '\0'; change++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *change);
    }
    else
    {
        glRasterPos3f(ball.getBx() - 10, ball.getBy() + 8, ball.getBz());
        for (change = a; *change != '\0'; change++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *change);
    }
    
    if (sj == 1)
        ball.selfJump(sj);

    if (j == 1 && circulate <= sameNum)
    {
        ball.jump(jumpTime, (graphical + 1)->getGx() - stillnessX, (graphical + 1)->getGz() - stillnessZ, circulate);
        circulate++;
    }

    if ( circulate == sameNum + 1)
    {
        angle = 0;
        j = 0;
        circulate = 1;
        jumpTime = 1.8;
        score += graphical[1].build();
        stillnessX = ball.getBx();
        stillnessZ = ball.getBz();
        graphical->changeModel(graphical);
        distance1++;
    }

    if (theEnd >= 3)
    {
        Sleep(1000);
        exit(0);
    }
    
    glutSwapBuffers();
}

void script()
{
    jumpTime = pt;
    j = 1;
}

void remoteSense()
{
    angle += 2;
    if (angle >= 45)
        angle = 45;
}

void mouse(int button, int state, int x, int y)
{
    static int turn = 0;
    switch (button)
    {
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
            glutIdleFunc(script);
            turn = 1;
        }  
        break;
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN && turn == 1)
        {
            turn = 0;
            glutIdleFunc(NULL);
        }
        break;
        
    default:
        break;
    }
}

void  keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'm':
            if (model == 1)
                model = 0;
            else
                model = 1;
            break;

        case 'p':
            if (prompt == 1)
                prompt = 0;
            else
                prompt = 1;
            break;

        case 'b':
            if (background < 3)
                background++;
            else
                background = 0;
            break;

        case 'v':
            if (view == 3)
                view = 1;
            else
                view = 3;
            break;

        case 27:
            exit(0);

        case 'c':
            ball.colorRandom();
            break;

        case 'j':
            jumpTime += 0.05; 
            remoteSense();
            break;

        case 'k':
            if (jumpTime <= 2.0 )
            {
                sj = 1;
            }
            else
            {
                Beep(784, 250);
                angle = 90;
                j = 1;
            }
            break;

        case 'r':
            if (role < 2)
                role++;
            else
                role = 0;
            break;

        default:
            break;
    }
}


int main(int argc, char** argv) {
    //PlaySound(TEXT("C:\\ALisa - The Way I Still Love You.WAV"), NULL, SND_ASYNC | SND_LOOP);
    srand(time(NULL));
    Inputobjfile(objname);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(windowWidth, windowHeigh);
    glutCreateWindow("跳一跳");
    init();
    glutDisplayFunc(display);  
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard); 
    glutTimerFunc(100, timer, 0);  //设置计时器函数--每100ms被调用1次
    glutMainLoop();
    return 0;
}
