function GenerujMaticu
n = input("Write your OWN number from 5 to 10000: ");
for attempt = 1:3
    if n >= 5 && n <= 10000
        break;
    else
        fprintf("Error\n")
       n = input("Write your OWN number from 5 to 10000: ");
    end
end

if n < 5 || n > 10000
    error('Wrong entery, you used up all 3 attepemps');
end
beginB = tic;
B = zeros(n);
for x = 1:n
    for y = 1:n
         B(x, y) = randi([0, 1]);
    end
end
vecNull = zeros(1,n);
B = B + diag(vecNull);
B = B .* B';
zaver = toc(beginB);
timeB = datetime('now');
save('DataInput\VstupStebelska.mat','n','B','timeB', 'zaver');
save ('DataInput\VystupStebelska.mat', 'n','B','timeB', 'zaver');
end
