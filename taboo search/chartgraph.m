%Nale¿y zmieniæ nazwê pliku wejœciowego w linijce 6 w razie koniecznoœci

close all;
clear all;

output = importdata('output_duzy.csv');
[rows, cols] = size(output.data);
workers_amount = (rows)/2; %iloœæ pracowników

workers = [1:1:workers_amount];
solution = output.data(1:1:workers_amount,:);
solution2 = output.data(1:1:workers_amount,:);
tasks = output.data(workers_amount + 1 :1: workers_amount*2,:);
problems_amount = max(max(tasks)); %iloœæ problemów

max_time = solution(1,1);
for i = 1:workers_amount
    for n = 2:1:cols
        solution(i,n) = solution(i,n-1)+solution(i,n);
        if solution(i, n) > max_time
            max_time = solution(i, n);
        end
    end
end


figure(1)
N = workers_amount;
hold on;
ylabel('workers');
xlabel('time');
set(gca, 'YDir', 'reverse', 'YTickLabel', workers);
yticklabels('auto');
color = [1 1 1];



for j = 0:cols-1
    H = solution(:,cols - j);
    for i = 1:N
        hold on;
        h = barh(i, H(i));

        if tasks(i, cols - j) == 0
            color = [1 1 1];
        elseif tasks(i, cols - j) == 1
            color = [1 0 0];
        elseif tasks(i, cols - j) == 2
            color = [0.7 0 0];
        elseif tasks(i, cols - j) == 3
            color = [0.4 0.6 0.4 ];
        elseif tasks(i, cols - j) == 4
            color = [0 1 0];
        elseif tasks(i, cols - j) == 5
            color = [0 0.7 0];               
        elseif tasks(i, cols - j) == 6
            color = [0 0.4 0];   
        elseif tasks(i, cols - j) == 7
            color = [0 0 1];   
        elseif tasks(i, cols - j) == 8
            color = [0.5 0.5 0.5];   
        elseif tasks(i, cols - j) == 9
            color = [0 0 0.4];   
        elseif tasks(i, cols - j) == 10
            color = [0 0.7 0.7];   
        elseif tasks(i, cols - j) == 11
            color = [0 0.4 0.4];   
        elseif tasks(i, cols - j) == 12
            color = [0 1 1];   
        elseif tasks(i, cols - j) == 13
            color = [1 1 0];
        elseif tasks(i, cols - j) == 14
            color = [0.7 0.7 0];
        elseif tasks(i, cols - j) == 15
            color = [0.4 0.4 0 ];
        elseif tasks(i, cols - j) == 16
            color = [1 0 1];
        elseif tasks(i, cols - j) == 17
            color = [0.7 0 0.7];               
        elseif tasks(i, cols - j) == 18
            color = [0.4 0 0.4];   
        elseif tasks(i, cols - j) == 19
            color = [0.7 0.7 0.7];   
        elseif tasks(i, cols - j) == 20
            color = [0.4 0.4 0.4];   
        elseif tasks(i, cols - j) == 21
            color = [1 0 0.4];   
        elseif tasks(i, cols - j) == 22
            color = [0.2 0.7 0.7];   
        elseif tasks(i, cols - j) == 23
            color = [0 1 0.4];   
        elseif tasks(i, cols - j) == 24
            color = [0.3 0.4 0.5];   
        end
        
        
        
        %Okreslono jedynie 12 kolorów dla problemów, trzeba bêdzie to
        %zrobiæ w pêtli zale¿nej od iloœci problemów. 
        
        
        set(h, 'FaceColor', color,'EdgeColor', [1 1 1], 'LineWidth', 0.1);
    end
   
end
axis([0 max_time 0.5 workers_amount+0.5]);
hold off;


%figure(2)
%H = barh(workers, solution2, 'stacked');
%set(gca, 'YDir', 'reverse', 'YTickLabel', workers);
%ylabel('workers');
%label('time');

%H(1,2)
%subplot(1,2,2)
%H = barh(workers,solution,'stacked');
%set(H([2]),'Visible','off');
%set(gca, 'YDir', 'reverse', 'YTickLabel', workers);