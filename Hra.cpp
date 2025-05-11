#include <iostream>
#include <string>
#include <limits>
#include <cstdlib> // For system("cls") or system("clear")
#include <ctime>   // For random number generation
using namespace std;

// Global variables for player stats
string playerName = "Bob";
int playerHealth = 100;
int playerMaxHealth = 100;
int playerStamina = 100;
int playerMaxStamina = 100;
int playerAttack = 10;
int playerMoney = 50;
int playerLevel = 1;
string playerSpecialAbility = "None yet";

// Global variables for story progression
bool metPebbles = false;
bool metKaren = false;
bool metBigBoy = false;
bool defeatedPrinterGoblin = false;
bool defeatedCoffeeCultist = false;
bool defeatedSlackbots = false;
bool defeatedHRDemoness = false;
bool defeatedCorporateDrone = false;
bool defeatedUnpaidInterns = false;
bool defeatedLinkedInKnights = false;
bool defeatedVPCheryl = false;
int healingCoffee = 3;
bool hasHRBadge = false;

// Forward declarations of functions
void ClearScreen();
void WaitForEnter();
void DisplayStoryText(const string &text);
void DisplayPlayerStats();
void LevelUp();
void UseHealingCoffee();
void UseSpecialAbility();
bool Battle(string enemyName, int enemyHealth, int enemyAttack, bool isBoss = false);
void MeetPebbles();
void MeetKaren();
void MeetBigBoy();
void PlayIntro();
void PrinterGoblinEncounter();
void CoffeeCultistEncounter();
void SlackbotEncounter();
void HRDemonessEncounter();
void CorporateDroneEncounter();
void UnpaidInternsEncounter();
void LinkedInKnightsEncounter();
void VPCherylEncounter();
void CheckGameProgress();
void GameLoop();
void ShowMainMenu();
void ShowMap();
void Shop();

// Function to clear screen (platform-dependent)
void ClearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to pause and wait for Enter key
void WaitForEnter() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to display story text with pauses
void DisplayStoryText(const string &text) {
    cout << text << endl;
    WaitForEnter();
}

// Function to display player stats
void DisplayPlayerStats() {
    cout << "\n===================================" << endl;
    cout << "Player Stats:" << endl;
    cout << "===================================" << endl;
    cout << "Name: " << playerName << endl;
    cout << "Level: " << playerLevel << endl;
    cout << "Health: " << playerHealth << "/" << playerMaxHealth << endl;
    cout << "Stamina: " << playerStamina << "/" << playerMaxStamina << endl;
    cout << "Attack: " << playerAttack << endl;
    cout << "Money: $" << playerMoney << endl;
    cout << "Special Ability: " << playerSpecialAbility << endl;
    if (healingCoffee > 0) {
        cout << "Healing Coffee: " << healingCoffee << " thermos" << endl;
    }
    if (hasHRBadge) {
        cout << "Items: HR Badge" << endl;
    }
    cout << "===================================" << endl << endl;
}

// Function to level up the player
void LevelUp() {
    playerLevel++;
    playerMaxHealth += 10;
    playerMaxStamina += 10;
    playerAttack += 2;
    
    // Restore health and stamina on level up
    playerHealth = playerMaxHealth;
    playerStamina = playerMaxStamina;
    
    // Bonus money for leveling up
    playerMoney += playerLevel * 20;
    
    cout << "\nCongratulations! You leveled up to level " << playerLevel << "!" << endl;
    cout << "Stats increased and health/stamina restored!" << endl;
    cout << "You received $" << (playerLevel * 20) << " as a level-up bonus!" << endl;
}

// Function to use healing coffee
void UseHealingCoffee() {
    if (healingCoffee <= 0) {
        cout << "You don't have any healing coffee left!" << endl;
        return;
    }
    
    int healAmount = 30;
    int oldHealth = playerHealth;
    playerHealth = min(playerMaxHealth, playerHealth + healAmount);
    healingCoffee--;
    
    cout << "You drink some healing coffee." << endl;
    cout << "Restored " << (playerHealth - oldHealth) << " health!" << endl;
    cout << "You have " << healingCoffee << " thermos of healing coffee left." << endl;
}

