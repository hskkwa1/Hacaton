function main()
    % Vygenerujeme vektor a s celými číslami z intervalu <0, 30> veľkosti 1 x 10
    a = randi([0, 30], 1, 10);

    % Otvoríme súbor pre zápis (s pridávaním výsledkov)
    fileID = fopen('SucetCisel.txt', 'w');
    fprintf(fileID, 'Vektor a: %s\n\n', num2str(a)); % Zapíše generovaný vektor do súboru

    while true
        % Požiadame používateľa o zadanie celého čísla K
        K = input('Zadajte hodnotu K: ');

        % Hľadáme trojice a_i, a_j, a_k pre zadané K
        found = findTriplet(a, K, fileID);
        
        % Spýtame sa používateľa, či chce pokračovať
        odpoved = input('Chcete zadať ďalšie K? (ano/nie): ', 's');
        if strcmpi(odpoved, 'nie')
            break; % Ukončíme cyklus, ak používateľ nechce pokračovať
        end
    end

    % Zatvoríme súbor
    fclose(fileID);

    % Informujeme používateľa o výsledku
    disp('Výsledky boli zapísané do súboru SucetCisel.txt.');
end

function found = findTriplet(a, K, fileID)
    found = false; % Inicializácia pre zistenie, či trojica existuje

    % Hľadáme všetky trojice a_i, a_j, a_k tak, že a_i + a_j + a_k = K
    for i = 1:length(a)
        for j = i+1:length(a)
            for k = j+1:length(a)
                if a(i) + a(j) + a(k) == K
                    % Ak nájdeme trojicu, zapíšeme ju do súboru
                    fprintf(fileID, 'Trojica s požadovaným súčtom: a_%d = %d, a_%d = %d, a_%d = %d\n', ...
                        i, a(i), j, a(j), k, a(k));
                    found = true; % Nastavíme found na true
                    return; % Odchádzame z funkcie
                end
            end
        end
    end

    % Ak trojica neexistuje, zapíšeme túto informáciu do súboru
    if ~found
        fprintf(fileID, 'Neexistuje trojica s požadovaným súčtom K = %d.\n', K);
    end
end
