// Projekt zaliczeniowy z przedmiotu Elementy animacji i grafiki 3D
// Kodowanie pliku - UTF-8, LF, C++, Linux
// Adrian Rupala 2019

// Biblioteki użyte w projekcie
#include <iostream>
#include <random>
#include <thread>
#include <fstream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

using namespace std;

// Wielkości okna, definiowanie wartości PI
#define WIDTH 1280
#define HEIGHT 720
#define PI 3.14159265358

// Struktura potrzebna do pracy na krzywych, punkty które później będą przekształcane
struct point{
		double x, y;
};

// Zdefiniowana maksymalna głębokość jaką fraktal ma przyjąć
int max_depth; 

// Funkcja rysująca Krzywą Kocha
void koch_curve(){       

	// Pobranie od użytkownika ilości iteracji (zagnieżdżenia fraktalu)
	cout << "Podaj maksymalne zagnieżdżenie " << endl;
	cin >> max_depth;

	// Inicjowanie biblioteki graficznej, tworzenie okna o określonej wielkości i nazwie, aktywowanie okna, ustawianie punktu rysowania.
	glfwInit();
	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Krzywa Kocha", NULL, NULL);
	glfwMakeContextCurrent(window);
	glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0);
	double side_length = (HEIGHT * 3.0/2.0) / sqrt(3.0);
	double width_offset = (WIDTH - side_length) / 2.0;
	
	// Ustawianie koloru tła okna, ustawianie koloru rysowania linii, inicjowanie rysowania linii, 
	// tworzenie vektora przyjmującego wcześniej zefiniowaną strukturę dotyczącego punktów jakie będziemy później zmieniać/modyfikować na potrzeby przekształceń
	// dodanie zmodyfikowanych położeń punktów do vektora
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	vector<point> points;
	points.push_back({.x = width_offset, .y = HEIGHT/4.0});
	points.push_back({.x = WIDTH - width_offset, .y = HEIGHT/4.0});
	points.push_back({.x = WIDTH/2, .y = HEIGHT});

	// Główna pętla odpowiedzialna za ilość wywołań obliczeń			
	for(int d = 0; d < max_depth; d++){
		vector<point> new_points;
		
		// Pętla która w iteruje się w zależności od rozmiaru vektora
		for(int i = 0; i < points.size(); i++){

			// Obliczenia związane z podziałem krzywej w związku ze wzorem 1/3 l opisanem w PDF, dodawanie punktów do vektora			
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

			// Jeśli wartość absolutna (abs) z różnicy punktów jest mniejsza od 0.01 (), 
			// do nowych punktów dodaj punkt x określony następująćym wzorem oraz punkt y określony następującym wzorem
			if(abs(ry1 - ry2) < 0.01){
				new_points.push_back({.x = (rx2 - rx1) / 2.0 + rx1, .y = ry1 + (rx1 - rx2) * sqrt(3.0) / 2.0});
			} // Jeśli wartość punktu x2 jest większa od punktu x1 || jest równe || wartości punktu y1 który jest większy od wartości punktu y2
			  // do nowych punktów dodaj wartość x oraz y określaną następującym wzorem 
			else if((x2 > x1) == (y1 > y2)){
				new_points.push_back({.x = rx1 + (rx1 - rx2), .y = ry2});
			} else { // w przeciwym wypadku do punktów dodaj wartość x oraz y określoną następującym wzorem
				new_points.push_back({.x = rx2 + (rx2 - rx1), .y = ry1});
			}
			// Niech nowe punkty x oraz y zostają przypisane jako wartości obliczone rx2 dla x oraz y
			new_points.push_back({.x = rx2, .y = ry2});
		}

		// Stare punkty są nowymi punktami, "przekopiowanie" wartości			
		points = new_points;
	}
	// stwórz wierzchołek z następujących punktów x oraz y
	glVertex2i(points[points.size()-1].x, points[points.size()-1].y);

	// Iterowanie po ilości vektoru points
	// Następnie rysowanie wierzchołków o określonych punktach
	for(int i = 0; i < points.size(); i++){
		glVertex2i(points[i].x, points[i].y);
		glVertex2i(points[i].x, points[i].y);
	}

	// Rysowanie wierzchołku 0, zakończenie obliczeń opengl, zostawienie okna
	glVertex2i(points[0].x, points[0].y);
	glEnd();
	glfwSwapBuffers(window);	
}

