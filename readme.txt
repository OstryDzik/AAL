##README##
Autor: 
	Filip Łęczycki, nr indeksu 253114
Treść projektu:
	Dany jest zbiór prostopadłościanów {a1, … , an} oraz obszar
	prostopadłościenny o zadanych dwóch bokach nie mniejszych od
	największego z boków prostopadłościanów w zbiorze. Należy wyznaczyć,
	stosując różne metody heurystyczne, a także przeszukiwanie
	systematyczne, najmniejszą dlugość trzeciego boku obszaru pozwalającą na
	rozmieszczenie ortogonalne bez kolizji zbioru w obszarze. Porównać czas
	obliczeń i wyniki różnych metod.
Sposoby akywacji programu:
	Program uruchamiany jest poprzez odpalenie pliku exe. Następnie użytkownikowi prezentowane jest menu i jasnym opisem dostępnych opcji:
	-h - wyświetlenie listy poleceń
	-r - wygenerowanie jednego zestawu danych testowych i zapisanie do pamięci
	-l - wczytanie jednego zestawu danych testowych z pliku i zapisanie do pamięci
	-em - przeprowadzenie eksperymentu - program zapyta użytkownika o liczbę oraz rozmiar prób do przeprowadzenia. Następnie wynik zostanie zapisany do pliku .csv
	-ef - j.w. tylko dane z pliku
	-p - program wypisze zestaw danych testowych aktualnie przechowywany w pamięci
	-s - program przejdzie do rozwiązania problemu załądowanego do pamięci z graficzną prezentacją rezultatu
	-q - zakończenie działania programu
Dane wejściowe:
	- program akceptuje pliki z danymi testowymi w następującym formacie:
		bin:rozmiarX,rozmiarZ
		box:rozmiarX,rozmiarY,rozmiarZ
		box:...
	- program akceptuje pliki z konfiguracją ekperymentu w następującym formacie:
		Experiment //naglowek kontrolny
		bin:rozmiarX,rozmiarZ
		box:max,min //maksymalny i minimalny bok paczki
		size1 //rozmiary probki
		size2
	- program generuje pliki z wynikiem eksperymentu w następującym formacie:
		Bin foot size: 50,100
		Samples count: 2
		ID|Size|ShelfAlg time|ShelfAlg H|LayerAlg time|LayerAlg H|NaiveAlg time|NaiveAlg H
		1|50|0.015600|246|0.015600|229|0.000000|872|
		2|100|0.031200|483|0.000000|444|0.000000|1683|
Metoda rozwiązania:
	Zaimplementowane zostały 3 algorytmy: naiwny, warstwowy półkowy, warstwowy drzewiasty. Dokładny opis algorytmów wraz z pseudokodem znajduje się w dokumentacji. 
	Ze struktur danych warto zwrócić uwagę na stukturę drzewa binarnego, która została wykorzystana do przechowywania infowrmacji o wolnej przestrzeni na warstwie w algorytmie drzewiastym. W pozostałych przypadkach wykorzystywane są struktury z biblioteki standardowej.
Przewodnik po źródłach:
	Jeden plik nagłówkowy zawiera w sobie definicję jednej klasy o nazwie zgodnej z nazwą pliku.
	Opis klas:
		Bin,Box,Space - klasy użytkowe definiujące typy którymi operuje się w programie.
			Bin reprezentuje niezapakowany kosz wraz ze zbiorem pudełek
			Box reprezentuje pudełko
			Space reprezentuje dwuwymiarowy obszar
		Solver,LayerSolver,TrivialSolver,ThirdSolver: klasy rozwiązujące zadany problem z wykorzystaniem jednego z strzech algortmów
			Solver jest klasą abstrakcyjną narzucającą interfejs pozostałym "solverom"
		Scena - widok projektu, klasa realizująca wyświetlanie wyników obliczeń w formie graficznej
		FileManager - klasa typu singleton, odpowiada za zapis i odczyt informacji z plików
		Experiment - klasa sterująca umożliwiająca przeprowadzenie eksperymentu z określoną liczbą próbek, i zapisanie wyników, pomiaru czasu itp
	Plik main.cpp realizuje tekstowy interfejs użytkownika