// Function to use special ability
void UseSpecialAbility() {
    int staminaCost = 30;
    
    if (playerStamina < staminaCost) {
        cout << "Not enough stamina to use special ability!" << endl;
        return;
    }
    
    playerStamina -= staminaCost;
    
    if (playerSpecialAbility == "None yet") {
        cout << "You don't have a special ability yet!" << endl;
    }
    else if (playerSpecialAbility == "Jack of All Trades") {
        cout << "You use Jack of All Trades!" << endl;
        cout << "All stats temporarily increased by 5!" << endl;
        playerAttack += 5; // This would normally be temporary
    }
    else if (playerSpecialAbility == "Manager Summoner") {
        cout << "You use Manager Summoner!" << endl;
        cout << "Releasing powerful perfume to stun all enemies!" << endl;
        // In a real battle system, this would stun enemies
    }
    else if (playerSpecialAbility == "Natural Armor") {
        cout << "You use Natural Armor!" << endl;
        cout << "Damage reduction increased to 30%!" << endl;
        // In a real battle system, this would reduce damage
    }
    else if (playerSpecialAbility == "Glass Ego") {
        cout << "You use Glass Ego!" << endl;
        cout << "Dealing massive damage this turn!" << endl;
        playerAttack += 10; // This would normally be temporary
    }
}

