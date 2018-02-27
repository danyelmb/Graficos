#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

void initFunc();
void funReshape(int w, int h);
void funDisplay();
void drawTriangulo(char color);
void funKeyboard(int key, int x, int y);
void drawEsfera(char forma,char color);
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
    glutCreateWindow("Sesion 4");
    
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
    glPolygonOffset(1.0,1.0);
    
 // Modelo de sombreado
    glShadeModel(GL_SMOOTH);
 /*   
 //Culling de las caras traseras
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
*/
    
 // Modo de rasterizado de las caras
    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_LINE); 
 
 // Simulación de niebla    
    glEnable(GL_FOG);    
    glFogi(GL_FOG_MODE,GL_LINEAR);
    glFogf(GL_FOG_START, 10.0);
    glFogf(GL_FOG_END  , 20.0);
    GLfloat colorNiebla[4] = {0.0, 0.0, 0.0, 1.0};
    glFogfv(GL_FOG_COLOR, colorNiebla);
    
    
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
    //No deformar camara
    //GLfloat aspectRatio = (GLfloat)w/(GLfloat)h;
    //Tipos Camaras
    //Configuracion 1
    GLfloat fovy = 50.0f, aspectRatio = (GLfloat)w/(GLfloat)h, nplane = 1.0f, fplane = 20.0f;
    gluPerspective(fovy,aspectRatio,nplane,fplane);
    
    //Configuracion 2
    //GLfloat left = -2.0f, right = 2.0f, bottom = -2.0f, top = 2.0f, nplane = 1.0f, fplane = 20.0f;
    //Ortografica
    //glOrtho(left,right,bottom,top,nplane,fplane);
    //Perspectiva 1
    //glFrustum(left,right,bottom,top,nplane,fplane);
    
    
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (Cámara)
    // Aquí cargaremos la matriz V
    GLfloat eye[3]    = {0.0,  2.0,  0.0};
    GLfloat center[3] = {0.0,  0.0,  -5.0};
    GLfloat up[3]     = {0.0,  1.0,  0.0};
    gluLookAt(    eye[0],    eye[1],    eye[2],
               center[0], center[1], center[2],
                   up[0],     up[1],     up[2]);

 // Dibujamos los objetos (M)
    glTranslatef(0.0f, 0.0f, desZ);
    
    glPushMatrix();
        glScalef(1.0f,1.0f,1.0f);
        glRotatef(girar,0.0f,1.0f, 0.0f);
         glEnable(GL_POLYGON_OFFSET_FILL);
            drawEsfera('w','g');
         glDisable(GL_POLYGON_OFFSET_FILL);
    glPopMatrix();
    glPushMatrix();
        glScalef(1.0f,1.0f,1.0f);
        glRotatef(girar,0.0f,1.0f, 0.0f);
        drawEsfera('s','b');
    glPopMatrix();
    
 // Intercambiamos los buffers
    glutSwapBuffers();
    
}

void drawEsfera(char forma,char color){
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
    switch(forma){
        case 's':
            glutSolidSphere(1.0f,50,50);
            break;
        case 'w':
            glutWireSphere(1.0f,50,50);
            break;
        default:
            glutWireSphere(1.0f,50,50);
    }

}


void drawTriangulo(char color) {
    int var = 0;
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
        case 'm':
            var=1;
            break;
        default:
            glColor3f(1.0f, 1.0f, 1.0f);            
    }
    
    if (var > 0){
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f( 0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f( 0.0f,  0.5f, 0.0f);
    }else{
    
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glVertex3f( 0.5f, -0.5f, 0.0f);
        glVertex3f( 0.0f,  0.5f, 0.0f);
    glEnd();
    
    }
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
    girar += 0.5f ;
    Sleep(10);
    glutPostRedisplay();
    glutTimerFunc(10, repeat, 0);
}