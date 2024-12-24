function [ xn ] = filtro( x, w,alpha,mgrid )
% x es la solución aproximada de la imagen/seña.
%Esta almacenada en un array unidimensional
% w es un factor que depende del residuo del proceso
% alpha es el parámetro del filtro
%  mgrid es la resolución de la imagenmat = reshape(x, mgrid, mgrid);

mat2 = mat;
for i=2:mgrid-1
    for j=2:mgrid-1
        termino1 = q(w,mat(i,j),mat(i+1,j))+q(w,mat(i,j),mat(i,j+1))+q(w,mat(i,j),mat(i-1,j))+q(w,mat(i,j),mat(i,j-1));
        termino2 = q(w,mat(i,j),mat(i+1,j+1))+q(w,mat(i,j),mat(i-1,j+1))+q(w,mat(i,j),mat(i-1,j-1))+q(w,mat(i,j),mat(i+1,j-1));
        mat2(i,j) = (1/(4+4*alpha)) *(termino1 + alpha*termino2);
    end               
end

%xn = zeros(size(x));
xn = reshape(mat2, mgrid*mgrid, 1);


