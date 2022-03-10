#ifndef HAMMING_H
#define HAMMING_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <string>

using namespace std;

class Hamming {

    string word;
    int begin = 0;
    int temp[50];
    int n, check;
    char parity;

public:
    Hamming(){
        parity = 'P';
        word = "";
        n = check = 0;
        for( int i = 0; i < 50; i++ ) {
            temp[i] = palabra[i] = 0;
        }
    }
    int palabra[50];
    string code;

    void generate( string message ){

        word = message;
        n = word.size();
        parity = 'P';
        for( unsigned int i = 0; i < word.size(); i++ ) {
            if(word[i] == '1')
                temp[i+1]=1;
            else
                temp[i+1]=0;
        }
        computeCode();

    }

    void computeCode() {

        check = findr();
        // cout << "Numero de Bits de Verificacion: " << check << endl;
        // cout << "Numero de bits en la palabra : " << n+check << endl;
        for( int i = (n+check), j = n; i > 0; i-- ) {
            if((i & (i - 1)) != 0)
                palabra[i] = temp[j--];
            else
                palabra[i] = setParity(i);
        }
        // cout << "Bits de Paridad - ";
        // for( int i = 0; i < check; i++ )
        // cout << "P" << pow(2,i) << " : " << palabra[(int)pow(2,i)] << "\t";
        // cout << endl;
        // cout << "Palabra: " << endl;
        for( int i = 1; i <= ( n + check ); i++ )
            code += to_string( palabra[i] );
    }

    int findr() {
        for ( int i = 1; ; i++ ) {
            if ( n + i + 1 <= pow(2,i) )
                return i;
        }
    }

    int setParity( int x ) {

        bool flag = true;
        int bit;
        if ( x == 1 ) {
            bit = palabra[x+2];
            for ( int j = x+3; j <= (n+check); j++ ) {
                if(j%2) {
                    bit ^= palabra[j];
                }
            }
        } else {
            bit = palabra[x+1];
            for( int i = x; i <= (n+check); i++ ) {
                if(flag) {
                    if(i==x || i==x+1)
                        bit = palabra[x+1];
                    else
                        bit ^= palabra[i];
                }
                if((i+1)%x == 0)
                    flag = !flag;
            }
        }
        if ( parity == 'I' || parity == 'i' )
            return !bit;
        else
            return bit;
    }

    void correct() {

        do{
            cout << endl << "Introduce la trama de bits con errores: ";
            cin >> word;
        } while(word.find_first_not_of("01") != string::npos);

        string checkWord = "";
        int counter = 0;

        for( unsigned int i = 0; i < word.size()+1; i++ ) {

            counter++;
            checkWord += word[i];
            if( word[i] == '1' )
                palabra[i+1] = 1;
            else
                palabra[i+1] = 0;
            if ( counter % 12 == 0 && i > 0 ) {
                cout << checkWord << endl;
                detect(checkWord);
                checkWord = "";
            }
        }
    }


    unsigned int bin_to_dec( string temp, int n ) {

        unsigned int counter = 0;
        for ( int i = n-1, j=0; i >= 0; i--, j++ ) if ( temp[i] == '1') counter+=pow(2,j);
        return counter;

    }

    void detect( string codeWord ) {

        int p1, p2;
        string p3, p4, aux = "";
        bool flag;

        p1 = codeWord[0] ^ codeWord[2] ^ codeWord[4] ^ codeWord[6]  ^ codeWord[8] ^ codeWord[10];
        aux += to_string(p1);
        cout << "P1: " << to_string(p1) << endl;
        p2 = codeWord[1] ^ codeWord[2] ^ codeWord[5] ^ codeWord[6]  ^ codeWord[9] ^ codeWord[10];
        aux += to_string(p2);
        cout << "P2: " << to_string(p2) << endl;
        p3 = codeWord[3] ^ codeWord[4] ^ codeWord[5] ^ codeWord[6]  ^ codeWord[11];
        aux += p3;
        cout << "P3: " << p3 << endl;
        p4 = codeWord[7] ^ codeWord[8] ^ codeWord[9] ^ codeWord[10] ^ codeWord[11];
        aux += p4;
        cout << "P4: " << p4 << endl;

        //searchInDictionary();


    }

    /*
    void searchInDictionary() {

    int counter = 0, limit = 0;
    fstream dictionary;
    string correctWord = "", line, temp = wordH;

    dictionary.open( "palabras.txt", ios::in );
    while ( !dictionary.eof() ) {

        getline(dictionary, line);
        if ( line.length() == temp.length() ) {
            counter  = 0;
            for ( int i = 0; i < temp.length(); i++ ) {
                if ( temp[i] == line[i] ) counter++;
            }
            if ( counter > limit ) {
                limit = counter;
                correctWord = line;
            }
        }

    }
    cout << endl << "La palabra '" << wordH << "' que tenia errores, fue corregida por '" << correctWord << "'" << endl;
    hammingW = "";
    wordH    = "";
    dictionary.close();

    } */
};

#endif // HAMMING_H
