tic;
Z = randi([-50, 50], 50, 1000);
time_Z = toc;
fprintf('Cas na vytvorenie matice Z je: %.2f s\n', time_Z);

tic;
W = zeros(50000, 10000);
W(Z > 0) = 1;   
W(Z < 0) = -1;
time_W = toc;
fprintf('Cas na vytvorenie matice W: %.2f s\n', time_W);