#ifndef HAMMING_H
#define HAMMING_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <string>

using namespace std;

/*class Hamming {

    private:
        string hammingW;
        string wordH;

    public:
        Hamming() {
            hammingW = "";
            wordH    = "";
        }

        string getCode() {
            return hammingW;
        }
        string getWord() {
            return wordH;
        }

        void create( string word );

        void searchInDictionary();

        void verificate( string hammingCode );

};*/

class Hamming {

    string word;

    int temp[50];
    int n, check;
    char parity;

public:
    Hamming(){
        parity = 'I';
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

    string entero_a_binario(char bit, int tam){
        string cadena = "";
        for( int i = tam-1; i >= 0; i-- ) cadena += ( (bit & ( 1 << i )) ? '1' : '0');
        cout << "Cadena de Bits: " << cadena << endl;
        return cadena;
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

    int setParity(int x) {
        bool flag = true;
        int bit;
        if(x == 1) {
            bit = palabra[x+2];
            for( int j = x+3; j <= (n+check); j++ ) {
                if(j%2) {
                    bit ^= palabra[j];
                }
            }
        } else {
            bit = palabra[x+1];
            for( int i = x; i <= (n+check); i++ ) {
                if(flag)
                {
                    if(i==x || i==x+1)
                        bit = palabra[x+1];
                    else
                        bit ^= palabra[i];
                }
                if((i+1)%x == 0)
                    flag = !flag;
            }
        }
        if ( parity == 'P' || parity == 'p' )
            return !bit;
        else
            return bit;
    }

    void correct() {
        do{
            cout << "Introduce la palabra recibida: ";
            cin >> word;
        } while(word.find_first_not_of("01") != string::npos);

        for( unsigned int i = 0; i < word.size(); i++ ) {
            if( word[i] == '1' )
                palabra[i+1] = 1;
            else
                palabra[i+1] = 0;
        }
        detect();
    }

    void detect() {

        int position = 0;
        cout << "Bits de Paridad - ";
        for( int i = 0; i < check; i++ ) {
            bool flag = true;
            int x = pow(2,i);
            int bit = palabra[x];
            if(x == 1)
            {
                for( int j = x+1; j <= (n+check); j++ ) {
                    if(j%2) {
                        bit ^= palabra[j];
                    }
                }
            } else {
                for(int k=x+1;k<=(n+check);k++) {
                    if(flag) {
                        bit ^= palabra[k];
                    }
                    if((k+1)%x == 0)
                        flag = !flag;
                }
            }
            cout << "P" << x << ": " << bit << "\t";
            if((parity=='I' || parity == 'i') && bit==1)
                position += x;
            if((parity=='P' || parity == 'p') && bit==0)
                position += x;
        }
        cout << endl << "Palabra recibida: " << endl;
        for(int i=1;i<=(n+check);i++)
            cout<<palabra[i]<<" ";
        cout<<endl;
        if(position != 0) {
            cout << "Error en el bit: " << position << endl;
            palabra[position] = !palabra[position];
            cout<<"Palabra corregida: "<<endl;
            for(int i=1;i<=(n+check);i++) {
                code += to_string(palabra[i]);
            }
            cout<<endl;
        }
        else
            cout << "Sin error en el codigo recibido." << endl;
        cout << "El mensaje recibido es: ";
        for ( int i = 1; i <= ( n + check ); i++ )
            if ( ( i & (i - 1) ) != 0 )
                cout << palabra[i]<<" ";
        cout << endl;
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
