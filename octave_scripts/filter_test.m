 pkg load signal
a=1; %fir filter so a is zero always

imag_part = [];
%imag part, right side of reference
for i=0:49
  imag_part= [imag_part mod(i,10)];
endfor

real_part = 0:49; %left side of reference

 b_std=[10,22,31,31,22,10];
out_std_imag= filter(b_std,a,imag_part);
out_std_real= filter(b_std,a,real_part);
%f

%---------------------------------------------------------------------
 b_sym=[10,22,31,31,22,10];
out_sym_imag= filter(b_std,a,imag_part);

out_sym_real= filter(b_std,a,real_part);
%---------------------------------------------------------------------



amp=[1 1 0 0];
f=[0 0.25 0.75 1];


<<<<<<< HEAD
b_poly = remez(10, f,amp);  %in matlab use function firpm, in octave use function remez
=======
b_poly = remez(10, f,amp);  //in matlab use function firpm, in octave use function remez
>>>>>>> 80fffc13ee6cf7c4ab42225fc763f9677d7f95d2
b_poly = round(2^10*b_poly');%make it signed 11 bits

out_poly_1_imag=  round(upfirdn (imag_part, b_poly, 1, 2)/2^10);  %filter, downsample by two, divide by 2^10 to set unitary gain and round
out_poly_1_real=  round(upfirdn (real_part, b_poly, 1, 2)/2^10); 



refvector =  create_ref(out_poly_1_real,out_poly_1_imag);