#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Hráčove staty
int maxZivoty = 5, zivoty = 5, maxMana = 5, mana = 5, utok = 3;
int level = 1, xp = 0, xpNaLevel = 10, zlato = 0;
bool hori = false, otraveny = false;
int horiKola = 0, otravaKola = 0;
string jmenoClassy = "";

void vypisStaty() {
    cout << "\n=== " << jmenoClassy << " ===" << endl;
    cout << "HP: " << zivoty << "/" << maxZivoty << " | Mana: " << mana << "/" << maxMana;
    cout << " | Utok: " << utok << " | Zlato: " << zlato << " | Level: " << level << endl;
    if (hori) cout << "HORIS! (" << horiKola << " kol)" << endl;
    if (otraveny) cout << "OTRAVENY! (" << otravaKola << " kol)" << endl;
}

void vyberClassy() {
    while (true) {
        cout << "\nVyber classu:\n1.Paladin(5HP,5M,3A) 2.Lovec(4HP,4M,4A) 3.Mag(3HP,6M,2A) 4.Warlock(4HP,5M,3A)\n";
        int v; cin >> v;

        if (v == 1) { jmenoClassy = "Paladin"; maxZivoty = zivoty = maxMana = mana = 5; utok = 3; }
        else if (v == 2) { jmenoClassy = "Lovec"; maxZivoty = zivoty = maxMana = mana = 4; utok = 4; }
        else if (v == 3) { jmenoClassy = "Mag"; maxZivoty = zivoty = 3; maxMana = mana = 6; utok = 2; }
        else if (v == 4) { jmenoClassy = "Warlock"; maxZivoty = zivoty = 4; maxMana = mana = 5; utok = 3; }
        else { cout << "Neplatna volba!\n"; continue; }

        vypisStaty();
        cout << "Potvrdit? (1=ano): "; cin >> v;
        if (v == 1) break;
    }
}

void pridejXP(int k) {
    xp += k;
    cout << "+" << k << " XP ";
    if (xp >= xpNaLevel) {
        level++; xp -= xpNaLevel; xpNaLevel += 5; maxZivoty++; utok++;
        cout << "LEVEL UP! Level " << level << ", HP+" << maxZivoty - 1 << "->" << maxZivoty << ", Utok+" << utok - 1 << "->" << utok;
    }
    cout << endl;
}

