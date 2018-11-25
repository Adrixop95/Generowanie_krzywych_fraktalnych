#include <iostream>
#include <fstream>

// libglfw3-dev libglfw3 debian apt pkgs
#include <GLFW/glfw3.h>
#include <GL/gl.h>

using namespace std;

int main() {
	int user_choice;
	bool is_running = true;
	  
	// Powitanie
	cout << "Witaj! Wybierz jedna z opcji!" << endl;

	// Proste menu wyboru
	while (is_running == true) {

		// Opcje wyboru
		cout << "\n1 - Krzywa a" << endl;
		cout << "2 - Krzywa a" << endl;
		cout << "3 - Krzywa a" << endl;
		cout << "4 - Krzywa a" << endl;
		cout << "5 - Krzywa a" << endl;
		cout << "6 - Krzywa a " << endl;
		cout << "0 - Wyjdz z aplikacji\n" << endl;

		cin >> user_choice;
		cin.get();

		if (user_choice == 1) {
		}
		else if (user_choice == 2) {
        }
		else if (user_choice == 3) {
		}
		else if (user_choice == 4) {
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