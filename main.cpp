#include "hamming.h"

int main() {

    char choice;
    do {
        Hamming a;
        cout << "Emisor : " << endl;
        a.generate();
        cout << endl << "Receptor : " << endl;
        a.correct();
        cout << endl << "Introducir otro codigo ? (Y/N) : ";
        cin >> choice;
        cout << endl;
    } while ( choice == 'y' || choice == 'Y' );

    return 0;
}
