#include <windows.h>
#include <vector>
#include <iostream>
#include <cstdlib>

/*  Tipos de funciones del DLL  */
typedef void (*BigO_Start_Fn)(int);
typedef void (*BigO_Stop_Fn)();
typedef void (*BigO_Clear_Fn)();
typedef void (*BigO_Export_Fn)(const char*);


void merge(std::vector<int>& v, int l, int m, int r)
{
    std::vector<int> temp;
    int i = l, j = m + 1;

    while (i <= m && j <= r)
        temp.push_back(v[i] < v[j] ? v[i++] : v[j++]);

    while (i <= m) temp.push_back(v[i++]);
    while (j <= r) temp.push_back(v[j++]);

    for (int k = 0; k < (int)temp.size(); ++k)
        v[l + k] = temp[k];
}

void mergesort(std::vector<int>& v, int l, int r)
{
    if (l >= r) return;

    int m = (l + r) / 2;
    mergesort(v, l, m);
    mergesort(v, m + 1, r);
    merge(v, l, m, r);
}

int main()
{
    /* Cargar DLL */
    HMODULE dll = LoadLibraryA("DLLBigO.dll");
    if (!dll)
    {
        std::cerr << "No se pudo cargar DLLBigO.dll\n";
        return 1;
    }

    auto BigO_Start  = (BigO_Start_Fn)GetProcAddress(dll, "BigO_Start");
    auto BigO_Stop   = (BigO_Stop_Fn)GetProcAddress(dll, "BigO_Stop");
    auto BigO_Clear  = (BigO_Clear_Fn)GetProcAddress(dll, "BigO_Clear");
    auto BigO_Export = (BigO_Export_Fn)GetProcAddress(dll, "BigO_ExportMatlabScript");

    if (!BigO_Start || !BigO_Stop || !BigO_Clear || !BigO_Export)
    {
        std::cerr << "Error resolviendo símbolos del DLL\n";
        FreeLibrary(dll);
        return 1;
    }

    /* Usar el profiler */
    BigO_Clear();

    for (int n = 500; n <= 10000; n += 500)
    {
        std::vector<int> v(n);
        for (int& x : v)
            x = rand();

        BigO_Start(n);
        mergesort(v, 0, (int)v.size() - 1);
        BigO_Stop();
    }

    BigO_Export("mergesort_bigo.m");

    FreeLibrary(dll);
    return 0;
}