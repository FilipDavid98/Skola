#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Hracovy staty
int maxZivoty = 5, zivoty = 5, maxMana = 5, mana = 5, utok = 3;
int level = 1, xp = 0, xpNaLevel = 8, zlato = 0;
bool hori = false, otraveny = false;
int horiKola = 0, otravaKola = 0;
string jmenoClassy = "";

void vypisStaty() {
    cout << "\n====== STAV HRACE ======\n";
    cout << "Class: " << jmenoClassy << "\n";
    cout << "HP    : " << zivoty << "/" << maxZivoty << "\n";
    cout << "Mana  : " << mana << "/" << maxMana << "\n";
    cout << "Utok  : " << utok << "\n";
    cout << "Level : " << level << " (XP: " << xp << "/" << xpNaLevel << ")\n";
    cout << "Zlato : " << zlato << "\n";
    if (hori) cout << " Horis! (" << horiKola << " kol)\n";
    if (otraveny) cout << " Otraveny! (" << otravaKola << " kol)\n";
    cout << "========================\n";
}

void vyberClassy() {
    while (true) {
        cout << "\nVyber si svoji classu:\n";
        cout << "1. Paladin   (HP = 7, Mana = 5, Utok = 3)\n";
        cout << "2. Lovec     (HP = 6, Mana = 5, Utok = 4)\n";
        cout << "3. Mag       (HP = 5, Mana = 7, Utok = 2)\n";
        cout << "4. Warlock   (HP = 6, Mana = 6, Utok = 3)\n";
        cout << "Tvoje volba: ";
        int v; cin >> v;

        if (v == 1) { jmenoClassy = "Paladin"; maxZivoty = zivoty = 7; maxMana = mana = 5; utok = 3; }
        else if (v == 2) { jmenoClassy = "Lovec"; maxZivoty = zivoty = 6; maxMana = mana = 5; utok = 4; }
        else if (v == 3) { jmenoClassy = "Mag"; maxZivoty = zivoty = 5; maxMana = mana = 7; utok = 2; }
        else if (v == 4) { jmenoClassy = "Warlock"; maxZivoty = zivoty = 6; maxMana = mana = 6; utok = 3; }
        else { cout << " Neplatna volba!\n"; continue; }

        vypisStaty();
        cout << "Potvrdit svuj vyber? (1 = ano): ";
        cin >> v;
        if (v == 1) break;
    }
}

void pridejXP(int k) {
    xp += k;
    cout << "Ziskane XP: +" << k;
    if (xp >= xpNaLevel) {
        level++; xp -= xpNaLevel; xpNaLevel += 4;
        maxZivoty += 1; utok += 1;
        mana = maxMana; zivoty = maxZivoty;
        cout << " LEVEL UP! HP a Mana obnoveny!";
    }
    cout << "\n";
}

void vesnice() {
    cout << "\n===  VESNICE ===\nObchodnik: 'Vitej, dobrodruhu! Co potrebujes?'\n";
    while (true) {
        cout << "\n1. Vylecit (3 zlata)\n2. Zvysit MaxHP (5 zlata)\n3. Zvysit MaxMana (5 zlata)\n4. Zvysit Utok (5 zlata)\n5. Odejit\n";
        cout << "Tvoje zlato: " << zlato << "\nTvoje volba: ";
        int v; cin >> v;

        if (v == 1 && zlato >= 3) {
            zivoty = maxZivoty; mana = maxMana; zlato -= 3;
            cout << " Uplne ses vylecil!\n";
        } else if (v == 2 && zlato >= 5) {
            maxZivoty++; zlato -= 5;
            cout << " MaxHP navysene na " << maxZivoty << "\n";
        } else if (v == 3 && zlato >= 5) {
            maxMana++; zlato -= 5;
            cout << " MaxMana navysene na " << maxMana << "\n";
        } else if (v == 4 && zlato >= 5) {
            utok++; zlato -= 5;
            cout << " Utok zvysen na " << utok << "\n";
        } else if (v == 5) {
            cout << "Opoustis vesnici...\n";
            break;
        } else {
            cout << " Nedostatek zlata nebo neplatna volba!\n";
        }
    }
}

