// Game of Othello -- Example of main
// Universidad Simon Bolivar, 2012.
// Author: Blai Bonet
// Last Revision: 10/23/12
// Modified by: 

#include "othello_cut.h" // won't work correctly until .h is fixed!
//#include "othello_Negamax.h"
//#include "othello_Negascout.h"
#include "othello_Alpha_Beta_Pruning.h"
//#include "Alter_Negascout.h"

#include <iostream>
#include <string>

#include <sys/time.h>

using namespace std;

struct timeval t, t2, p;

float microsegundos;

double getSeconds(timeval t, timeval t2) {
    return (double) (((t2.tv_sec * 1000000)+(t2.tv_usec))-((t.tv_sec * 1000000) + t.tv_usec)) / 1000000;
}

int main(int argc, const char **argv) {
    //bool tt = false;
    /*if (((string)argv[1]).compare("-tt")==0){
        tt = !tt;
        cout << "USING TRANSPOSITION TABLES" << endl;
    }*/
    bool tt;
    cout <<"Want to use TRANSPOSITION TABLES 0=NO 1=YES? ";
    cin >> tt;
    tt ? (cout<<"using tt"<<endl):(cout<<"NOT using tt"<<endl);
    state_t state;
    state_t Vector[33]; //Guardo los estados de la VP en un arreglo y luego itero inversamente sobre el
    //Aplicando cada uno de los algoritmos.
    cout << "Principal variation:" << endl;
    for (int i = 0; PV[i] != -1; ++i) {
        bool player = i % 2 == 0; // black moves first!
        int pos = PV[i];
        //     cout << state;
        Vector[i] = state;
        //    cout << (player ? "Black" : "White")
        //           << " moves at pos = " << pos << (pos == 36 ? " (pass)" : "")
        //          << endl;
        state = state.move(player, pos);
        //    cout << "Board after " << i + 1 << (i == 0 ? " ply:" : " plies:") << endl;
        //Comentado para que no imprima la variación principal
    }
    //cout << state;
    Vector[32] = state;
    //cout << Vector[32];
    cout << "Value of the game = " << state.value() << endl;
    cout << "#bits per state = " << sizeof (state) * 8 << endl;
    int a;
    cout << "Ingrese 1 Negascout, 2 Negamax, 3 Alpha Beta Pruning ? eleccion= ";
    cin >> a;
    gettimeofday(&p, NULL);
/*    if (a == 1) {
        //NEGASCOUT
        for (int iter = 32; iter >= 0; iter--) {
            cout << "Board after " << iter << " plies " << endl;
            //cout << Vector[iter] << endl;
            gettimeofday(&t, NULL);
            if (iter % 2 == 1) {
                if (!tt) {
                    cout << NegascoutG(Vector[iter], 60, -1000000000, 1000000000) << endl;
                } else {
                    cout << NegascoutG_TT(Vector[iter], 60, -1000000000, 1000000000) << endl;
                }
            }
            if (iter % 2 == 0) {
                if (!tt) {
                    cout << NegascoutF(Vector[iter], 60, -1000000000, 1000000000) << endl;
                } else {
                    cout << NegascoutF_TT(Vector[iter], 60, -1000000000, 1000000000) << endl;
                }

            }
            cout << "====================" << endl;
            gettimeofday(&t2, NULL);
            cout << "Elapsed time: " << getSeconds(t, t2) << " seconds." << endl;
        }
    }
    if (a == 2) {
        //NEGAMAX
        for (int iter = 32; iter >= 0; iter--) {
            cout << "Board after " << iter << " plies " << endl;
            //cout << Vector[iter] << endl;
            gettimeofday(&t, NULL);
            if (iter % 2 == 1) {
                if (!tt) {
                    cout << "Value of the game: " << -Negamax(Vector[iter], 1000, -1000000000, 1000000000, -1) << endl;
                } else {
                    cout << "Value of the game: " << -Negamax_TT(Vector[iter], 1000, -1000000000, 1000000000, -1) << endl;
                }
            }
            if (iter % 2 == 0) {
                if (!tt) {
                    cout << "Value of the game: " << Negamax(Vector[iter], 1000, -1000000000, 1000000000, 1) << endl;
                } else {
                    cout << "Value of the game: " << Negamax_TT(Vector[iter], 1000, -1000000000, 1000000000, 1) << endl;
                }
            }
            gettimeofday(&t2, NULL);
            cout << "Elapsed time: " << getSeconds(t, t2) << " seconds." << endl;
            cout << "====================" << endl;
        }
    }*/
    if (a == 3) {
        //ALPHA BETA PRUNING    
        for (int iter = 32; iter >= 0; iter--) {
            cout << "Board after " << iter << " plies " << endl;
            //cout << Vector[iter] << endl;
            gettimeofday(&t, NULL);
            if (iter % 2 == 1) {
                if (!tt) {
                    cout << alpha_beta_pruning(Vector[iter], 1000, -1000000000, 1000000000, 0) << endl;
                } else {
                    cout << alpha_beta_pruning_TT(Vector[iter], 1000, -1000000000, 1000000000, 0) << endl;
                }
            }
            if (iter % 2 == 0) {
                if (!tt) {
                    cout << alpha_beta_pruning(Vector[iter], 1000, -1000000000, 1000000000, 1) << endl;
                }else{
                    cout << alpha_beta_pruning_TT(Vector[iter], 1000, -1000000000, 1000000000, 1) << endl;
                }
            }
            gettimeofday(&t2, NULL);
            cout << "Parcial Elapsed time: " << getSeconds(t, t2) << " seconds." << endl;
            //gettimeofday(&t2, NULL);
            cout << "Total Elapsed time: " << getSeconds(p, t2) << " seconds." << endl;
            cout << "====================" << endl;
        }
    }

    if (argc > 1) {
        int n = atoi(argv[1]);
        cout << endl << "Apply " << n << " random movements at empty board:";
        state = state_t();
        for (int i = 0; i < n; ++i) {
            bool player = i % 2 == 0; // black moves first
            int pos = state.get_random_move(player);
            state = state.move(player, pos);
            cout << " " << pos;
        }
        cout << endl << state;
    }

    return 0;
}

