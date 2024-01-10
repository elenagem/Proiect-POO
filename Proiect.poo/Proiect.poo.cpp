#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <map>
#pragma warning(disable : 4996)
using namespace std;

class Produs {
protected:
	// Variabile
	string nume_produs;
	float pret;
	int cantitate;
public:
	// Getters
	string getNume_produs() {
		return nume_produs;
	}
	float getPret() {
		return pret;
	}
	int getCantitate() {
		return cantitate;
	}
	// Setters
	void setNume_produs(string nume_p) {
		nume_produs = nume_p;
	}
	void setPret(float pret_p) {
		pret = pret_p;
	}
	void setCantitate(int cant_p) {
		cantitate = cant_p;
	}
	// Constructorul fara parametrii
	Produs() {
		this->nume_produs = "Fara nume";
		this->pret = 0;
		this->cantitate = 0;
	}
	// Constructorul de copiere
	Produs(const Produs& p) {
		this->nume_produs = p.nume_produs;
		this->pret = p.pret;
		this->cantitate = p.cantitate;
	}
	// Constructorul cu toti parametrii
	Produs(string nume_produs, float pret, int cantitate) {
		this->nume_produs = nume_produs;
		this->pret = pret;
		this->cantitate = cantitate;
	}
	// Forma supraincarcata a operatorului =
	Produs& operator=(const Produs& p) {
		if (this != &p) {
			this->nume_produs = p.nume_produs;
			this->pret = p.pret;
			this->cantitate = p.cantitate;
		}
		return *this;
	}
	// Supraincarcarea operatorului >>
	friend istream& operator>>(istream& in, Produs& p) {
		cout << "\nNume produs: "; in >> p.nume_produs;
		cout<< "\nPret: "; in >> p.pret;
		cout << "\nCantitate Produs: "; in >> p.cantitate;
		return in;
	}
	// Supraincarcarea operatorului <<
	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << "\nNume produs: " << p.nume_produs;
		out << "\nPret produs: " << p.pret;
		out << "\nCantitate ramasa in stoc: " << p.cantitate;
		return out;
	}
	// Operatorul ==
	bool operator==(const Produs& p) {
		if (this->pret == p.pret) return true;
		return false;
	}
	// Operatorul +
	Produs operator+(float p) {
		Produs aux(*this);
		aux.pret = aux.pret + p;
		return aux;
	}
	// Operatorul -
	Produs operator-(float p) {
		Produs aux(*this);
		aux.pret = aux.pret - p;
		return aux;
	}
	// Destructorul
	~Produs() {}
	void afisareProdus() {
		cout << "\nNume produs: " << nume_produs;
		cout << "\nPret produs: " << pret;
		cout << "\nCantitate ramasa in stoc: " << cantitate;
	}
};

//Interfata
class Discount {
public:
	virtual void afisareInfoClient() {
		cout << "\nTip client: Tip nespecificat";
	}
	virtual float pretFinal() = 0;
};

