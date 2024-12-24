% Supongamos que A es la matriz asociada al escaner (CT) y que b es el
% sinograma obtenido al realizar un tac a un paciente
% Hay que que resolver (Ax=b) el sistema de ecuaciones lineales de dimensiones mxn:

% Nota 1.- puedes consultar la información del comendo QR, mediante el comando help qr
% Puedes probar todas las opciones.
% Una posibilidad de resolución es:
[c,R]=qr(A,b,0); 
 x=R\c;

% Si x^ es una aproximación a la solución del sistema de ecuaciones Ax=b
% para reconstruir la imagen de CT asociada al sinograma b podemos seguir 
% las siguientes sentencias:
dim=sqrt(length(x));  % Consideramos un CT de dimensiones cuadradas
IM=reshape(x, dim, dim);%Colocamos los datos en forma de matriz de píxeles (imagen)
figure, imcontrast(imshow(IM)) % Mostramos la imagen con posibilidad de modificar el contraste.

%  Nota 2.- Métodos más eficientes de resolución del sistema los podemos 
% encontrar en la librería suiteSparse QR. 
%  Bibliográfia;
%  CT image reconstruction with SuiteSparseQR factorization package
%  DOI: 10.1016/j.radphyschem.2019.04.039Part of ISSN: 0969-806X
%  https://www.google.com/search?client=firefox-b-d&q=suitesparseQR
%  https://dl.acm.org/doi/10.1145/2049662.2049670