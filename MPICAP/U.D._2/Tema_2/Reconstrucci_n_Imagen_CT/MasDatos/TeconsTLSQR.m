clc
clear 
close all
% Cargamos la matriz del SRM en formato coordenado
A=load('Matrix_A1.txt');
%Cargamos el vector resultado de las proyecciones realizadas
b=load('B.txt');
%Observamos los 10 primeros elementos de la matriz
A(1:10,:)
% se observa que el vector de índices de filas y columnas empieza en 0
% Hay que pasarlo a 1, pues se trabaja en MATLAB
A(:,1)=A(:,1)+1;
A(:,2)=A(:,2)+1;
% Formamos la matriz en formato disperso de MATLAB mediante el comando
% sparse
S=sparse(A(:,1),A(:,2),A(:,3));
%Visualizamos la matriz
figure
spy(S)
title('estructura de la matriz S')
% Visualaizamos una parte de la matriz S
figure
spy(S(1:500,500:1000))
title('estrucutra de la matriz S(1:500,500:1000)')

% se puede observar los tipos de datos y su magnitud
whos
% se resuleve el sistema Sx=b mediante el método lsqr con la opción básica
help lsqr

pause

[X,FLAG,RELRES,ITER,RESVEC,LSVEC]=lsqr(S,b);
 %se muestra la imagen recontruida img1=reshape(x,60,60);
n=sqrt(size(S,2));
imag1=reshape(X,n,n);
% for i=1:60
%    for j=1:60
%        imag1(i,j)=X(j+60*(i-1));
%    end;
% end;
figure, 
imshow(imag1), imcontrast
title('Imagen recontruida-sin indicar maxiter')
%_______________________
    pause
% se resuleve con maxiter =1000 

[X1,FLAG,RELRES,ITER,RESVEC,LSVEC]=lsqr(S,b, 1.e-6,1000);
n=sqrt(size(S,2));
imga1=reshape(X,n,n);
%se muestra la imagen recontruida

figure, 
imshow(imag1), imcontrast
title('Imagen recontruida-con maxiter=1000')
%_______________________
    pause
    

    

    [X_10,FLAG,RELRES,ITER,RESVEC,LSVEC]=lsqr(S,b, 1.e-6,10)
%se muestra la imagen recontruida
n=sqrt(size(S,2));
imag1=reshape(X,n,n);
figure, 
imshow(imag1), imcontrast
title('Imagen recontruida-con maxiter=10')
%_______________________
