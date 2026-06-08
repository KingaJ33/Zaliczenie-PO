// Zaliczenie PO.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

class Kosmetyk {
private:
    int id;

protected:
    string nazwaObiektu;
    string marka;
    float cena;

public:
    Kosmetyk(string nadajNazweObiektu, int nadajId, string nadajMarke, float nadajCene)
        : id(nadajId), nazwaObiektu(nadajNazweObiektu), marka(nadajMarke), cena(nadajCene) {
    }

    virtual ~Kosmetyk() {}

    string getNazwaObiektu() { return nazwaObiektu; }
    int getId() { return id; }
    void setId(int noweId) { id = noweId; }

    virtual bool czyNalezyDo(string wezel) {
        return wezel == "Kosmetyk" || wezel == "A";
    }

    virtual bool czyLisc() { return false; }

    virtual void show() {
        cout << "Nazwa w systemie: " << nazwaObiektu << " | ID: " << id << " | Marka: " << marka << " | Cena: " << cena << " PLN\n";
    }

    virtual void modyfikuj() {
        cout << "Podaj nowa marke: "; cin >> marka;
        cout << "Podaj nowa cene: "; cin >> cena;
    }

    virtual void wczytajZKonsoli() = 0;
    virtual void wczytajZPliku(ifstream& plik) = 0;
    virtual void zapisz(ofstream& plik) = 0;
};

class Perfumy : public Kosmetyk {
private:
    string nutaZapachowa;
protected:
    int pojemnoscMl;

public:
    Perfumy(string nadajNazwe, int nadajId, string nadajMarke, float nadajCene, string nadajNute, int nadajPojemnosc)
        : Kosmetyk(nadajNazwe, nadajId, nadajMarke, nadajCene)
    {
        nutaZapachowa = nadajNute;
        pojemnoscMl = nadajPojemnosc;
    }

    bool czyNalezyDo(string wezel) override {
        return wezel == "Perfumy" || wezel == "B" || Kosmetyk::czyNalezyDo(wezel);
    }

    bool czyLisc() override { return true; }

    void show() override {
        cout << "--- PERFUMY ---\n";
        Kosmetyk::show();
        cout << "Nuta zapachowa: " << nutaZapachowa << " | Pojemnosc: " << pojemnoscMl << " ml\n";
    }

    void modyfikuj() override {
        Kosmetyk::modyfikuj();
        cout << "Podaj nowa nute zapachowa: "; cin >> nutaZapachowa;
        cout << "Podaj nowa pojemnosc (ml): "; cin >> pojemnoscMl;
    }

    void wczytajZKonsoli() override {
        cout << "Podaj nute zapachowa: "; cin >> nutaZapachowa;
        cout << "Podaj pojemnosc (ml): "; cin >> pojemnoscMl;
    }

    void wczytajZPliku(ifstream& plik) override {
        plik >> nutaZapachowa >> pojemnoscMl;
    }

    void zapisz(ofstream& plik) override {
        plik << "Perfumy " << nazwaObiektu << " " << getId() << " " << marka << " " << cena << " " << nutaZapachowa << " " << pojemnoscMl << "\n";
    }
};

class DoTwarzy : public Kosmetyk {
private:
    string typCery;
protected:
    int waznoscProduktu;

public:
    DoTwarzy(string nadajNazwe, int nadajId, string nadajMarke, float nadajCene, string nadajTypCery, int nadajWaznosc)
        : Kosmetyk(nadajNazwe, nadajId, nadajMarke, nadajCene)
    {
        typCery = nadajTypCery;
        waznoscProduktu = nadajWaznosc;
    }

    string getTypCery() { return typCery; }

    bool czyNalezyDo(string wezel) override {
        return wezel == "DoTwarzy" || wezel == "C" || Kosmetyk::czyNalezyDo(wezel);
    }

    virtual void show() override {
        Kosmetyk::show();
        cout << "Typ cery: " << typCery << " | Waznosc: " << waznoscProduktu << " miesiecy\n";
    }

    void modyfikuj() override {
        Kosmetyk::modyfikuj();
        cout << "Podaj nowy typ cery: "; cin >> typCery;
        cout << "Podaj nowa waznosc: "; cin >> waznoscProduktu;
    }

