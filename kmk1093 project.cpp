//ADAPTIVE MEMORY AND REACTION TIME TEST
//G5 KMK1093
//Lecturer: Dr. Norhasmira binti Mohammad
//Group members:
//(109155) Azrif bin Ibrahim
//(109438) Cloudia Madelina Anak Maju
//(111229) Nataliea Lanus
//(112098) Queenchel Joseph
//(108556) Syukrin Hani binti Mohd Abd Nasir

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <windows.h>
#include <cstdlib> 
#include <algorithm>
#include <fstream>

using namespace std;
using namespace std::chrono;

struct Player {
    string name;
    double avgTime = 0;
    double totalTime = 0;
};

//saving result to file to leaderboard
void saveResult(string filename, string name, double avg) {
    ofstream outFile(filename, ios::app); 
    if (outFile.is_open()) {
        outFile << name << " " << avg << endl;
        outFile.close();
    }
}

void showLeaderboard(string filename, string title) {
    system("cls");
    ifstream inFile(filename);
    vector<Player> board;
    Player temp;

    if (inFile.is_open()) {
        while (inFile >> temp.name >> temp.avgTime) {
            board.push_back(temp);
        }
        inFile.close();
    }

    sort(board.begin(), board.end(), [](const Player &a, const Player &b) {
        return a.avgTime < b.avgTime;
    });

    cout << "=== " << title << " LEADERBOARD ===\n";
    cout << "Rank\tName\t\t\tAverage Time\n";
    cout << "-------------------------------------------------\n";
    
    if (board.empty()) {
        cout << "No records found for this mode yet.\n";
    } else {
        for (int i = 0; i < board.size(); i++) {
            string displayName = board[i].name;
            size_t pos = displayName.find('&');
            
            cout << i + 1 << ".\t" << displayName << "\t\t" << board[i].avgTime << "s" << endl;
        }
    }
    cout << "\nPress any key to return...";
    system("pause > nul");
}

void manageProfiles(string filename) {
    system("cls");
    vector<Player> board;
    
    {
        ifstream inFile(filename);
        Player temp;
        if (inFile.is_open()) {
            while (inFile >> temp.name >> temp.avgTime) {
                board.push_back(temp);
            }
            inFile.close();
        }
    }

    if (board.empty()) {
        cout << "Error: " << filename << " is empty or not found!\n";
        Sleep(1500);
        return;
    }

    cout << "=== PROFILE MANAGEMENT (" << filename << ") ===\n";
    cout << "1. Edit Profile\n2. Delete Record\nChoice: ";
    int choice; cin >> choice;
    
    string target;
    
    //hard mode
    if (filename == "hard.txt") {
        string p1, p2;
        cout << "Enter Player 1 Name: ";
		cin >> p1;
        cout << "Enter Player 2 Name: ";
		cin >> p2;
        target = p1 + "&" + p2;
    } else {
        cout << "Enter Player Name: ";
		cin >> target;
    }

    bool found = false;
    for (int i = 0; i < board.size(); i++) {
        if (board[i].name == target) {
            found = true;
            if (choice == 1) {
                if (filename == "hard.txt") {
                    string newP1, newP2;
                    cout << "Match found! Enter NEW Player 1: ";
					cin >> newP1;
                    cout << "Enter NEW Player 2: ";
					cin >> newP2;
                    board[i].name = newP1 + "&" + newP2;
                } else {
                    cout << "Match found! Enter NEW name: ";
                    cin >> board[i].name;
                }
            } else if (choice == 2) {
                cout << "Deleting record for " << board[i].name << "...\n";
                board.erase(board.begin() + i);
            }
            break;
        }
    }

    //save clean data
    if (found) {
        ofstream outFile(filename, ios::out | ios::trunc); 
        if (outFile.is_open()) {
            for (const auto &p : board) {
                outFile << p.name << " " << p.avgTime << "\n";
            }
            outFile.flush();
            outFile.close();
            cout << "\nSUCCESS: File updated!\n";
        }
    } else {
        cout << "\nNOT FOUND: Could not find " << target << " in " << filename << endl;
        cout << "Hint: Ensure names are in the same order as when you played.\n";
    }
    
    cout << "Returning to menu...";
    Sleep(2500);
}

void resetSystem() {
    system("color 07");
    system("cls");
}

