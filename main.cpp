#include <GL/freeglut.h>  
#include <GL/glut.h>   
#include <cmath>


struct Planet {
    float radius;
    float distance;
    float rotationSpeed;
    float orbitSpeed;
    float rotationAngle;
    float orbitAngle;
    float color[3];
};


Planet sun = {1.0, 0.0, 1.0, 0.0, 0.0, 0.0, {1.0, 0.7, 0.0}};   
Planet mercury = {0.2, 2.0, 2.0, 4.0, 0.0, 0.0, {0.7, 0.7, 0.7}};   
Planet venus = {0.3, 3.0, 1.5, 3.0, 0.0, 45.0, {0.9, 0.7, 0.5}};  
Planet earth = {0.4, 4.0, 1.0, 2.0, 0.0, 90.0, {0.0, 0.5, 1.0}};  
Planet mars = {0.3, 5.0, 1.2, 2.5, 0.0, 135.0, {1.0, 0.0, 0.0}};    
Planet jupiter = {0.5, 6.0, 0.8, 1.5, 0.0, 180.0, {1.0, 0.5, 0.0}};     
Planet saturn = {0.4, 7.0, 0.7, 1.2, 0.0, 225.0, {0.8, 0.7, 0.4}};      
Planet uranus = {0.3, 8.0, 0.6, 1.0, 0.0, 270.0, {0.4, 0.8, 0.8}};  
Planet neptune = {0.3, 9.0, 0.5, 0.8, 0.0, 315.0, {0.0, 0.0, 1.0}};  

void drawSphere(float radius, int slices, int stacks) {
    for (int i = 0; i < stacks; i++) {
        float phi1 = (float)i / stacks * M_PI;
        float phi2 = (float)(i + 1) / stacks * M_PI;
        
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++) {
            float theta = (float)j / slices * 2.0f * M_PI;
            
            float x1 = radius * sin(phi1) * cos(theta);
            float y1 = radius * sin(phi1) * sin(theta);
            float z1 = radius * cos(phi1);
            
            float x2 = radius * sin(phi2) * cos(theta);
            float y2 = radius * sin(phi2) * sin(theta);
            float z2 = radius * cos(phi2);
            
            glNormal3f(x1/radius, y1/radius, z1/radius);
            glVertex3f(x1, y1, z1);
            
            glNormal3f(x2/radius, y2/radius, z2/radius);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
}

void drawPlanet(const Planet& planet) {
    glPushMatrix();
    
    
    glRotatef(planet.orbitAngle, 0.0, 1.0, 0.0);
    glTranslatef(planet.distance, 0.0, 0.0);
    
        
    glRotatef(planet.rotationAngle, 0.0, 1.0, 0.0);
    
    
    if (planet.distance == 0.0) {  
            
        glDisable(GL_LIGHTING);
        glColor3f(planet.color[0], planet.color[1], planet.color[2]);
    } else {
            
        GLfloat mat_diffuse[] = {planet.color[0], planet.color[1], planet.color[2], 1.0};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    }
    
    
    drawSphere(planet.radius, 32, 32);
    
    
    if (planet.distance == 0.0) {
        glEnable(GL_LIGHTING);
    }
    
    glPopMatrix();
}

void updatePlanets() {
    
    sun.rotationAngle += sun.rotationSpeed;
    mercury.rotationAngle += mercury.rotationSpeed;
    mercury.orbitAngle += mercury.orbitSpeed;
    venus.rotationAngle += venus.rotationSpeed;
    venus.orbitAngle += venus.orbitSpeed;
    earth.rotationAngle += earth.rotationSpeed;
    earth.orbitAngle += earth.orbitSpeed;
    mars.rotationAngle += mars.rotationSpeed;
    mars.orbitAngle += mars.orbitSpeed;
    jupiter.rotationAngle += jupiter.rotationSpeed;
    jupiter.orbitAngle += jupiter.orbitSpeed;
    saturn.rotationAngle += saturn.rotationSpeed;
    saturn.orbitAngle += saturn.orbitSpeed;
    uranus.rotationAngle += uranus.rotationSpeed;
    uranus.orbitAngle += uranus.orbitSpeed;
    neptune.rotationAngle += neptune.rotationSpeed;
    neptune.orbitAngle += neptune.orbitSpeed;
    
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    
    gluLookAt(0.0, 10.0, 15.0,  
              0.0, 0.0, 0.0,        
              0.0, 1.0, 0.0);       
    
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
    
    GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
   
    GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    
    
    drawPlanet(sun);
    drawPlanet(mercury);
    drawPlanet(venus);
    drawPlanet(earth);
    drawPlanet(mars);
    drawPlanet(jupiter);
    drawPlanet(saturn);
    drawPlanet(uranus);
    drawPlanet(neptune);
    

    glutSwapBuffers();
}

void update(int value) {
    updatePlanets();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  
}
int WindowWidth = 900;
int WindowHeight = 700;

void init(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WindowWidth, WindowHeight);
    glutCreateWindow("Solar System");
    
   
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, float(WindowWidth)/float(WindowHeight), 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    
   
    glutTimerFunc(0, update, 0);
}

int main(int argc, char** argv) {
    init(argc, argv);
    glutDisplayFunc(display);
    glutMainLoop();                       
    return 0;
}