    void wczytajZKonsoli() override {
        cout << "Podaj typ cery: "; cin >> typCery;
        cout << "Podaj waznosc (msc): "; cin >> waznoscProduktu;
    }

    void wczytajZPliku(ifstream& plik) override {
        plik >> typCery >> waznoscProduktu;
    }

    void zapisz(ofstream& plik) override {}
};

class Podklad : public DoTwarzy {
private:
    string odcien;
protected:
    string podton;

public:
    Podklad(string nNazwa, int nId, string nMarka, float nCena, string nTypCery, int nWaznosc, string nOdcien, string nPodton)
        : DoTwarzy(nNazwa, nId, nMarka, nCena, nTypCery, nWaznosc)
    {
        odcien = nOdcien;
        podton = nPodton;
    }

    bool czyNalezyDo(string wezel) override {
        return wezel == "Podklad" || wezel == "F" || DoTwarzy::czyNalezyDo(wezel);
    }

    bool czyLisc() override { return true; }

    void show() override {
        cout << "--- PODKLAD ---\n";
        DoTwarzy::show();
        cout << "Odcien: " << odcien << " | Podton: " << podton << "\n";
    }

    void modyfikuj() override {
        DoTwarzy::modyfikuj();
        cout << "Podaj nowy odcien: "; cin >> odcien;
        cout << "Podaj nowy podton: "; cin >> podton;
    }

    void wczytajZKonsoli() override {
        DoTwarzy::wczytajZKonsoli();
        cout << "Podaj odcien: "; cin >> odcien;
        cout << "Podaj podton: "; cin >> podton;
    }

    void wczytajZPliku(ifstream& plik) override {
        DoTwarzy::wczytajZPliku(plik);
        plik >> odcien >> podton;
    }

    void zapisz(ofstream& plik) override {
        plik << "Podklad " << nazwaObiektu << " " << getId() << " " << marka << " " << cena << " " << getTypCery() << " " << waznoscProduktu << " " << odcien << " " << podton << "\n";
    }
};

class Korektor : public DoTwarzy {
private:
    string krycie;
protected:
    string efekt;

public:
    Korektor(string nNazwa, int nId, string nMarka, float nCena, string nTypCery, int nWaznosc, string nKrycie, string nEfekt)
        : DoTwarzy(nNazwa, nId, nMarka, nCena, nTypCery, nWaznosc)
    {
        krycie = nKrycie;
        efekt = nEfekt;
    }

    bool czyNalezyDo(string wezel) override { return wezel == "Korektor" || wezel == "G" || DoTwarzy::czyNalezyDo(wezel); }
    bool czyLisc() override { return true; }

    void show() override {
        cout << "--- KOREKTOR ---\n";
        DoTwarzy::show();
        cout << "Krycie: " << krycie << " | Efekt: " << efekt << "\n";
    }

    void modyfikuj() override {
        DoTwarzy::modyfikuj();
        cout << "Podaj nowe krycie: "; cin >> krycie;
        cout << "Podaj nowy efekt: "; cin >> efekt;
    }

    void wczytajZKonsoli() override {
        DoTwarzy::wczytajZKonsoli();
        cout << "Podaj krycie: "; cin >> krycie;
        cout << "Podaj efekt: "; cin >> efekt;
    }

    void wczytajZPliku(ifstream& plik) override {
        DoTwarzy::wczytajZPliku(plik);
        plik >> krycie >> efekt;
    }

    void zapisz(ofstream& plik) override {
        plik << "Korektor " << nazwaObiektu << " " << getId() << " " << marka << " " << cena << " " << getTypCery() << " " << waznoscProduktu << " " << krycie << " " << efekt << "\n";
    }
};

class DoOczu : public Kosmetyk {
private:
    int trwaloscWgodzinach;
protected:
    int wagaWgramach;

public:
    DoOczu(string nNazwa, int nId, string nMarka, float nCena, int nTrwalosc, int nWage)
        : Kosmetyk(nNazwa, nId, nMarka, nCena)
    {
        trwaloscWgodzinach = nTrwalosc;
        wagaWgramach = nWage;
    }

