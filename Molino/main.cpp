#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <Windows.h>

void initFunc();
void funReshape(int w, int h);
void funDisplay();
void drawTriangulo(char color);
void drawAspas();
void funKeyboard(int key, int x, int y);
void repeat(int t);


using namespace std;

// Variables globales
int w = 500;
int h = 500;
GLfloat desZ = -5.0f;
GLfloat rotY =  0.0f;
GLfloat girar = 0.0f;



int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Sesion 3");
    
 // Inicializamos GLEW
    GLenum err = glewInit();
    if(GLEW_OK != err) printf("Error: %s\n", glewGetErrorString(err));
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    printf("This system supports OpenGL Version: %s\n", oglVersion);
    
 // Inicializaciones específicas
    initFunc();
    
 // Configuración CallBacks
    glutReshapeFunc(funReshape);
    glutDisplayFunc(funDisplay);
    glutSpecialFunc(funKeyboard);
    glutTimerFunc(10, repeat, 0);
 // Bucle principal
    glutMainLoop();
    
    return 0;
}

void initFunc() {
   
 // Test de profundidad
    glEnable(GL_DEPTH_TEST);
    
 // Modelo de sombreado
    glShadeModel(GL_FLAT);
    

    
    

    
    
    
    
}

void funReshape(int wnew, int hnew) {
    
 // Configuración del Viewport
    glViewport(0, 0, wnew, hnew);

 // Captura de w y h
    w = wnew;
    h = hnew;
    
}

void funDisplay() {
    
 // Borramos el buffer de color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
 // Para configurar la matriz matriz P
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
 // Matriz de Proyección P (Cámara)
    GLfloat aspectRatio = (GLfloat)w/(GLfloat)h;    
    GLfloat fovy = 50.0f, nplane = 0.1f, fplane = 20.0f;
    gluPerspective(fovy,aspectRatio,nplane,fplane);
    
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (Cámara)
    // Aquí cargaremos la matriz V

 // Dibujamos un triángulo
    //glScalef(int, int, int);
    glTranslatef( 0.0f, 0.0f, desZ);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glPushMatrix();
        glTranslatef( 0.0f, 1.5f, 0.0f);
        glRotatef(girar, 0.0f, 0.0f, 1.0f);
        drawAspas();
    glPopMatrix();
    glPushMatrix();
        glTranslatef( 0.0f, 1.5f, -0.051f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glutSolidCylinder(0.05f, 1.5f, 20, 5);
    glPopMatrix();

    
 // Intercambiamos los buffers
    glutSwapBuffers();
    
}

void drawAspas(){
    glPushMatrix();
        glTranslatef(0.0f, -0.74f, 0.0f);
        drawTriangulo('g');
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(120, 0.0f, 0.0f, 1.0f);
        glTranslatef( 0.0f, -0.74f, 0.0f);
        drawTriangulo('r');
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(240, 0.0f, 0.0f, 1.0f);
        glTranslatef( 0.0f, -0.74f, 0.0f);
        drawTriangulo('b');
    glPopMatrix();
}

void drawTriangulo(char color) {
    
    switch(color) {
        case 'r':
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        case 'g':
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        case 'b':
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        default:
            glColor3f(1.0f, 1.0f, 1.0f);            
    }
    
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.2f, 0.0f, 0.0f);
        glVertex3f( 0.25f, -0.3f, 0.0f);
        glVertex3f( 0.0f,  0.75f, 0.0f);
    glEnd();
    
}

void funKeyboard(int key, int x, int y) {
    
    switch(key) {
        case GLUT_KEY_UP:
            desZ -= 0.1f;
            break;
        case GLUT_KEY_DOWN:
            desZ += 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            rotY -= 5.0f;
            break;
        case GLUT_KEY_LEFT:
            rotY += 5.0f;
            break;
        default:
            desZ = -5.0f;  
            rotY =  0.0f;
    }
    
    glutPostRedisplay();
      
    
  
}

void repeat(int t){
    girar += 1.25f ;
    //Sleep(10);
    glutPostRedisplay();
    glutTimerFunc(10, repeat, 0);
 
}
