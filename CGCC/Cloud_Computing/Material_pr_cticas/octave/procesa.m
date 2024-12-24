cd <carpeta dentro del contenedor>	
load A;
load B;
x=A\B;
save x;
err=norm(x-ones(size(x)))