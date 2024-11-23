#include <iostream>
using namespace std;
// max 5 materii,max 30 de elevi in clasa
typedef struct materie
{
    char nume[20];
    int nr_note;
    int note[100];
    int absente;
}materie;

typedef struct elev
{
    char nume[20];
    char prenume[20];
    float medie_f;
    int m; // nr materii
    materie materii[5];
}elev;

typedef struct clasa {
    int numar_clasa;       
    char litera_clasa;     
    int nr_elevi;          
    elev elevi[30];        
} clasa;

int medie_materie(materie a) {
    int s = 0;
    for (int i = 0; i < a.nr_note; i++) {
        s += a.note[i];
    }

    if (a.nr_note == 0) 
        return 0; 
    return (s * 100) / a.nr_note;
}


int medie_finala(elev e) {
    int s = 0;
    for (int i = 0; i < e.m; i++)
        s += medie_materie(e.materii[i]);

    return s / e.m;
}

void construieste_clasa(clasa &cls) {
    cout << "Introduceti numarul clasei (9-12): ";
    cin >> cls.numar_clasa;

    cout << "Introduceti litera clasei (A-D): ";
    cin >> cls.litera_clasa;

    cout << "Introduceti numarul de elevi: ";
    cin >> cls.nr_elevi;

    for (int i = 0; i < cls.nr_elevi; i++) {
        cout << "Elev " << i + 1 << ":\n";
        cout << "Nume: ";
        cin >> cls.elevi[i].nume;
        cout << "Prenume: ";
        cin >> cls.elevi[i].prenume;

        cout << "Numarul de materii: ";
        cin >> cls.elevi[i].m;

        for (int j = 0; j < cls.elevi[i].m; j++) 
        {
            cout << "Materie " << j + 1 << ":\n";

            cout << "Numele materiei: ";
            cin >> cls.elevi[i].materii[j].nume;

            cout << "Numarul de note: ";
            cin >> cls.elevi[i].materii[j].nr_note;

            cout << "Introduceti notele: ";
            for (int k = 0; k < cls.elevi[i].materii[j].nr_note; k++) {
                cin >> cls.elevi[i].materii[j].note[k];
            }

        cls.elevi[i].medie_f = medie_finala(cls.elevi[i]);
        }
    }
}

void adauga_elev(clasa &cls) {
    if (cls.nr_elevi >= 30) {
        cout << "Clasa este plina. Nu se mai pot adauga elevi.\n";
        return;
    }

    cout << "Adaugati detaliile elevului nou:\n";
    cout << "Nume: ";
    cin >> cls.elevi[cls.nr_elevi].nume;
    cout << "Prenume: ";
    cin >> cls.elevi[cls.nr_elevi].prenume;

    cout << "Numarul de materii: ";
    cin >> cls.elevi[cls.nr_elevi].m;

    for (int j = 0; j < cls.elevi[cls.nr_elevi].m; j++) {
        cout << "Materie " << j + 1 << ":\n";
        cout << "Nume materie: ";
        cin >> cls.elevi[cls.nr_elevi].materii[j].nume;

        cout << "Numarul de note: ";
        cin >> cls.elevi[cls.nr_elevi].materii[j].nr_note;

        cout << "Introduceti notele: ";
        for (int k = 0; k < cls.elevi[cls.nr_elevi].materii[j].nr_note; k++)
            cin >> cls.elevi[cls.nr_elevi].materii[j].note[k];

        cout << "Numarul de absente: ";
        cin >> cls.elevi[cls.nr_elevi].materii[j].absente;
    }

    cls.elevi[cls.nr_elevi].medie_f = medie_finala(cls.elevi[cls.nr_elevi]);
    cls.nr_elevi++;
}

void sorteaza_elevi(clasa &cls) {
    for (int i = 0; i < cls.nr_elevi - 1; i++)
        for (int j = i + 1; j < cls.nr_elevi; j++) 
            if (cls.elevi[i].medie_f < cls.elevi[j].medie_f) {
                elev k = cls.elevi[i];
                cls.elevi[i] = cls.elevi[j];
                cls.elevi[j] = k;
            }
}

int main() 
{
    clasa cls;
    construieste_clasa(cls);
    
    char optiune;
    cout << "Doriti sa adaugati un elev nou? (y/n): ";
    cin >> optiune;
    while (optiune == 'y') {
        adauga_elev(cls);
        cout << "Doriti sa adaugati un alt elev? (y/n): ";
        cout << '\n';
        cin >> optiune;
    }

    sorteaza_elevi(cls);

    cout << "Elevii sortati descrescator dupa media finala:\n";

    for (int i = 0; i < cls.nr_elevi; i++) 
    {
        cout << cls.elevi[i].nume << " | " << cls.elevi[i].prenume;
        for (int j = 0; j < cls.elevi[i].m; j++) 
        {
            int medie = medie_materie(cls.elevi[i].materii[j]);
            cout << " | " << medie / 100 << "." << (medie % 100);
        }
        int medie_entiera = cls.elevi[i].medie_f;
    cout << " | " << medie_entiera / 100 << "." << (medie_entiera % 100) << endl;
    }

    return 0;
}