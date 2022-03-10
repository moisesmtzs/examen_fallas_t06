/*
Martinez Sanchez Moises
                                                    S
                                                     E
                                                      C
                                                       C
                                                        I
                                                         O
                                                          N
                                                           D
                                                            0
                                                             2

 ----- EN CASO DE NO COMPILAR, ES NECESARIO EN LAS "BUILD OPTIONS" DEL PROYECTO ELEGIR LA VERSION -STD=C++11 -----
 ----- ESPECIFICAMENTE, "HAVE G++ FOLLOW THE C++ 11 ISO C++ LANGUAGE STANDARD [-STD=C++11]" -----
*/

#include "hamming.h"

string int_to_bin( char bit, int n );

int main() {

    char o;
    do {
        string word, binWord, finalWord;
        Hamming hamming;
        system("cls");
        cout << "------------------EXAMEN DE COMPUTACION TOLERANTE A FALLAS------------------" << endl << endl;

        // LADO DEL "EMISOR"
        cout << "Ingresa una palabra: ";
        getline( cin, word );
        cin.ignore();
        for ( int i = 0; i < word.length(); i++ ) {

            binWord = int_to_bin( word[i], 8 );
            hamming.generate(binWord);

        }
        cout << "Codigo de Hamming para la palabra ingresada es: " << hamming.code << endl << endl;

        hamming.correct();
        /*

        // LADO DEL "RECEPTOR"
        cout << endl << "Ingresa la cadena binaria en Hamming: ";
        getline( cin, word );
        cin.ignore();

*/
        system("PAUSE");
        cout << endl << "Intentar de nuevo? (N para salir) : ";
        cin >> o;
        cin.ignore();
        cout << endl;
    } while ( o != 'n' && o != 'N' );

    return 0;

}

string int_to_bin( char bit, int n ) {

    string temp = "";
    for ( int i = n-1; i >= 0; i-- ) temp+= ( (bit & ( 1 << i )) ? '1' : '0' );
    return temp;

}
