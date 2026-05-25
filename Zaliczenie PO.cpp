// Zaliczenie PO.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string>

using namespace std;

class Kosmetyk { //A
private:
    int id;

protected:
    string marka;
    float cena;

public:
    Kosmetyk(int nadajId, string nadajMarke, float nadajCene) {
        id = nadajId;
        marka = nadajMarke;
        cena = nadajCene;
    }

    virtual ~Kosmetyk(){}

    virtual void show() {
        cout << "ID: " << id << " | Marka: " << marka << " | Cena: " << cena << " PLN" << endl;
    }
};

class Perfumy : public Kosmetyk { //B
private:
    string nutaZapachowa;

protected:
    int pojemnoscMl;

public:
    Perfumy(int nadajId, string nadajMarke, float nadajCene, string nadajNute, int nadajPojemnosc)
        : Kosmetyk(nadajId, nadajMarke, nadajCene) 
    {
        nutaZapachowa = nadajNute;
        pojemnoscMl = nadajPojemnosc;
    }
    void show() override {
        cout << "--- PERFUMY ---" << endl;
        Kosmetyk::show();
        cout << "Nuta zapachowa: " << nutaZapachowa << " | Pojemnosc: " << pojemnoscMl << " ml" << endl;
    }

};

class DoTwarzy : public Kosmetyk { //C
private:
    string typCery;

protected:
    int waznoscProduktu; // w miesiacach

public:
    DoTwarzy(int nadajId, string nadajMarke, float nadajCene, string nadajTypCery, int nadajWaznosc)
        : Kosmetyk(nadajId, nadajMarke, nadajCene)
    {
        typCery = nadajTypCery;
        waznoscProduktu = nadajWaznosc;
    }
    virtual void show() override {
        Kosmetyk::show();
        cout << "Typ cery: " << typCery << " | Waznosc: " << waznoscProduktu << " miesiecy" << endl;
    }
};

class Podklad : public DoTwarzy { //F
private:
    string odcien;

protected:
    string podton;
    
public:
    Podklad(int nadajId, string nadajMarke, float nadajCene, string nadajTypCery, int nadajWaznosc, string nadajOdcien, string nadajPodton)
        : DoTwarzy(nadajId, nadajMarke, nadajCene, nadajTypCery, nadajWaznosc)
    {
        odcien = nadajOdcien;
        podton = nadajPodton;
    }
    void show() override {
        cout << "--- PODKLAD ---" << endl;
        DoTwarzy::show();
        cout << "Odcien: " << odcien << " | Podton: " << podton << endl;
    }
};

class Korektor : public DoTwarzy { //G
private:
    string krycie;

protected:
    string efekt;

public:
    Korektor(int nadajId, string nadajMarke, float nadajCene, string nadajTypCery, int nadajWaznosc, string nadajKrycie, string nadajEfekt)
        : DoTwarzy(nadajId, nadajMarke, nadajCene, nadajTypCery, nadajWaznosc)
    {
        krycie = nadajKrycie;
        efekt = nadajEfekt;
    }
    void show() override {
        cout << "--- KOREKTOR ---" << endl;
        DoTwarzy::show();
        cout << "Krycie: " << krycie << " | Efekt: " << efekt << endl;
    }
};

class DoOczu : public Kosmetyk { //D
private:
  int trwaloscWgodzinach;

protected:
    int wagaWgramach;

public:
    DoOczu(int nadajId, string nadajMarke, float nadajCene, int nadajTrwalosc, int nadajWage)
        : Kosmetyk(nadajId, nadajMarke, nadajCene)
    {
        trwaloscWgodzinach = nadajTrwalosc;
        wagaWgramach = nadajWage;
    }
    virtual void show() override {
        Kosmetyk::show();
        cout << "Trwalosc: " << trwaloscWgodzinach << " h | Waga: " << wagaWgramach << " g" << endl;
    }
};

class Tusz : public DoOczu { //H
private:
    bool czyWodoodporny;

protected:
    string kolor;

public:
    Tusz(int nadajId, string nadajMarke, float nadajCene, int nadajTrwalosc, int nadajWage, bool nadajWodoodp, string nadajKolor)
        : DoOczu(nadajId, nadajMarke, nadajCene, nadajTrwalosc, nadajWage)
    {
        czyWodoodporny = nadajWodoodp;
        kolor = nadajKolor;
    }
    void show() override {
        cout << "--- TUSZ DO RZES ---" << endl;
        DoOczu::show();
        cout << "Wodoodporny: " << (czyWodoodporny ? "Tak" : "Nie") << " | Kolor: " << kolor << endl;
    }
};

class Cienie : public DoOczu { //I
private:
    string barwy;

protected:
    int iloscKolorow;

public:
    Cienie(int nadajId, string nadajMarke, float nadajCene, int nadajTrwalosc, int nadajWage, string nadajBarwe, int nadajIloscKolorow)
        : DoOczu(nadajId, nadajMarke, nadajCene, nadajTrwalosc, nadajWage)
    {
        barwy = nadajBarwe;
        iloscKolorow = nadajIloscKolorow;
    }
    void show() override {
        cout << "--- PALETA CIENI ---" << endl;
        DoOczu::show();
        cout << "Barwy: " << barwy << " | Ilosc kolorow: " << iloscKolorow << endl;
    }
};

class DoUst : public Kosmetyk { //E
private:
    string typ;

protected:
    string wlasciwosci;

public:
    DoUst(int nadajId, string nadajMarke, float nadajCene, string nadajTyp, string nadajWlasciwosci)
        : Kosmetyk(nadajId, nadajMarke, nadajCene)
    {
        typ = nadajTyp;
        wlasciwosci = nadajWlasciwosci;
    }

    virtual void show() override {
        Kosmetyk::show(); 
        cout << "Typ: " << typ << " | Wlasciwosci: " << wlasciwosci << endl; 
    }
};

class Szminka : public DoUst { //J
private:
    bool czyMaDrobinki;

protected:
    int numerOdcienia;

public:
    Szminka(int nadajId, string nadajMarke, float nadajCene, string nadajTyp, string nadajWlasciwosci, bool nadajDrobinki, int nadajNumer)
        : DoUst(nadajId, nadajMarke, nadajCene, nadajTyp, nadajWlasciwosci) 
    {
        czyMaDrobinki = nadajDrobinki;
        numerOdcienia = nadajNumer;
    }

    void show() override {
        cout << "--- SZMINKA ---" << endl;
        DoUst::show(); 
        cout << "Drobinki: " << (czyMaDrobinki ? "Tak" : "Nie") << " | Odcien nr: " << numerOdcienia << endl;
    }
};


int main()
{
    
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
