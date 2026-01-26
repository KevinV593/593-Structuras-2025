% Datos de medición
n = [500 1000 1500 2000 2500 3000 3500 4000 4500 5000 5500 6000 6500 7000 7500 8000 8500 9000 9500 10000 ];
t = [0.0005602 0.0011071 0.0018087 0.0022718 0.0031093 0.0036853 0.0041855 0.0046702 0.0056652 0.0064334 0.0068097 0.0070339 0.0070977 0.0072468 0.0075484 0.0078535 0.0092053 0.0096094 0.0104538 0.0107326 ];

% Modelos de complejidad
models = {
  'n', n;
  'n^2', n.^2;
  'n^3', n.^3;
  'log n', log(n);
  'n log n', n.*log(n);
  '2^n', 2.^n;
  'n!', arrayfun(@(x) factorial(min(x,10)), n)
};

% Ajuste y error
errors = zeros(size(models,1),1);
scales = zeros(size(models,1),1);

for i = 1:size(models,1)
  f = models{i,2};
  a = (f * t') / (f * f');
  scales(i) = a;
  errors(i) = norm(a*f - t);
end

figure; hold on; grid on;
plot(n, t, 'ko', 'DisplayName', 'Datos reales');
for i = 1:size(models,1)
  plot(n, scales(i)*models{i,2}, 'DisplayName', models{i,1});
end
xlabel('Tamaño de entrada n');
ylabel('Tiempo (s)');
title('Análisis de Complejidad Big-O');
legend('show');

[bestError, idx] = min(errors);
fprintf('Mejor ajuste Big-O: %s\n', models{idx,1});

% MergeSort.cpp ejecuta → Mide tiempos con DLL → Exporta datos MATLAB
%                                    ↓
%                          mergesort_bigo.m ajusta modelos
%                                    ↓
%                        Gráfica que confirma O(n log n)