    int getTrwalosc() { return trwaloscWgodzinach; }

    bool czyNalezyDo(string wezel) override { return wezel == "DoOczu" || wezel == "D" || Kosmetyk::czyNalezyDo(wezel); }

    virtual void show() override {
        Kosmetyk::show();
        cout << "Trwalosc: " << trwaloscWgodzinach << " h | Waga: " << wagaWgramach << " g\n";
    }

    void modyfikuj() override {
        Kosmetyk::modyfikuj();
        cout << "Podaj nowa trwalosc (h): "; cin >> trwaloscWgodzinach;
        cout << "Podaj nowa wage (g): "; cin >> wagaWgramach;
    }

    void wczytajZKonsoli() override {
        cout << "Podaj trwalosc (h): "; cin >> trwaloscWgodzinach;
        cout << "Podaj wage (g): "; cin >> wagaWgramach;
    }

    void wczytajZPliku(ifstream& plik) override {
        plik >> trwaloscWgodzinach >> wagaWgramach;
    }

    void zapisz(ofstream& plik) override {}
};

class Tusz : public DoOczu {
private:
    string wodoodporny;
protected:
    string kolor;

public:
    Tusz(string nNazwa, int nId, string nMarka, float nCena, int nTrwalosc, int nWage, string nWodoodp, string nKolor)
        : DoOczu(nNazwa, nId, nMarka, nCena, nTrwalosc, nWage)
    {
        wodoodporny = nWodoodp;
        kolor = nKolor;
    }

    bool czyNalezyDo(string wezel) override { return wezel == "Tusz" || wezel == "H" || DoOczu::czyNalezyDo(wezel); }
    bool czyLisc() override { return true; }

    void show() override {
        cout << "--- TUSZ DO RZES ---\n";
        DoOczu::show();
        cout << "Wodoodporny: " << wodoodporny << " | Kolor: " << kolor << "\n";
    }

    void modyfikuj() override {
        DoOczu::modyfikuj();
        cout << "Wodoodporny (wpisz np. tak/nie): "; cin >> wodoodporny;
        cout << "Podaj nowy kolor: "; cin >> kolor;
    }

    void wczytajZKonsoli() override {
        DoOczu::wczytajZKonsoli();
        cout << "Wodoodporny?: "; cin >> wodoodporny;
        cout << "Podaj kolor: "; cin >> kolor;
    }

    void wczytajZPliku(ifstream& plik) override {
        DoOczu::wczytajZPliku(plik);
        plik >> wodoodporny >> kolor;
    }

    void zapisz(ofstream& plik) override {
        plik << "Tusz " << nazwaObiektu << " " << getId() << " " << marka << " " << cena << " " << getTrwalosc() << " " << wagaWgramach << " " << wodoodporny << " " << kolor << "\n";
    }
};

class Cienie : public DoOczu {
private:
    string barwy;
protected:
    int iloscKolorow;

public:
    Cienie(string nNazwa, int nId, string nMarka, float nCena, int nTrwalosc, int nWage, string nBarwe, int nIloscKolorow)
        : DoOczu(nNazwa, nId, nMarka, nCena, nTrwalosc, nWage)
    {
        barwy = nBarwe;
        iloscKolorow = nIloscKolorow;
    }

    bool czyNalezyDo(string wezel) override { return wezel == "Cienie" || wezel == "I" || DoOczu::czyNalezyDo(wezel); }
    bool czyLisc() override { return true; }

    void show() override {
        cout << "--- PALETA CIENI ---\n";
        DoOczu::show();
        cout << "Barwy: " << barwy << " | Ilosc kolorow: " << iloscKolorow << "\n";
    }

    void modyfikuj() override {
        DoOczu::modyfikuj();
        cout << "Podaj nowe barwy: "; cin >> barwy;
        cout << "Podaj nowa ilosc kolorow: "; cin >> iloscKolorow;
    }

    void wczytajZKonsoli() override {
        DoOczu::wczytajZKonsoli();
        cout << "Podaj barwy: "; cin >> barwy;
        cout << "Ile kolorow: "; cin >> iloscKolorow;
    }

    void wczytajZPliku(ifstream& plik) override {
        DoOczu::wczytajZPliku(plik);
        plik >> barwy >> iloscKolorow;
    }

