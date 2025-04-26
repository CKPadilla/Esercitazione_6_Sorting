/*
Nome, cognome e matricola: Cael Kyler Padilla | 307931
Esercitazione_6_Sorting
*/

#pragma once

#include <iostream>
#include <vector>


namespace SortLibrary {


// Creo un template con concept Sortable per assicurarmi di lavorare solo con valori confrontabili o che soddisfano "<"

template<typename T>
concept Sortable = requires(T& t) {
    {t < t} -> std::convertible_to<bool>;
};

//******************************************************************************************************** */
// Scrivo il BubbleSort

template<Sortable T>
void BubbleSort(std::vector<T>& v)
{
    unsigned int n = v.size();

    bool scambio = true;   /// Esegue gli scambi finchè c'è da scambiare

    while (scambio){
        scambio = false;   /// se non entra nel ciclo if di scambio, allora rimane false => vettore ordinato
        for(unsigned int i = 0; i < n-1; i++)
        {
            // swap
            if(v[i]>v[i+1]) {
                scambio = true;   /// ogni volta che entra qui, significa che c'è scambio
                T tmp = v[i];
                v[i] = v[i+1];
                v[i+1] = tmp;
                
            }

        }
        n--;   /// Ogni volta che fa salire un "bubble", diminuiamo n
    }
};



//*********************************************************************************************************** */
// Scrivo la Heap Sort: 1. la funzione heapify / 2. il template HeapSort

/* Scrivo la funzione di heapify:
- v: vettore
- n: lunghezza del vettore
- i: indice della radice
- return: vettore v che ha v[i] più grande del figlio sinistro e destro
*/
template<typename T>
void heapify(std::vector<T>& v, unsigned int n, unsigned int i) {
    unsigned int mag_index = i;    // madre: la poniamo il valore più grande
    unsigned int sin_index = 2*i+1;   //figlio sinistro
    unsigned int des_index = 2*i+2;   // figlio destro

    // confronto chi è più grande tra mag_index e figlio sinistro
    if (sin_index < n && v[sin_index]>v[mag_index]){
        mag_index = sin_index;
    }

    // confronto chi è più grande tra mag_index e figlio destro
    if(des_index <n && v[des_index]>v[mag_index]){
        mag_index = des_index;
    }

    /* se il valore maggiore non è nell'indice i (che è l'indice di radice) allora:
    - scambio i valori
    - proseguo la heapify
    */
    if(mag_index != i) {
        T tmp = v[i];
        v[i] = v[mag_index];
        v[mag_index] = tmp;
        heapify(v, n, mag_index);   
    }
};

// HeapSort

template<Sortable T>
void HeapSort(std::vector<T>& v)
{

    const unsigned int n = v.size();

    // max heap
    for (int i= n/2 -1 ; i >= 0 ; i--){
        heapify(v,n,i);
    }

    for (unsigned int i = n - 1; i > 0; i--)
    {
        // sposto il massimo alla fine con uno swap
        T tmp = v[i];
        v[i] = v[0];
        v[0] = tmp;

        heapify(v, i, 0);    // Heap di nuovo
    }

};
}