// Function for simple turn-based battle
bool Battle(string enemyName, int enemyHealth, int enemyAttack, bool isBoss) {
    int playerCurrentHealth = playerHealth;
    int enemyCurrentHealth = enemyHealth;
    
    cout << "\n[BATTLE BEGINS]" << endl;
    cout << "You face off against " << enemyName << "!" << endl;
    
    while (playerCurrentHealth > 0 && enemyCurrentHealth > 0) {
        // Display battle status
        cout << "\n----------------------------------" << endl;
        cout << playerName << ": " << playerCurrentHealth << "/" << playerMaxHealth << " HP" << endl;
        cout << enemyName << ": " << enemyCurrentHealth << "/" << enemyHealth << " HP" << endl;
        cout << "----------------------------------" << endl;
        
        // Player's turn
        cout << "\nYour turn! What will you do?" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Use Special Ability" << endl;
        cout << "3. Drink Healing Coffee (" << healingCoffee << " left)" << endl;
        
        int choice;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer
        
        switch (choice) {
            case 1: {
                // Basic attack
                int damage = playerAttack + (rand() % 5); // Base damage + random 0-4
                enemyCurrentHealth -= damage;
                cout << "You attack " << enemyName << " for " << damage << " damage!" << endl;
                break;
            }
            case 2: {
                // Use special ability
                if (playerSpecialAbility == "None yet") {
                    cout << "You don't have a special ability yet!" << endl;
                    continue;
                }
                
                int staminaCost = 30;
                if (playerStamina < staminaCost) {
                    cout << "Not enough stamina to use special ability!" << endl;
                    continue;
                }
                
                playerStamina -= staminaCost;
                
                if (playerSpecialAbility == "Jack of All Trades") {
                    cout << "You use Jack of All Trades!" << endl;
                    cout << "All stats temporarily increased by 5!" << endl;
                    int damage = (playerAttack + 5) + (rand() % 5);
                    enemyCurrentHealth -= damage;
                    cout << "You attack " << enemyName << " for " << damage << " damage!" << endl;
                }
                else if (playerSpecialAbility == "Manager Summoner") {
                    cout << "You use Manager Summoner!" << endl;
                    cout << "Releasing powerful perfume to stun all enemies!" << endl;
                    int damage = (playerAttack * 2) + (rand() % 10);
                    enemyCurrentHealth -= damage;
                    cout << "You deal " << damage << " area damage to " << enemyName << "!" << endl;
                }
                else if (playerSpecialAbility == "Natural Armor") {
                    cout << "You use Natural Armor!" << endl;
                    cout << "Damage reduction increased to 30%!" << endl;
                    int damage = playerAttack + (rand() % 5);
                    enemyCurrentHealth -= damage;
                    cout << "You attack " << enemyName << " for " << damage << " damage while protected!" << endl;
                }
                else if (playerSpecialAbility == "Glass Ego") {
                    cout << "You use Glass Ego!" << endl;
                    cout << "Dealing massive damage this turn!" << endl;
                    int damage = (playerAttack * 1.5) + (rand() % 15);
                    enemyCurrentHealth -= damage;
                    cout << "You deal " << damage << " massive damage to " << enemyName << "!" << endl;
                }
                break;
            }
            case 3: {
                // Use healing coffee
                if (healingCoffee <= 0) {
                    cout << "You don't have any healing coffee left!" << endl;
                    continue;
                }
                
                int healAmount = 30;
                int oldHealth = playerCurrentHealth;
                playerCurrentHealth = min(playerMaxHealth, playerCurrentHealth + healAmount);
                healingCoffee--;
                
                cout << "You drink some healing coffee." << endl;
                cout << "Restored " << (playerCurrentHealth - oldHealth) << " health!" << endl;
                cout << "You have " << healingCoffee << " thermos of healing coffee left." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Try again." << endl;
                continue;
        }
        
        // Check if enemy is defeated
        if (enemyCurrentHealth <= 0) {
            cout << "\nYou defeated " << enemyName << "!" << endl;
            
            // Reward for winning
            int moneyGained = isBoss ? 100 : 50;
            playerMoney += moneyGained;
            cout << "You gained $" << moneyGained << "!" << endl;
            
            // Update player health after battle
            playerHealth = playerCurrentHealth;
            return true;
        }
        
        // Enemy's turn
        cout << "\n" << enemyName << "'s turn!" << endl;
        int enemyDamage = enemyAttack + (rand() % 3); // Base damage + random 0-2
        
        // Check if player has Natural Armor
        if (playerSpecialAbility == "Natural Armor") {
            enemyDamage = static_cast<int>(enemyDamage * 0.7); // 30% damage reduction
            cout << "Your Natural Armor reduces the damage!" << endl;
        }
        
        playerCurrentHealth -= enemyDamage;
        cout << enemyName << " attacks you for " << enemyDamage << " damage!" << endl;
        
        // Check if player is defeated
        if (playerCurrentHealth <= 0) {
            cout << "\nYou were defeated by " << enemyName << "!" << endl;
            playerHealth = max(1, playerMaxHealth / 2); // Restore half health after defeat
            cout << "You wake up later with " << playerHealth << " health." << endl;
            return false;
        }
    }
    
    return false; // Should never reach here
}

// Function to meet Pebbles
void MeetPebbles() {
    if (!metPebbles) {
        DisplayStoryText("[Location: Secret Hideout: Copy Room]\nYou step into the dimly lit copy room, the hum of ancient copiers buzzing like distant war drums. Papers litter the floor, and old toner stains line the walls. This isn't just any office—it's a rebel outpost. A man the size of a vending machine stands beside you, his arms crossed. He looks like he's been fighting this corporate war for years.");
        
        DisplayStoryText("PEBBLES:\n\"They took my break room... now I take theirs.\"");
        
        DisplayStoryText("You raise an eyebrow, scanning the cluttered room.\n\nYou:\n\"We're gonna need more than your size to take down this corporate behemoth.\"");
        
        DisplayStoryText("Pebbles grins, a glint of mischief in his eyes.\n\nPEBBLES:\n\"Don't worry, Bob. I'm packing more than just muscle.\"\n(He pulls out a sandwich that looks suspiciously... strategic.)\n\"Here's the plan: I eat this, we win.\"");
        
        DisplayStoryText("You stare at the sandwich, unsure if this is genius or madness.\n\nYou:\n\"What's in the sandwich?\"");
        
        DisplayStoryText("PEBBLES:\n\"The power of victory, my friend. Now, you get ready to heal up or upgrade—because we're going in hot!\"");
        
        cout << "\nPebbles joins your party!" << endl;
        
        cout << "\nPebbles' Stats:" << endl;
        cout << "Health: 150" << endl;
        cout << "Stamina: 70" << endl;
        cout << "Attack: 7" << endl;
        cout << "Money: $30" << endl;
        cout << "Special Ability: Natural Armor" << endl;
        cout << "Description: Reduces incoming damage by 30% due to natural padding." << endl;
        
        metPebbles = true;
        
        // Option to learn Pebbles' special ability
        char choice;
        cout << "\nDo you want to learn Pebbles' special ability? (Y/N): ";
        cin >> choice;
        cin.ignore(); // Clear input buffer
        
        if (choice == 'Y' || choice == 'y') {
            playerSpecialAbility = "Natural Armor";
            cout << "You learned Pebbles' special ability: Natural Armor!" << endl;
            cout << "You now take 30% less damage from attacks!" << endl;
            
            // Increase player's max health to reflect the natural armor ability
            playerMaxHealth += 30;
            playerHealth += 30;
            cout << "Your maximum health increased to " << playerMaxHealth << "!" << endl;
        }
        
        // Pebbles shares some snacks that restore health
        int healthRestored = 20;
        playerHealth = min(playerMaxHealth, playerHealth + healthRestored);
        cout << "Pebbles shares some snacks with you. You restored " << healthRestored << " health!" << endl;
    } else {
        cout << "Pebbles is already in your party." << endl;
    }
}

// Function to meet Karen
void MeetKaren() {
    if (!metKaren) {
        DisplayStoryText("You encounter Karen in the hallway. She's wearing an excessive amount of perfume and looks ready to complain to management.");
        
        DisplayStoryText("KAREN:\n\"Excuse me! I need to speak to whoever's in charge here!\"");
        
        DisplayStoryText("You:\n\"Karen, I think we're on the same side here. We're both trying to take down this corporate mess.\"");
        
        DisplayStoryText("KAREN:\n\"Well, I'll have you know I've been writing strongly worded emails for YEARS! And my perfume is a secret weapon!\"");
        
        cout << "\nKaren joins your party!" << endl;
        
        cout << "\nKaren's Stats:" << endl;
        cout << "Health: 80" << endl;
        cout << "Stamina: 120" << endl;
        cout << "Attack: 10" << endl;
        cout << "Money: $100" << endl;
        cout << "Special Ability: Manager Summoner" << endl;
        cout << "Description: Releases a powerful perfume that stuns multiple enemies at once." << endl;
        
        metKaren = true;
        
        // Option to learn Karen's special ability
        char choice;
        cout << "\nDo you want to learn Karen's special ability? (Y/N): ";
        cin >> choice;
        cin.ignore(); // Clear input buffer
        
        if (choice == 'Y' || choice == 'y') {
            playerSpecialAbility = "Manager Summoner";
            cout << "You learned Karen's special ability: Manager Summoner!" << endl;
            cout << "You can now stun multiple enemies with powerful perfume!" << endl;
        }
        
        // Karen gives you some money
        playerMoney += 50;
        cout << "Karen gives you $50. Your money increased to $" << playerMoney << "!" << endl;
    } else {
        cout << "Karen is already in your party." << endl;
    }
}

// Function to meet Big Boy
void MeetBigBoy() {
    if (!metBigBoy) {
        DisplayStoryText("You encounter Big Boy in the executive lounge. He looks like he's ready to take on the whole company.");
        
        DisplayStoryText("BIG BOY:\n\"They call me Big Boy for a reason! No one hits harder than me!\"");
        
        DisplayStoryText("You:\n\"We could use someone with your... confidence.\"");
        
        DisplayStoryText("BIG BOY:\n\"Confidence? I've got skills to back it up! Watch me take down this whole place!\"");
        
        cout << "\nBig Boy joins your party!" << endl;
        
        cout << "\nBig Boy's Stats:" << endl;
        cout << "Health: 70" << endl;
        cout << "Stamina: 110" << endl;
        cout << "Attack: 15" << endl;
        cout << "Money: $65" << endl;
        cout << "Special Ability: Glass Ego" << endl;
        cout << "Description: Deals massive damage until hit, then attack drops until healed." << endl;
        
        metBigBoy = true;
        
        // Option to learn Big Boy's special ability
        char choice;
        cout << "\nDo you want to learn Big Boy's special ability? (Y/N): ";
        cin >> choice;
        cin.ignore(); // Clear input buffer
        
        if (choice == 'Y' || choice == 'y') {
            playerSpecialAbility = "Glass Ego";
            cout << "You learned Big Boy's special ability: Glass Ego!" << endl;
            cout << "You now deal massive damage until you get hit!" << endl;
            
            // Increase player's attack to reflect the Glass Ego ability
            playerAttack += 5;
            cout << "Your attack increased to " << playerAttack << "!" << endl;
        }
        
        // Big Boy teaches you a fighting technique
        playerAttack += 2;
        cout << "Big Boy teaches you a new fighting technique. Your attack increased by 2!" << endl;
    } else {
        cout << "Big Boy is already in your party." << endl;
    }
}

// Function to play Intro
void PlayIntro() {
    ClearScreen();
    
    cout << "CORPORATE LADDER TO HEAVEN" << endl;
    cout << "You are BOB. Just... Bob." << endl;
    cout << "An average employee in a soul-crushing mega-corp that stretches across Earth." << endl;
    cout << "One day, after being passed over for promotion by a guy who can't even spell \"Excel,\" something in you snaps." << endl;
    cout << "You will rise — not up the corporate ladder, but through it." << endl;
    cout << "Coworkers, HR demons, soulless executives..." << endl;
    cout << "And if needed, you'll kill the CEO of Earth himself." << endl;
    cout << "Heaven help you. Because he won't." << endl;
    
    WaitForEnter();
    ClearScreen();
    
    DisplayStoryText("[Location: Break Room – Smells like burnt coffee and lost dreams.]\nYou jolt awake in the corner of the break room.\nYour badge is gone. Your dignity is questionable.\nAcross from you stands an old janitor with glowing eyes.");
    
    DisplayStoryText("JANITOR:\n\"The system is broken, kid... but you can break it first.\"");
    
    healingCoffee = 3;
    cout << "[You receive a thermos of Healing Coffee (+HP).]" << endl;
    cout << "You now have " << healingCoffee << " uses of Healing Coffee." << endl;
    
    WaitForEnter();
}

// Function for Printer Goblin Encounter
void PrinterGoblinEncounter() {
    if (!defeatedPrinterGoblin) {
        DisplayStoryText("[Location: Copy Area]\nYou step into the dim hallway, the hum of flickering fluorescent lights echoing in the stillness. The air feels heavy, thick with an unsettling silence. Then, a faint noise shatters the quiet. A soft scratching. A rhythmic clicking. Something is near.");
        
        DisplayStoryText("You turn the corner and—\nA creature emerges from the shadows, its fingers stained with toner, twitching erratically. Its eyes gleam with a cold, mechanical light. A screech cuts through the air, sharp and jarring.");
        
        DisplayStoryText("Enemy: PRINTER GOBLIN\n\"NO PRINT FOR YOU!\"");
        
        DisplayStoryText("You raise an eyebrow, unfazed.\nYou: \"I don't even want a print.\"");
        
        DisplayStoryText("The Printer Goblin sneers, its jagged mouth creaking open like a malfunctioning printer.\nEnemy: \"Of course YOU don't.\"");
        
        DisplayStoryText("With a hiss, it lunges at you, flinging broken paper trays and shredded documents like makeshift weapons. Its movements are erratic, like a malfunctioning machine desperate for a fix.");
        
        bool victory = Battle("Printer Goblin", 40, 5, false);
        
        if (victory) {
            DisplayStoryText("The Printer Goblin stumbles back, sparks flying from its torn wires. It snarls in frustration, its limbs twitching spasmodically.");
            
            DisplayStoryText("Printer Goblin: \"Curse you! No one beats me... not... not even in the printer room...\"");
            
            DisplayStoryText("It crumples into a pile of malfunctioning gears and scraps, its glowing eyes dimming to nothingness. You step over the mess, unscathed.");
            
            DisplayStoryText("You: \"Next time, don't mess with someone who's on a paperless mission.\"");
            
            defeatedPrinterGoblin = true;
        } else {
            DisplayStoryText("The Printer Goblin grins wickedly, its jagged mouth stretching wider as it flings more paper shrapnel in your direction. The last thing you hear before everything goes dark is the screeching sound of an error message.");
            
            DisplayStoryText("Printer Goblin: \"No print for you... ever again.\"");
            
            DisplayStoryText("Your vision fades, the only thing left in your mind the cold mechanical laughter of your foe.");
            
            DisplayStoryText("You wake up later, determined to try again...");
        }
    } else {
        cout << "You've already defeated the Printer Goblin." << endl;
    }
}