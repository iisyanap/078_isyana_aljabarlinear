#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<cmath>
#include<stdlib.h>

#define MAX_SIZE 20  // Maksimum ukuran matriks
#define SIZE 10      // Ukuran untuk invers matriks

using namespace std;

/* Fungsi untuk menyelesaikan sistem persamaan linear dengan eliminasi Gauss-Jordan */
void eliminasiGaussJordan()
{
    double a[MAX_SIZE][MAX_SIZE];
    int i,j,k,n,m;
    const double epsilon = 1e-9; // Toleransi untuk menganggap angka sebagai nol

    /* Input */
    /* 1. Membaca jumlah baris dan kolom */
    cout<<"=====Eliminasi Gauss Jordan====\n";
    cout<<"Masukkan jumlah baris (n): ";
    cin>>n;
    cout<<"Masukkan jumlah kolom (m): ";
    cin>>m;

    if(n > MAX_SIZE || m > MAX_SIZE)
    {
        cout << "Jumlah baris atau kolom melebihi batas maksimum.";
        return;
    }

    /* 2. Membaca elemen matriks augmented */
    cout<<"Masukkan elemen matriks augmented (termasuk konstanta):\n";
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            cout<<"A["<< i+1<<"]["<< j+1<<"]= ";
            cin>>a[i][j];
        }
    }

    /* Menampilkan Matriks Awal */
    cout << "\nMatriks Augmented Awal:\n";
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            cout << setw(10) << a[i][j] << "\t";
        }
        cout << endl;
    }

    /* Menerapkan Eliminasi Gauss-Jordan */
    vector<pair<int,int>> pivot_columns; // pasangan (pivot_col, row_index)
    for(i=0, j=0; i<n && j<m-1; j++)
    {
        // Mencari pivot
        int maxRow = i;
        for(k=i+1;k<n;k++)
        {
            if(abs(a[k][j]) > abs(a[maxRow][j]))
            {
                maxRow = k;
            }
        }
        if(abs(a[maxRow][j]) > epsilon)
        {
            // Tukar baris i dengan baris maxRow
            if(i != maxRow)
            {
                for(int l=0; l<m; l++)
                {
                    swap(a[i][l], a[maxRow][l]);
                }
            }
            // Normalisasi baris pivot
            double pivot = a[i][j];
            for(int l=0;l<m;l++)
            {
                a[i][l] = a[i][l] / pivot;
            }

            // Eliminasi elemen di atas dan di bawah pivot
            for(k=0;k<n;k++)
            {
                if(k != i)
                {
                    double ratio = a[k][j];
                    for(int l=0;l<m;l++)
                    {
                        a[k][l] -= ratio * a[i][l];
                    }
                }
            }

            // Mengatur nilai yang sangat kecil menjadi nol
            for(int p=0;p<n;p++)
            {
                for(int q=0;q<m;q++)
                {
                    if(abs(a[p][q]) < epsilon)
                        a[p][q] = 0;
                }
            }

            pivot_columns.push_back(make_pair(j,i));
            i++;

            /* Menampilkan Matriks setelah setiap operasi */
            cout << "\nMatriks Setelah Operasi pada kolom " << j+1 << ":\n";
            for(int p=0;p<n;p++)
            {
                for(int q=0;q<m;q++)
                {
                    cout << setw(10) << a[p][q] << "\t";
                }
                cout << endl;
            }
        }
    }

    /* Mengecek Konsistensi Sistem */
    bool inconsistent = false;
    for(i=0;i<n;i++)
    {
        bool all_zero = true;
        for(j=0;j<m-1;j++)
        {
            if(abs(a[i][j]) > epsilon)
            {
                all_zero = false;
                break;
            }
        }
        if(all_zero && abs(a[i][m-1]) > epsilon)
        {
            inconsistent = true; // Sistem tidak konsisten
            break;
        }
    }

    if(inconsistent)
    {
        cout << "\nSistem persamaan tidak konsisten.";
    }
    else
    {
        /* Menentukan Variabel Dasar dan Variabel Bebas */
        vector<int> basic_variables;
        vector<int> free_variables;
        vector<bool> is_basic(m-1, false);

        for(auto pivot : pivot_columns)
        {
            is_basic[pivot.first] = true;
        }
        for(j=0;j<m-1;j++)
        {
            if(is_basic[j])
                basic_variables.push_back(j);
            else
                free_variables.push_back(j);
        }

        /* Menampilkan Solusi Parametrik */
        cout<< endl<<"Solusi Sistem Persamaan adalah:\n";
        for(auto var : basic_variables)
        {
            int row = -1;
            // Cari baris yang memiliki pivot pada kolom var
            for(auto pivot : pivot_columns)
            {
                if(pivot.first == var)
                {
                    row = pivot.second;
                    break;
                }
            }
            if(row == -1)
                continue;

            cout << "Variabel x" << var+1 << " = ";

            bool first = true;
            double value = a[row][m-1];

            if(abs(value) > epsilon)
            {
                cout << value;
                first = false;
            }

            // Variabel Bebas
            for(auto free_var : free_variables)
            {
                double coeff = -a[row][free_var];
                if(abs(coeff) > epsilon)
                {
                    if(first)
                    {
                        if (coeff == 1)
                            cout << "x" << free_var+1;
                        else if (coeff == -1)
                            cout << "-x" << free_var+1;
                        else
                            cout << coeff << " x" << free_var+1;
                        first = false;
                    }
                    else
                    {
                        if(coeff > 0)
                            cout << " + ";
                        else
                        {
                            cout << " - ";
                            coeff = -coeff;
                        }
                        if (coeff == 1)
                            cout << "x" << free_var+1;
                        else
                            cout << coeff << " x" << free_var+1;
                    }
                }
            }

            if(first)
                cout << "0";

            cout << endl;
        }

        for(auto var : free_variables)
        {
            cout << "Variabel x" << var+1 << " adalah variabel bebas.\n";
        }
    }cout<<"=================================================================================\n";
}