void boj(int pocet, bool miniboss, bool boss) {
    string jmena[] = {"Goblin", "Troll", "Ork", "Kostlivec", "Netopyr", "Zlodej", "Vlk", "Hmyz", "Bandita", "Sliz", "Skret", "Plamenak", "Netvor", "Zombie", "Demon", "Stin"};
    string mbJmena[] = {"Obr Krug", "Necromancer"};

    int zivotyM[3], maxZivotyM[3];
    string jmenoM[3];
    bool horiM[3] = {false}, otravenyM[3] = {false};
    int horiKolaM[3] = {0}, otravaKolaM[3] = {0};

    for (int i = 0; i < pocet; i++) {
        if (boss) {
            jmenoM[i] = " PYROCOIL";
            maxZivotyM[i] = 40;
        } else if (miniboss) {
            jmenoM[i] = mbJmena[i % 2];
            maxZivotyM[i] = 15 + rand() % 11;
        } else {
            jmenoM[i] = jmena[rand() % 16];
            maxZivotyM[i] = 4 + rand() % 4;
        }
        zivotyM[i] = maxZivotyM[i];
    }

    cout << "\n===== BOJ ZACINA! =====\n";
    for (int i = 0; i < pocet; i++) {
        cout << i + 1 << ". " << jmenoM[i] << " [" << zivotyM[i] << " HP]\n";
    }

    bool hracTah = !(miniboss || boss);
    int kolo = 1;

    while (zivoty > 0) {
        cout << "\n----- KOLO " << kolo++ << " -----\n";

        // Efekty na hráča
        if (hori) { zivoty -= 1; cout << " Horis! -2 HP\n"; if (--horiKola <= 0) hori = false; }
        if (otraveny) { zivoty--; cout << " Otrava! -1 HP\n"; if (--otravaKola <= 0) otraveny = false; }

        if (zivoty <= 0) break;

        if (hracTah) {
            vypisStaty();
            cout << "1. Utok\n2. Schopnost\nTvoje volba: ";
            int v; cin >> v;

            if (v == 1) {
                cout << "Vyber cil (1-" << pocet << "): ";
                for (int i = 0; i < pocet; i++) if (zivotyM[i] > 0) cout << i + 1 << "." << jmenoM[i] << " ";
                cout << "\n"; int c; cin >> c; c--;
                if (c >= 0 && c < pocet && zivotyM[c] > 0) {
                    zivotyM[c] -= utok;
                    if (zivotyM[c] <= 0) zivotyM[c] = 0;
                    cout << " Zasiahnut " << jmenoM[c] << " za " << utok << " dmg!\n";
                }
            } else if (v == 2) {
                cout << "1. Specialni schopnost\n2. Leceni\nTvoje volba: ";
                int s; cin >> s;
                if (s == 1) {
                    if (jmenoClassy == "Paladin" || jmenoClassy == "Warlock") {
                        int healed = rand() % 5 + 5;
                        for (int i = 0; i < pocet; i++) if (zivotyM[i] > 0) { zivotyM[i] -= 2; cout << jmenoM[i] << " -2 HP\n"; }
                    } else if (jmenoClassy == "Mag" && mana >= 3) {
                        cout << "Cil: "; int c; cin >> c; c--;
                        if (c >= 0 && c < pocet && zivotyM[c] > 0) {
                            mana -= 3; horiM[c] = true; horiKolaM[c] = 4;
                            cout << jmenoM[c] << " hori!\n";
                        }
                    } else if (jmenoClassy == "Warlock" && mana >= 2) {
                        cout << "Cil: "; int c; cin >> c; c--;
                        if (c >= 0 && c < pocet && zivotyM[c] > 0) {
                            mana -= 2; otravenyM[c] = true; otravaKolaM[c] = 4;
                            cout << jmenoM[c] << " otráven!\n";
                        }
                    } else cout << " Nedostatok many!\n";
                } else if (s == 2 && mana >= 1) {
                    mana--; if (zivoty < maxZivoty) zivoty++;
                    cout << " Lec1eni! Aktualni HP: " << zivoty << "\n";
                }
            }
        }

        // Nepriatelia útočia
        for (int i = 0; i < pocet; i++) {
            if (zivotyM[i] > 0) {
                if (horiM[i]) { zivotyM[i] -= 2; cout << jmenoM[i] << " hori! -2 HP\n"; if (--horiKolaM[i] <= 0) horiM[i] = false; }
                if (otravenyM[i]) { zivotyM[i]--; cout << jmenoM[i] << " otrava! -1 HP\n"; if (--otravaKolaM[i] <= 0) otravenyM[i] = false; }
                if (zivotyM[i] <= 0) continue;

                int dmg = 1 + rand() % 2;
                if (boss && kolo % 5 == 0) {
                    cout << "\n PYROCOIL EXPLODUJE! Všetci horia!\n";
                    dmg = 8; hori = true; horiKola = 3;
                } if (miniboss) dmg += 1;

                zivoty -= dmg;
                cout << jmenoM[i] << " utoci! -" << dmg << " HP (Ty: " << zivoty << ")\n";
            }
        }

        hracTah = true;

        // Skontroluj výhru
        bool vsetciMrtvi = true;
        for (int i = 0; i < pocet; i++) if (zivotyM[i] > 0) vsetciMrtvi = false;

        if (vsetciMrtvi) {
            cout << "\n VYHRAL SI BOJ!\n";
            for (int i = 0; i < pocet; i++) {
                if (boss) { pridejXP(20); zlato += 20; }
                else if (miniboss) { pridejXP(10); zlato += 10; }
                else { pridejXP(3); zlato += 3 + rand() % 3; }
            }
            mana = maxMana;
            zivoty = min(zivoty + 2, maxZivoty);
            return;
        }
        if (zivoty <= 0) {
            cout << "\n PROHRA! Dosiahnuty Level: " << level << ", Zlato: " << zlato << "\n";
            exit(0);
        }
    }
}

void spustHru() {
    cout << "===============================\n";
    cout << "RPG PYROCOIL\nPoraz mocné stvoreni z ohne!\n";
    cout << "===============================\n";
    vyberClassy();

    // Mapa
    vesnice(); boj(1, 0, 0); boj(1, 0, 0); boj(2, 0, 0); vesnice(); boj(1, 1, 0);
    vesnice(); boj(1, 0, 0); boj(2, 0, 0); boj(2, 0, 0); boj(1, 1, 0);
    vesnice(); boj(2, 0, 0); boj(2, 0, 0); boj(3, 0, 0); vesnice(); boj(1, 0, 1);

    cout << "\n *** GRATULUJU! *** \n";
    cout << "Porazil si Pyrocoila a zachránil si krajinu!\n";
}

int main() {
    srand(time(0));
    spustHru();
    return 0;
}
