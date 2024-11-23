% Nastavenie náhodného semena pre reprodukovateľnosť
rng('shuffle');

% Rozmery matice
rows = 50000;
cols = 10000;

% Meranie času na vytvorenie matice Z
tic; % Spustenie merania času
% Vytvorenie matice Z s náhodnými celými číslami v intervale -50 -> 50
Z = randi([-50, 50], rows, cols);
time_Z = toc; % Zastavenie merania času
fprintf('Čas potrebný na vytvorenie matice Z: %.4f sekúnd\n', time_Z);

% Meranie času na vytvorenie matice W
tic; % Spustenie merania času
% Inicializácia matice W
W = zeros(rows, cols);

% Vytvorenie matice W podľa podmienok
W(Z > 0) = 1;   % Ak je z_ij > 0, nastavíme w_ij na 1
W(Z < 0) = -1;  % Ak je z_ij < 0, nastavíme w_ij na -1
% W(Z == 0) už je prednastavené na 0

time_W = toc; % Zastavenie merania času
fprintf('Čas potrebný na vytvorenie matice W: %.4f sekúnd\n', time_W);

% (Voliteľné) Uloženie matíc do súborov pre neskoršie použitie
save('matica_Z.mat', 'Z');
save('matica_W.mat', 'W');

disp('Matice Z a W boli úspešne vytvorené.');