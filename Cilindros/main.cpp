#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

void initFunc();
void funReshape(int w, int h);
void funDisplay();
void funKeyboard(int key, int x, int y);
void drawCilindro(char forma,char color);
void drawCilindroProfundidad(char color, char rayas);
void repeat(int t);

using namespace std;

// Variables globales
int w = 500;
int h = 500;
GLfloat desZ = 0.0f;
GLfloat rotarY = 0.0f;

int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("PracticaPrueba1");
    
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
    //Funcion Movimiento Continuo
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
        Esto hace que las caras delanteras de los poligonos se vean completas
            mientras que las partes de atras solo las lineas
   
 //Culling de las caras traseras
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

 // Modo de rasterizado de las caras
    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_LINE); 
*/
    
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
    /*
    //No deformar camara
    GLfloat aspectRatio = (GLfloat)w/(GLfloat)h;
     */
    //Tipos Camaras
    //Configuracion 1
    GLfloat fovy = 50.0f, aspectRatio = (GLfloat)w/(GLfloat)h, nplane = 1.0f, fplane = 20.0f;
    gluPerspective(fovy,aspectRatio,nplane,fplane);

    
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (Cámara)
    // Aquí cargaremos la matriz V
    GLfloat eye[3]    = {0.0,  0.0,  5.0};  //Posicion
    GLfloat center[3] = {0.0,  0.0,  0.0};  //Referencia
    GLfloat up[3]     = {0.0,  1.0,  0.0};  //VectorDireccion
    gluLookAt(    eye[0],    eye[1],    eye[2],
               center[0], center[1], center[2],
                   up[0],     up[1],     up[2]);

 // Dibujamos los objetos (M)
    
    //glScalef(1.0f,1.0f,1.0f); Escalar
    //glRotatef(rotar, 0.0f, 0.0f, 0.0f); Rotar
    //glTranslatef( 0.0f, 0.0f, 0.0f ); Mover
    
    
    glTranslatef(0.0f, 0.0f, desZ);
    glTranslatef( 0.0f, 0.5f, 0.0f );
    glRotatef(rotarY, 0.0f, 1.0f, 0.0f);
    glPushMatrix();
        glScalef(0.25f, 1.0f, 0.25f);
        drawCilindroProfundidad('b','g');
    glPopMatrix();
    glPushMatrix();
        glTranslatef( -0.75f, 0.0f, 0.0f );
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        glRotatef(-60, 1.0f, 0.0f, 0.0f);
        glScalef(0.15f, 0.75f, 0.15f);
        drawCilindroProfundidad('b','g');
    glPopMatrix();
    glPushMatrix();
        glTranslatef( 0.1f,  -0.05f, 0.1f );
        glTranslatef( -0.75f, 0.0f, 0.0f );
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        glRotatef(45, 0.0f, 0.0f, -1.0f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        glRotatef(30, 1.0f, 0.0f, 0.0f);
        glScalef(0.10f, 0.5f, 0.10f);
        drawCilindroProfundidad('b','g');
    glPopMatrix();
    
    
    
 // Intercambiamos los buffers
    glutSwapBuffers();
    
}

void drawCilindroProfundidad(char color, char rayas){
    glPushMatrix();
         glEnable(GL_POLYGON_OFFSET_FILL);
            drawCilindro('w',rayas);
         glDisable(GL_POLYGON_OFFSET_FILL);
    glPopMatrix();
    glPushMatrix();
        drawCilindro('s',color);
    glPopMatrix();
}

void drawCilindro(char forma,char color){
    glRotatef(90, 1.0f, 0.0f, 0.0f); //Vertical
    GLfloat radio = 1.0f;
    GLfloat altura = 1.0f;
    
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
        //glutSolidCylinder(radio.f, altura.f, divisionesVerticales, divisionesHorizontales);
        case 's':
            glutSolidCylinder( radio, altura, 12, 6 );
            break;
        case 'w':
            glutWireCylinder( radio, altura, 12, 6 );
            break;
        default:
            glutWireCylinder( radio, altura, 12, 6 );
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
            rotarY -= 5.0f;
            break;
        case GLUT_KEY_LEFT:
            rotarY += 5.0f;
            break;
        default:
            desZ = -5.0f;  
    }
    
    glutPostRedisplay();
      
}

void repeat(int t){
    //rotarZ += 0.5f ;
    Sleep(10);
    glutPostRedisplay();
    glutTimerFunc(10, repeat, 0);
}

/*
    switch(key) {
 *       case 111: (o)
 *       case  99: (c)   
 *       case 120: (x) 
 *       case 121: (y) 
 *       case 122: (z) 
 *       case 114: (r)
 *        
 * 
        case GLUT_KEY_UP:
 *          switch (objeto):
            desZ -= 0.1f;
            break;
        case GLUT_KEY_DOWN:
            desZ += 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            rotarY -= 5.0f;
            break;
        case GLUT_KEY_LEFT:
            rotarY += 5.0f;
            break;
        default:
            desZ = -5.0f;  
    }
 
 
 */