

[V,D]=eigs(@(x)prodNucle(x,L21,L22,L11,M11,M12),219,5)



function [y] = prodNucle(x,L21,L22,L11,M11,M12)
% [y] = prodNucle(L21,L22,L11,M11,M12,x)
% Esta funci�n realiza el producto matriz por vector ( y=A*x), donde A es la matriz que se obtiene de la discretizaci�n de la ecuaci�n de la difusi�n neur�tica en dos grupos de energ�a.
%  No se dispone de la matriz explicita ,  A= inv(L11)(M11+M12*inv(L22)*L21)), por tanto cuando se tiene que realizar el producto de A*y tenemos que realizar las operaciones siguientes:
%  el resultado se almacena en el vector y

	val1=M11.*x; % producto matriz diagonal por vector
	val2=L21.*x; %  producto matriz diagonal por vector
	%val3=gmres(L22,val2,10,1.e-7,1000); % Resoluci�n de sistema no sim�trico
	val3=cgs(L22,val2,1.e-7,1000); % Resoluci�n de sistema sim�trico y del +
	val3=M12.*val3; % Producto matriz diagonal por vector
	val1=val1+val3; %Suma de vectores
	%y=gmres(L11,val1,10,1.e-7,1000); %Resoluci�n de sistema no sim�trico
	y=cgs(L11,val1,1.e-7,1000); %Resoluci�n de sistema sim�trico y del +
end

