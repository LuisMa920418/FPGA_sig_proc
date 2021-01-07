function refvector =  create_ref(real,imag)
  N = length(real);
  refvector = "static t_ref ref_input[]  = {"
  for i=1:N-1
    refvector = strcat(refvector,"t_ref(",mat2str(real(i)),",",mat2str(imag(i)),"),");
  endfor
  refvector = strcat(refvector," t_ref(",mat2str(real(N)),",",mat2str(imag(N)),")");
  
  refvector = strcat(refvector,"};");
  
  %refvector = strcat 
endfunction
