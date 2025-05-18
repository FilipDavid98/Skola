// Textova RPG hra - verze bez OOP, psana jako by ji delal prvak na stredni skole
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Staty hrace
int maxZivoty = 5;
int zivoty = 5;
int maxMana = 5;
int mana = 5;
int utok = 3;
int level = 1;
int xp = 0;
int xpNaLevel = 10;
int zlato = 0;
bool hori = false;
int horiKola = 0;

string jmenoClassy = "";
bool ziva = true;

// Funkce pro vypis statistiky
void vypisStaty() {
    cout << "\nStaty postavy:" << endl;
    cout << "Zivoty: " << zivoty << "/" << maxZivoty << endl;
    cout << "Mana: " << mana << "/" << maxMana << endl;
    cout << "Utok: " << utok << endl;
    cout << "Zlato: " << zlato << endl;
    cout << "Level: " << level << " (" << xp << "/" << xpNaLevel << ")" << endl;
    cout << endl;
}

// Funkce pro vyber classy
void vyberClassy() {
    while (true) {
        cout << "Vyber si classu:" << endl;
        cout << "1. Paladin\n2. Lovec\n3. Mag\n4. Warlock" << endl;
        int volba;
        cin >> volba;

        if (volba == 1) {
            jmenoClassy = "Paladin";
            maxZivoty = 5;
            zivoty = 5;
            maxMana = 5;
            mana = 5;
            utok = 3;
        } else if (volba == 2) {
            jmenoClassy = "Lovec";
            maxZivoty = 4;
            zivoty = 4;
            maxMana = 4;
            mana = 4;
            utok = 4;
        } else if (volba == 3) {
            jmenoClassy = "Mag";
            maxZivoty = 3;
            zivoty = 3;
            maxMana = 6;
            mana = 6;
            utok = 2;
        } else if (volba == 4) {
            jmenoClassy = "Warlock";
            maxZivoty = 4;
            zivoty = 4;
            maxMana = 5;
            mana = 5;
            utok = 3;
        } else {
            cout << "Neplatna volba." << endl;
            continue;
        }

        cout << "\nClass: " << jmenoClassy << endl;
        vypisStaty();
        cout << "Chces tuto classu? (1 = ano, 0 = ne): ";
        int potvrzeni;
        cin >> potvrzeni;
        if (potvrzeni == 1) break;
    }
}

// Funkce pro ziskani XP a level up
void pridejXP(int kolik) {
    xp += kolik;
    cout << "Ziskavas " << kolik << " XP." << endl;
    if (xp >= xpNaLevel) {
        level++;
        xp -= xpNaLevel;
        xpNaLevel += 5;
        maxZivoty++;
        utok++;
        cout << "LEVEL UP! Mas novy level " << level << "!" << endl;
        cout << "Max zivoty +1, Utok +1!" << endl;
    }
}

// Funkce pro vesnici
void vesnice() {
    cout << "\nVchazis do vesnice. Co chces delat?" << endl;
    while (true) {
        cout << "1. Vylecit zivoty (3 zlata)\n2. Zvysit max zivoty (5 zlata)\n3. Zvysit max manu (5 zlata)\n4. Zvysit utok (5 zlata)\n5. Odejit" << endl;
        int volba;
        cin >> volba;
        if (volba == 1 && zlato >= 3) {
            zivoty = maxZivoty;
            zlato -= 3;
            cout << "Zivoty doplneny." << endl;
        } else if (volba == 2 && zlato >= 5) {
            maxZivoty++;
            zlato -= 5;
            cout << "Max zivoty zvyseny." << endl;
        } else if (volba == 3 && zlato >= 5) {
            maxMana++;
            zlato -= 5;
            cout << "Max mana zvysena." << endl;
        } else if (volba == 4 && zlato >= 5) {
            utok++;
            zlato -= 5;
            cout << "Utok zvysen." << endl;
        } else if (volba == 5) {
            break;
        } else {
            cout << "Nemas dost zlata nebo neplatna volba." << endl;
        }
    }
}

