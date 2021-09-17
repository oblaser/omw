% author         Oliver Blaser
% date           15.09.2021
% copyright      MIT - Copyright (c) 2021 Oliver Blaser

% byte function, all values in range [0; 255]. Colors as 4x1 vector [r;g;b;a]
function result = a_over_b_8bit(a, b)
  if(isvector(a) && isvector(b))
    tmpA = a ./ 255;
    tmpB = b ./ 255;
    result = a_over_b(tmpA, tmpB) .* 255;
  else
    error ("a_over_b_8bit: expecting vector for a and b");
  endif
endfunction
