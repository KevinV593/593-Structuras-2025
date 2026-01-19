% Limpiar espacio de trabajo
clear; clc;

% Nombres de archivos
dll_name = 'LogComplexity.dll';
header_name = 'LogComplexity.hpp';
lib_name = 'LogComplexity';

% 1. Cargar la DLL si no está cargada
if ~libisloaded(lib_name)
    loadlibrary(dll_name, header_name);
    disp('Librería cargada exitosamente.');
end

% 2. Definir los tamaños de entrada (N) para probar
% Probaremos desde 10 hasta 1,000,000 elementos
input_sizes = [10, 100, 1000, 10000, 100000, 1000000, 5000000];
num_tests = length(input_sizes);

% Crear un arreglo vacío para recibir los tiempos/pasos
execution_times = zeros(1, num_tests);

% 3. Llamar a la función de la DLL
% MATLAB maneja los punteros automáticamente con 'libpointer' si pasamos las variables
% Pero aquí pasamos los arreglos directamente, MATLAB los convierte a punteros C.
[~, results] = calllib(lib_name, 'calculate_execution_times', input_sizes, execution_times, num_tests);

% Descargar la librería para liberar memoria
unloadlibrary(lib_name);

% 4. Graficar los resultados
figure;
plot(input_sizes, results, '-o', 'LineWidth', 2, 'MarkerSize', 6);
grid on;

% Estética del gráfico
title('Complejidad Logarítmica O(log n) - C++ DLL en Matlab');
xlabel('Tamaño de entrada (N) - Escala Logarítmica');
ylabel('Pasos de ejecución (Tiempo)');

% Nota: Para visualizar mejor una curva logarítmica en un rango tan amplio,
% a veces conviene poner el eje X en escala logarítmica también.
set(gca, 'XScale', 'log'); 

disp('Gráfico generado.');