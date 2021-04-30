#include <string>
#include <map>

using namespace std;

class Hilfe {
	private:
        map<int,string> hilfeTexte;
        int anzahl = 0;
        typedef map<int, string>::iterator it_type;
	public:
        void addHelp(string hilfeText){
            hilfeTexte[anzahl++] = hilfeText;
        }
        string getHelp(){
            string returnString = "Help:\n";
            for(it_type iterator = hilfeTexte.begin(); iterator != hilfeTexte.end(); iterator++) {
                returnString = returnString + iterator->second + "\n";
            }
            return returnString;
        }
};
