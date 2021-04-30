#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include "Cherrytree.h"
#include "Hilfe.h"
#include "Clock.h"

#define T string

using namespace std;

size_t ANZAHLZUFALLSWERTE = 1000000; // 1 Millionen
int addCount = 0;
static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

void noTreeException() {cout << "There is no tree in your garden. Try planting one with 'n'." << endl;}
void alreadyTreeException() {cout << "There is a tree in your garden. Delete it first with 'd'." << endl;}

int random(int x = 0) {
    return (int) (rand()*rand());
}

unsigned int random(unsigned int x = 0) {
    return (unsigned int) (rand()*rand());
}

string random(string x = "") {
    int laenge = 5;
    string s;
    for (int i = 0; i < laenge; ++i) {
        s = s + alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return s;
}

void mysticAdd(T a, Cherrytree<T> &k,bool showMessage) {
    ++addCount;
	if (k.add(a) && showMessage) cout << a << " wurde hinzugefuegt." << endl;
	else if (showMessage) cout << a << " wurde NICHT hinzugefuegt." << endl;
	if (!showMessage && (addCount % 10000 == 0)) {cout << "."; addCount = 0;}
	if (showMessage) {
        addCount = 0;
	}
}

void mysticRemove(T a, Cherrytree<T> &k) {
	if (k.remove(a)) cout << a << " wurde entfernt." << endl;
	else cout << a << " wurde NICHT entfernt." << endl;
}

void mysticCount(Cherrytree<T> &k) {
	cout << k.count() << " entrys." << endl;
}

void mysticMember(T a, Cherrytree<T> &k) {
	if (k.member(a)) cout << "Baum enthaelt " << a << "." << endl;
	else cout << "Baum enthaelt " << a << " NICHT." << endl;
	getchar();
}

int main() {
	cout << "=Cherrytree-testprogram=\n\nVersion: Alpha 1.0.1\nLast edited on 30.04.2021\nFelix Mark\n\n";
    Hilfe hilfe;
    hilfe.addHelp("# [value] ....... SET ............ set auto-add valuecount");
    hilfe.addHelp("a [value] ....... ADD ............ add [value]");
    hilfe.addHelp("c ............... COUNT .......... show count");
    hilfe.addHelp("d ............... DELETE ......... delete tree");
    hilfe.addHelp("h ............... HELP ........... show help");
    hilfe.addHelp("m [value] ....... MEMBER ......... member [value]");
    hilfe.addHelp("n ............... NEW ............ new tree");
    hilfe.addHelp("t ............... TIME ........... toggle measuretimemode");
    hilfe.addHelp("p [value] ....... PRINT .......... print tree layer (-1 for all layers)");
    hilfe.addHelp("f [value] ....... FLAT ........... print flat tree layer (-1 for all layers)");
    hilfe.addHelp("q ............... QUIT ........... quit");
    hilfe.addHelp("r [value] ....... REMOVE ......... remove [value]");
    hilfe.addHelp("x ............... EXECUTE ........ auto-add [valuecount] random values");

    cout << hilfe.getHelp() << endl;

    T x;
    int inputValue = -1;
	char in;
	Clock stoppuhr;
	Cherrytree<T> *test = NULL;
	bool measureTime = false;

	while (true) {
		cout << ">";
		cin >> in;

        if (in == 'a' || in == 'r' || in == 'm') {
            cin >> x;
        } else if (in == 'p' || in == '#' || in == 'f') {
            cin >> inputValue;
        }

		cout << "\n";
		stoppuhr.start();
		switch (in) {
			case 'a': if (test != NULL) {mysticAdd(x,*test,true);} else {noTreeException();} break;
			case 'c': if (test != NULL) {mysticCount(*test);} else {noTreeException();} break;
			case 'd': if (test != NULL) {delete test; test = NULL;} else {noTreeException();} break;
			case 'r': if (test != NULL) {mysticRemove(x,*test);} else {noTreeException();} break;
			case '#': ANZAHLZUFALLSWERTE = inputValue; break;
			case 't': measureTime = !measureTime; cout << "Measure time mode: " << (measureTime?"ON":"OFF") << endl; break;
			case 'x': if (test != NULL) {for (size_t i=0; i < ANZAHLZUFALLSWERTE; ++i) {mysticAdd(random(x),*test,false);} cout << "\n";} else {noTreeException();} break;
			case 'm': if (test != NULL) {mysticMember(x,*test);} else {noTreeException();} break;
			case 'n': if (test == NULL) {test = new Cherrytree<T>();} else {alreadyTreeException();} break;
			case 'p': if (test != NULL) {test->print(inputValue,false);} else {noTreeException();} break;
			case 'f': if (test != NULL) {test->print(inputValue,true);} else {noTreeException();} break;
			case 'h': cout << hilfe.getHelp(); break;
			case 'q': return 0;
			default: cout << "What is '" << in << "' ? Try 'h' for help.\n"; break;
		}
		if (measureTime) cout << "Time: " << setprecision(20) << stoppuhr.stopexact()/1000.0 << " seconds\n";
		cout << endl;
	}
}
