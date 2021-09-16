% Jose Martinez
% ECE520 Mini Project
% Prof. Mirzaei
% Reads data from txt file and plots it to a graph.

M = readmatrix('waveform.csv')
stairs(M(:, 1)', M(:, 2)', 'LineWidth', 2)
title('Waveform Generator Graph')
xlabel('period(ms)')
ylabel('Drop Value (mV)')
xlim([0 max(M(:,1))])
ylim([min(M(:,2)) max(M(:,2))])
grid on
