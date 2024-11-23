clear; clc;

%Menu:
%Zadajte kvadraticku funkciu pomocou koef. a, b, c.
%Nakreslit graf zadanej kvadratickej funkcie.
%Vypocitat funkcne hodnory kvadratickej funkcie pre vektor x, v ktorom sa
%tada min., max. hodnot a krok. Vysledok sa zapise da suboru
%VystypKvadraticka.txt


% Inicializácia koeficientov (predvolené hodnoty)
a = 0; b = 0; c = 0;
x_min = -10; x_max = 10; krok = 1;

while true
    % Zobrazenie menu
    disp('--- Menu ---');
    disp('1. Zadajte koeficienty kvadratickej funkcie');
    disp('2. Nastavte rozsah a krok pre výpočet funkčných hodnôt');
    disp('3. Vypočítajte funkčné hodnoty a uložte do súboru');
    disp('4. Nakreslite graf kvadratickej funkcie');
    disp('5. Ukončite program');
    
    volba = input('Vyberte si možnosť: ');
    
    switch volba
        case 1
            % Zadanie koeficientov kvadratickej funkcie
            a = input('Zadajte koeficient a: ');
            b = input('Zadajte koeficient b: ');
            c = input('Zadajte koeficient c: ');
            % Vypíše rovnica
            fprintf('Vaša kvadratická rovnica je: f(x) = %.2fx^2 + %.2fx + %.2f\n', a, b, c);
            disp('Koeficienty boli úspešne nastavené.');

        case 2
            % Nastavenie rozsahu a kroku pre výpočet hodnôt
            x_min = input('Zadajte minimálnu hodnotu x: ');
            x_max = input('Zadajte maximálnu hodnotu x: ');
            krok = input('Zadajte krok: ');
            disp('Rozsah a krok boli úspešne nastavené.');

        case 3
            % Výpočet funkčných hodnôt a uloženie do súboru
            x_vektor = x_min:krok:x_max;
            y_vysledky = a*x_vektor.^2 + b*x_vektor + c;
            
            % Uloženie do súboru
            fileID = fopen('VystupKvadraticka.txt', 'w');
            fprintf(fileID, 'x\tf(x)\n'); % Hlavička tabuľky
            for i = 1:length(x_vektor)
                fprintf(fileID, '%.2f\t%.2f\n', x_vektor(i), y_vysledky(i));
            end
            fclose(fileID);
            disp('Výsledky boli uložené do súboru VystupKvadraticka.txt');

        case 4
            % Nakreslenie grafu kvadratickej funkcie
            x_vektor = x_min:krok:x_max;
            y_vysledky = a*x_vektor.^2 + b*x_vektor + c;
            figure;
            plot(x_vektor, y_vysledky, 'b-', 'LineWidth', 2);
            title('Graf kvadratickej funkcie');
            xlabel('x');
            ylabel('f(x)');
            grid on;
            disp('Graf bol úspešne nakreslený.');

        case 5
            % Ukončenie programu
            disp('Program sa ukončuje.');
            break;
            
        otherwise
            disp('Neplatná voľba. Skúste znova.');
    end
end