// Funkcja rysująca Smok Heighwaya
void dragon_curve(){

	// Pobranie od użytkownika ilości iteracji (zagnieżdżenia fraktalu)
	cout << "Podaj maksymalne zagnieżdżenie " << endl;
	cin >> max_depth;

	// Inicjowanie biblioteki graficznej, tworzenie okna o określonej wielkości i nazwie, aktywowanie okna, ustawianie punktu rysowania.
	glfwInit();
	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Smok Heighwaya", NULL, NULL);
	glfwMakeContextCurrent(window);
	glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0);

	// Ustawianie koloru tła okna, ustawianie koloru rysowania linii, inicjowanie rysowania linii, 
	// tworzenie vektora przyjmującego wcześniej zefiniowaną strukturę dotyczącego punktów jakie będziemy później zmieniać/modyfikować na potrzeby przekształceń
	// dodanie zmodyfikowanych położeń punktów do vektora, określenie długości linii rysowanej
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	vector<point> points;
	points.push_back({.x = WIDTH/4.0, .y = HEIGHT/2.0});
	points.push_back({.x = WIDTH/2.0, .y = HEIGHT/4.0});
	points.push_back({.x = WIDTH*3.0/4.0, .y = HEIGHT/2.0});
	double length = sqrt((WIDTH * WIDTH / 16.0) + (HEIGHT * HEIGHT / 16.0));
	
	// Główna pętla odpowiedzialna za ilość wywołań obliczeń			
	for(int d = 0; d < max_depth; d++){
		length = length / sqrt(2.0);
		vector<point> new_points;	

		// Pętla która w iteruje się w zależności od rozmiaru vektora
		// Definiowanie wartości oraz obliczenia związane ze wzorami opisanymi w PDF, 
		// określanie punktów przekształceń (dodawanie ich do nowego vektora)
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

		// Stare punkty są nowymi punktami, "przekopiowanie" wartości			
		points = new_points;
	}
		
	// Rysowanie zerowego wierzchołka
	glVertex2i(points[0].x, points[0].y);
	
	// Rysowanie pozostałych wierzchołków
	for(int i = 1; i < points.size() - 1; i++){
		glVertex2i(points[i].x, points[i].y);
		glVertex2i(points[i].x, points[i].y);
	}
	
	// Rysowanie ostatniego wierzchołka, zakończenie obliczeń opengl, zostawienie okna
	glVertex2i(points[points.size()-1].x, points[points.size()-1].y);
	glEnd();
	glfwSwapBuffers(window);
}

// Funkcja rysująca Krzywą Hilberta
void hilbert_curve(){
	
	// Pobranie od użytkownika ilości iteracji (zagnieżdżenia fraktalu)
	cout << "Podaj maksymalne zagnieżdżenie " << endl;
	cin >> max_depth;

	// Inicjowanie biblioteki graficznej, tworzenie okna o określonej wielkości i nazwie, aktywowanie okna, ustawianie punktu rysowania.
	glfwInit();
	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Krzywa Hilberta", NULL, NULL);
	glfwMakeContextCurrent(window);
	glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0);
	
	// Ustawianie koloru tła okna, ustawianie koloru rysowania linii, inicjowanie rysowania linii, 
	// tworzenie vektora przyjmującego wcześniej zefiniowaną strukturę dotyczącego punktów jakie będziemy później zmieniać/modyfikować na potrzeby przekształceń
	// dodanie zmodyfikowanych położeń punktów do vektora, określenie długości linii rysowanej
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	vector<point> points;
	points.push_back({.x = WIDTH/4.0, .y = HEIGHT/4.0});
	points.push_back({.x = WIDTH/4.0, .y = HEIGHT*3.0/4.0});
	points.push_back({.x = WIDTH*3.0/4.0, .y = HEIGHT*3.0/4.0});
	points.push_back({.x = WIDTH*3.0/4.0, .y = HEIGHT/4.0});

	// Główna pętla odpowiedzialna za ilość wywołań obliczeń			
	for(int d = 0; d < max_depth; d++){
		vector<point> new_points;

		// Pętla która w iteruje się w zależności od rozmiaru vektora
		// Obliczenia matematycznie związane z obrotem, przesunięciem nowych krzywych (wierzchołków krzywych)
		// Jeśli wartość absolutna różnicy punktów x jest mniejsza od różnicy punktów y
		// wykonaj następujące obliczenia a następnie dodaj do vektora nowe punkty
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
			} else { // w przeciwnym wypadku
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

		// Stare punkty są nowymi punktami, "przekopiowanie" wartości			
		points = new_points;
	}

	// Rysowanie wierzchołków zerowych
	glVertex2i(points[0].x, points[0].y);

	// Rysowanie wszystkich kolejnych wierzchołków
	for(int i = 1; i < points.size() - 1; i++){
		glVertex2i(points[i].x, points[i].y);
		glVertex2i(points[i].x, points[i].y);
	}

	// Rysowanie ostatniego wierzchołka, zakończenie obliczeń opengl, zostawienie okna
	glVertex2i(points[points.size()-1].x, points[points.size()-1].y);
	glEnd();
	glfwSwapBuffers(window);
}

