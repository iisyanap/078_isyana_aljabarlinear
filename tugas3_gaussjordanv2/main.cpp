// main.cpp
#include<iostream>

using namespace std;

/* Deklarasi fungsi */
void eliminasiGaussJordan();
void inversGaussJordan();

int main()
{
    int pilihan;
    do
    {
        cout << "\nPilih operasi yang ingin dilakukan:\n";
        cout << "1. Eliminasi dengan metode Gauss-Jordan\n";
        cout << "2. Menghitung invers matriks dengan metode Gauss-Jordan\n";
        cout << "0. Keluar\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        switch(pilihan)
        {
            case 1:
                eliminasiGaussJordan();
                break;
            case 2:
                inversGaussJordan();
                break;
            case 0:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
    } while(pilihan != 0);

    return 0;
}
