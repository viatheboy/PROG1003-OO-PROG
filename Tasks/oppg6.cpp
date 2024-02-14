#include <iostream>
#include <string>
using namespace std;


int main() {
    string hello = "Hello ";
    string name;
    string lastName;
    string occupation;
    string favMovie;

    
    cout << "Please enter your first name: ";
    cin >> name;
    cin.ignore();

    cout << hello + name + "\n";
    cout << "What is your occupation?\n";
    getline(cin, occupation);

    cout << "What is your favourite movie?\n";
    getline(cin, favMovie);

    cout << "And finally, please enter your last name: \n";
    getline(cin, lastName);

    cout << "Cool!\nYour name is " + name + " " + lastName + " and your line of work is " + occupation << "\n";
    cout << "We appriacte your favorite movie, " + favMovie + ", too!\n";
    

    string nyTekst = "Her er det noe\n";
    string endaNyere = nyTekst;

    cout << endaNyere;

    if (nyTekst == endaNyere)
        cout << "Its true\n";

    if (endaNyere.length() > 4)
        cout << "Og den er større enn 4!\n";
        
    return 0;

}
