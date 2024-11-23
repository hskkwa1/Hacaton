while true
    disp('--- Menu ---');
    disp('1. Zadať kvadratickú funkciu');
    disp('2. Nakresliť graf funkcie');
    disp('3. Vypočítať hodnoty funkcie pre vektor x a zapísať do súboru');
    disp('4. Ukončiť');
    
    choice = input('Vyberte možnosť: ');
    
    switch choice
        case 1
           
            a = input('Zadajte koeficient a: ');
            b = input('Zadajte koeficient b: ');
            c = input('Zadajte koeficient c: ');
            
            
            equation = sprintf('f(x) = %gx^2 %s %gx %s %g', a, sign_str(b), abs(b), sign_str(c), abs(c));
            disp(['Zadaná kvadratická funkcia je: ', equation]);
            
        case 2
            
            if exist('a', 'var') && exist('b', 'var') && exist('c', 'var')
                x = linspace(-10, 10, 100);
                y = a*x.^2 + b*x + c;
                
                plot(x, y);
                title(['Graf kvadratickej funkcie: ', equation]);
                xlabel('x');
                ylabel('f(x)');
                grid on;
            else
                disp('Najprv musíte zadať koeficienty funkcie (možnosť 1).');
            end
            
        case 3
            
            if exist('a', 'var') && exist('b', 'var') && exist('c', 'var')
                xmin = input('Zadajte minimálnu hodnotu x: ');
                xmax = input('Zadajte maximálnu hodnotu x: ');
                krok = input('Zadajte krok: ');
                
                x = xmin:krok:xmax;
                y = a*x.^2 + b*x + c; 
                
                
                fileID = fopen('VystupKvadraticka.txt', 'w');
                if fileID == -1
                    error('Súbor sa nepodarilo otvoriť.');
                end
                
                
                for i = 1:length(x)
                    fprintf(fileID, 'f(%.2f) = %.2f\n', x(i), y(i));
                end
               
             
                fclose(fileID);
                
                disp('Hodnoty funkcie boli zapísané do súboru VystupKvadraticka.txt.');
            else
                disp('Najprv musíte zadať koeficienty funkcie (možnosť 1).');
            end
            
        case 4
            disp('Program sa ukončil.');
            break;
            
        otherwise
            disp('Neplatná voľba, skúste znova.');
    end
end

function s = sign_str(value)
    if value >= 0
        s = '+';
    else
        s = '-';
    end
end

