def menu():
    """ Proste menu, pozwala wybrać krzywą jaką użytkownik chce narysować """
    print("\nJaką krzywą chcesz narysować?")
    print("\n1 - Krzywa a \n"
          "2 - Krzywa b\n"
          "3 - Krzywa c\n")

    """ Zmienna globalna choice odpowiedzialne za wybór użytkownika """
    global choice
    choice = input("Twój wybór: ")



""" Wywołanie funkcji """
menu()