// Funkcja rysująca Trójkąt Sierpińskiego
void sierpinski_gasket(){
	
	// Pobranie od użytkownika ilości iteracji (zagnieżdżenia fraktalu)
	cout << "Podaj maksymalne zagnieżdżenie " << endl;
	cin >> max_depth;
	
	// Inicjowanie biblioteki graficznej, tworzenie okna o określonej wielkości i nazwie, aktywowanie okna, ustawianie punktu rysowania.
	glfwInit();
	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Trojkat Sierpinskiego", NULL, NULL);
	glfwMakeContextCurrent(window);
	glOrtho(-WIDTH/2, WIDTH/2, 0, HEIGHT, -1.0, 1.0);

	// Definiowanie 3 początkowych (ilość) oraz ich przypisanie do wielkości okna
	int num_corners = 3;
	point corners[num_corners];
	corners[0].x = 0;
	corners[0].y = HEIGHT;
	corners[1].x = WIDTH/2;
	corners[1].y = 0;
	corners[2].x = -WIDTH/2;
	corners[2].y = 0;

	// Wykorzystanie pseudolosowego generatora liczb oraz stworzenie obiektów związanych z zależnością odległości między wierzchołkami a wysokością i szerokością
	default_random_engine rand;
	uniform_real_distribution<double> height_dist(0.0, (double) HEIGHT);
	uniform_real_distribution<double> width_dist((double) -WIDTH/2.0, (double) WIDTH/2.0);
	uniform_int_distribution<int> corner_dist(0, num_corners-1);

	// Generowanie koloru okna oraz inicjowanie rysowania punktów
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	// Generowanie losowych punktów
	point p;
	p.x = width_dist(rand);
	p.y = height_dist(rand);

	// Główna pętla odpowiedzialna za ilość wywołań obliczeń ( * 10000 ze względu na dużą ilość punktów konieczną przy wpisywaniu, użytkownik może podać mniejszą liczbę)	
	// Określanie kolejnych wierzchołków bazując na generatorze liczb losowych	
	for(int i = 0; i < max_depth * 10000; i++){
		int corner = corner_dist(rand);

		p.x = p.x - (p.x - corners[corner].x) / 2.0;
		p.y = p.y - (p.y - corners[corner].y) / 2.0;

		// Ustalenie koloru oraz rysowanie kolejnych punktów (wierzchołków)
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2i(p.x, p.y);
	}

	// Zakończenie obliczeń opengl, zostawienie okna
	glEnd();
	glfwSwapBuffers(window);
}

// Główna funkcja posiadające proste menu oparte o wybory użytkownika a następnie wywołanie wybranej wcześniej funkcji
int main() {
	int user_choice;
	bool is_running = true;
	  
	cout << "Witaj! Wybierz jedna z opcji!" << endl;

	while (is_running == true) {
		cout << "\n1 - Krzywa Kocha (Koch snowflake)" << endl;
		cout << "2 - Smok Heighwaya (Dragon curve)" << endl;
		cout << "3 - Krzywa Hilberta (Hilbert curve)" << endl;
		cout << "4 - Trójkąt Sierpińskiego (Sierpinski gasket)" << endl;
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
		else if (user_choice == 0) {
			is_running = false;

			cout << "\nDo zobaczenia!" << endl;
			cout << "Nacisnij klawisz [Enter] aby zamknac okno...\n" << endl;
		}
	}

    cin.get();
    return 0;
}