function [ xn, tn, xtempn ] = aceleracion( x, t, xtemp )
h = x;

tn = (1 + sqrt(1 + 4*(t^2))) / 2;

xn = h + ((t - 1)/tn) * (h - xtemp);

xtempn = h;
end

