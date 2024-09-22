#include<iostream>
#include<iomanip>
#include<cmath>
#include<stdlib.h>

#define SIZE 10     

using namespace std;

void inversGaussJordan()
{
    float a[SIZE][2*SIZE];
    int i,j,k,n;

    cout<<"============Invers Metode Gauss Jordan============\n";
    cout<<"Masukkan ordo matriks (maksimum "<< SIZE << "): ";
    cin>>n;

    if(n > SIZE)
    {
        cout << "Ukuran matriks melebihi batas maksimum.";
        return;
    }

    cout<<"Masukkan elemen matriks: " << endl;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            cout<<"A["<< i<<"]["<< j<<"]= ";
            cin>>a[i][j];
        }
    }

    for(i=1;i<=n;i++)
    {
        for(j=n+1;j<=2*n;j++)
        {
            if(i==(j-n))
            {
                a[i][j] = 1;
            }
            else
            {
                a[i][j] = 0;
            }
        }
    }

    cout << "\nMatriks Augmented Awal:\n";
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=2*n;j++)
        {
            if(j == n+1)
                cout << " | ";
            cout << setw(10) << a[i][j] << "\t";
        }
        cout << endl;
    }

    for(i=1;i<=n;i++)
    {
        if(a[i][i] == 0.0)
        {
            cout<<"Terjadi Kesalahan Matematis!";
            exit(0);
        }
        for(j=1;j<=n;j++)
        {
            if(i!=j)
            {
                float rasio = a[j][i]/a[i][i];
                cout << "\nMengeliminasi a["<< j <<"]["<< i <<"] menjadi nol menggunakan operasi baris:";
                cout << "\nR" << j << " = R" << j << " - (" << rasio << ") * R" << i;
                for(k=1;k<=2*n;k++)
                {
                    a[j][k] = a[j][k] - rasio*a[i][k];
                }
                cout << "\nMatriks Setelah Operasi:\n";
                for(int p=1;p<=n;p++)
                {
                    for(int q=1;q<=2*n;q++)
                    {
                        if(q == n+1)
                            cout << " | ";
                        cout << setw(10) << a[p][q] << "\t";
                    }
                    cout << endl;
                }
            }
        }
    }
    cout << "\nMengubah elemen diagonal utama menjadi 1:";
    for(i=1;i<=n;i++)
    {
        float diagonal = a[i][i];
        cout << "\nMembagi baris " << i << " dengan " << diagonal << ":";
        for(j=1;j<=2*n;j++)
        {
            a[i][j] = a[i][j]/diagonal;
        }
        cout << "\nMatriks Setelah Normalisasi:\n";
        for(int p=1;p<=n;p++)
        {
            for(int q=1;q<=2*n;q++)
            {
                if(q == n+1)
                    cout << " | ";
                cout << setw(10) << a[p][q] << "\t";
            }
            cout << endl;
        }
    }
    cout<< endl<<"Matriks Invers adalah:"<< endl;
    for(i=1;i<=n;i++)
    {
        for(j=n+1;j<=2*n;j++)
        {
            cout<< a[i][j]<<"\t";
        }
        cout<< endl;
    }
    cout<<"=================================================================================\n";
}
