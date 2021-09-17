% author         Oliver Blaser
% date           15.09.2021
% copyright      MIT - Copyright (c) 2021 Oliver Blaser

% normalized function, all values in range [0; 1]. Colors as 4x1 vector [r;g;b;a]
function result = a_over_b(a, b)
  if(isvector(a) && isvector(b))
    aa = a(4,1);
    ab = b(4,1);
    ar = aa + ab*(1 - aa);
    result = (a.*aa .+ b.*ab.*(1-aa)) ./ ar;
    result(4,1) = ar;
  else
    error ("a_over_b: expecting vector for a and b");
  endif
endfunction
