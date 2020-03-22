#include <iostream>

#include <vector>

#include <fstream>

#include <cmath>

#include <list>

#include <cstdlib>

#include <chrono>

#include <algorithm>

using namespace std;
using namespace std::chrono;

ifstream fin("citire.in");
ofstream fout("citire.out");

void BubbleSort(vector < long long > & v, int n) {

  int i, j;
  for (i = 0; i < n - 1; i++)
    for (j = 0; j < n - i - 1; j++)
      if (v[j] > v[j + 1])
        swap(v[j], v[j + 1]);
}

void CountSort(vector < long long > & v, int dim) {
  int ct[10], maxi;
  vector < long long > out(v.size());
  maxi = v[0];
  for (int i = 1; i < dim; i++) {
    if (v[i] > maxi)
      maxi = v[i];
  }
  for (int i = 0; i <= maxi; ++i) {
    ct[i] = 0;
  }

  for (int i = 0; i < dim; i++) {
    ct[v[i]]++;
  }
  for (int i = 1; i <= maxi; i++) {
    ct[i] += ct[i - 1];
  }
  for (int i = dim - 1; i >= 0; i--) {
    out[ct[v[i]] - 1] = v[i];
    ct[v[i]]--;
  }
  for (int i = 0; i < dim; i++) {
    v[i] = out[i];
  }
}
//RADIXSORT
int nrcif(int x) {
  int k = 0;
  while (x) {
    x /= 10;
    k++;
  }
  return k;
}
void RadixSort(vector < long long > & v, int & nrcifmax) {

  int i, j, poz, sterge_poz_ant, cif_de_sortat;
  list < long long > liste[10];
  for (i = 0; i < nrcifmax; i++) {
    poz = ceil(pow(10, i + 1));
    sterge_poz_ant = ceil(pow(10, i));
    for (j = 0; j < v.size(); j++) {
      cif_de_sortat = (v[j] % poz) / sterge_poz_ant;
      liste[cif_de_sortat].push_back(v[j]);
    }
    v.clear();
    for (j = 0; j < 10; j++) {
      if (liste[j].size() > 0) {
        v.insert(v.end(), liste[j].begin(), liste[j].end());
        liste[j].clear();
      }

    }
  }
}

//MERGESORT
void sortare(int st, int dr, vector < long long > & v) {
  if (v[st] > v[dr]) {
    int aux = v[st];
    v[st] = v[dr];
    v[dr] = aux;
  }
}
void interclasare(int st, int dr, int m, vector < long long > & v) {
  int i = st, j = m + 1, k = 0;
  vector < long long > w;
  while (i <= m && j <= dr) {
    if (v[i] < v[j])
      w.push_back(v[i++]);
    else
      w.push_back(v[j++]);
  }
  while (i <= m)
    w.push_back(v[i++]);
  while (j <= dr)
    w.push_back(v[j++]);

  for (i = st; i <= dr; i++)
    v[i] = w[i - st];
}

void MergeSort(int st, int dr, vector < long long > & v) {
  int mij;
  if (dr - st <= 1)
    sortare(st, dr, v);
  else {
    mij = st + (dr - st) / 2;
    MergeSort(st, mij, v);
    MergeSort(mij + 1, dr, v);
    interclasare(st, dr, mij, v);
  }
}

//QUICKSORT
int mediana3(int st, int dr, int mij, vector < long long > & v) {
  int s = v[st], m = v[mij], d = v[dr];
  if ((s > m) != (s > d))
    return st;
  else if ((m > s) != (m > dr))
    return mij;
  else
    return dr;
}
int partitie(int st, int dr, vector < long long > & v) {
  int piv = v[dr], i;
  int indexmin = st;
  for (i = st; i < dr; i++) {

    if (v[i] <= piv) {
      swap(v[i], v[indexmin]);
      indexmin++;
    }
  }
  swap(v[dr], v[indexmin]);
  return indexmin;
}

void QuickSort(int st, int dr, vector < long long > & v) {
  if (st < dr) {

    int piv = partitie(st, dr, v);
    QuickSort(st, piv - 1, v);
    QuickSort(piv + 1, dr, v);
  }
}
void QuickSortMed3(int st, int dr, vector < long long > & v) {
  if (st < dr) {
    int mij = (st + dr) / 2;
    int piv = mediana3(st, dr, mij, v);
    swap(v[piv], v[dr]);
    piv = partitie(st, dr, v);
    QuickSortMed3(st, piv - 1, v);
    QuickSortMed3(piv + 1, dr, v);
  }
}
void afisare(int v[], int n) {
  for (int i = 0; i < n; i++) {
    fout << v[i] << " ";
  }
}

