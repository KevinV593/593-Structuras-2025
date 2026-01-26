#include <windows.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

/* Tipos de funciones del DLL */
typedef void (*BigO_Start_Fn)(int);
typedef void (*BigO_Stop_Fn)();
typedef void (*BigO_Clear_Fn)();
typedef void (*BigO_Export_Fn)(const char*);

// Implementar búsqueda binaria
int binarySearch(std::vector<int>& v, int target)
{
    int left = 0, right = v.size() - 1;
    
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (v[mid] == target) return mid;
        if (v[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
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

    // Medir búsqueda binaria con diferentes tamaños
    for (int n = 500; n <= 10000; n += 500)
    {
        std::vector<int> v(n);
        for (int& x : v) x = rand();
        
        std::sort(v.begin(), v.end()); // Necesario para búsqueda binaria

        BigO_Start(n);
        binarySearch(v, v[n/2]); // Buscar elemento en el medio
        BigO_Stop();
    }

    BigO_Export("binarysearch_bigo.m");

    FreeLibrary(dll);
    return 0;
}