void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//test functions
double askRetype(string word, double limit, int mode) {
    string input;
    int tries = 0;
    double totalElapsed = 0;
    // set time limit: 700ms (0.7s) for medium, 1500ms (1.5s) for hard
	int waitTime = (mode == 1) ? 700 : 1500;
	
    system("cls");
    cout << "\nMEMORIZE THIS WORD:\n\n--- " << word << " ---" << endl;
    Sleep(waitTime);

    system("cls");

    while (tries < 3) {
        cout << "Type the word you just saw: ";
        auto start = steady_clock::now();
        cin >> input;
        auto end = steady_clock::now();
        totalElapsed += duration<double>(end - start).count();

        if (input == word) {
            cout << "CORRECT!" << endl;
            Sleep(600);
            break; 
        } else {
            tries++;
            if (tries < 3) cout << "WRONG! Try again." << endl;
            else totalElapsed += 5.0;
        }
    }
    return totalElapsed;
}

double askScramble(string correct, string scrambled, double limit, int mode) {
    string input;
    int tries = 0;
    double totalElapsed = 0;
    // set time limit: 3000ms (3s) for medium, 7000ms (7s) for hard
	int waitTime = (mode == 1) ? 3000 : 7000;

    system("color 07");
    system("cls");

    cout << "\n====== MEMORIZE THIS SENTENCE ======" << endl;
    cout << "\nCORRECT: " << correct << endl;
    Sleep(waitTime);
    system("cls");

    while (tries < 3) {
        cout << "\n====== REARRANGE THESE WORDS ======" << endl;
        cout << "\nSCRAMBLED: " << scrambled << endl;
        cout << "\nAttempt: " << tries + 1 << "/3" << endl;
        cout << "Your Answer: ";
        auto start = steady_clock::now();
        getline(cin, input);
        auto end = steady_clock::now();
        duration<double> elapsed = end - start;
        totalElapsed += elapsed.count();

        if (input == correct) {
            cout << "\nCORRECT!" << endl;
            Sleep(800);
            break; 
        } else {
            tries++;
            if (tries < 3) {
            	cout << "WRONG! Try again." << endl;
			}
            else {
                cout << "FAILED. The correct answer was: " << correct << endl;
                totalElapsed += 5.0;
                Sleep(2000);
            }
        }
    }
    return totalElapsed;
}

double askStroop(string word, int colorCode, string answer, double limit, int mode) {
    string input;
    int tries = 0;
    double totalElapsed = 0;
    // set time limit: 1000ms (1s) for medium, 700ms (0.7s) for hard
    int waitTime = (mode == 1) ? 1000 : 700;

    while (tries < 3) {
        resetSystem();
        cout << "\n====== MEMORIZE THE COLOR ======\n\n>> ";
        setTextColor(colorCode); 
        cout << word << endl;
        setTextColor(7);
        
        Sleep(waitTime);
		
        system("cls");

        cout << "\nAttempt: " << tries + 1 << "/3\nWhat was the COLOR?\nYour Answer: ";
        auto start = steady_clock::now();
        cin >> input;
        auto end = steady_clock::now();
        totalElapsed += duration<double>(end - start).count();

        transform(input.begin(), input.end(), input.begin(), ::tolower);
		
        if (input == answer) {
            cout << "\nCORRECT!" << endl;
            Sleep(600);
            break; 
        } else {
            tries++;
            if (tries < 3) { cout << "WRONG!\n"; Sleep(800); }
            else { cout << "FAILED. Answer: " << answer << endl; totalElapsed += 5.0; Sleep(1500); }
        }
    }
    return totalElapsed;
}

