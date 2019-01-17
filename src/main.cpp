#include <iostream>
#include <random>
#include <thread>
#include <fstream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

#define WIDTH 1280
#define HEIGHT 720
#define PI 3.14159265358

typedef GLfloat point2[2];
point2 v[]={{-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15}};


struct point{
		double x, y;
};

int max_depth;


void koch_curve(){       

	cout << "Podaj maksymalne zagnieżdżenie " << endl;
	cin >> max_depth;

	glfwInit();
	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Krzywa Kocha", NULL, NULL);
	glfwMakeContextCurrent(window);
	glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0);
	double side_length = (HEIGHT * 3.0/2.0) / sqrt(3.0);
	double width_offset = (WIDTH - side_length) / 2.0;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	vector<point> points;
	points.push_back({.x = width_offset, .y = HEIGHT/4.0});
	points.push_back({.x = WIDTH - width_offset, .y = HEIGHT/4.0});
	points.push_back({.x = WIDTH/2, .y = HEIGHT});
				
	for(int d = 0; d < max_depth; d++){
		vector<point> new_points;
		
		for(int i = 0; i < points.size(); i++){
			double x1 = points[i].x;
			double x2 = points[(i+1)%points.size()].x;
			double y1 = points[i].y;
			double y2 = points[(i+1)%points.size()].y;
							
			double rx1 = (x2 - x1) / 3.0 + x1;
			double ry1 = (y2 - y1) / 3.0 + y1;
			double rx2 = 2.0 * (x2 - x1) / 3.0 + x1;
			double ry2 = 2.0 * (y2 - y1) / 3.0 + y1;
			new_points.push_back(points[i]);
			new_points.push_back({.x = rx1, .y = ry1});

			if(abs(ry1 - ry2) < 0.01){
				new_points.push_back({.x = (rx2 - rx1) / 2.0 + rx1, .y = ry1 + (rx1 - rx2) * sqrt(3.0) / 2.0});
			}
			else if((x2 > x1) == (y1 > y2)){
				new_points.push_back({.x = rx1 + (rx1 - rx2), .y = ry2});
			} else {
				new_points.push_back({.x = rx2 + (rx2 - rx1), .y = ry1});
			}
			new_points.push_back({.x = rx2, .y = ry2});
		}
						
		points = new_points;
	}

	glVertex2i(points[points.size()-1].x, points[points.size()-1].y);
		
	for(int i = 0; i < points.size(); i++){
		glVertex2i(points[i].x, points[i].y);
		glVertex2i(points[i].x, points[i].y);
	}

	glVertex2i(points[0].x, points[0].y);
	glEnd();
	glfwSwapBuffers(window);	
}

void dragon_curve(){

	cout << "Podaj maksymalne zagnieżdżenie " << endl;
	cin >> max_depth;

	glfwInit();
	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Smok Heighwaya", NULL, NULL);
	glfwMakeContextCurrent(window);
	glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	vector<point> points;
	points.push_back({.x = WIDTH/4.0, .y = HEIGHT/2.0});
	points.push_back({.x = WIDTH/2.0, .y = HEIGHT/4.0});
	points.push_back({.x = WIDTH*3.0/4.0, .y = HEIGHT/2.0});
	double length = sqrt((WIDTH * WIDTH / 16.0) + (HEIGHT * HEIGHT / 16.0));
		
	for(int d = 0; d < max_depth; d++){
		length = length / sqrt(2.0);
		vector<point> new_points;	

		for(int i = 0; i < points.size() - 1; i++){
			double x1 = points[i].x;
			double y1 = points[i].y;
			double theta = atan2(points[i+1].y - y1, points[i+1].x - x1);
			double length = sqrt(pow(points[i+1].x - x1, 2.0) + pow(points[i+1].y - y1, 2.0)) / sqrt(2.0);
			double delta_angle = ((i % 2) == 0 ? (PI / 4.0) : -(PI / 4.0));
			double rx = x1 + length * cos(theta + delta_angle);
			double ry = y1 + length * sin(theta + delta_angle);
			new_points.push_back(points[i]);
			new_points.push_back({.x = rx, .y = ry});
		}
		new_points.push_back(points[points.size() - 1]);
		points = new_points;
	}
		
	glVertex2i(points[0].x, points[0].y);
		
	for(int i = 1; i < points.size() - 1; i++){
		glVertex2i(points[i].x, points[i].y);
		glVertex2i(points[i].x, points[i].y);
	}
		
	glVertex2i(points[points.size()-1].x, points[points.size()-1].y);
	glEnd();
	glfwSwapBuffers(window);
}

