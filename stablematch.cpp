#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>

using namespace std;

// Number of people in both groups of men and women
const int NP = 5;

void ReadPreferenceLists(int menPref[NP][NP], int womPref[NP][NP]);
void StableMatch(int menPref[NP][NP], int womPref[NP][NP]);
void PrintPrefRanks(int prefRanking[NP][NP]);
void PrintMatches(int matches[NP]);

int main() {
	int menPref[NP][NP];
	int womPref[NP][NP];

	ReadPreferenceLists(menPref, womPref);
	StableMatch(menPref, womPref);

	return 0;
}

void ReadPreferenceLists(int menPref[NP][NP], int womPref[NP][NP]) {
	ifstream menPrefFile;
	ifstream womPrefFile;
	string menFilename = "menpref.txt";
	string womFilename = "wompref.txt";
	menFilename = menFilename.c_str();
	womFilename = womFilename.c_str();

	int curMan, curWom, curPref;

	// Read men's preference list from file
	menPrefFile.open(menFilename);
	if (!menPrefFile) {
		cout << "Error: Men's preference list file could not be opened" << endl;
	} else {
		for (int i=0; i<NP; i++) { 
			for (int i=0; i<NP; i++) {
				menPrefFile >> curMan >> curPref;
				menPref[curMan][i] = curPref;
			}
		}
		menPrefFile.close();
	}

	// Read women's preference list from file
	womPrefFile.open(womFilename);
	if (!womPrefFile) {
		cout << "Error: Women's preference list file could not be opened" << endl;
	} else {
		for (int i=0; i<NP; i++) { 
			for (int i=0; i<NP; i++) {
				womPrefFile >> curWom >> curPref;
				womPref[curWom][i] = curPref;
			}
		}
		womPrefFile.close();
	}
}

void StableMatch(int menPref[NP][NP], int womPref[NP][NP]) {
	// Stack of single men
	stack <int> freeWomen;
	// Preference Ranking 2 dimensional array
	int prefRanking[NP][NP], matches[NP], nextMan[NP];
	// Indicates not matched
	int notEngaged = -1;
	// Current man and woman
	int m, w;

	// Initialize lists
	for(int i=0; i<NP; i++) {
		freeWomen.push(i);
		nextMan[i] = 0;
		matches[i] = notEngaged;

		// Rank women's preferences
		for(int m=0; m<NP; m++) {
			prefRanking[i][menPref[i][m]] = m;
		}
	}

	PrintPrefRanks(prefRanking);

	// Start matching
	while(!freeWomen.empty()) {

		// Propose to first man in preference list
		w = freeWomen.top();
		m = womPref[w][nextMan[w]++];
		cout << w << " proposes to " << m << endl;
		cout << m << " is ranked " << nextMan[w] << " in " << w << "'s preference list" << endl;

		// If this man is not engaged, the two are now engaged
		if(matches[m] == notEngaged) {
			matches[m] = w;
			cout << m << " accepts proposal from " << w << "!" << endl;
			freeWomen.pop();

		// If he is engaged determine if the woman is preferable to the current partner
		} else {
			cout << m << " is already engaged. Determining if woman " << w << " is preferable" << endl; 

			// If so, replace current partner
			if(prefRanking[m][matches[m]] > prefRanking[m][w]) {
				cout << w << " is preferable. Replacing " << matches[m] << endl;
				freeWomen.pop();
				freeWomen.push(matches[m]);
				matches[m] = w;
			} else {
				cout << w << " is not preferable compared to " << matches[m] << endl;
			}
		}
	}

	cout << "All matches have been selected" << endl;
	cout << "Printing final matches" << endl;
	PrintMatches(matches);
}

void PrintPrefRanks(int prefRanking[NP][NP]) {
	// Print preference ranking list
	cout << "Preference rank for each woman in each man's list" << endl;
	for(int i=0; i<NP; i++) {
		cout << "Man " << i << "'s ranked preference list" << endl;
		for(int l=0; l<NP; l++) {
			cout << "Woman: " << l << " Rank: " << prefRanking[i][l] << endl;
		}
	}
}

void PrintMatches(int matches[NP]) {
	for(int i=0; i<NP; i++) {
		cout << "Man: " << i << " has married Woman: " << matches[i] << endl;
	}
}
