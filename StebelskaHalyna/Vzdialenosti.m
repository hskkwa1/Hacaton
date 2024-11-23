function Vzdialenosti 
load ("DataInput\VystupStebelska.mat");

file = fullfile("DataOutput\OutputInfoStebelska.txt");
if exist(file, 'file') == 0
    file = fopen("DataOutput\OutputInfoStebelska.txt","w");
     fprintf(file,'%s Creating matrix B, wich parameters %d\n',timeB,n);
    fprintf(file,'Stebelska Halyna , 2 ročnik, fakulta FEI, P.M. .\n');
    fprintf(file,'¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬\n');
   
    fprintf(file,'Count of elements in matrix B: %d\n',n*n);
else 
    file = fopen('DataOutput\OutputInfoStebelska.txt','a');
A = B;
A = ones(n);
for a = 1:n
    for b = 1:n
        if a == b
            A(a,b) = randi([1 n]);
        end
    end
end
A = A.*A';

beginH = tic;
H = cell(1,n);
sssr = tic;
H{1} = A;
srsr = toc(sssr);

k = 2; 
while k <= n
    gptH = tic;
    H{k} = logical(H{1} * H{k-1});
    openaiH = toc(gptH);
    k = k + 1; 
end
finishH = toc(beginH);
save('DataOutput\Vystup.mat','H');

beginD = tic;
D = zeros(n);
schotchik =0;
for a=1:n
    for b = 1:n
        for k = 1:n
            schotchik = schotchik +1;
            if B(a,b) == 1
                D(a,b) = 0;
                break;
            end
            schotchik = schotchik +1;
            if H{k}(a,b) == 1
                D(a,b) = k;
                break;
            end
        end
    end
end
finishD = toc(beginD);
fprintf(file,'The requring time for crating matrix D: %d\n',finishD);
save('DataOutput\Vystup.mat', 'D');


E = ones(n);
tinkoff=0;
for k = 1:n
    if E == H{k}
        tinkoff = tinkoff +1;
    end
end
flag = (n-1)*(n-1)*n^2;
vohnyk = (n-1)*(n^3);
fprintf(file,'Count of addition operations in matrix creating time : %d\n', flag);
fprintf(file,'Count of multiplications in matrix creating time H: %d\n', vohnyk);
fprintf(file,'Count of comparisons of two real numbers in matrix creating time D: %d\n', schotchik);
fprintf(file,'The number of matrix H contains only units: %d\n',tinkoff);
fclose(file);
end