/* Fungsi untuk menghitung invers matriks dengan eliminasi Gauss-Jordan */
void inversGaussJordan()
{
    float a[SIZE][2*SIZE];
    int i,j,k,n;

    /* Input */
    /* 1. Membaca ordo matriks */
    cout<<"============Invers Metode Gauss Jordan============\n";
    cout<<"Masukkan ordo matriks (maksimum "<< SIZE << "): ";
    cin>>n;

    if(n > SIZE)
    {
        cout << "Ukuran matriks melebihi batas maksimum.";
        return;
    }

    /* 2. Membaca elemen Matriks */
    cout<<"Masukkan elemen matriks: " << endl;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            cout<<"A["<< i<<"]["<< j<<"]= ";
            cin>>a[i][j];
        }
    }

    /* Menambahkan Matriks Identitas */
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

    /* Menampilkan Matriks Augmented */
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

    /* Menerapkan Eliminasi Gauss-Jordan */
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
                /* Menampilkan Matriks Augmented setelah setiap operasi baris */
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
    /* Operasi Baris untuk Membuat Elemen Diagonal Utama Menjadi 1 */
    cout << "\nMengubah elemen diagonal utama menjadi 1:";
    for(i=1;i<=n;i++)
    {
        float diagonal = a[i][i];
        cout << "\nMembagi baris " << i << " dengan " << diagonal << ":";
        for(j=1;j<=2*n;j++)
        {
            a[i][j] = a[i][j]/diagonal;
        }
        /* Menampilkan Matriks Augmented setelah normalisasi diagonal */
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
    /* Menampilkan Matriks Invers */
    cout<< endl<<"Matriks Invers adalah:"<< endl;
    for(i=1;i<=n;i++)
    {
        for(j=n+1;j<=2*n;j++)
        {
            cout<< a[i][j]<<"\t";
        }
        cout<< endl;
    }cout<<"=================================================================================\n";
}

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