bool Verif(vector < long long > & v, vector < long long > & sortat) {
  for (int i = 0; i < v.size(); i++)
    if (v[i] != sortat[i])
      return false;
  return true;
}
int main() {
  vector < long long > v, copie, sortat;
  int nrcifmax = 0, n;
  int x;
  int t[100], m[100], p, nrt, i;
  cout << "Teste:";
  fin >> nrt;
  cout << nrt << '\n';
  for (int i = 0; i < nrt; i++) {
    cout << "N = ";
    fin >> t[i];
    cout << t[i] << '\n';
    cout << "Max = ";
    fin >> m[i];
    cout << m[i] << '\n';
  }
  for (p = 0; p < nrt; p++) {

    for (int i = 0; i < t[p]; i++) {
      int value = rand() % m[p];
      v.push_back(value);
      copie.push_back(value);
      if (nrcif(v[i]) > nrcifmax)
        nrcifmax = nrcif(v[i]);
    }
    fout << "Testul Numarul:" << p+1 << '\n';
    //Vector nesortat
    fout << "Vector nesortat" << '\n';
    for (i = 0; i < v.size(); i++) {
      fout << v[i] << " ";
    }
    fout << '\n';

    //STL Sort
    for (i = 0; i < copie.size(); i++)
      v[i] = copie[i];
    fout << "STL Sort" << '\n';
    auto start = high_resolution_clock::now();
    sort(v.begin(), v.end());
    auto stop = high_resolution_clock::now();
    for (i = 0; i < v.size(); i++)
      fout << v[i] << " ";
    fout << '\n';
    duration < double, std::milli > fp_ms = stop - start;
    fout << "STLSort:" << fp_ms.count() / 1000 << '\n';
    for (i = 0; i < v.size(); i++)
      sortat.push_back(v[i]);
    ///////////////////////////////////////////////////
    //Bubble Sort
    for (i = 0; i < copie.size(); i++)
      v[i] = copie[i];
    fout << "BubbleSort" << '\n';
    if (v.size() > 10000) {
      fout << "Vector prea mare pentru Bubble" << '\n';
    } else {
      auto start = high_resolution_clock::now();
      BubbleSort(v, v.size());
      auto stop = high_resolution_clock::now();
      for (i = 0; i < v.size(); i++)
        fout << v[i] << " ";
      fout << '\n';
      duration < double, std::milli > fp_ms = stop - start;
      fout << "BubbleSort:" << fp_ms.count() / 1000 << '\n';
      if (Verif(v, sortat) == true) fout << "Corect" << '\n';
      else fout << "Gresit" << '\n';
    }
    ///////////////////////////////////////////////////
    //Radix Sort
    for (i = 0; i < copie.size(); i++)
      v[i] = copie[i];
    fout << "RadixSort" << '\n';
    start = high_resolution_clock::now();
    RadixSort(v, nrcifmax);
    stop = high_resolution_clock::now();
    for (i = 0; i < v.size(); i++)
      fout << v[i] << " ";
    fout << '\n';
    fp_ms = stop - start;
    fout << "RadixSort:" << fp_ms.count() / 1000 << '\n';
    if (Verif(v, sortat) == true) fout << "Corect" << '\n';
    else fout << "Gresit" << '\n';
    ///////////////////////////////////////////////////
    //Merge Sort
    for (i = 0; i < copie.size(); i++)
      v[i] = copie[i];
    fout << "MergeSort" << '\n';
    start = high_resolution_clock::now();
    MergeSort(0, v.size() - 1, v);
    stop = high_resolution_clock::now();
    for (i = 0; i < v.size(); i++)
      fout << v[i] << " ";
    fout << '\n';
    fp_ms = stop - start;
    fout << "MergeSort:" << fp_ms.count() / 1000 << '\n';
    if (Verif(v, sortat) == true) fout << "Corect" << '\n';
    else fout << "Gresit" << '\n';
    ///////////////////////////////////////////////////
    //CountSort
    for (i = 0; i < copie.size(); i++)
      v[i] = copie[i];
    fout << "CountSort" << '\n';
    if (m[p] == 10) {
      start = high_resolution_clock::now();
      CountSort(v, v.size());
      stop = high_resolution_clock::now();
      for (i = 0; i < v.size(); i++)
        fout << v[i] << " ";
      fout << '\n';
      fp_ms = stop - start;
      fout << "CountSort:" << fp_ms.count() / 1000 << '\n';
      if (Verif(v, sortat) == true) fout << "Corect" << '\n';
      else fout << "Gresit" << '\n';
    } else fout << "Numerele sunt prea mari pentru Count Sort" << '\n';

  //QuickSort
  for (i = 0; i < copie.size(); i++)
    v[i] = copie[i];
  fout << "QuickSort" << '\n';
  start = high_resolution_clock::now();
  QuickSort(0, v.size() - 1, v);
  stop = high_resolution_clock::now();
  for (i = 0; i < v.size(); i++)
    fout << v[i] << " ";
  fout << '\n';
  fp_ms = stop - start;
  fout << "QuickSort:" << fp_ms.count() / 1000 << '\n';
  if (Verif(v, sortat) == true) fout << "Corect" << '\n';
  else fout << "Gresit" << '\n';
  for (i = 0; i < copie.size(); i++)
    v[i] = copie[i];
  /////////
  fout << "QuickSortMed3" << '\n';
  start = high_resolution_clock::now();
  QuickSortMed3(0, v.size() - 1, v);
  stop = high_resolution_clock::now();
  for (i = 0; i < v.size(); i++)
    fout << v[i] << " ";
  fout << '\n';
  fp_ms = stop - start;
  fout << "QuickSortMed3:" << fp_ms.count() / 1000 << '\n';
  if (Verif(v, sortat) == true) fout << "Corect" << '\n';
  else fout << "Gresit" << '\n';
  fout << '\n';
  v.clear();
  copie.clear();
  sortat.clear();
  }
  return 0;
}
