clear; clc;

%rows = input('Zadajte počet riadkov matice: ');
%cols = input('Zadajte počet stĺpcov matice: ');

%A = randi([-100, 100], rows, cols);

%save ('MaticaA',"A");
%disp('Vygenerovaná matica:');
%disp(A);
load('MaticaA.mat');

[rows, cols] = size(A);
B = zeros(rows,cols);

for i= 1:rows
    for j = 1:cols
        if A(i, j)>0
            B(i,j)=1;
        elseif A(i,j)<0
            B(i,j) = -1;
        end
    end
end

writematrix(B, 'ZnamienkovaMaticaB.txt');
fileID = fopen('cv4.m')

% Vytvorite funkciu f(x) = a*x^3 - b*e^x +c.
% Vytvorite vektor x1 ktory bude mat nahodne realne cisla z intervalu<-30,30> rozmeru
% m x 1
% Vypocitajte funkcie hodnoty v bide x1, t.j. f(x1).
%Vysledok zapiste do suboru HodnotyFunkcie.txt v tvare pr. Hodnota
% funkcie je f(2.5) = 55,24. pod seba.



a = input('Zadajte hodnotu pre a: ');
b = input('Zadajte hodnotu pre b: ');
c = input('Zadajte hodnotu pre c: ');

f = @(x) a * x.^3 - b * exp(x) + c;


m = input('Zadajte počet riadkov vektora x1: ');
x1 = -30 + (30 + 30) * rand(m, 1); %vektor


f_values = f(x1); %vypocet hodnot


fileID = fopen('HodnotyFunkcie.txt', 'w');
for i = 1:length(x1)
    fprintf(fileID, 'Hodnota funkcie je f(%.2f) = %.2f\n', x1(i), f_values(i));
end
fclose(fileID); %zapis vysledkov

disp('Výsledky boli zapísané do súboru HodnotyFunkcie.txt.');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fileID = fopen('Vysledky.txt', 'w');
pokus = 0;

while true
    pokus = pokus + 1;
    
    A = rand() * 100;
    B = rand() * 100;
    
    C = A + B;
   
    if C < 10
        fprintf(fileID, 'Podarilo sa najst take C=%.2f pri takom A=%.2f a B=%.2f\n', C, A, B);
        fprintf(fileID, 'Počet pokusov: %d\n', pokus);
        break;
    end
end

fclose(fileID);

disp('Podarilo sa nájsť také číslo C. Výsledok bol zapísaný do súboru Vysledky.txt.');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Volim si pismene A, B,C,D,E,FX. Na zaklade tejto volby sa vytvori %zadanie
%zadanie, ktore sa zapise s nazvom: Zadanie-A.txt ( A zodpoveda volbe ).
%Dostanem informaciu,kde to je zadanie ,pouzijeme switch (mathlab)
a=0;
while a == 0

volba = input('Zadaj svoje poziadane hodnotenie (A, B, C, D, E alebo FX): ', 's');

% Použijeme switch na vytvorenie obsahu zadania podľa voľby
switch volba

    case 'A'
        zadanie = 'Toto je zadanie pre písmeno A.';a=1;
    case 'B'
        zadanie = 'Toto je zadanie pre písmeno B.';a=1;
    case 'C'
        zadanie = 'Toto je zadanie pre písmeno C.';a=1;
    case 'D'
        zadanie = 'Toto je zadanie pre písmeno D.';a=1;
    case 'E'
        zadanie = 'Toto je zadanie pre písmeno E.';a=1;
    case 'FX'
        zadanie = 'Toto je zadanie pre písmeno FX.';a=1;
    otherwise
        error('Neplatná voľba! Prosím, zadajte jedno z písmen A, B, C, D, E alebo FX.');
end
end

% Vytvárame názov súboru podľa voľby používateľa
nazovSuboru = ['Zadanie-', volba, '.txt'];

% Zapíšeme zadanie do súboru
fileID = fopen(nazovSuboru, 'w');
fprintf(fileID, '%s\n', zadanie);
fclose(fileID);

% Informujeme používateľa o názve vytvoreného súboru
disp(['Zadanie bolo vytvorené a uložené do súboru: ', nazovSuboru]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5555
%Vygeneruj vektor cele cisla a_1 ay a_10  z intervalu <0,30>
%Zvolime celociselnu hodnotu K.
%Testujeme, ci existuje tri cisla a_i,a_j,a_k take, ze a_i+a:j+a_k = K
%ak nie je taka trojica tak piseme ze neexistuje

% Vygenerujeme vektor a s celými číslami z intervalu <0, 30> veľkosti 1 x 10
a = randi([0, 30], 1, 10);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
K = input('Zadajte hodnotu K: ');
fileID = fopen('SucetCisel.txt', 'w');

found = false;

for i = 1:length(a)
    for j = i+1:length(a)
        for k = j+1:length(a)
            if a(i) + a(j) + a(k) == K
                
                fprintf(fileID, 'Trojica s požadovaným súčtom: a_%d = %d, a_%d = %d, a_%d = %d\n', ...
                    i, a(i), j, a(j), k, a(k));
                found = true;
                break;
            end
        end
        if found
            break;
        end
    end
    if found
        break;
    end
end

if ~found
    fprintf(fileID, 'Neexistuje trojica s požadovaným súčtom K = %d.\n', K);
end

fclose(fileID);

disp('Výsledok bol zapísaný do súboru SucetCisel.txt.');


