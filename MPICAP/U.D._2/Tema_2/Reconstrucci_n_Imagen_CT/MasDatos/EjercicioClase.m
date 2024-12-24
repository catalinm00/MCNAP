clc
clear 
close all
% Cargamos la matriz del SRM en formato coordenado
A1=load('Matrix_A1.txt');
%Cargamos el vector resultado de las proyecciones realizadas
b=load('B1.txt');
%Observamos los 10 primeros elementos de la matriz
A1(1:10,:)
% se observa que el vector de índices de filas y columnas empieza en 0
% Hay que pasarlo a 1, pues se trabaja en MATLAB
A1(:,1)=A1(:,1)+1;
A1(:,2)=A1(:,2)+1;
% Formamos la matriz en formato disperso de MATLAB mediante el comando
% sparse
S=sparse(A1(:,1),A1(:,2),A1(:,3));
%Visualizamos la matriz
figure
spy(S)
title('estrucutra de la matriz S')
% Visualaizamos una parte de la matriz S
figure
spy(S(1:500,500:1000))
title('estrucutra de la matriz S(1:500,500:1000)')

% se puede observar los tipos de datos y su magnitud
whos

