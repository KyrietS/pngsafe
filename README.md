# pngsafe

Konsolowa aplikacja, która ukrywa dowolny plik w pikselach obrazu PNG, a następnie jest w stanie z tego obrazu odzyskać cały plik. Do przechowania danych w obrazie używany jest ostatni bit każdego kanału, dlatego różnica w wyglądzie obrazu wynikowego jest niedostrzegalna ludzkim okiem.

## Instrukcja

### Dostępne polecenia

* `store` - zapisanie pliku do obrazu
* `load` - wczytanie pliku z obrazu
* `help` - wyświetlenie pomocy

### Opis poleceń

`pngsafe store <plik_wejściowy> <obraz_wejściowy> <obraz_wyjściowy>`

Zapisuje zawartość pliku wejściowego w pikselach obrazu wejściowego i produkuje nowy obraz wyjściowy. 

*Obraz wejściowy nie jest modyfikowany.*

* `<plik_wejściowy>` - ścieżka do pliku, który ma zostać ukryty w obrazie.
* `<obraz_wejściowy>` - ścieżka do obrazu w formacie PNG, w którym zostanie ukryty plik.
* `<obraz_wyjściowy>` - nazwa nowego obrazu w formacie PNG, z zakodowanym w środku plikiem, który zostanie utworzony.

---

`pngsafe load <obraz_wejściowy> <plik_wyjściowy>`

Wydobywa plik ukryty wcześniej w obrazie wejściowym i zapisuje go jako plik wyjściowy.

* `<obraz_wejściowy>` - obraz, w którym został ukryty plik.
* `<plik_wyjściowy` - nazwa pliku, który zostanie utworzony po wydobyciu go z obrazu.

---

`pngsafe help`

Wyświetla pomoc dotyczącą użycia programu.

## Przykłady

Mamy obrazek `obraz.png` oraz plik `tajne.pdf`.

**Ukrycie dokumentu w obrazie:**
`pngsafe store tajne.pdf obraz.png tajny-obraz.png`

Od dokument `tajny.pdf` jest zakodowany w pikselach obrazu `tajny-obraz.png`. Oczywiście obraz ten jest w pełni używalny i nierozróżnialny od oryginalnego `obraz.png` bez specjalistycznych narzędzi, programów etc..

**Odzyskanie dokumentu z obrazu**
`pngsafe load tajny-obraz.png odzyskany.pdf`

Odzyskaliśmy dokument. Pliki `tajny.pdf` oraz `odzyskany.pdf` są identyczne.

## Uwagi

* W jednym obrazie można zakodować maksymalnie jeden plik (ale może to być również ZIP).
* Plik może być zbyt duży, aby udało się go poprawnie zakodować w obrazie. W takiej sytuacji zostanie wypisany błąd i należy wtedy użyć większego obrazu (który ma więcej pikseli)
* Kompresja, zmiana rozmiaru czy jakakolwiek modyfikacja obrazu zniszczy zapisane na nim dane.

## Kompilacja

Należy użyć narzędzia **[premake](https://premake.github.io/)** do wygenerowania plików projektu dla wspieranego środowiska programistycznego, np.:

`premake5 vs2019` - tworzy rozwiąznie wraz z projektem dla Visual Studio 2019

lub pliku Makefile dla systemu Linux. Po więcej opcji wpisz `premake --help` lub zajrzyj na [oficjalną dokumentację](https://github.com/premake/premake-core/wiki/Using-Premake).

Projekt może zostać skompilowany w dwóch konfiguracjach: *Debug* i *Release*. Pliki wynikowe zostaną umieszczone w katalogu `bin/`, który zostanie utworzony w trakcie kompilacji.

## Zależności zewnętrzne

Projekt wykorzystuje kod do przetwarzania obrazów z biblioteki **[stb](https://github.com/nothings/stb)** (Public Domain).