void vesnice() {
    cout << "\n=== VESNICE ===\nObchodnik: 'Vitej! Co si prejes?'\n";
    while (true) {
        cout << "1.Lecit(3z) 2.+maxHP(5z) 3.+maxMana(5z) 4.+Utok(5z) 5.Odejit | Zlato:" << zlato << "\n";
        int v; cin >> v;
        if (v == 1 && zlato >= 3) { zivoty = maxZivoty; mana = maxMana; zlato -= 3; cout << "Vylecen!\n"; }
        else if (v == 2 && zlato >= 5) { maxZivoty++; zlato -= 5; cout << "MaxHP: " << maxZivoty << "\n"; }
        else if (v == 3 && zlato >= 5) { maxMana++; zlato -= 5; cout << "MaxMana: " << maxMana << "\n"; }
        else if (v == 4 && zlato >= 5) { utok++; zlato -= 5; cout << "Utok: " << utok << "\n"; }
        else if (v == 5) break;
        else cout << "Nemas zlato/neplatna volba!\n";
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
        if (boss) { jmenoM[i] = "Pyrocoil"; maxZivotyM[i] = 40; }
        else if (miniboss) { jmenoM[i] = mbJmena[i % 2]; maxZivotyM[i] = 15 + rand() % 11; }
        else { jmenoM[i] = jmena[rand() % 16]; maxZivotyM[i] = 4 + rand() % 4; }
        zivotyM[i] = maxZivotyM[i];
    }

    bool hracTah = !(miniboss || boss);
    int kolo = 1;

    cout << "\n=== BOJ ===\nNepriatelia: ";
    for (int i = 0; i < pocet; i++) cout << jmenoM[i] << "(" << zivotyM[i] << "HP) ";
    cout << endl;

    while (zivoty > 0) {
        cout << "\n--- Kolo " << kolo++ << " ---\n";

        // Efekty na hraca
        if (hori) { zivoty -= 2; cout << "Horis! -2HP\n"; if (--horiKola <= 0) hori = false; }
        if (otraveny) { zivoty--; cout << "Otrava! -1HP\n"; if (--otravaKola <= 0) otraveny = false; }
        if (zivoty <= 0) break;

        if (hracTah) {
            vypisStaty();
            cout << "1.Utok 2.Schopnost: "; int v; cin >> v;

            if (v == 1) {
                cout << "Ciel(1-" << pocet << "): ";
                for (int i = 0; i < pocet; i++) if (zivotyM[i] > 0) cout << i + 1 << "." << jmenoM[i] << " ";
                cout << "\n"; int c; cin >> c; c--;
                if (c >= 0 && c < pocet && zivotyM[c] > 0) {
                    zivotyM[c] -= utok;
                    if (zivotyM[c] <= 0) zivotyM[c] = 0;
                    cout << "Zasah " << jmenoM[c] << " za " << utok << "!\n";
                }
            } else if (v == 2) {
                cout << "1.Spec1 2.Leceni: "; int s; cin >> s;
                if (s == 1) {
                    if (jmenoClassy == "Paladin" && mana >= 2) {
                        mana -= 2; cout << "Svetlo!\n";
                        for (int i = 0; i < pocet; i++) if (zivotyM[i] > 0) { zivotyM[i]--; cout << jmenoM[i] << " -1HP\n"; }
                    } else if (jmenoClassy == "Mag" && mana >= 3) {
                        cout << "Ciel: "; int c; cin >> c; c--;
                        if (c >= 0 && c < pocet && zivotyM[c] > 0) {
                            mana -= 3; horiM[c] = true; horiKolaM[c] = 3;
                            cout << jmenoM[c] << " hori!\n";
                        }
                    } else if (jmenoClassy == "Warlock" && mana >= 2) {
                        cout << "Ciel: "; int c; cin >> c; c--;
                        if (c >= 0 && c < pocet && zivotyM[c] > 0) {
                            mana -= 2; otravenyM[c] = true; otravaKolaM[c] = 3;
                            cout << jmenoM[c] << " otraveny!\n";
                        }
                    } else cout << "Malo many!\n";
                } else if (s == 2 && mana >= 1) {
                    mana--; if (zivoty < maxZivoty) zivoty++;
                    cout << "Lecenie! HP:" << zivoty << "\n";
                }
            }
        }

        // Nepriatelia utocia
        for (int i = 0; i < pocet; i++) {
            if (zivotyM[i] > 0) {
                if (horiM[i]) { zivotyM[i] -= 2; cout << jmenoM[i] << " hori -2HP\n"; if (--horiKolaM[i] <= 0) horiM[i] = false; }
                if (otravenyM[i]) { zivotyM[i]--; cout << jmenoM[i] << " otrava -1HP\n"; if (--otravaKolaM[i] <= 0) otravenyM[i] = false; }
                if (zivotyM[i] <= 0) { zivotyM[i] = 0; continue; }

                int dmg = 1 + rand() % 3;
                if (boss && kolo % 5 == 0) { cout << "PYROCOIL EXPLODUJE!\n"; dmg = 8; hori = true; horiKola = 3; }
                else if (miniboss) dmg += 2;

                zivoty -= dmg;
                cout << jmenoM[i] << ": -" << dmg << "HP (ty:" << zivoty << ")\n";
            }
        }

        hracTah = true;

        // Výhra?
        bool mrtvy = true;
        for (int i = 0; i < pocet; i++) if (zivotyM[i] > 0) mrtvy = false;

        if (mrtvy) {
            cout << "\nVYHRA!\n";
            for (int i = 0; i < pocet; i++) {
                if (boss) { pridejXP(20); zlato += 20; }
                else if (miniboss) { pridejXP(10); zlato += 10; }
                else { pridejXP(3); if (rand() % 2) zlato += 2 + rand() % 4; }
            }
            mana = min(maxMana, mana + 2);
            return;
        }
        if (zivoty <= 0) { cout << "\nPREHRA! Level:" << level << " Zlato:" << zlato << endl; exit(0); }
    }
}

void spustHru() {
    cout << "=== RPG PYROCOIL ===\nPoraz mocne stvorenie z ohne!\n";
    vyberClassy();

    // Mapa
    vesnice(); boj(1, 0, 0); boj(1, 0, 0); boj(2, 0, 0); boj(1, 1, 0);
    vesnice(); boj(1, 0, 0); boj(2, 0, 0); boj(2, 0, 0); boj(1, 1, 0);
    vesnice(); boj(2, 0, 0); boj(2, 0, 0); boj(3, 0, 0); vesnice(); boj(1, 0, 1);

    cout << "\n*** GRATULACIA! ***\nPorazil si Pyrocoila a zachranil krajinu!\n";
}

int main() {
    srand(time(0));
    spustHru();
    return 0;
}
