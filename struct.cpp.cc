#include <iostream>
#include <string.h>
using namespace std;

/*
    TODO: Definiti o structura de date numita "character" care sa 
    aiba urmatoarele caracteristici:
    - "name" numele caracterului exprimat printr-un sir de caractere
    - "hp" (viata) exprimata printr-un nr. intreg
    - "atk" (puterea de atac) exprimata printr-un nr. intreg
    - "hp_regen" (regenerare in timpul luptei) exprimata printr-un bool
        true daca are regenerare a vieti = 10/s
        false daca nu
    - "speed" (viteza atacului) exprimata printr-un nr. real(float)

    ! Folositi typedef
*/
typedef struct Character
{
    char name[20];
    int hp;
    int atk;
    bool hp_regen;
    float speed;
}character;


/* Scrieti o functie "fight" de tip character care primeste ca argument
    2 variabile de tip character si returneaza player-ul invingator
*/
character fight(character p1, character p2)
{
    character aux, winner;
    int hitsp2 = 1;
    if (p1.speed > p2.speed)
    {
        aux = p1;
        p1 = p2;
        p2 = aux;
    }
    for(float i = p1.speed; p1.hp <= 0 || p2.hp <= 0; i += p1.speed)
    {
        p2.hp -= p1.atk;
        if (hitsp2 * p2.speed < i)
        {
            p1.hp -= p2.atk;
            hitsp2++;
        }

        if (p1.hp_regen == true)
            p1.hp += 10;
        if (p2.hp_regen == true)
            p2.hp += 10;
        
    }
    if (p2.hp == 0)
        winner = p1;
    else
        winner = p2;
    return winner;
}


/* Scrieti o functie turneu care primeste un vector de variabile de tip
    character si intoarce castigatorul turneului
*/
character turneu(character *participants, int n)
{
    character winner = participants[0];
    for (int i = 0; i <= n - 1; i++)
        winner = fight(winner, participants[i]);
    return winner;
}

int main() {
    /*"praslea mage elf pekka"*/
    character x, y, z, t;

    strcpy(x.name, "Praslea");
    x.hp = 100;
    x.atk = 10;
    x.hp_regen = false;
    x.speed = 5;

    strcpy(y.name, "Mage");
    y.hp = 100;
    y.atk = 30;
    y.hp_regen = true;
    y.speed = 5;

    strcpy(z.name, "Elf");
    z.hp = 70;
    z.atk = 8;
    z.hp_regen = true;
    z.speed = 2;

    strcpy(t.name, "Pekka");
    t.hp = 200;
    t.atk = 60;
    t.hp_regen = false;
    t.speed = 5;

    character participants[5];
    participants[0] = x;
    participants[1] = y;
    participants[2] = z;
    participants[3] = t;

    character fight_winner = fight(x, y);
    cout << "Fight winner: " << fight_winner.name << '\n';
    character tournament_winner = turneu(participants, 4);
    cout << "Tournament winner: " << tournament_winner.name << '\n';

    return 0;
}
