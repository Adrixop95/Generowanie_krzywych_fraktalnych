//https://www.cs.unm.edu/~angel/CS433.S05/LECTURES/AngelCG06.pdf

#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

#define WIDTH 1280
#define HEIGHT 720

typedef GLfloat point2[2];
point2 v[]={{-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15}};

int max_depth;

void triangle( point2 a, point2 b, point2 c) {
	glBegin(GL_TRIANGLES);
	glVertex2fv(a);
	glVertex2fv(b);
	glVertex2fv(c);
	glEnd();
}

void divide_triangle(point2 a, point2 b, point2 c, int max_depth) {
    point2 v0, v1, v2;
    int j;

    if(max_depth > 0) {

        for(j=0; j<2; j++){
            v0[j] = (a[j]+b[j]) / 2;
        } 

        for(j=0; j<2; j++){
             v1[j] = (a[j]+c[j]) / 2;
        }

        for(j=0; j<2; j++){ 
            v2[j] = (b[j]+c[j]) / 2; 
        }

        divide_triangle(a, v0, v1, max_depth-1);
        divide_triangle(c, v1, v2, max_depth-1);
        divide_triangle(b, v2, v0, max_depth-1);
    } else {
        (triangle(a,b,c));
    }
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	divide_triangle(v[0], v[1], v[2], max_depth);
	glFlush();
}

void sierpinski_gasket(){

	cout << "Podaj maksymalne zagnieżdżenie " << endl;
	cin >> max_depth; 	

	int argc = 1;
	char *argv[1] = {(char*)"Something"};
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Trojkat Sierpinskiego");
	glutDisplayFunc(display);

    glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);

	glutMainLoop();
}

int main(){

    sierpinski_gasket();
}