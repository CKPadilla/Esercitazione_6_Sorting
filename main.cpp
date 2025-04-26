/*
Nome, cognome e matricola: Cael Kyler Padilla | 307931
Esercitazione_6_Sorting
*/


#include <cmath> // contiene floor
#include <iostream>
#include <numeric> // contiene iota
#include <sstream>
#include <chrono> // https://en.cppreference.com/w/cpp/chrono

#include "SortingAlgorithm.hpp"
using namespace std;


/// Per stampare i vettori

template<typename T>
string ArrayToString(const vector<T>& v)
{
    string str;
    ostringstream toString;
    toString << "[ ";
    for (const T& e: v)
        toString << e << " ";
    toString << "]";

    return toString.str();
}

struct ClassObj{
    double value;

    // bool operator< (const ClassObj& rhs) { return value < rhs.value; }
};

inline bool operator< (const ClassObj& lhs, const ClassObj& rhs) { return lhs.value < rhs.value; }

/// Per calcolare i tempi

template<typename function, typename T>
double MisuraTempo(function sorting, const vector<T>& vec, unsigned int num_experiment){

    double time_elapsed = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        std::vector<T> v = vec;

        auto start_time = std::chrono::steady_clock::now();
        sorting(v);
        auto end_time = std::chrono::steady_clock::now();
        time_elapsed += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed = time_elapsed / num_experiment;

    return time_elapsed;
}

//********************************************************************************************* */
/// main

int main(int argc, char *argv[])
{

    /// Stampiamo il numero di argomenti passati al programma (argc) e gli argomenti stessi (argv)
    cout << "argc: " << argc << endl;
    for(int a = 0; a < argc; a++)
        cout << argv[a] << " ";
    cout << endl;

    /// Se non c'è argomento, allora usiamo di default m=10
    size_t m = 10;
    if(argc > 1)
    {
        istringstream convert(argv[1]);
        convert >> m;
        cout << "use value: "  << m << endl;
    }
    else
        cerr << "use default value: "  << m << endl;

    /// Vettore 1: m valori interi da -4 incluso in avanti
    vector<int> v1(m);
    std::iota(v1.begin(), v1.end(), -4); // l'ultimo argomento è il valore di partenza

    cout << "v1: " << endl;
    cout << ArrayToString(v1) << endl;

    /// Vettore 2: m valori casuali da 0 a 1
    srand(2);
    vector<double> v2(m);
    for(size_t i = 0; i < m; i++)
        v2[i] = rand() / ((double)RAND_MAX);

    cout << "v2: " << endl;
    cout << ArrayToString(v2) << endl;

    /// Vettore 3: prima metà come v1 e la secondametà composta da valori rand() % 1000
    vector<int> v3(m, 0);
    copy(v1.begin(), v1.begin() + floor(m * 0.5) + 1, v3.begin());

    for(size_t i = floor(m * 0.5) + 1; i < m; i++)
        v3[i] = rand() % 1000;

    cout << "v3: " << endl;
    cout << ArrayToString(v3) << endl;

//************************************************************************************** */
    /// MISURO I TEMPI DI ESECUZIONE
    unsigned int num_experiment = 100;   // Numero di prove che voglio eseguire


    /// Calcolo il tempo impiegato da BubbleSort
    auto bubbletime_v1 = MisuraTempo([](auto& v){ SortLibrary::BubbleSort(v); }, v1, num_experiment);
    auto bubbletime_v2 = MisuraTempo([](auto& v){ SortLibrary::BubbleSort(v); }, v2, num_experiment);
    auto bubbletime_v3 = MisuraTempo([](auto& v){ SortLibrary::BubbleSort(v); }, v3, num_experiment);
    auto heaptime_v1 = MisuraTempo([](auto& v){ SortLibrary::HeapSort(v); }, v1, num_experiment);
    auto heaptime_v2 = MisuraTempo([](auto& v){ SortLibrary::HeapSort(v); }, v2, num_experiment);
    auto heaptime_v3 = MisuraTempo([](auto& v){ SortLibrary::HeapSort(v); }, v3, num_experiment);

    cout << "Bubble Time v1 : " << bubbletime_v1 << endl;
    cout << "Bubble Time v2 : " << bubbletime_v2 << endl;
    cout << "Bubble Time v3 : " << bubbletime_v3 << endl;
    cout << "Heap Time v1 : " << heaptime_v1 << endl;
    cout << "Heap Time v2 : " << heaptime_v2 << endl;
    cout << "Heap Time v3 : " << heaptime_v3 << endl;

    return 0;
}


