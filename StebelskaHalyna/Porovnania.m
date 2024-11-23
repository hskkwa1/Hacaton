function Porovnania

load ('DataOutput\Vystup.mat','D');
load ('DataInput\VstupStebelska.mat','n')


x = input('Write YOUR coordinate of x : ');
y = input('Write YOUR coordinate of y : ');
if x >= n && y >= n && x < 1 && y < 1
    disp('Error');
    return;
end

file = fullfile("DataOutput\VystupInfoStebelska.txt");
if exist(file, 'file') == 0
    file = fopen("DataOutput\VystupInfoStebelska.txt","w");
   fprintf(file,'Stebelska Halyna , 2 ročnik, fakulta FEI, P.M. .\n');
    fprintf(file,'¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬\n');
   
else 
    file = fopen('DataOutput\VystupInfoStebelska.txt','a');


for i = 1:n
    for j = 1:n
        if D(i,j) < D(x,y)
            fprintf(file,'Distance i=%d a j=%d, smaller than x=%d and y=%d.\n',i,j,x,y);
        end   
    end
end
fclose(file);
end