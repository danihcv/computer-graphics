#include <iostream>
#include <GL/glut.h>

static int year = 0, day = 0;
float lx = 0, ly = 0, lz = 2;

void init(void) {
    /* selecionar cor de fundo (preto) */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
}

// Funcao callback chamada para fazer o desenho
void display(void) {
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
    GLfloat lightPosition[] = {lx, ly, lz, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
        glColor3f(1, 1, 0);
        glRotatef((GLfloat) year, 1.0, 0.0, 0.0);
        glRotatef((GLfloat) day, 0.0, 0.0, 1.0);
        glutSolidSphere(1.0, 100, 100);    /* desenha o sol */
    glPopMatrix();

    glPushMatrix();
        glRotatef((GLfloat) year, 0.0, 1.0, 0.0);
        glTranslatef(2.0, 0.0, 0.0);

        glPushMatrix();
            glColor3f(0, 0, 1);
            glRotatef((GLfloat) day, 0.0, 1.0, 0.0);
            glutSolidSphere(0.2, 50, 50); /* planeta 1 */
        glPopMatrix();

        glPushMatrix();
            glColor3ub(255, 0, 0);
            glRotatef((GLfloat) day, 0.0, 0.0, 1.0);
            glTranslatef(0.5, 0.0, 0.0);
            glutSolidSphere(0.05, 50, 50); /* lua 1 */
        glPopMatrix();

        glPushMatrix();
            glColor3ub(0, 255, 0);
            glRotatef((GLfloat) day, 0.0, 1.0, 1.0);
            glTranslatef(0.4, 0, 0);
            glutSolidSphere(0.025, 50, 50); /* lua 2 */
        glPopMatrix();

        glColor3ub(255, 255, 255);
    glPopMatrix();

    glPushMatrix();
        glRotatef((GLfloat) year, 0.0, (GLfloat) -1.0, 0.0);
        glTranslatef((GLfloat) -3.0, 0.0, 0.0);        /* translada a partir do novo sistema de coordenadas resultante da Rotacao */
        glRotatef((GLfloat) day, 0.0, (GLfloat) -1.0, 0.0);
        glutSolidSphere(0.2, 10, 8); /* desenha o segundo planeta */
    glPopMatrix();

    //executa os comandos
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // posicao da camera
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'd':
            day = (day + 10) % 360;    // % valor do resto
            glutPostRedisplay();
            break;
        case 'D':
            day = (day - 10) % 360;
            glutPostRedisplay();
            break;
        case 'y':
            year = (year + 5) % 360;
            glutPostRedisplay();
            break;
        case 'Y':
            year = (year - 5) % 360;
            glutPostRedisplay();
            break;
        case 'x':
//            if (lx < 1)
                lx += 0.1;
            glutPostRedisplay();
            break;
        case 'X':
//            if (lx > -1)
                lx -= 0.1;
            glutPostRedisplay();
            break;
        case 'z':
            if (lz < 4)
                lz += 0.1;
            glutPostRedisplay();
            break;
        case 'Z':
//            if (lz > -2)
                lz -= 0.1;
            glutPostRedisplay();
            break;
        case 'c':
//            if (ly < 1)
                ly += 0.1;
            glutPostRedisplay();
            break;
        case 'C':
//            if (ly > -1)
                ly -= 0.1;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
        default:
            break;
    }
}


int main(int argc, char *argv[]) {

    /* inicializa o sitema GLUT */
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotacao de planetas");

    //chama a funcao init e inicia as propriedades View Port
    init();
    /* Callback para mostrar objetos na tela */
    glutDisplayFunc(display);
    /* Callback para para interagir com teclado */
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    /* inicia o processamento dos eventos... */
    glutMainLoop();

    return 0;
}