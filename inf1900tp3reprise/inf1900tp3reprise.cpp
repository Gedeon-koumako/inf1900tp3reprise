#define F_CPU 8000000
//#include <util/delay.h>
//#include <avr/io.h> 
#include <iostream>
#include <fstream>
using namespace std;
#define NB_CYCLE1 2*60 // 10 secondes * frequence du cycles
#define NB_CYCLE2 2*400 // 10 secondes * frequence du cycles
#define DELAY_B1 133333
#define DELAY_B2 20000
#define ZERO = 0


int numCycle = 1;
enum class PuissMoteur { POURC_0, POURC_25, POURC_50, POURC_75, POURC_100 };
ofstream MyFile("data.txt");

void wtf(string i) {
    

    // Write to the file
    MyFile << i<<"\n";

    // Close the file
    
}

void a(string aa) {
    //cout << "     " << aa << endl;
    wtf(aa);
}

void a2(string aa, int ii) {

    // Write to the file
    MyFile << aa << ii << "\n";

    // Close the file
    
    
}
void allumerMoteur(long int delaiB, int pourc) {
    //_delay_loop_2(delaiB*pourc/4);
    //cout << "_delay_loop_2(delaiB*pourc/4);" << endl;
    //PORTB |= (1<<PORTB0);
    //cout << "PORTB |= (1<<PORTB0);" << endl;
    //_delay_loop_2((delaiB-delaiB*pourc)/4);
    //cout << "_delay_loop_2((delaiB-delaiB*pourc)/4);" << endl;
    //PORTB &= ~(1<<PORTB0);
    //cout << "PORTB &= ~(1<<PORTB0);" << endl;
}

void switchpuissMoteur(PuissMoteur& state) {
    switch (state)
    {
    case PuissMoteur::POURC_0:
        a("Changement de puissance de 0 a 25%");
        state = PuissMoteur::POURC_25;
        break;
    case PuissMoteur::POURC_25:
        a("Changement de puissance de 25 a 50%");
        state = PuissMoteur::POURC_50;
        break;
    case PuissMoteur::POURC_50:
        a("Changement de puissance de 50 a 75%");
        state = PuissMoteur::POURC_75;
        break;
    case PuissMoteur::POURC_75:
        a("Changement de puissance de 75 a 100%");
        state = PuissMoteur::POURC_100;
        break;
    case PuissMoteur::POURC_100:
        a("Changement de puissance de 100 a 0%");
        state = PuissMoteur::POURC_0;
        numCycle++;
        break;

    }
}
void executepuissMoteur(PuissMoteur& state) {
    switch (state)
    {

    case PuissMoteur::POURC_0:
        a("Moteur allumee : Puissance 0");
        allumerMoteur(DELAY_B1, 0);
        break;
    case PuissMoteur::POURC_25:
        a("Moteur allumee : Puissance 25");
        allumerMoteur(DELAY_B1, 25);
        break;
    case PuissMoteur::POURC_50:
        a("Moteur allumee : Puissance 50");
        allumerMoteur(DELAY_B1, 50);
        break;
    case PuissMoteur::POURC_75:
        a("Moteur allumee : Puissance 75");
        allumerMoteur(DELAY_B1, 75);
        break;
    case PuissMoteur::POURC_100:
        a("Moteur allumee : Puissance 100");
        allumerMoteur(DELAY_B1, 100);
        break;
    }
}

int main() {
    int compteur = 0;
    a2("Conpteur : ", compteur);
    PuissMoteur state = PuissMoteur::POURC_0;
    while (numCycle < 3)  // boucle sans fin
    {
        a("Avant le if");
        a2("Conpteur : ", compteur);
        if (numCycle == 1) {
            a("Dans le if");
            a2("Conpteur : ", compteur);
            //executepuissMoteur(state, DELAY_B1);
            executepuissMoteur(state);
            compteur++;
            if (compteur >= NB_CYCLE1) {
                switchpuissMoteur(state);
                compteur = 0;

            }
        }
        else {
            a("Dans le else");
            a2("Conpteur : ", compteur);
            executepuissMoteur(state);
            compteur++;
            if (compteur >= NB_CYCLE2) {
                //switchpuissMoteur(state, numCycle);
                switchpuissMoteur(state);
                compteur = 0;

            }
        }


    }
    MyFile.close();
}
