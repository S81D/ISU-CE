%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Correlation Analysis Infrastructure Part 1 %
%         --> Selecting the ASICs            %
% ------------------------------------------ %
%   This script is to be run first, and is   %
%      tasked with identifying the ASIC      %
%  centerpoints, which are to be used in the %
%     correlation analysis (next script).    %
% 
%    Two figures will automatically open.    %
% The first window that appears will be the  %
%  first dataset. Hover the cursor over the  %
%  data and, in ascending order, select the  %
%   rough centerpoints of the ASICs. Don't   %
%  worry about how perfect the selection is; %
%    just select some point on the ASIC's    %
% front surface. Once you have selected all  %
%   the ASIC centerpoints for figure 1, the  %
%   figure will automatically close and the  %
% process is repeated for figure 2 (data 2). %
% If any of the correlation images produced  %
% by the next script look abnormal, go back  %
% and re-select the centers more carefully.  %
% ------------------------------------------ %
%            Author: Steven Doran            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


close all;
clear all;
pathname = '';

% The fixture shown *should be* in the correct orientation (not mirrored). 
% Ensure this is true before proceeding. The figures below that will pop up
% are transposed so that they reflect the correct orientation. 
% Select the ASIC centerpoints in ascending order, as to match the correlation
% analysis ordering technique.

% Gate on the front wall of the ASIC, so that the features are 
% clearly seen and defined
start_time_index=1; 
end_time_index=100;

disp(' ');
disp('Loading Figures...');

% % % % % % % % % % % % % % % % % % % % %
%           Parameterization            %
% % % % % % % % % % % % % % % % % % % % %

% Load in data files
t_1 = 'data/20_49.sdt';
t_2 = 'data/20_49_after_100.sdt';

% specify dimensions of data file
x_dim = 960;   % running this code with some extremely large value (> 1500 or so)
y_dim = 780;   % will yield errors that will tell you the limiting dim. of the file

% specify number of ASICs to be analyzed
N = 8;         % how many ASICs were scanned and are in your dataset

% % % % % % % % % % % % % % % % % % % % %

t_Data_1 = ReadSDTFileIW(fullfile(pathname,t_1));
t_Data_2 = ReadSDTFileIW(fullfile(pathname,t_2));
datachannel =2;
       
for iz=1:1:1;
   for ii=1:1:x_dim;
       for ij=1:1:y_dim;
           
        t_image_data_1(iz,ii,ij)=squeeze(max(abs(t_Data_1(datachannel).rawdata(ii,ij,start_time_index:end_time_index))));
        t_image_data_2(iz,ii,ij)=squeeze(max(abs(t_Data_2(datachannel).rawdata(ii,ij,start_time_index:end_time_index))));
        
       end
   end
end

% Figure 1 (dataset1)
f1=figure('Renderer', 'painters', 'Position', [10 10 1600 1600], 'visible', 'on');
imagesc(squeeze(t_image_data_1(1,:,:))');  % add prime to shift it into what we see
colormap(gca,'jet')
caxis([0.0 0.5])
colorbar;

[x,y] = ginput(N);

fid1 = fopen("dataset_1.txt", 'w');
for it=1:1:N;
    x_text = int16(x(it));
    y_text = int16(y(it));
    fprintf(fid1, '%i', x_text);
    fprintf(fid1, '%s', ' ');
    fprintf(fid1, '%i\n', y_text);
end
fclose(fid1);

% dataset 2
f2=figure('Renderer', 'painters', 'Position', [10 10 1600 1600], 'visible', 'on');
imagesc(squeeze(t_image_data_2(1,:,:))');  % add prime to shift it into what we see
colormap(gca,'jet')
caxis([0.0 0.5])
colorbar;

[x,y] = ginput(N);

fid = fopen("dataset_2.txt", 'w');
for it=1:1:N;
    x_text = int16(x(it));
    y_text = int16(y(it));
    fprintf(fid, '%i', x_text);
    fprintf(fid, '%s', ' ');
    fprintf(fid, '%i\n', y_text);
end
fclose(fid);

close all;

disp('ASIC Coodinates recorded in dataset_1.txt and dataset_2.txt');
disp(' ');
disp('done');
disp(' ');