    void zapisz(ofstream& plik) override {
        plik << "Cienie " << nazwaObiektu << " " << getId() << " " << marka << " " << cena << " " << getTrwalosc() << " " << wagaWgramach << " " << barwy << " " << iloscKolorow << "\n";
    }
};

class DoUst : public Kosmetyk {
private:
    string typ;
protected:
    string wlasciwosci;

public:
    DoUst(string nNazwa, int nId, string nMarka, float nCena, string nTyp, string nWlasciwosci)
        : Kosmetyk(nNazwa, nId, nMarka, nCena)
    {
        typ = nTyp;
        wlasciwosci = nWlasciwosci;
    }

    string getTyp() { return typ; }

    bool czyNalezyDo(string wezel) override { return wezel == "DoUst" || wezel == "E" || Kosmetyk::czyNalezyDo(wezel); }

    virtual void show() override {
        Kosmetyk::show();
        cout << "Typ: " << typ << " | Wlasciwosci: " << wlasciwosci << "\n";
    }

    void modyfikuj() override {
        Kosmetyk::modyfikuj();
        cout << "Podaj nowy typ: "; cin >> typ;
        cout << "Podaj nowe wlasciwosci: "; cin >> wlasciwosci;
    }

    void wczytajZKonsoli() override {
        cout << "Podaj typ: "; cin >> typ;
        cout << "Podaj wlasciwosci: "; cin >> wlasciwosci;
    }

    void wczytajZPliku(ifstream& plik) override {
        plik >> typ >> wlasciwosci;
    }

    void zapisz(ofstream& plik) override {}
};

class Szminka : public DoUst {
private:
    string drobinki;
protected:
    int numerOdcienia;

public:
    Szminka(string nNazwa, int nId, string nMarka, float nCena, string nTyp, string nWlasciwosci, string nDrobinki, int nNumer)
        : DoUst(nNazwa, nId, nMarka, nCena, nTyp, nWlasciwosci)
    {
        drobinki = nDrobinki;
        numerOdcienia = nNumer;
    }

    bool czyNalezyDo(string wezel) override { return wezel == "Szminka" || wezel == "J" || DoUst::czyNalezyDo(wezel); }
    bool czyLisc() override { return true; }

    void show() override {
        cout << "--- SZMINKA ---\n";
        DoUst::show();
        cout << "Drobinki: " << drobinki << " | Odcien nr: " << numerOdcienia << "\n";
    }

    void modyfikuj() override {
        DoUst::modyfikuj();
        cout << "Czy ma drobinki (wpisz np. tak/nie): "; cin >> drobinki;
        cout << "Podaj nowy numer odcienia: "; cin >> numerOdcienia;
    }

    void wczytajZKonsoli() override {
        DoUst::wczytajZKonsoli();
        cout << "Drobinki?: "; cin >> drobinki;
        cout << "Numer odcienia: "; cin >> numerOdcienia;
    }

    void wczytajZPliku(ifstream& plik) override {
        DoUst::wczytajZPliku(plik);
        plik >> drobinki >> numerOdcienia;
    }

    void zapisz(ofstream& plik) override {
        plik << "Szminka " << nazwaObiektu << " " << getId() << " " << marka << " " << cena << " " << getTyp() << " " << wlasciwosci << " " << drobinki << " " << numerOdcienia << "\n";
    }
};

void wyswietlMenu() {
    cout << "                      MENU GLOWNE\n";
    cout << endl;
    cout << " TREE         - Pokaz strukture drzewa dziedziczenia\n";
    cout << " CD [wezel]   - Zmien biezacy wezel (np. CD Podklad)\n";
    cout << " DIR          - Wyswietl obiekty w biezacym wezle\n";
    cout << " MO [nazwa]   - Dodaj obiekt (tylko w wezle liscia)\n";
    cout << " DO [nazwa]   - Usun obiekt (tylko w wezle liscia)\n";
    cout << " MDO [nazwa]  - Modyfikuj obiekt (tylko w wezle liscia)\n";
    cout << " SHOW [nazwa] - Pokaz wszystkie szczegoly obiektu\n";
    cout << " SAVE         - Zapisz stan bazy do pliku (baza.txt)\n";
    cout << " READ         - Wczytaj stan bazy z pliku (baza.txt)\n";
    cout << " MENU         - Wyswietl to menu ponownie\n";
    cout << " EXIT         - Zakoncz dzialanie programu\n";
    cout << endl;

}

