function [kvad] = KvadratickaFunkcia
clc;
disp(['Zadaj kvadraticku funkciu f(x) = ' num2str(a), '*x^2 +', num2str(b), '*x+', num2str(c),'.'])
a= input ('Zadaj koeficient a =');
clc;
disp(['Zadaj kvadraticku funkciu f(x) = ' num2str(a), '*x^2 +', num2str(b), '*x+', num2str(c),'.'])
b = input ('Zadaj koeficient b = ');
clc;
disp(['Zadaj kvadraticku funkciu f(x) = ' num2str(a), '*x^2 +', num2str(b), '*x+', num2str(c),'.'])
c = input ('Zadaj koeficient c = ');
clc;
disp(['Zadaj kvadraticku funkciu f(x) = ' num2str(a), '*x^2 +', num2str(b), '*x+', num2str(c),'.'])
kvad = @(x)(a*x.^2+b*x+c);
end