// Funkce pro boj (1 az 3 nepratele)
void boj(int pocet, bool miniboss, bool boss) {
    string jmena[16] = {"Goblin", "Troll", "Ork", "Kostlivec", "Netopyr", "Zlodej", "Divoky vlk", "Zmutovany hmyz", "Bandita", "Sliz", "Zluty skret", "Plamenak", "Netvor", "Zombie", "Demon", "Cerny stin"};
    string mbJmena[2] = {"Obr Krug", "Necromancer"};
    string hbJmeno = "Pyrocoil";
    int zivotyM[3];
    int maxZivotyM[3];
    string jmenoM[3];

    for (int i = 0; i < pocet; i++) {
        if (boss) {
            jmenoM[i] = hbJmeno;
            maxZivotyM[i] = 40;
        } else if (miniboss) {
            jmenoM[i] = mbJmena[i % 2];
            maxZivotyM[i] = 20;
        } else {
            jmenoM[i] = jmena[rand() % 16];
            maxZivotyM[i] = 5 + rand() % 3;
        }
        zivotyM[i] = maxZivotyM[i];
    }

    bool hracTahnePrvni = !(miniboss || boss);
    int kolo = 1;

    cout << "\nBojujes proti: ";
    for (int i = 0; i < pocet; i++) {
        cout << jmenoM[i] << " (" << zivotyM[i] << ") ";
    }
    cout << endl;

    while (zivoty > 0) {
        if (hori) {
            zivoty -= 2;
            cout << "Horis! Ztracis 2 zivoty." << endl;
            horiKola--;
            if (horiKola <= 0) hori = false;
        }

        if (hracTahnePrvni) {
            cout << "Tvoje kolo. Vyber akci:" << endl;
            cout << "1. Utok (" << utok << ")\n2. Schopnost (1. utok vsechny za 1 dmg - 2 mana, 2. leceni +1 hp - 1 mana)" << endl;
            int volba;
            cin >> volba;
            if (volba == 1) {
                cout << "Vyber cil (0 az " << pocet - 1 << "): ";
                int cil;
                cin >> cil;
                if (cil >= 0 && cil < pocet && zivotyM[cil] > 0) {
                    zivotyM[cil] -= utok;
                    cout << "Zasahujes " << jmenoM[cil] << " za " << utok << " dmg." << endl;
                }
            } else if (volba == 2) {
                cout << "1 = utok na vsechny, 2 = leceni" << endl;
                int schop;
                cin >> schop;
                if (schop == 1 && mana >= 2) {
                    mana -= 2;
                    for (int i = 0; i < pocet; i++) {
                        zivotyM[i]--;
                        cout << jmenoM[i] << " zasazen." << endl;
                    }
                } else if (schop == 2 && mana >= 1) {
                    mana -= 1;
                    if (zivoty < maxZivoty) zivoty++;
                    cout << "Lecis se." << endl;
                }
            }
        }

        for (int i = 0; i < pocet; i++) {
            if (zivotyM[i] > 0) {
                int dmg = 1 + rand() % 2;
                if (boss && jmenoM[i] == "Pyrocoil") {
                    if (kolo % 4 == 0) {
                        cout << "Pyrocoil preteka ohnem a exploduje!" << endl;
                        zivoty -= 15;
                        zivotyM[i] -= 20;
                    } else {
                        if (hori) {
                            dmg += 3;
                        } else {
                            hori = true;
                            horiKola = 2;
                        }
                    }
                }
                zivoty -= dmg;
                cout << jmenoM[i] << " ti dava " << dmg << " dmg." << endl;
            }
        }

        hracTahnePrvni = true;
        kolo++;

        // kontrola vyhry
        bool vsichniMrtvi = true;
        for (int i = 0; i < pocet; i++) {
            if (zivotyM[i] > 0) vsichniMrtvi = false;
        }
        if (vsichniMrtvi) {
            cout << "\nVyhrals souboj!" << endl;
            for (int i = 0; i < pocet; i++) {
                if (miniboss || boss || rand() % 2 == 0) {
                    zlato += 3 + rand() % 5;
                }
                pridejXP(3);
            }
            return;
        }

        if (zivoty <= 0) {
            cout << "Prohrals hru. Konec." << endl;
            exit(0);
        }
    }
}

// Funkce hlavni linie hry
void spustHru() {
    string intro = "Vydavas se na dlouhou cestu skrz temne lesy a nebezpecne planiny, abys porazil Pyrocoila, stvoreni z cisteho ohne.";
    cout << intro << endl;
    vyberClassy();

    // mapa dle zadani: |V| > |M| > |M|> |2xM| > |MB| > |V| > |M| > |2xM| > |2xM| > |MB| > |V| > |2xM| > |2xM| > |3xM| > |V| > |HB|
    vesnice(); boj(1,false,false); boj(1,false,false); boj(2,false,false); boj(1,true,false); 
    vesnice(); boj(1,false,false); boj(2,false,false); boj(2,false,false); boj(1,true,false);
    vesnice(); boj(2,false,false); boj(2,false,false); boj(3,false,false); vesnice(); boj(1,false,true);

    cout << "Gratuluju! Porazils Pyrocoila a zachranils krajinu od ohne." << endl;
}

int main() {
    srand(time(0));
    spustHru();
    return 0;
}
