#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape (int w, int h);

#define AZUL     0.0, 0.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO  1.0, 1.0, 0.0
#define VERDE    0.0, 1.0, 0.0
#define CYAN     1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1
#define ROSEO    0.7, 0.1, 0.6
#define CINZA    0.6, 0.6, 0.6

#define VERMELHO_ESCURO_1 0.78, 0.15, 0.21
#define VERMELHO_ESCURO_2 0.78, 0.36, 0.30
#define CINZA_1 0.92, 0.92, 0.92
#define CINZA_2 0.94, 0.94, 0.94
#define CINZA_3 0.96, 0.96, 0.96
#define CINZA_4 0.98, 0.98, 0.98
#define PRETO 0.0, 0.0, 0.0

static GLfloat vertices[100]={
        0.0,  30.0, 40.0, /* 0 */
        30.0, 30.0, 40.0, /* 1 */
        30.0,  0.0, 40.0, /* 2 */
        0.0,   0.0, 40.0, /* 3 */
        0.0,  30.0, 0.0, /* 4 */
        30.0, 30.0, 0.0, /* 5 */
        30.0,  0.0, 0.0, /* 6 */
        0.0,   0.0, 0.0, /* 7 */
        15.0, 40.0, 40.0, /* 8 */
        15.0, 40.0, 0.0, /* 9 */
        11.0, 0.0, 40.1,
        19.0, 0.0, 40.1,
        19.0, 15.0, 40.1,
        11.0, 15.0, 40.1,
        -50.0, 0.0, 90.0,
        80.0, 0.0, 90.0,
        80.0, 0.0, -50.0,
        -50.0, 0.0, -50.0
};

static GLubyte frenteIndices[]          = {8,0,3,2,1};
static GLubyte trasIndices[]            = {4,9,5,6,7};
static GLubyte esquerdaIndices[]        = {0,4,7,3};
static GLubyte direitaIndices[]         = {2,6,5,1};
static GLubyte fundoIndices[]           = {2,3,7,6};
static GLubyte telhadoEsquerdoIndices[] = {9,4,0,8};
static GLubyte telhadoDireitoIndices[]  = {8,1,5,9};
static GLubyte portaIndices[]  = {10,11,12,13};
static GLubyte chaoIndices[]  = {14,15,16,17};

static int eixoy, eixox;
int largura, altura, dist = 90;
double currR = 0;

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void init(void){
    glClearColor(5.0/255.0, 154.0/255.0, 244.0/255.0, 1.0);
    glOrtho(-65, 65, -65, 65, -100 , 100);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void reshape (int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    largura=w;
    altura=h;
}

void display(void){
    glPushMatrix();
    glRotatef ((GLfloat) eixoy, 0.0, 1.0, 0.0);
    glTranslatef(-15.0, -35.0, -20.0);
    glRotatef ((GLfloat) eixox, 1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glColor3f (CINZA_2); /* frente */
    glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, frenteIndices);

    glColor3f (VERMELHO); /* esquerda */
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, esquerdaIndices);

    glColor3f (ROSEO); /* tras */
    glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, trasIndices);

    glColor3f (AMARELO); /* direita */
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, direitaIndices);

    glColor3f (LARANJA); /* fundo */
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, fundoIndices);

    glColor3f (VERMELHO_ESCURO_2); /* telhado esquerdo */
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, telhadoEsquerdoIndices);

    glColor3f (VERMELHO_ESCURO_1); /* telhado direito */
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, telhadoDireitoIndices);

    glColor3f (PRETO); /* porta */
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, portaIndices);

    glColor3f (VERDE); /* chao */
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, chaoIndices);

    glDisableClientState (GL_VERTEX_ARRAY);

    glPopMatrix();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
    bool skip = false;
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'a':
            printf("%d, %d\n",x,y);
            break;
        case 'y':
            eixoy = (eixoy + 5) % 360;
            glutPostRedisplay();
            break;
        case 'Y':
            eixoy = (eixoy - 5) % 360;
            glutPostRedisplay();
            break;
        case 'x':
            eixox = (eixox + 5) % 360;
            glutPostRedisplay();
            break;
        case 'X':
            eixox = (eixox - 5) % 360;
            glutPostRedisplay();
            break;
        case 'p':
            glLoadIdentity();
            gluPerspective(65.0, (GLfloat) largura /(GLfloat) altura, 20.0, 1200.0);
            gluLookAt(0, 0, -90, 0, 0, 0, 0, 1, 0);
            glutPostRedisplay();
            break;
        case 'o':
            glLoadIdentity();
            glOrtho(-65, 65, -65, 65, -100 , 100);
            glutPostRedisplay();
            break;
        case 'r':
            currR += 0.05;
            skip = true;
        case 'R':
            if (!skip)
                currR -= 0.05;

            glLoadIdentity();
            gluPerspective(65.0, (GLfloat) largura /(GLfloat) altura, 20.0, 1200.0);
            gluLookAt(sin(currR) * dist, 5, cos(currR) * dist,
                      0, 0, 0,
                      0, 1, 0);
            glutPostRedisplay();
            break;
    }
}