% Požiadajte používateľa o zadanie písmena (A, B, C, D, E alebo FX)
volba = input('Zadajte svoju volbu (A, B, C, D, E alebo FX): ', 's');

% Požiadajte používateľa o veľkosť matice
rows = input('Zadajte počet riadkov matice: ');
cols = input('Zadajte počet stĺpcov matice: ');

% Vygenerujte náhodnú maticu s prvkami v intervale <-10, 10>
matica = randi([-10, 10], rows, cols);

% Použijeme switch na vytvorenie obsahu zadania podľa voľby
switch volba
    case 'A'
        zadanie = 'Toto je zadanie pre písmeno A.';
    case 'B'
        zadanie = 'Toto je zadanie pre písmeno B.';
    case 'C'
        zadanie = 'Toto je zadanie pre písmeno C.';
    case 'D'
        zadanie = 'Toto je zadanie pre písmeno D.';
    case 'E'
        zadanie = 'Toto je zadanie pre písmeno E.';
    case 'FX'
        zadanie = 'Toto je zadanie pre písmeno FX.';
    otherwise
        error('Neplatná voľba! Prosím, zadajte jedno z písmen A, B, C, D, E alebo FX.');
end

% Vytvárame názov súboru podľa voľby používateľa
nazovSuboru = ['Zadanie-', volba, '.txt'];

% Zapíšeme zadanie a maticu do súboru
fileID = fopen(nazovSuboru, 'w');
fprintf(fileID, '%s\n', zadanie);  % Zapíše text zadania
fprintf(fileID, '\nMatica:\n');    % Pridáme nadpis "Matica:"

% Zapíše maticu do súboru v riadkoch
for i = 1:rows
    fprintf(fileID, '%d ', matica(i, :));
    fprintf(fileID, '\n');
end

% Zatvoríme súbor
fclose(fileID);

% Informujeme používateľa o názve vytvoreného súboru
disp(['Zadanie a matica boli uložené do súboru: ', nazovSuboru]);
