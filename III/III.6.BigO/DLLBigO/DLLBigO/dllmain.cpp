#include "pch.h"

#define BIGO_EXPORT extern "C" __declspec(dllexport)

/* ===============================
   Estado interno del profiler
   =============================== */

static std::chrono::high_resolution_clock::time_point g_start;
static int g_currentN = 0;

static std::vector<std::pair<int, double>> g_samples;

/* ===============================
   API pública del DLL
   =============================== */

BIGO_EXPORT void BigO_Start(int n)
{
    g_currentN = n;
    g_start = std::chrono::high_resolution_clock::now();
}

BIGO_EXPORT void BigO_Stop()
{
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - g_start;
    g_samples.emplace_back(g_currentN, elapsed.count());
}

BIGO_EXPORT void BigO_Clear()
{
    g_samples.clear();
}

BIGO_EXPORT void BigO_ExportMatlabScript(const char* filename)
{
    std::ofstream file(filename);
    if (!file.is_open()) return;

    /* ===============================
       Datos
       =============================== */
    file << "% Datos de medición\n";
    file << "n = [";
    for (auto& s : g_samples) file << s.first << " ";
    file << "];\n";

    file << "t = [";
    for (auto& s : g_samples) file << s.second << " ";
    file << "];\n\n";

    /* ===============================
       Modelos Big-O
       =============================== */
    file << "% Modelos de complejidad\n";
    file << "models = {\n";
    file << "  'n', n;\n";
    file << "  'n^2', n.^2;\n";
    file << "  'n^3', n.^3;\n";
    file << "  'log n', log(n);\n";
    file << "  'n log n', n.*log(n);\n";
    file << "  '2^n', 2.^n;\n";
    file << "  'n!', arrayfun(@(x) factorial(min(x,10)), n)\n";
    file << "};\n\n";

    /* ===============================
       Ajuste por mínimos cuadrados
       =============================== */
    file << "% Ajuste y error\n";
    file << "errors = zeros(size(models,1),1);\n";
    file << "scales = zeros(size(models,1),1);\n\n";

    file << "for i = 1:size(models,1)\n";
    file << "  f = models{i,2};\n";
    file << "  a = (f * t') / (f * f');\n";
    file << "  scales(i) = a;\n";
    file << "  errors(i) = norm(a*f - t);\n";
    file << "end\n\n";

    /* ===============================
       Gráfica
       =============================== */
    file << "figure; hold on; grid on;\n";
    file << "plot(n, t, 'ko', 'DisplayName', 'Datos reales');\n";

    file << "for i = 1:size(models,1)\n";
    file << "  plot(n, scales(i)*models{i,2}, 'DisplayName', models{i,1});\n";
    file << "end\n";

    file << "xlabel('Tamaño de entrada n');\n";
    file << "ylabel('Tiempo (s)');\n";
    file << "title('Análisis de Complejidad Big-O');\n";
    file << "legend('show');\n\n";

    /* ===============================
       Resultado
       =============================== */
    file << "[bestError, idx] = min(errors);\n";
    file << "fprintf('Mejor ajuste Big-O: %s\\n', models{idx,1});\n";

    file.close();
}

BOOL APIENTRY DllMain(HMODULE, DWORD, LPVOID)
{
    return TRUE;
}
