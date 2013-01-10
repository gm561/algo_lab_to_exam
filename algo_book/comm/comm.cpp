#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Dwa z najczesciej uzywanych typow o dlugich nazwach - ich skrocenie jest bardzo istotne
typedef vector<int> VI;
typedef long long LL;

// W programach bardzo rzadko mozna znalezc w pelni zapisana instrukcje petli. Zamiast niej, wykorzystywane sa trzy nastepujace makra:
// FOR - petla zwiekszajaca zmienna x od b do e wlacznie
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
// FORD - petla zmniejszajaca zmienna x od b do e wlacznie
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
// REP - petla zwiekszajaca zmienna x od 0 do n. Jest ona bardzo czesto wykorzystywana do konstruowania i przegladania struktur danych
#define REP(x, n) for(int x = 0; x < (n); ++x)
// Makro VAR(v,n) deklaruje nowa zmienna o nazwie v oraz typie i wartosci zmiennej n. Jest ono czesto wykorzystywane podczas operowania na iteratorach struktur danych z biblioteki STL, ktorych nazwy typow sa bardzo dlugie
#define VAR(v, n) __typeof(n) v = (n)
// ALL(c) reprezentuje pare iteratorow wskazujacych odpowiednio na pierwszy i za ostatni element w strukturach danych STL. Makro to jest bardzo przydatne chociazby w przypadku korzystania z funkcji sort, ktora jako parametry przyjmuje pare iteratorow reprezentujacych przedzial elementow do posortowania.
#define ALL(c) (c).begin(), (c).end()
// Ponizsze makro sluzy do wyznaczania rozmiaru struktur danych STL. Uzywa sie go w programach, zamiast pisac po prostu x.size() z uwagi na fakt, iz wyrazenie x.size() jest typu unsigned int i w przypadku porownywania z typem int, w procesie kompilacji generowane jest ostrzezenie.
#define SIZE(x) ((int)(x).size())
// Bardzo pozyteczne makro, sluzace do iterowania po wszystkich elementach w strukturach danych STL.
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
// Skrot - zamiast pisac push_back podczas wstawiania elementow na koniec struktury danych, takiej jak vector, wystarczy napisac PB
#define PB push_back
// Podobnie - zamiast first bedziemy pisali po prostu ST
#define ST first
// a zamiast second - ND.
#define ND second
#include <list>
template<class V, class E> struct Graph {
// Typ krawedzi (Ed) dziedziczy po typie zawierajacym dodatkowe informacje zwiazane z krawedzia (E). Zawiera on rowniez pole v, okreslajace numer wierzcholka, do ktorego prowadzi krawedz. Zaimplementowany konstruktor pozwala na skrocenie zapisu wielu funkcji korzystajacych ze struktury grafu.
	struct Ed : E {
		int v; 
		Ed(E p, int w) : E(p), v(w) {}
	};
// Typ wierzcholka (Ve) dziedziczy po typie zawierajacym dodatkowe informacje z nim zwiazane (V) oraz po wektorze krawedzi. To drugie dziedziczenie moze wydawac sie na pierwszy rzut oka stosunkowo dziwne, lecz jest ono przydatne - umozliwia latwe iterowanie po wszystkich krawedziach wychodzacych z wierzcholka v: FOREACH(it, g[v])
	struct Ve : V,vector<Ed> {};
// Wektor wierzcholkow w grafie
	vector<Ve> g;
// Konstruktor grafu - przyjmuje jako parametr liczbe wierzcholkow
	Graph(int n=0) : g(n) {}
// Funkcja dodajaca do grafu nowa krawedz skierowana z wierzcholka b do e, zawierajaca dodatkowe informacje okreslone przez zmienna d.
	void EdgeD(int b, int e, E d = E()) {g[b].PB(Ed(d,e));}
// Wektor sluzacy do odznaczania odwiedzonych wierzcholkow
  VI vis;
// Wskaznik do konstruowanego grafu silnie spojnych skladowych
  Graph<V,E> *sccRes;
// Funkcja przechodzaca graf algorytmem DFS. Jest ona wykorzystywana dwukrotnie - w pierwszej fazie podczas wyznaczania kolejnosci wierzcholkow dla drugiej fazy, oraz podczas drugiej fazy - do wyznaczania silnie spojnych skladowych oraz konstrukcji grafu silnie spojnych skladowych
  void SccDfs(int v,int nr, bool phase){
// Zaznacz wierzcholek jako odwiedzony
    g[v].t = 1;
// Jesli wykonywana jest druga faza przeszukiwania, to ustaw dla wierzcholka numer silnie spojnej skladowej
	if(!phase) vis[v] = nr;
// Odwiedz kolejne wierzcholki oraz (jesli wykonywana jest druga faza) dodaj krawedz do konstruowanego grafu silnie spojnych skladowych
    FOREACH(it, g[v]) if (g[it->v].t == -1)
		SccDfs(it->v, nr, phase); else 
		if(!phase && nr > vis[it->v])
		sccRes->EdgeD(g[it->v].t, vis[it->v]=nr);
// Jesli wykonywana jest pierwsza faza, to wstaw wierzcholek do listy, jesli natomiast druga, to zaktualizuj jego czas
	if(phase) vis.PB(v); else g[v].t = nr;
  }
// Funkcja wyznaczajaca silnie spojne skladowe w grafie
  Graph<V,E> Scc() {
// Graf gt to graf transponowany, natomiast res to konstruowany graf silnie spojnych skladowych
    Graph<V,E> gt(SIZE(g)),res(SIZE(g)),*tab[]={this, & gt};
    gt.sccRes=&res; gt.vis.resize(SIZE(g), -1); vis.clear();
// Budowa grafu transponowanego
    REP(i,SIZE(g)) FOREACH(it,g[i]) gt.EdgeD(it->v,i);
// Przeprowadz dwie fazy algorytmu DFS...
    REP(i,2){
// Zaznacz wierzcholki jako nieodwiedzone
      FOREACH(it,tab[i]->g) it->t = -1;
      int comp=0,v;
// Dla kolejnych, nieodwiedzonych wierzcholkow, wykonaj przeszukiwanie
      FORD(j,SIZE(g)-1,0)
        if (tab[i]->g[v=(i?vis[j]:j)].t == -1) tab[i]->SccDfs(v,comp++,1-i);
      if (i) res.g.resize(comp);
    }
    REP(i,SIZE(g)) g[i].t=gt.g[i].t;
    return res;
  }
};
// Struktura wierzcholka zostala wzbogacona o pole t wymagane przez algorytm do wyznaczania silnie spojnych skladowych oraz pola c i n potrzebne do zaznaczania odpowiednio odwiedzonych i wybranych do komisji poslow
struct Vs {int t; bool c,n; Vs(){c=n=false;}};
struct Empty {};
// Graf zaleznosci
Graph<Vs, Empty> gr;
// Transponowany graf zaleznosci
Graph<Empty, Empty> grTr;

