#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;

void menu_main(vector <vector<int> > graf, queue<int> bfs, bool stworzony, int najwiekszy);
void tworz(vector <vector<int> > &graf, bool &stworzony, int &najwiekszy);
void wyswietl(vector <vector<int> > graf, bool stworzony, int najwiekszy);
void przeszukiwanie(vector <vector<int> > graf, queue<int> kolejka, bool stworzony);
bool szukaj(vector <vector<int> > graf, int wierzcholek, int cel);


int main()
{
	vector < vector<int> > graf;//przedstawienie grafu
	queue <int> bfs;
	int najwiekszy = 11;
	bool stworzony = false; //zmienna stworzona po to aby niepotrzebnie nie przeszukiwac ani nie wyswietlac grafu skoro go nie ma

	menu_main(graf,bfs,stworzony, najwiekszy);

	system("pause");
	return 0;
}


void menu_main(vector <vector<int> > graf, queue<int> bfs, bool stworzony, int najwiekszy)
{
	int wybor;
	do {
		cout << "Przeszukiwanie grafu metoda BFS." << endl << endl;
		cout << "1. Tworzenie grafu." << endl;
		cout << "2. Wyswietlanie grafu." << endl;
		cout << "3. Przeszukiwanie grafu." << endl;
		cout << "4. Usuwanie grafu."<<endl;
		cout << "5. Wyjscie" << endl;
		cout << endl << "Wybierz opcje: ";

		cin >> wybor;
		cout << endl;
		system("cls");

		switch(wybor){
			case 1: tworz(graf,stworzony, najwiekszy);
					break;
			case 2: wyswietl(graf,stworzony, najwiekszy);
					break;
			case 3: przeszukiwanie(graf, bfs, stworzony);
					break;
			case 4: if(stworzony == true)
					{
					graf.clear();
					stworzony = false;
					}
					break;
			case 5: return;
		}

	} while (wybor);
}


void tworz(vector <vector<int> > &graf,bool &stworzony, int &najwiekszy)
{
	int wierzcholek = 0;
	int cel = 0;
	int wiekszy = 0; // obydwie zmienne sa do tego aby przechowywac w nich najwiekszy wierzcholek
	int nwiekszy = 0;
	string odpowiedz;


	for(int i = 0; i < najwiekszy+1; i++)
		graf.push_back(vector <int>() );//tworzymy wierzcholki od 0 do 10,poniewaz przewidujemy,¿e tyle starczy u¿ytkownikowi,
										//ale potem jesli uzytownik sobie zazyczy mozna to zwiekszyc

	while(odpowiedz != "n") {
		cout<<"Podaj wierzcholek z ktorego chcesz poprowadzic sciezke :";
		cin>>wierzcholek;
		cout<<endl<<"Podaj wierzcholek ktory ma byc celem :";
		cin >> cel;
		if(wierzcholek != -1)
		{
			if(wierzcholek > cel )
				{
					wiekszy = wierzcholek;
				}
				else if( wierzcholek < cel )
				{
					wiekszy = cel;
				}

			if(wiekszy > najwiekszy) //tutaj jesli ktorykolwiek wierzcholek jest wiekszy od zmiennej 'najwiekszy' to dobudowujemy kolejne wierzcholki az do tego ktorego potrzebujemy
				{
				for(int i = 0; i <= wiekszy; i++)
				graf.push_back(vector <int>() );
				}
			if(wierzcholek != cel and !szukaj(graf, wierzcholek, cel))
				{
				stworzony = true;//tutaj juz graf jakikolwiek by nie byl to istnieje
				graf[wierzcholek].push_back(cel);//w tym wypadku robimy graf nieskierowany ,wiec trzeba zrealizowac 2 polaczenia
				graf[cel].push_back(wierzcholek);


			    if(nwiekszy >= wiekszy)//nwiekszy zapamietuje nasz najwiekszy wierzcholek i jesli jest wiekszy od "wiekszy" to go podmienia aby potem moc wyswietlac polaczenia
			    	wiekszy = nwiekszy;

			    if(wiekszy > najwiekszy)
					najwiekszy = wiekszy;

				;
				}
			else 
				{
				cout << endl << "Taki sasiad juz istnieje." << endl;
				system("pause");
				system("cls");
				continue;
				}
		}
		else
			break;
		cout << endl << "Chcesz dodac nastepna droge? T/N: ";
	    cin >> odpowiedz;
		system("cls");
	} ;


}

void wyswietl(vector <vector<int> > graf, bool stworzony, int najwiekszy)
{
	if(stworzony == true)
	{ cout<<najwiekszy<<"to ten"<<endl;
		for(int i = 0; i <= najwiekszy; i++)
			if(i <= najwiekszy and !graf[i].empty())
				{
				cout << endl << "Wierzcholek " << i << " i jego sasiedzi: ";
				for(int j = 0; j < graf[i].size(); j++)
					cout << graf[i][j] << " ";
				}
		cout << endl << endl;
	}
	else cout << "Nie stworzyles jeszcze zadnego grafu." << endl << endl;

	system("pause");
	system("cls");
}

void przeszukiwanie(vector <vector<int> > graf, queue<int> bfs, bool stworzony)
{
	bool visited[graf.size()];//tworzymy vektor o dlugosci takiej samej jaka ma dlugosc vektor "graf" i wszedzie ustawiamy,'false' jako, ze nie sa odwiedzone
	int decyzja;
	if(stworzony == true)
	{
	for(int i = 0; i < graf.size(); i++)
		visited[i] = false;
	cout<<"Zdecyduj od jakiego wierzcholka chcesz rozpoczac przeszukiwanie :";
		do
	{
	cin >> decyzja;
	if(graf[decyzja].empty() == true)//aby przeszukiwanie mialo sens podany wierzcholek musi miec sasiadow
	cout << "Wybierz inny wierzcholek";
	}while(graf[decyzja].empty());

	system("cls");

	visited[decyzja] = true;
	for(int i = 0; i < graf[decyzja].size(); i++) //przeszukujemy vektor wewnatrz vektora "gra" aby odnalezc wszystkich sasiadow
	{
		bfs.push(graf[decyzja][i]);
		visited[graf[decyzja][i]] = true;	//ustawiamy,ze sa juz odwiedzone dlatego,ze jak sa w kolejce to predzj czy pozniej je odwiedzimy
	}
	cout << decyzja << " ";

	int wierzcholek;
	while(!bfs.empty())
		{
		wierzcholek = bfs.front();// wyciagamy z gory kolejki jakis wierzcholek
		bfs.pop(); //usuwamy go

			cout << wierzcholek << " ";

			for(int i = 0; i < graf[wierzcholek].size(); i++) // przeszukujemy czy ten wierzcholek ma sasiadow ktorych nie odwiedzilismy
				if(visited[graf[wierzcholek][i]] == false)		//jesli ma to wpisujemy ja do kolejki
				{
					bfs.push(graf[wierzcholek][i]);
					visited[graf[wierzcholek][i]] = true;
				}
		}
		cout << endl << endl;
	}
	else
		cout << "Nie stworzyles jeszcze grafu." << endl << endl;

	system("pause");
	system("cls");
}


bool szukaj(vector <vector<int> > graf, int wierzcholek, int cel)
{
	bool byl = false;

	for(int i = 0; i < graf[wierzcholek].size(); i++) //szukamy tutaj czy aby na pewno nie ma juz stworzonego takiego samego polaczenia
		if(graf[wierzcholek][i] == cel) byl = true;

	return byl;
}


