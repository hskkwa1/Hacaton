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