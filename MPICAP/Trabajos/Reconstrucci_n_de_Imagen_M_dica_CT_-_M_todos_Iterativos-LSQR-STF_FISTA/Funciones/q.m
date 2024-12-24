function [ x ] = q( w,y,z )
if (abs(y-z)<w)
    x = (y+z)/2;
else if (y-z>=w)
        x = y-w/2;
    else
        x = y+w/2;
    end
end
end