void startTest(Player &p, int mode, double limit) {
    p.totalTime = 0;
    
    //test 1: retype shown word
    system("cls");
	cout << "==========================================" << endl;
	cout << "        SECTION 1: WORD RETYPE           " << endl;
	cout << "==========================================" << endl;
	cout << "INSTRUCTIONS:" << endl;
	cout << "1. A word will appear on the screen." << endl;
	cout << "2. Once it disappears, type the word exactly." << endl;
	cout << "\nTIP: Watch for capitalization and spelling!" << endl;
	cout << "==========================================" << endl;
	cout << "\nPress any key to answer the test..." << endl;
    system("pause > nul");
    if (mode == 1) {
    	p.totalTime += askRetype("Concept", limit, mode);
    	p.totalTime += askRetype("Amature", limit, mode);
    	p.totalTime += askRetype("Principle", limit, mode);
    	p.totalTime += askRetype("Barbecue", limit, mode);
    	p.totalTime += askRetype("Morrow", limit, mode);
    	p.totalTime += askRetype("Morquee", limit, mode);
    	p.totalTime += askRetype("Definitely", limit, mode);
    	p.totalTime += askRetype("Beautiful", limit, mode);
    	p.totalTime += askRetype("Government", limit, mode);
    	p.totalTime += askRetype("Environment", limit, mode);
	}
    else {
    	p.totalTime += askRetype("Serendipity", limit, mode);
    	p.totalTime += askRetype("Apricity", limit, mode);
    	p.totalTime += askRetype("Mellifluous", limit, mode);
    	p.totalTime += askRetype("Petrichor", limit, mode);
    	p.totalTime += askRetype("Effervescent", limit, mode);
    	p.totalTime += askRetype("Ephemeral", limit, mode);
    	p.totalTime += askRetype("Limerence", limit, mode);
    	p.totalTime += askRetype("Evanescent", limit, mode);
    	p.totalTime += askRetype("Susurrus", limit, mode);
    	p.totalTime += askRetype("Quiescent", limit, mode);
	}
    
    //test 2: rearrange words in sentence
    system("cls");
	cout << "==========================================" << endl;
	cout << "        SECTION 2: SENTENCE SCRAMBLE      " << endl;
	cout << "==========================================" << endl;
	cout << "INSTRUCTIONS:" << endl;
	cout << "1. You will see a correct sentence first." << endl;
	cout << "2. Then, the words will be mixed up (scrambled)." << endl;
	cout << "3. Rearrange them to form the original sentence." << endl;
	cout << "\nTIP: Watch out for the capitalization and spelling.\nUse spaces between words correctly!" << endl;
	cout << "==========================================" << endl;
	cout << "\nPress any key to answer the test..." << endl;
    system("pause > nul");
	
	cin.ignore(100, '\n'); //debug: to enter the next screen directly after clearing using system("cls")
	
    if (mode == 1) {
    	p.totalTime += askScramble("I like yellow balloons", "balloons - like - I - yellow", limit, mode); 
    	p.totalTime += askScramble("Red is my favourite colour", "favourite - is - Red - my - colour", limit, mode); 
    	p.totalTime += askScramble("The big tree is green", "big - green - The - is - tree", limit, mode);
    	p.totalTime += askScramble("The bright sun is yellow", "sun - yellow - bright - is - The", limit, mode);
    	p.totalTime += askScramble("The fresh milk is white", "is - white - fresh - The - milk", limit, mode);
    	p.totalTime += askScramble("The orange juice is sour", "orange - The - juice - sour - is", limit, mode);
    	p.totalTime += askScramble("The soil is wet and brown", "wet - soil - brown - The - and - is", limit, mode);
    	p.totalTime += askScramble("The purple dress is beautiful", "beautiful - purple - dress - is - The", limit, mode);
    	p.totalTime += askScramble("The small cat is black", "small - black - The - cat - is", limit, mode);
    	p.totalTime += askScramble("That house is big", "house - big - is - That", limit, mode);
	}
    else {
    	p.totalTime += askScramble("The old man with a cane walks slowly across the busy street", "slowly - walks - cane - The - across - busy -\nstreet - man - old - with - a", limit, mode);
    	p.totalTime += askScramble("The children are playing happily in the colourful playground near the school", "playground - colorful - The - near -\nhappily - are - children - in - playing - the - school", limit, mode);
    	p.totalTime += askScramble("My sister always drinks hot chocolate before going to bed at night", "hot - drinks - chocolate - going - sister -\nbefore - bed - always - My - to - at - night", limit, mode);
    	p.totalTime += askScramble("The teacher gave us a difficult assignment about environmental pollution", "assignment - difficult - a - gave - teacher -\npollution - about - environmental - The", limit, mode);
    	p.totalTime += askScramble("They watched a scary movie together during\nthe thunderstorm last weekend", "thunderstorm - watched - scary - last - weekend -\ntogether - the - during - movie - a - They", limit, mode);
    	p.totalTime += askScramble("The little puppy sleeps soundly beside the\nwarm fireplace every evening", "beside - puppy - fireplace - warm - The - sleeps -\nlittle - every - evening - soundly", limit, mode);
    	p.totalTime += askScramble("We are planning a surprise birthday party\nfor our best friend tomorrow", "tommorow - surprise - birthday - party - planning -\nbest - our - for - We - are - friend - a", limit, mode);
    	p.totalTime += askScramble("The students listened carefully to the\ninstructions before starting the experiment", "carefully - students - experiment - The -\nlistened - instructions - before - starting - to - the", limit, mode);
    	p.totalTime += askScramble("She bought a beautiful necklace from the\nmarket while visiting her aunt", "market - necklace - visiting - her - while - bought -\nfrom - beautiful - She - the - a - aunt", limit, mode);
    	p.totalTime += askScramble("The chef prepared a delicious meal using\nfresh ingredients from the garden", "garden - prepared - chef - The - ingredients -\nusing - fresh - from - meal - delicious - a", limit, mode);
	}
    
    //test 3: the stroop effect
    system("cls");
	cout << "==========================================" << endl;
	cout << "        SECTION 3: THE STROOP EFFECT      " << endl;
	cout << "==========================================" << endl;
	cout << "INSTRUCTIONS:" << endl;
	cout << "1. A color name will appear (e.g., 'BLUE')." << endl;
	cout << "2. The word will be printed in a DIFFERENT color." << endl;
	cout << "3. Ignore the text! Memorize the VISUAL COLOR." << endl;
	cout << "4. Type the name of the color you SAW." << endl;
	cout << "\nExample: If you see 'RED' printed in Blue, type 'BLUE'." << endl;
	cout << "\n\n...Psst! This section focuses on The Stroop Effect\nin Cognitive Psychology!" << endl;
	cout << "==========================================" << endl;
	cout << "\nPress any key to answer the test..." << endl;
    system("pause > nul");
    if (mode == 1) {
        p.totalTime += askStroop("BLUE", 4, "red", limit, mode);
        p.totalTime += askStroop("RED", 5, "purple", limit, mode);
        p.totalTime += askStroop("GREEN", 13, "pink", limit, mode);
        p.totalTime += askStroop("PURPLE", 14, "yellow", limit, mode);
        p.totalTime += askStroop("BROWN", 4, "red", limit, mode);
        p.totalTime += askStroop("BLACK", 10, "green", limit, mode);
        p.totalTime += askStroop("YELLOW", 1, "blue", limit, mode);
        p.totalTime += askStroop("DARK BLUE", 8, "gray", limit, mode);
        p.totalTime += askStroop("PINK", 14, "yellow", limit, mode);
        p.totalTime += askStroop("GRAY", 5, "purple", limit, mode);
    } else {
        p.totalTime += askStroop("YELOW", 5, "purple", limit, mode);
        p.totalTime += askStroop("BROWN", 4, "red", limit, mode);
        p.totalTime += askStroop("GREEN", 14, "yellow", limit, mode);
        p.totalTime += askStroop("WHITE", 13, "pink", limit, mode);
        p.totalTime += askStroop("RED", 10, "green", limit, mode);
        p.totalTime += askStroop("BLACK", 4, "red", limit, mode);
        p.totalTime += askStroop("PURPLE", 8, "gray", limit, mode);
        p.totalTime += askStroop("GREEN", 1, "blue", limit, mode);
        p.totalTime += askStroop("BROWN", 5, "purple", limit, mode);
        p.totalTime += askStroop("GRAY", 14, "yellow", limit, mode);
    }
    
    p.avgTime = p.totalTime / 30.0;
}

