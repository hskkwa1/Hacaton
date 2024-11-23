%[Kvadraticka] = KvadratickaFunkcia;
y = Kvadraticka(5);
 
NAmeOfFile = 'Matice.mat';
FPath = fullfile('DataOutPut', NAmeOfFile);
Matica = matfile(FPath, "Writable",	true);

Matica.I = eye(10000);
Matica.R = randi([10 100], 10000);
Matica.B = Matica.R.^2;
MAtica.B = Matica.B + 1;

%Vytvorit maticu Z nahodnych celych cisel z intervalu -50 -> 50 rozmeru 50 
%50000 x 10000.
%Vytvorime maticu W rovnakeho rozmeru ako matica Z s prvok w_ij = 1, ak
%z_ij>0, w_ij+-1, ak z_ij<0 a w_ij=0, ak z_ij = 0.
%Napisat, aky cas sme potrebovali na vytvorenie matice Z a motice W.

% Nastavenie náhodného semena pre reprodukovateľnosť
rng('shuffle');

% Rozmery matice
rows = 50000;
cols = 10000;

% Vytvorenie matice Z s náhodnými celými číslami v intervale -50 -> 50
Z = randi([-50, 50], rows, cols);

% Inicializácia matice W
W = zeros(rows, cols);

% Vytvorenie matice W podľa podmienok
W(Z > 0) = 1;   % Ak je z_ij > 0, nastavíme w_ij na 1
W(Z < 0) = -1;  % Ak je z_ij < 0, nastavíme w_ij na -1
% W(Z == 0) už je prednastavené na 0

% (Voliteľné) Uloženie matíc do súborov pre neskoršie použitie
save('matica_Z.mat', 'Z');
save('matica_W.mat', 'W');

disp('Matice Z a W boli úspešne vytvorené.');