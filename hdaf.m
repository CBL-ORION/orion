function val=hdaf(n,sigma,x)  
  en=1.0;
  ft=zeros(n,1);
   ft(1)=1.0;
   if n > 1 
    for i=2:n
      ft(i)=ft(i-1)*i;
    end
   end

  
  for i=1:n
    en=en+((x*sigma^2)/2).^i/ft(i);
  end

  val=(en.*exp((-1.0)*x*(sigma^2)/2));


  
    