int main() {
    int mainChoice;
    while (true) {
        resetSystem();
        cout << "=== ADAPTIVE MEMORY AND REACTION TIME TEST ===\n";
        cout << "1. Medium Mode\n2. Hard Mode\n3. View Leaderboards\n4. Manage Profiles\n5. Exit\nChoice: ";
        cin >> mainChoice;

        if (mainChoice == 5) break; //exit game
        
        //view leaderboard (medium/hard)
        if (mainChoice == 3) {
            cout << "\n1. Medium Leaderboard\n2. Hard Leaderboard\nChoice: ";
            int lbChoice;
			cin >> lbChoice;
            if (lbChoice == 1) showLeaderboard("medium.txt", "MEDIUM");
            else showLeaderboard("hard.txt", "HARD");
            continue;
        }

        //manage profiles (medium/hard)
        if (mainChoice == 4) {
		cout << "\nWhich file to edit?\n1. Medium\n2. Hard\nChoice: ";
		int edChoice;
		cin >> edChoice;
		
		if (edChoice == 1) {
			manageProfiles("medium.txt");
		} else {
			manageProfiles("hard.txt");
		}
        
		continue;
		}
		
		//start test
        if (mainChoice == 1 || mainChoice == 2) {
            Player p1;
            string p2Name, finalSaveName;
            
            if (mainChoice == 2) {
                cout << "Enter Player 1: ";
				cin >> p1.name;
                cout << "Enter Player 2: ";
				cin >> p2Name;
                finalSaveName = p1.name + "&" + p2Name; 
            } else {
                cout << "Enter Player Name: ";
				cin >> p1.name;
                finalSaveName = p1.name;
            }

            startTest(p1, mainChoice, 4.0);

            //save to specific files (medium/hard)
            if (mainChoice == 1) {
            	saveResult("medium.txt", finalSaveName, p1.avgTime);
			} else {
				saveResult("hard.txt", finalSaveName, p1.avgTime);
			}

            cout << "\nTest Complete! Saved to " << (mainChoice == 1 ? "Medium" : "Hard") << " Leaderboard." << endl;
            system("pause");
        }
    }
    return 0;
}
