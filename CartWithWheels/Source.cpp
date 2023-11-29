#include <glut.h>;
#include <math.h>;

float PI = 3.14;
double animationFactor = 0;

void init() {
    glClearColor(0.68, 0.85, 0.9, 1.0); // Set clear color to white
}

void reshape(int w, int h) {
    glViewport(0.0, 0.0, w, h);
    if (h == 0) {
        h = 1;
    }
    float aspect_ratio = (float)w / (float)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w >= h) {
        gluOrtho2D(-10.0 * aspect_ratio, 10.0 * aspect_ratio, -10.0, 10.0); // Define your coordinate system
        //left right top bottom
    }
    else {
        gluOrtho2D(-10.0, 10.0, -10.0 / aspect_ratio, 10.0 / aspect_ratio);
    }
}

void drawWheelPoke(float radius, int n) {
    glLineWidth(3.0);
    glBegin(GL_LINES);
    for (int i = 0; i < n; ++i) {
        float angle = 2 * PI * i / n;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2d(x, y);
        glVertex2d(0, 0);
    }
    glEnd();
}

void drawCircle(float radius, int n) {
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Draw n-sided regular polygon (circle approximation) here
    glBegin(GL_POLYGON);
    for (int i = 0; i <= n; ++i) {
        float angle = 2 * PI * i / n;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2d(x, y);
    }
    glEnd();
}

void drawWheel() {
    glPushMatrix();

    //rotating wheels
    glRotated(-(animationFactor), 0, 0, 1);

    //Outer circle
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(1.5, 32);

    //Inner circle
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(1.2, 32);

    //Wheel poke
    glColor3f(0.8, 0.0, 0.0);
    drawWheelPoke(1.4, 12);

    //Middle circle
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(0.4, 32);

    glPopMatrix();

}

void drawCartRectangle() {
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.0, 0.0);
    glVertex2f(0.0, 0.0);//left bottom
    glVertex2f(0.0, 4.0);//left top
    glVertex2f(9.0, 4.0);//right top
    glVertex2f(9.0, 0.0);//right bottom
    glEnd();

}

void drawCart() {

    glPushMatrix();
    glTranslated(2.0, -5.5, 0.0);
    drawCartRectangle();
    glPopMatrix();

    glPushMatrix();//push MODEL_VIEW_MATRIX to the stack
    glTranslated(3.75, -7.0, 0.0); //translation --first
    drawWheel();
    glPopMatrix();//reset MODEL_VIEW_MATRIX_STACK by popping the top matrix

    glPushMatrix();//push MODEL_VIEW_MATRIX to the stack
    glTranslated(9.25, -7.0, 0.0); //translation --first
    drawWheel();
    glPopMatrix();

}

void drawRoad() {
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex2f(-20.0, -20.0);//left bottom
    glVertex2f(-20.0, -2.0);//left top
    glVertex2f(20.0, -2.0);//right top
    glVertex2f(20.0, -20.0);//right bottom
    glEnd();

    //line 1
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(-20.0, -6.0);//left
    glVertex2f(20.0, -6.0);//right
    glEnd();

    //line 2
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(-20.0, -5.8);//left
    glVertex2f(20.0, -5.8);//right
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawRoad();

    glPushMatrix();
    //animate cart
    glTranslated(animationFactor / 20, 0, 0);
    glTranslated(1.0, -0.3, 0);
    glScaled(0.65, 0.65, 0.0);
    drawCart();
    glPopMatrix();

    //glFlush();
    
    //swap buffers
    glutSwapBuffers();

    animationFactor++;
}

void animate(int value) {
    glutPostRedisplay();
    glutTimerFunc(30, animate, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'r') {
        animationFactor++;
    }
    glutPostRedisplay();

}

void specialKey(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) {
        animationFactor++;
    }
    if (key == GLUT_KEY_LEFT) {
        animationFactor--;
    }
    if (key == GLUT_KEY_UP) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (key == GLUT_KEY_DOWN) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glutPostRedisplay();

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1080, 720);
    glutCreateWindow("OpenGL Wheel");
    init();

    //create graphic
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(30, animate, 0);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);

    glutMainLoop();

    return 0;
}