// Funkcja zaznacza jako przetworzonych wszystkich poslow, od ktorych v jest zalezny
void markUsed(int v) {
	if (!gr.g[v].n) {
		gr.g[v].n = true;
		FOREACH(it, grTr.g[v])
			markUsed(it->v);
	}
}

// Funkcja wybiera posla v oraz wszystkich poslow od niego zaleznych do komisji
void mark(int v) {
	if (!gr.g[v].n) {
		gr.g[v].n = gr.g[v].c = true;
// Jesli posel v nalezy do komisji, to posel bedacy w jego partii nie moze byc w komisji - zostaje on zaznaczony jako przetworzony
		markUsed(v^1);
		FOREACH(it, gr.g[v])
			mark(it->v);
	}
}

int main() {
	int n, m, b, e;
// Wczytaj liczbe partii oraz liczbe par nielubiacych sie poslow
	cin >> n >> m;
// Stworz grafy zaleznosci o odpowiedniej wielkosci
	gr.g.resize(2*n);
	grTr.g.resize(2*n);
// Wczytaj kolejne pary nielubiacych sie poslow i wstaw odpowiednie krawedzie do grafow zaleznosci. Krawedz (v,w) w takim grafie oznacza, ze jesli posel v trafi do Komisji, to posel w rowniez musi do niej trafic.
	REP(x, m) {
		cin >> b >> e;
		gr.EdgeD(--b, (--e)^1);
		gr.EdgeD(e, b^1);
		grTr.EdgeD(e^1, b);
		grTr.EdgeD(b^1, e);
	}
// Wyznacz silne spojne skladowe w grafie zaleznosci. Numeracja silnie spojnych skladowych jest zgodna z porzadkiem topologicznym, wiec nie trzeba wykonywac dodatkowego sortowania topologicznego
	gr.Scc();
	VI rep(SIZE(gr.g), -1);
	REP(x, 2*n) {
		rep[gr.g[x].t] = x;
	}
// Dla kazdej silnie spojnej skladowej (w kolejnosci odwroconego porzadku topologicznego), umiesc wszystkich poslow z tej skladowej (oraz poslow od nich zaleznych) w komisji
	FORD(x, SIZE(gr.g)-1, 0) if(rep[x] != -1) mark(rep[x]);
	int size = 0;
// Sprawdz, czy wyznaczona komisja spelnia podane w zadaniu wymagania
	REP(x, 2*n) {
		if (gr.g[x].c) {
			size++;
			FOREACH(it, gr.g[x]) 
				if (gr.g[it->v^1].c) size = n+1;
		}
		if (gr.g[x].c == gr.g[x^1].c) size = n+1;
	}
// Wypisz wynik
	if (size != n)
		cout << "NIE" << endl;
	else
		REP(x, 2*n) if (gr.g[x].c) cout << x+1 << endl;
	return 0;
}