void hilbert_curve(){
	
	cout << "Podaj maksymalne zagnieżdżenie " << endl;
	cin >> max_depth;

	glfwInit();
	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Krzywa Hilberta", NULL, NULL);
	glfwMakeContextCurrent(window);
	glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
		
	vector<point> points;
	points.push_back({.x = WIDTH/4.0, .y = HEIGHT/4.0});
	points.push_back({.x = WIDTH/4.0, .y = HEIGHT*3.0/4.0});
	points.push_back({.x = WIDTH*3.0/4.0, .y = HEIGHT*3.0/4.0});
	points.push_back({.x = WIDTH*3.0/4.0, .y = HEIGHT/4.0});

	for(int d = 0; d < max_depth; d++){
		vector<point> new_points;
		for(int i = 0; i < points.size(); i += 4){
			if(abs(points[i+1].x - points[i].x) < abs(points[i+1].y - points[i].y)){
				double offset = (points[i+1].y - points[i].y) / 4.0;
								
				double x = points[i].x;
				double y = points[i].y;
				new_points.push_back({.x = x - offset, .y = y - offset});
				new_points.push_back({.x = x + offset, .y = y - offset});
				new_points.push_back({.x = x + offset, .y = y + offset});
				new_points.push_back({.x = x - offset, .y = y + offset});
								
				x = points[i+1].x;
				y = points[i+1].y;
				new_points.push_back({.x = x - offset, .y = y - offset});
				new_points.push_back({.x = x - offset, .y = y + offset});
				new_points.push_back({.x = x + offset, .y = y + offset});
				new_points.push_back({.x = x + offset, .y = y - offset});

				x = points[i+2].x;
				y = points[i+2].y;
				new_points.push_back({.x = x - offset, .y = y - offset});
				new_points.push_back({.x = x - offset, .y = y + offset});
				new_points.push_back({.x = x + offset, .y = y + offset});
				new_points.push_back({.x = x + offset, .y = y - offset});
				x = points[i+3].x;
				y = points[i+3].y;
				new_points.push_back({.x = x + offset, .y = y + offset});
				new_points.push_back({.x = x - offset, .y = y + offset});
				new_points.push_back({.x = x - offset, .y = y - offset});
				new_points.push_back({.x = x + offset, .y = y - offset});
			} else {
				double offset = (points[i+1].x - points[i].x) / 4.0;
							
				double x = points[i].x;
				double y = points[i].y;
				new_points.push_back({.x = x - offset, .y = y - offset});
				new_points.push_back({.x = x - offset, .y = y + offset});
				new_points.push_back({.x = x + offset, .y = y + offset});
				new_points.push_back({.x = x + offset, .y = y - offset});
							
				x = points[i+1].x;
				y = points[i+1].y;
				new_points.push_back({.x = x - offset, .y = y - offset});
				new_points.push_back({.x = x + offset, .y = y - offset});
				new_points.push_back({.x = x + offset, .y = y + offset});
				new_points.push_back({.x = x - offset, .y = y + offset});
	
				x = points[i+2].x;
				y = points[i+2].y;
				new_points.push_back({.x = x - offset, .y = y - offset});
				new_points.push_back({.x = x + offset, .y = y - offset});
				new_points.push_back({.x = x + offset, .y = y + offset});
				new_points.push_back({.x = x - offset, .y = y + offset});

				x = points[i+3].x;
				y = points[i+3].y;
				new_points.push_back({.x = x + offset, .y = y + offset});
				new_points.push_back({.x = x + offset, .y = y - offset});
				new_points.push_back({.x = x - offset, .y = y - offset});
				new_points.push_back({.x = x - offset, .y = y + offset});
			}
		}

		points = new_points;
	}
	glVertex2i(points[0].x, points[0].y);

	for(int i = 1; i < points.size() - 1; i++){
		glVertex2i(points[i].x, points[i].y);
		glVertex2i(points[i].x, points[i].y);
	}

	glVertex2i(points[points.size()-1].x, points[points.size()-1].y);
	glEnd();
	glfwSwapBuffers(window);
}

void triangle( point2 a, point2 b, point2 c) {
	glBegin(GL_TRIANGLES);
	glVertex2fv(a);
	glVertex2fv(b);
	glVertex2fv(c);
	glEnd();
}

void divide_triangle(point2 a, point2 b, point2 c, int m) {
    point2 v0, v1, v2;
    int j;

    if(m>0) {
        for(j=0; j<2; j++){
            v0[j]=(a[j]+b[j])/2;
        } 
        for(j=0; j<2; j++){
             v1[j]=(a[j]+c[j])/2;
        }

        for(j=0; j<2; j++){ 
            v2[j]=(b[j]+c[j])/2; 
        }

        divide_triangle(a, v0, v1, m-1);
        divide_triangle(c, v1, v2, m-1);
        divide_triangle(b, v2, v0, m-1);
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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);

	glutMainLoop();
}

int main(int argc, char * argv[]) {
	int user_choice;
	bool is_running = true;
	  
	// Powitanie
	cout << "Witaj! Wybierz jedna z opcji!" << endl;

	// Proste menu wyboru
	while (is_running == true) {

		// Opcje wyboru
		cout << "\n1 - Krzywa Kocha (Koch snowflake)" << endl;
		cout << "2 - Smok Heighwaya (Dragon curve)" << endl;
		cout << "3 - Krzywa Hilberta (Hilbert curve)" << endl;
		cout << "4 - Trójkąt Sierpińskiego (Sierpinski gasket)" << endl;
		cout << "5 - null" << endl;
		cout << "6 - null" << endl;
		cout << "0 - Wyjdz z aplikacji\n" << endl;

		cin >> user_choice;
		cin.get();

		if (user_choice == 1) {
            koch_curve();
		}
		else if (user_choice == 2) {
			dragon_curve();
        }
		else if (user_choice == 3) {
			hilbert_curve();
		}
		else if (user_choice == 4) {
			sierpinski_gasket();
		}
		else if (user_choice == 5) {
		}
		else if (user_choice == 6) {
		}
		else if (user_choice == 0) {
			is_running = false;

			cout << "\nDo zobaczenia!" << endl;
			cout << "Nacisnij klawisz [Enter] aby zamknac okno...\n" << endl;
		}
	}

    cin.get();
    return 0;
}