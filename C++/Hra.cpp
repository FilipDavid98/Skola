#include <iostream>
#include <string>
using namespace std;

string GetName() {
    string Name;
    string LikeName;
    bool WantName = false;
    
    while (!WantName) {
        cout << "Type Your Character Name: ";
        cin >> Name;
        cout << "You Chose The Name \"" << Name << "\". Are You Sure You Want To Use It?" << endl;
        cout << "Yes Or No: ";
        cin >> LikeName;
        
        if (LikeName == "Yes" || LikeName == "yes" || LikeName == "Y" || LikeName == "y") {
            WantName = true;
        } else {
            cout << "Let's Choose A Different Name Then." << endl;
        }
    }
    cout << "Perfect. " << Name << " Now Lets Choose Your Class" << endl << endl;
    return Name;
}

void Bob (){
    // manages to be good at everything and at the same time has his had in his ass. Its Just Bob
    // balanced HP MANA and ATTACK
}
void Karen (){
    // When she is in trouble she uses her too strong perfume to get rid of multiple enemies at once
    // Lower HP more MANA baalanced Base attack Powerfull ability
}
void Pebbles (){
    // Dont let the name fool you bebbles hat a little to much to eat but now he has natural armor
    // A lot of HP less MANA (has to work on his stamina) Lesser attack (to fat to reach far) lesser demage to enemies further away
}
void Big_Boy (){
    // acts tough and can give a pretty good puch but when he gets hit his ego cant take it
    // Does a lot o damage until Pebbles is guarding him once hes hit he does much smaller demage
    // Attack high MANA high until hes git and HP low
}


int main() {

    string Name = GetName();
    cout << "========================================================================================" << endl << endl;

    return 0;
}