int main() {
    vector<Kosmetyk*> baza;
    string current_node = "Kosmetyk";
    string komenda;
    int next_id = 1;

    wyswietlMenu();

    while (true) {
        cout << "[" << current_node << "]> ";
        cin >> komenda;

        if (komenda == "EXIT") {
            break;
        }
        else if (komenda == "MENU") {
            wyswietlMenu();
        }
        else if (komenda == "TREE") {
            cout << "Kosmetyk (A)\n"
                << "  |- Perfumy (B)\n"
                << "  |- DoTwarzy (C)\n"
                << "  |    |- Podklad (F)\n"
                << "  |    |- Korektor (G)\n"
                << "  |- DoOczu (D)\n"
                << "  |    |- Tusz (H)\n"
                << "  |    |- Cienie (I)\n"
                << "  |- DoUst (E)\n"
                << "       |- Szminka (J)\n";
        }
        else if (komenda == "CD") {
            string wezel;
            cin >> wezel;
            if (wezel == "Kosmetyk" || wezel == "A" || wezel == "Perfumy" || wezel == "B" || wezel == "DoTwarzy" || wezel == "C" || wezel == "Podklad" || wezel == "F" || wezel == "Korektor" || wezel == "G" || wezel == "DoOczu" || wezel == "D" || wezel == "Tusz" || wezel == "H" || wezel == "Cienie" || wezel == "I" || wezel == "DoUst" || wezel == "E" || wezel == "Szminka" || wezel == "J") {
                current_node = wezel;
            }
            else {
                cout << "Blad! Nie ma takiego wezla w strukturze.\n";
            }
        }
        else if (komenda == "DIR") {
            bool found = false;
            for (int i = 0; i < baza.size(); i++) {
                if (baza[i]->czyNalezyDo(current_node)) {
                    cout << "- " << baza[i]->getNazwaObiektu() << "\n";
                    found = true;
                }
            }
            if (!found) cout << "Brak obiektow w tym wezle.\n";
        }
        else if (komenda == "MO") {
            string nazwa;
            cin >> nazwa;

            string marka; float cena;
            cout << "Podaj marke: "; cin >> marka;
            cout << "Podaj cene: "; cin >> cena;

            Kosmetyk* nowy = nullptr;

            if (current_node == "Perfumy" || current_node == "B")       nowy = new Perfumy(nazwa, next_id++, marka, cena, "", 0);
            else if (current_node == "Podklad" || current_node == "F")  nowy = new Podklad(nazwa, next_id++, marka, cena, "", 0, "", "");
            else if (current_node == "Korektor" || current_node == "G") nowy = new Korektor(nazwa, next_id++, marka, cena, "", 0, "", "");
            else if (current_node == "Tusz" || current_node == "H")      nowy = new Tusz(nazwa, next_id++, marka, cena, 0, 0, "", "");
            else if (current_node == "Cienie" || current_node == "I")    nowy = new Cienie(nazwa, next_id++, marka, cena, 0, 0, "", 0);
            else if (current_node == "Szminka" || current_node == "J")   nowy = new Szminka(nazwa, next_id++, marka, cena, "", "", "", 0);

            if (nowy != nullptr) {
                nowy->wczytajZKonsoli();
                baza.push_back(nowy);
                cout << "Obiekt dodany pomyslnie.\n";
            }
            else {
                cout << "Blad! Obiekty mozna dodawac tylko do lisci. Uzyj komendy CD.\n";
            }
        }
        else if (komenda == "DO") {
            string nazwa;
            cin >> nazwa;

            if (current_node == "Kosmetyk" || current_node == "A" || current_node == "DoTwarzy" || current_node == "C" || current_node == "DoOczu" || current_node == "D" || current_node == "DoUst" || current_node == "E") {
                cout << "Blad! Obiekty mozna usuwac tylko bedac na poziomie liscia!\n";
            }
            else {
                bool usunieto = false;

                for (int i = 0; i < baza.size(); i++) {
                    if (baza[i]->getNazwaObiektu() == nazwa) {
                        if (baza[i]->czyNalezyDo(current_node)) {
                            delete baza[i];
                            baza.erase(baza.begin() + i);
                            cout << "Usunieto obiekt " << nazwa << ".\n";
                            usunieto = true;
                        }
                        break;
                    }
                }

                if (!usunieto) {
                    cout << "Nie usunieto obiektu (zla nazwa lub nie nalezy do obecnego liscia).\n";
                }
            }
        }
        else if (komenda == "MDO") {
            string nazwa;
            cin >> nazwa;

            if (current_node == "Kosmetyk" || current_node == "A" || current_node == "DoTwarzy" || current_node == "C" || current_node == "DoOczu" || current_node == "D" || current_node == "DoUst" || current_node == "E") {
                cout << "Blad! Obiekty mozna modyfikowac tylko bedac na poziomie liscia!\n";
            }
            else {
                bool znaleziono = false;
                for (int i = 0; i < baza.size(); i++) {
                    if (baza[i]->getNazwaObiektu() == nazwa && baza[i]->czyNalezyDo(current_node)) {
                        baza[i]->modyfikuj();
                        znaleziono = true;
                        cout << "Zmodyfikowano.\n";
                        break;
                    }
                }
                if (!znaleziono) cout << "Nie znaleziono obiektu w biezacym wezle.\n";
            }
        }
        else if (komenda == "SHOW") {
            string nazwa;
            cin >> nazwa;
            bool found = false;
            for (int i = 0; i < baza.size(); i++) {
                if (baza[i]->getNazwaObiektu() == nazwa) {
                    baza[i]->show();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Nie znaleziono takiego obiektu.\n";
        }
        else if (komenda == "SAVE") {
            ofstream plik("baza.txt");
            if (plik.is_open()) {
                for (int i = 0; i < baza.size(); i++) {
                    baza[i]->zapisz(plik);
                }
                plik.close();
                cout << "Zapisano do pliku.\n";
            }
            else {
                cout << "Blad przy zapisywaniu pliku.\n";
            }
        }
        else if (komenda == "READ") {
            ifstream plik("baza.txt");
            if (plik.is_open()) {
                for (int i = 0; i < baza.size(); i++) delete baza[i];
                baza.clear();
                next_id = 1;

                string typKlasy, nazwa, marka;
                int id; float cena;

                while (plik >> typKlasy >> nazwa >> id >> marka >> cena) {
                    Kosmetyk* wczytany = nullptr;

                    if (typKlasy == "Perfumy")       wczytany = new Perfumy(nazwa, id, marka, cena, "", 0);
                    else if (typKlasy == "Podklad")  wczytany = new Podklad(nazwa, id, marka, cena, "", 0, "", "");
                    else if (typKlasy == "Korektor") wczytany = new Korektor(nazwa, id, marka, cena, "", 0, "", "");
                    else if (typKlasy == "Tusz")      wczytany = new Tusz(nazwa, id, marka, cena, 0, 0, "", "");
                    else if (typKlasy == "Cienie")    wczytany = new Cienie(nazwa, id, marka, cena, 0, 0, "", 0);
                    else if (typKlasy == "Szminka")   wczytany = new Szminka(nazwa, id, marka, cena, "", "", "", 0);

                    if (wczytany != nullptr) {
                        wczytany->wczytajZPliku(plik);
                        baza.push_back(wczytany);
                        if (id >= next_id) next_id = id + 1;
                    }
                }
                plik.close();
                cout << "Wczytano z pliku.\n";
            }
            else {
                cout << "Blad otwarcia pliku (prawdopodobnie jeszcze nie istnieje).\n";
            }
        }
        else {
            cout << "Nieznana komenda. Wpisz MENU aby zobaczyc liste dostepnych opcji.\n";
        }

        cout << "\nNacisnij ENTER, aby kontynuowac";
        cin.ignore(10000, '\n');
        cin.get();              

        system("cls");          
        wyswietlMenu();
    }

    for (int i = 0; i < baza.size(); i++) delete baza[i];
    return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
