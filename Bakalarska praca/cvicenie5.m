clear; clc;

%Menu :
% Zadat kvadraticku funkciu pomocou koef. a,b,c
%Nakreslit graf zadanej kvadratickej funkcie.
%Vypocitat funkcne hodnoty kvadratickej funkcie pre vektor x v ktorom sa
%zadava min., max. hodnota a krok. Vytvor subor VystupKvadraticka.txt do ktoreho sa zapise
%vysledok


% Zadané koeficienty kvadratickej funkcie
a = input('Zadajte koeficient a: ');
b = input('Zadajte koeficient b: ');
c = input('Zadajte koeficient c: ');

% Zadané minimálne a maximálne hodnoty a krok
min_hodnota = input('Zadajte minimálnu hodnotu x: ');
max_hodnota = input('Zadajte maximálnu hodnotu x: ');
krok = input('Zadajte krok: ');

% Vytvorenie vektora x
x = min_hodnota:krok:max_hodnota;

% Vypocet funkcných hodnôt kvadratickej funkcie
y = a*x.^2 + b*x + c;

% Nakreslenie grafu
figure;
plot(x, y);
title('Graf kvadratickej funkcie');
xlabel('x');
ylabel('f(x)');
grid on;

% Uloženie výsledkov do súboru
vystup_file = 'VystupKvadraticka.txt';
fid = fopen(vystup_file, 'w');
fprintf(fid, 'x\tf(x)\n');
fprintf(fid, '%.4f\t%.4f\n', [x; y]);
fclose(fid);

disp(['Výsledky boli uložené do súboru: ' vystup_file]);