class Client : public Discount {
protected:
	// Variabile
	char* nume_client;
	const int id_client;
	float* pretCumparaturi;
	int nr_produse;
	string* cumparaturi;
public:
	static int nr_client;
	// Getters
	char* getNume_client() {
		return this->nume_client;
	}
	float* getPretCumparaturi() {
		return this->pretCumparaturi;
	}
	string* getCumparaturi() {
		return this->cumparaturi;
	}
	int getNr_produse() {
		return nr_produse;
	}
	const int getIdClient() {
		return id_client;
	}
	// Setters
	void setNume_client(char* nume_client) {
		if (this->nume_client != NULL)
			delete[] this->nume_client;
		this->nume_client = new char[strlen(nume_client) + 1];
		strcpy(this->nume_client, nume_client);
	}
	void setPretCumparaturi(float* c, int n) {
		this->nr_produse = n;
		if (this->pretCumparaturi != NULL)
			delete[] this->pretCumparaturi;
		this->pretCumparaturi = new float[n];
		for (int i = 0; i < n; i++)
			this->pretCumparaturi[i] = c[i];
	}
	void setCumparaturi(string c, int n) {
		this->nr_produse = n;
		if (this->cumparaturi != NULL)
			delete[] this->cumparaturi;
		this->cumparaturi = new string[n];
		for (int i = 0; i < n; i++)
			this->cumparaturi[i] = c;
	}
	// Constructorul fara parametrii
	Client() :id_client(nr_client++) {
		this->nume_client = new char[strlen("Fara nume" + 1)];
		strcpy(this->nume_client, "Fara nume");
		this->pretCumparaturi = NULL;
		this->nr_produse = 0;
		this->cumparaturi = NULL;
	}
	// Constructorul de copiere
	Client(const Client& c) :id_client(c.id_client) {
		this->nr_produse = c.nr_produse;
		this->nume_client = new char[strlen(c.nume_client) + 1];
		strcpy(this->nume_client, c.nume_client);
		this->pretCumparaturi = new float[c.nr_produse];
		for (int i = 0; i < c.nr_produse; i++)
			this->pretCumparaturi[i] = c.pretCumparaturi[i];
		this->cumparaturi = new string[c.nr_produse];
		for (int i = 0; i < c.nr_produse; i++)
			this->cumparaturi[i] = c.cumparaturi[i];
	}
	// Constructorul cu toti parametrii
	Client(char* nume_client, int nr_produse, float* pretCumparaturi, string* cumparaturi) :id_client(nr_client++) {
		this->nr_produse = nr_produse;
		this->nume_client = new char[strlen(nume_client) + 1];
		strcpy(this->nume_client, nume_client);
		this->pretCumparaturi = new float[nr_produse];
		for (int i = 0; i < nr_produse; i++)
			this->pretCumparaturi[i] = pretCumparaturi[i];
		this->cumparaturi = new string[nr_produse];
		for (int i = 0; i < nr_produse; i++)
			this->cumparaturi[i] = cumparaturi[i];
	}
	// Forma supraincarcata a operatorului =
	Client& operator=(const Client& c) {
		if (this != &c) {
			if (this->nume_client != NULL)
				delete[] this->nume_client;
			if (this->pretCumparaturi != NULL)
				delete[] this->pretCumparaturi;
			if (this->cumparaturi != NULL)
				delete[] this->cumparaturi;
			this->nr_produse = c.nr_produse;
			this->nume_client = new char[strlen(c.nume_client) + 1];
			strcpy(this->nume_client, c.nume_client);
			this->pretCumparaturi = new float[c.nr_produse];
			for (int i = 0; i < c.nr_produse; i++)
				this->pretCumparaturi[i] = c.pretCumparaturi[i];
			this->cumparaturi = new string[c.nr_produse];
			for (int i = 0; i < c.nr_produse; i++)
				this->cumparaturi[i] = c.cumparaturi[i];
		}
		return *this;
	}
	// Supraincarcarea operatorului >>
	friend istream& operator>>(istream& in, Client& c) {
		cout << "\nNume: ";
		char n[100];
		in >> n;
		if (c.nume_client != NULL)
			delete[] c.nume_client;
		c.nume_client = new char[strlen(n) + 1];
		strcpy(c.nume_client, n);
		cout << "\nCate produse ati cumparat? "; in >> c.nr_produse;
		cout << "\nNume produse: ";
		if (c.cumparaturi != NULL)
			delete[] c.cumparaturi;
		c.cumparaturi = new string[c.nr_produse];
		for (int i = 0; i < c.nr_produse; i++)
			in >> c.cumparaturi[i];
		return in;
	}
	// Supraincarcarea operatorului <<
	friend ostream& operator<<(ostream& out, const Client& c) {
		out << "\nID client: " << c.id_client;
		out << "\nNume client: " << c.nume_client;
		out << "\nNumar de produse cumparate: " << c.nr_produse;
		out << "\nProduse: ";
		for (int i = 0; i < c.nr_produse; i++)
			out << c.cumparaturi[i] << " ";
		return out;
	}
	// Operatorul []
	string operator[](int i) {
		if (i >= 0 && i < this->nr_produse) return this->cumparaturi[i];
		else cout << "\nIndex gresit";
	}
	// Destructorul
	~Client() {
		if (this->nume_client != NULL)
			delete[] this->nume_client;
		if (this->pretCumparaturi != NULL)
			delete[] this->pretCumparaturi;
		if (this->cumparaturi != NULL)
			delete[] this->cumparaturi;
	}
	float pretInitial() {
		float t = 0;
		for (int i = 0; i < nr_produse; i++)
			t = t + pretCumparaturi[i];
		return t;
	}
	void afisareCumparaturi() {
		cout << "\nCumparaturi: ";
		for (int i = 0; i < nr_produse; i++)
			cout << cumparaturi[i] << " ";
	}
	void stergeProdus(string produs, Client& cl) {
		string* aux;
		int ok = 0, k = 0;
		aux = new string[nr_produse - 1];
		for (int i = 0; i < cl.nr_produse; i++) {
			if (cl.cumparaturi[i] == produs && ok == 0) ok = 1;
			else aux[k++] = cl.cumparaturi[i];
		}
		cl.nr_produse--;
		if (cl.cumparaturi != NULL)
			delete[] cl.cumparaturi;
		cl.cumparaturi = new string[cl.nr_produse];
		for (int i = 0; i < cl.nr_produse; i++) {
			cl.cumparaturi[i] = aux[i];
		}
	}

