% author         Oliver Blaser
% date           15.09.2021
% copyright      MIT - Copyright (c) 2021 Oliver Blaser

% the values for to use in the unit tests

transpose(round(a_over_b_8bit([0;0;255;127],[255;0;0;255])))
transpose(round(a_over_b_8bit([0;0;255;127],[255;0;0;127])))
transpose(round(a_over_b_8bit([255;0;255;63],[0;255;0;255])))
transpose(round(a_over_b_8bit([255;0;255;127],[0;255;0;255])))
transpose(round(a_over_b_8bit([255;0;255;190],[0;255;0;255])))

transpose(round(a_over_b_8bit([255;0;255;63],[0;255;127;16])))
