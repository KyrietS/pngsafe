#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>
#include "Image.h"

using namespace std;

void PrintError(string message)
{
	cout << "Blad: " << message << endl;
}

void WrongUsage()
{
	PrintError("Niepoprawne uzycie programu");
	cout << "Dostepne polecenia: pngsafe <opcja>" << endl;
	cout << "    store  -  zapisanie danych do obrazu" << endl;
	cout << "    load   -  odzyskanie danych z obrazu" << endl;
	cout << "    help   -  pomoc" << endl;
}

void PrintHelp()
{
	// Wypisz pomoc
	cout << "------ POMOC ------" << endl;
	cout << "pngsafe store <plik_wejsciowy> <obraz_wejsciowy> <obraz_wyjsciowy>" << endl;
	cout << "  zapisuje zawartosc pliku wejsciowego w pikselach" << endl;
	cout << "  obrazu wyjsciowego i produkuje nowy obraz wyjsciowy." << endl;
	cout << "    <plik_wejsciowy>  -  sciezka do pliku z danymi do ukrycia w obrazie" << endl;
	cout << "    <obraz_wejsciowy> -  obraz PNG, w ktorym zostanie ukryty plik wejsciowy" << endl;
	cout << "    <obraz_wyjsciowy> -  nazwa nowego obrazu PNG, z zapisanym w srodku plikiem wejsciowym" << endl;
	cout << endl;
	cout << "pngsafe load <obraz_wejsciowy> <plik_wyjsciowy>" << endl;
	cout << "  odczytuje dane ukryte wczesniej w obrazie i zapisuje" << endl;
	cout << "  rezultat do pliku wyjsciowego o podanej nazwie" << endl;
	cout << "    <obraz_wejsciowy> -  obraz, w ktorym sa ukryte dane" << endl;
	cout << "    <plik_wyjsciowy>  -  nazwa nowego pliku, w ktorym zostana zapisane odczytane dane z obrazu" << endl;
	cout << endl;
	cout << "pngsafe help" << endl;
	cout << "  wyswietla pomoc dotyczaca uzycia programu" << endl;
}

int main(int argc, char** argv) 
{
	if (argc == 1) {
		WrongUsage();
		return 1;
	}
	string command(argv[1]);

	try {
		if (command == "store" && argc == 5) {
			// Wczytaj dane z pliku
			ifstream f(argv[2], ios::binary);
			vector<unsigned char> inputData((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
			// Otwórz obraz Ÿród³owy i zapisz do niego dane.
			Image image(argv[3]);
			image.store(inputData);
			// Zapisz zmieniony obraz
			image.save(argv[4]);
		}
		else if (command == "load" && argc == 4) {
			// Wczytaj obraz
			Image image(argv[2]);
			vector<unsigned char> inputData = image.load();
			// Zapisz dane do pliku
			ofstream f(argv[3], ios::binary);
			f.write((const char*)&inputData[0], inputData.size());
		}
		else {
			PrintHelp();
		}
	} catch (runtime_error error)
	{
		PrintError(error.what());
	}
	return 0;
}