	void incarcarePreturi(vector <Produs*> listaProduse) {
		int n = listaProduse.size();
		if (this->pretCumparaturi != NULL)
			delete[] this->pretCumparaturi;
		this->pretCumparaturi = new float[nr_produse];
		
		for (int i = 0; i < nr_produse; i++) {
			for (int j = 0; j < n; j++)
				if (cumparaturi[i] == (*listaProduse[j]).getNume_produs()) pretCumparaturi[i] = (*listaProduse[j]).getPret();
		}
	}
};

class PersoanaFizica :public Client {
protected:
	bool card_fidelitate;
public:
	bool getCard_fidelitate() {
		return card_fidelitate;
	}
	void setCard_fidelitate(bool cardF) {
		card_fidelitate = cardF;
	}
	PersoanaFizica() :Client() {
		this->card_fidelitate = false;
	}
	PersoanaFizica(const PersoanaFizica& pf) :Client(pf) {
		this->card_fidelitate = pf.card_fidelitate;
	}
	PersoanaFizica(char* nume_client, int nr_produse, float* pretCumparaturi, string* cumparaturi, bool card_fidelitate) :Client(nume_client, nr_produse, pretCumparaturi, cumparaturi) {
		this->card_fidelitate = card_fidelitate;
	}
	PersoanaFizica& operator=(const PersoanaFizica& pf) {
		if (this != &pf) {
			Client::operator=(pf);
			this->card_fidelitate = pf.card_fidelitate;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const PersoanaFizica& pf) {
		out << (Client&)pf;
		out << "\nCard de fidelitate: ";
		if (pf.card_fidelitate) out << "da";
		else out << "nu";
	}
	friend istream& operator>>(istream& in, PersoanaFizica& pf) {
		in >> (Client&)pf;
		cout << "\nCarnet de fidelitate (0-nu/1-da): ";
		in >> pf.card_fidelitate;
		return in;
	}
	~PersoanaFizica() {

	}
	void afisareInfoClient() {
		cout << "\nTip client: Persoana fizica";
	}
	float pretFinal() {
		float t = 0;
		int n;
		float* pc;
		n = this->getNr_produse();
		pc = this->getPretCumparaturi();
		for (int i = 0; i < n; i++)
			t = t + pc[i];
		if (card_fidelitate == 1) t = t - t / 10;       //Reducere 10%;
		return t;
	}
};

class PersoanaJuridica :public Client {
protected:
	string nume_firma;
	string nr_telefon;
public:
	string getNume_firma() {
		return nume_firma;
	}
	string getNr_telefon() {
		return nr_telefon;
	}
	void setNume_firma(string nf) {
		nume_firma = nf;
	}
	void setNr_telefon(string nrtel) {
		nr_telefon = nrtel;
	}
	PersoanaJuridica() :Client() {
		this->nume_firma = "Fara nume";
		this->nr_telefon = "Fara numar de telefon";
	}
	PersoanaJuridica(const PersoanaJuridica& pj) :Client(pj) {
		this->nume_firma = pj.nume_firma;
		this->nr_telefon = pj.nr_telefon;
	}
	PersoanaJuridica(char* nume_client, int nr_produse, float* pretCumparaturi, string* cumparaturi, string nume_firma, string nr_telefon) :Client(nume_client, nr_produse, pretCumparaturi, cumparaturi) {
		this->nume_firma = nume_firma;
		this->nr_telefon = nr_telefon;
	}
	PersoanaJuridica& operator=(const PersoanaJuridica& pj) {
		if (this != &pj) {
			Client::operator=(pj);
			this->nume_firma = pj.nume_firma;
			this->nr_telefon = pj.nr_telefon;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const PersoanaJuridica& pj) {
		out << (Client&)pj;
		out << "\nNume firma: " << pj.nume_firma;
		out << "\nNumar de telefon: " << pj.nr_telefon;
		return out;
	}
	friend istream& operator>>(istream& in, PersoanaJuridica& pj) {
		in >> (Client&)pj;
		cout << "\nNume firma: ";
		in >> pj.nume_firma;
		cout << "\nNumar de telefon: ";
		in >> pj.nr_telefon;
		return in;
	}
	~PersoanaJuridica() {

	}
	void afisareInfoClient() {
		cout << "\nTip client: Persoana juridica";
	}
	float pretFinal() {
		float ti = 0, tf;
		int n;
		float* pc;
		n = this->getNr_produse();
		pc = this->getPretCumparaturi();
		for (int i = 0; i < n; i++)
			ti = ti + pc[i];
		if (nume_firma == "SweetEvy" || nume_firma == "Carina's Sweets") {
			tf = ti - ti * 2 / 10;     // Reducere 20%;
			return tf;
		}
		else return ti;
	}
};

int Client::nr_client = 0;

ifstream f("date.in");
ofstream g("date.out");

int main()
{
	vector <Produs*> listaProduse;
	map <string, int> comenzi;

	Produs p;

	int n;
	f >> n;

	for (int i = 0; i < n; i++) {
		f >> p;
		listaProduse.push_back(&p);
		comenzi.insert(pair<string, int>(p.getNume_produs(), 0));
	}

	int com;
	int ok = 1;

	while (ok == 1) {
		cout << "\nApasa 1 pentru MAGAZIN";
		cout << "\nApasa 2 pentru CLIENT";
		cout << "\nApasa 10 pentru EXIT";
		cin >> com;

		switch (com) {
		case 1: {
			system("CLS");
			int ok1 = 1;
			int com1;
			while (ok1 == 1) {
				cout << "\nApasa 1 pentru AFISARE PRODUSE RAMASE";
				cout << "\nApasa 2 pentru ADAUGARE PRODUSE";
				cout << "\nApasa 3 pentru EDITARE PRODUSE";
				cout << "\nApasa 4 pentru STERGERE PRODUSE";
				cout << "\nApasa 5 pentru PRELUCRARE COMENZI";
				cout << "\nApasa 6 pentru REALIZARE RAPORT";
				cout << "\nApasa 10 pentru LOG OUT MAGAZIN";
				cin >> com1;

				switch (com1) {
				case 1: {
					system("CLS");
					for (int i = 0; i < listaProduse.size(); i++)
						cout << (*listaProduse[i]) << " ";
					break;
				}
				case 2: {
					system("CLS");
					Produs pr;
					cin >> pr;
					listaProduse.push_back(&pr);
					break;
				}
				case 3: {
					system("CLS");
					string pr;
					int cant;
					float prt;
					cout << "\nCe produs doriti sa editati?";
					cin >> pr;
					for (int i = 0; i < listaProduse.size(); i++) {
						if (pr == (*listaProduse[i]).getNume_produs()) {
							cout << "\nPretul intial este " << (* listaProduse[i]).getPret();
							cout << "\nCantitatea intiala este " << (*listaProduse[i]).getCantitate();
							cout << "\nIntroduceti pret nou: "; cin >> prt;
							cout << "\nIntroduceti cantitate noua: "; cin >> cant;
							(*listaProduse[i]).setPret(prt);
							(*listaProduse[i]).setCantitate(cant);
							break;
						}
					
					}
								
					
					break;
				}
				case 4: {
					system("CLS");
					cout << "\nCe produs doriti sa stergeti: ";
					string produs;
					cin >> produs;
					for (int i = 0; i < listaProduse.size(); i++)
					{
						if (produs == (*listaProduse[i]).getNume_produs())
							listaProduse.erase(listaProduse.begin() + i);
					}
					break;
				}
				case 5: {
					system("CLS");
					for (int i = 0; i < listaProduse.size(); i++) {
						string np = (*listaProduse[i]).getNume_produs();
						auto itr = comenzi.find(np);
						int ct = itr->second;
						comenzi.erase(np);
						comenzi.insert(pair<string, int>(np, 0));
						int ct_init = (*listaProduse[i]).getCantitate();
						ct_init = ct_init - ct;
						(*listaProduse[i]).setCantitate(ct_init);
					}
					break;
				}
				case 6: {
					system("CLS");
					string raport;
					cin >> raport;
					g << "\nRaport magazin: ";
					g << raport;
					break;
				}
				case 10: {
					ok1 = 0;
					break;
				}
				default: {
					cout << "\nCOMANDA INCORECTA";
					break;
				}

				}
			}
			break;
		}
		case 2: {
			system("CLS");
			int ok2 = 1;
			int com2;

			cout << "\nApasa f pentru PERSOANA FIZICA/j pentru PERSOANA JURIDICA: ";
			char c;
			cin >> c;
			if (c == 'f') {
			PersoanaFizica pf;

				while (ok2 == 1) {
					cout << "\nApasa 1 pentru VIZUALIZARE PRODUSE";
					cout << "\nApasa 2 pentru COMPLETARE DATE PERSONALE + SELECTARE PRODUSE";
					cout << "\nApasa 3 pentru STERGERE PRODUSE";
					cout << "\nApasa 4 pentru AFISARE PRET INITIAL/PRET FINAL";
					cout << "\nApasa 5 pentru REALIZARE RAPORT";
					cout << "\nApasa 10 pentru FINALIZARE COMANDA";
					cin >> com2;
					switch (com2) {
					case 1: {
						system("CLS");
						for (int i = 0; i < listaProduse.size(); i++)
							cout << (*listaProduse[i]) << " ";
						break;
					}
					case 2: {
						system("CLS");
						cin >> pf;
						string* cump = pf.getCumparaturi();
						for (int i = 0; i < pf.getNr_produse(); i++) {
							auto itr = comenzi.find(cump[i]);
							int ct = itr->second;
							ct++;
							comenzi.erase(cump[i]);
							comenzi.insert(pair<string, int>(cump[i], ct));
						}
						break;
					}
					case 3: {
						system("CLS");
						cout << "\nCe produs doriti sa stergeti: ";
						string prd;
						cin >> prd;
						(pf).stergeProdus(prd, pf);
						auto itr = comenzi.find(prd);
						int ct = itr->second;
						ct--;
						comenzi.erase(prd);
						comenzi.insert(pair<string, int>(prd, ct));

						pf.afisareCumparaturi();

						break;
					}
					case 4: {
						system("CLS");
						pf.incarcarePreturi(listaProduse);
						cout << "\nPret initial: " << pf.pretInitial() << " RON";
						cout << "\nPret final: " << pf.pretFinal() << " RON";
						break;
					}
					case 5: {
						system("CLS");
						string raport;
						cin >> raport;
						g << "\nRaport client: ";
						g << raport;
						break;
					}
					case 10: {
						system("CLS");
						
						ok2 = 0;
						break;
					}
					default: {
						cout << "\nCOMANDA INCORECTA";
						break;
					}
					}
				}
			}
			if (c == 'j') {
				PersoanaJuridica pj;
				cin >> pj;

				while (ok2 == 1) {
					cout << "\nApasa 1 pentru VIZUALIZARE PRODUSE";
					cout << "\nApasa 2 pentru COMPLETARE DATE PERSONALE + SELECTARE PRODUSE";
					cout << "\nApasa 3 pentru STERGERE PRODUSE";
					cout << "\nApasa 4 pentru AFISARE PRET INITIAL/PRET FINAL";
					cout << "\nApasa 5 pentru REALIZARE RAPORT";
					cout << "\nApasa 10 pentru FINALIZARE COMANDA";
					cin >> com2;
					switch (com2) {
					case 1: {
						system("CLS");
						for (int i = 0; i < listaProduse.size(); i++)
							cout << (*listaProduse[i]) << " ";
						break;
					}
					case 2: {
						system("CLS");
						cin >> pj;
						string* cump = pj.getCumparaturi();
						for (int i = 0; i < pj.getNr_produse(); i++) {
							auto itr = comenzi.find(cump[i]);
							int ct = itr->second;
							ct++;
							comenzi.erase(cump[i]);
							comenzi.insert(pair<string, int>(cump[i], ct));
						}
						break;
					}
					case 3: {
						system("CLS");
						cout << "\nCe produs doriti sa stergeti: ";
						string prd;
						cin >> prd;
						(pj).stergeProdus(prd, pj);
						auto itr = comenzi.find(prd);
						int ct = itr->second;
						ct--;
						comenzi.erase(prd);
						comenzi.insert(pair<string, int>(prd, ct));

						pj.afisareCumparaturi();
						break;
					}
					case 4: {
						system("CLS");
						pj.incarcarePreturi(listaProduse);
						cout << "\nPret initial: " << pj.pretInitial() << " RON";
						cout << "\nPret final: " << pj.pretFinal() << " RON";
						break;
					}
					case 5: {
						system("CLS");
						string raport;
						cin >> raport;
						g << "\nRaport client: ";
						g << raport;
						break;
					}
					case 10: {
						system("CLS");

						ok2 = 0;
						break;
					}
					default: {
						cout << "\nCOMANDA INCORECTA";
						break;
					}
					}
				}
			}
			break;
		}
        case 10: {
			ok = 0;
			break;
		}
		default: {
			cout << "\nCOMANDA INCORECTA";
			break;
		}


		}
	}
	return 0;
}

/*

Datele puse in fisierul de citire date.in:
5
Tort
54
1
Prajitura Oreo
28
5
Toffee Profiterol
22
3
Tiramisu
16
7
Chec cu ciocolata
40
2

*/
		