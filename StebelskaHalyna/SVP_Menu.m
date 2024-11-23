function SVP_Menu
clc;
fprintf("-----------\n");
fprintf("You have entered the SVP_Menu\n");
fprintf("WE greed YOU\n");
fprintf("Finished procedure of SVP_Menu press: 0\n");
fprintf("Trigger function GenerujMaticu press: 1\n");
fprintf("Trigger function Vzdialenosti press: 2\n");
fprintf ("Trigger function Porovnania press: 3\n");
fprintf("Trigger function Statistika press: 4\n");
fprintf("We'll be glad to see YOU again");
fprintf("-----------\n");

entery = 0;
while entery >= 0 && entery <= 4
    entery = input('Write the entery: ');
    switch entery
        case 0
            disp("Finishing of procedure SVP_Menu\n");
            return
        case 1
            disp('Starting function GenerujMaticu');
            GenerujMaticu;
        case 2
            disp('Starting function Vzdialenosti');
            Vzdialenosti;
        case 3
            disp('Starting function Porovnania');
            Porovnania;
        case 4
            disp('Starting function Statistika');
            disp('Uncomplited');

    end
end
end



