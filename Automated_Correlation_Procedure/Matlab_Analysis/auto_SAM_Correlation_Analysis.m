%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           Correlation Analysis for SAM ASIC data           %
% ---------------------------------------------------------- %
%    Performs a correlation analysis between two datasets.   %
%     Designed for comparing ASICs before and after cold     %
%    cycling. This correlation analysis utlizes acoustic     %
%      microscopy data taken the ISU CNDE, allowing for      %
% non-destructive analysis of the ASICs' internal structure, %
%   to see how they have changed due to cryogenic exposure.  %
% ---------------------------------------------------------- %
% -- 1. Reads in .sdt acoustic datasets and centering info   %
% -- 2. Slices the data ASIC-wise for each dataset           %
% -- 3. Crops data to exclude the pin region                 %
% -- 3. Performs allignment to minimize anti-correlations    %
% -- 4. Performs correlation analysis between the datasets   %
% -- 5. Produces heatmap showing regions of anti-correlation %
% -- 6. Outputs heatmap and other plots to .png files        %
% -- 7. Repeats code for multiple time (depth) windows       %
% ---------------------------------------------------------- %
%                   Author: Steven Doran                     %
%        --> with correlation analysis section code          %
%                by: Navaneeth Poonthottathill               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;
pathname = '';

disp(' ');
disp('Loading Fixture Data...')

%%%%%%%%%%%%%%%%%%%%%%%%%%%
%     Parameterization    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Load in fixture data

data_1 = 'data/20_49.sdt';
data_2 = 'data/20_49_after_100.sdt';

% dataset names (used for saving the files)

name_1 = '0';
name_2 = '100';

% Load in the .txt file containing the rough ASIC centerpoints

centers_1 = readmatrix('dataset_1.txt');
centers_2 = readmatrix('dataset_2.txt');

% these are loaded into a matrix, with dimensions (x,y)
% M(1,1) = first ASIC, x coordinate
% M(3,2) = third ASIC, y coordinate
% etc...

% The centerpoints were selected within a viewing window that was transposed. 
% The coordinates are flipped back into analysis mode.

% Specify number of ASICs in the dataset

N_ASICs = 8;

% Specify the time windows in which the correlation analysis will be done.
% These windows can be optimized by investigating the waveforms through
% A-scans. The time_loop array will be the directories in which the images
% are placed.

time_loop = {'t1_100', 't100_150', 't150_200', 't200_300'};
time_loop_Ni = [1 100 150 200];
time_loop_Nf = [100 150 200 300];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

t_1 = data_1;
t_2 = data_2; 

% This .m file requires the associated ReadSDTFileIW.m file
t_Data_1 = ReadSDTFileIW(fullfile(pathname,t_1));
t_Data_2 = ReadSDTFileIW(fullfile(pathname,t_2));
datachannel =2;

% % % % % % % % % % % % % % % % % % % % % % % % % % % % % 

for z=1:1:N_ASICs; 

    disp(' ');
    disp(strcat('ASIC_', num2str(z)));
    disp('----------------')

    % Step 1: Find an appropriate "window" for each ASIC. We have the
    % centerpoints from the previous script. We can load in the amplitude
    % value and search along the ASIC until we find the "edge" (amplitude
    % value will drop below 0.45 or so; this is very similar to the
    % edge-finding technique that will be employed later). Once the
    % "window" is found for each ASIC, we can then re-load the full ASIC
    % data and proceed. This technique is used for two reasons: firstly,
    % the full fixture data is tight - we can't load more than a few
    % pixels outside each ASIC or else we will bump into no-data. Secondly,
    % we only want the ASIC information and not the ridges of the fixture
    % or other ASICs. This can throw off the correlation analysis.

    edges_in_x_1 = [];
    edges_in_y_1 = []; 

    edges_in_x_2 = [];
    edges_in_y_2 = []; 

    % Front wall timegate - easy to analyze the edge as the slice point
    t_i = 1;
    t_f=100;

    % centerpoints of the ASICs

    c1_y = centers_1(z,2);
    c1_x = centers_1(z,1);

    c2_y = centers_2(z,2);
    c2_x = centers_2(z,1);


    % "walk" in both directions from the centerpoint until an amplitude
    % value under 0.45 is reached (this is the edge of the ASIC). Repeat
    % for the other dataset

    % Dataset 1

    % just loop through ~about the ASIC's width (unless you pick a point
    % dangerously close to the far edge, 100 pixels *should* get you to the
    % near edge (since the entire ASIC is ~103 pixels in width).

    for ix=1:1:100;   % this may need to be adjusted, depending on the size

        samp1a = max(abs(squeeze(t_Data_1(datachannel).rawdata((c1_x - ix),c1_y,t_i:t_f))));
        samp1b = max(abs(squeeze(t_Data_1(datachannel).rawdata((c1_x - ix),(c1_y-5),t_i:t_f))));
        samp1c = max(abs(squeeze(t_Data_1(datachannel).rawdata((c1_x - ix),(c1_y+5),t_i:t_f))));

        % this is done for 3 different rows, to ensure we don't find some random
        % low-value point that isn't actually the edge. Sometimes the text
        % on the surface of the ASIC will have a value < 0.45, so to be
        % safe we spread the 3 rows out by 5 pixel points. If you selected
        % a centerpoint that was really close (< 5 pixels) to an edge, you
        % still should be fine in principle, since the condition below for
        % identifying an edge requires all three rows to be under the
        % threshold.

        if (samp1a < 0.45) && (samp1b < 0.45) && (samp1c < 0.45);
            edges_in_x_1(end+1) = (c1_x-ix);
            break
        end
    end

    for iy=1:1:100;   % this may need to be adjusted, depending on the size

        samp1a = max(abs(squeeze(t_Data_1(datachannel).rawdata((c1_x),(c1_y - iy),t_i:t_f))));
        samp1b = max(abs(squeeze(t_Data_1(datachannel).rawdata((c1_x - 5),(c1_y - iy),t_i:t_f))));
        samp1b = max(abs(squeeze(t_Data_1(datachannel).rawdata((c1_x + 5),(c1_y - iy),t_i:t_f))));

        if (samp1a < 0.45) && (samp1b < 0.45) && (samp1c < 0.45);
            edges_in_y_1(end+1) = (c1_y-iy);
            break
        end
    end


    % Dataset 2

    for ix=1:1:100;   % this may need to be adjusted, depending on the size
        samp2a = max(abs(squeeze(t_Data_2(datachannel).rawdata((c2_x - ix),c2_y,t_i:t_f))));
        samp2b = max(abs(squeeze(t_Data_2(datachannel).rawdata((c2_x - ix),(c2_y-5),t_i:t_f))));
        samp2c = max(abs(squeeze(t_Data_2(datachannel).rawdata((c2_x - ix),(c2_y+5),t_i:t_f))));
        if (samp2a < 0.45) && (samp2b < 0.45) && (samp2c < 0.45);
            edges_in_x_2(end+1) = (c2_x-ix);
            break
        end
    end

    for iy=1:1:100;   % this may need to be adjusted, depending on the size
        samp2a = max(abs(squeeze(t_Data_2(datachannel).rawdata((c2_x),(c2_y - iy),t_i:t_f))));
        samp2b = max(abs(squeeze(t_Data_2(datachannel).rawdata((c2_x - 5),(c2_y - iy),t_i:t_f))));
        samp2c = max(abs(squeeze(t_Data_2(datachannel).rawdata((c2_x + 5),(c2_y - iy),t_i:t_f))));
        if (samp2a < 0.45) && (samp2b < 0.45) && (samp2c < 0.45);
            edges_in_y_2(end+1) = (c2_y-iy);
            break
        end
    end

    
    % Step 2: Load in the data, slicing out each individual ASIC from the
    % full dataset.

    % The ASICs are roughly ~103 pixels in width and in height. Using the 
    % window edges found above, we can "slice" out each ASIC from the
    % dataset, roughly. This will change depending on the size of the ASICs scanned. 
    % We include here a small buffer on each side, so that we capture the 
    % entirity of the ASIC.

    ASIC_size = 103;  % asic size in pixels
    buffer = 3;       % number of pixels beyond the edge we slice out
    
    x_i_1 = edges_in_x_1 - buffer;
    x_f_1 = edges_in_x_1 + ASIC_size + buffer;
    y_i_1 = edges_in_y_1 - buffer;
    y_f_1 = edges_in_y_1 + ASIC_size + buffer;

    x_i_2 = edges_in_x_2 - buffer;
    x_f_2 = edges_in_x_2 + ASIC_size + buffer;
    y_i_2 = edges_in_y_2 - buffer;
    y_f_2 = edges_in_y_2 + ASIC_size + buffer;

    x_dim = ASIC_size + 2*buffer;   % size of data window
    y_dim = ASIC_size + 2*buffer;
    
    % % % % % % % % % % % % % % % % % % % % % % % % % % % %

    s1 = squeeze(t_Data_1(datachannel).rawdata(x_i_1:x_f_1,y_i_1:y_f_1,t_i:t_f));
    s2 = squeeze(t_Data_2(datachannel).rawdata(x_i_2:x_f_2,y_i_2:y_f_2,t_i:t_f));

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%       

    % Step 3: Alignment procedure. Perform alignment in all directions (x,y
    % = spatial, and in time (z/height direction).

    % For the individual cryocycle edge search (allignment procedure),
    % we want the 'image' searched to be the maximum signal amplitude,
    % as it provides a clean edge for alligning the datasets

    for iz=1:1:1;  % for matrix-dimensionality reasons
        for ix=1:1:x_dim;
            for iy=1:1:y_dim;
                t_image_data_1(iz,ix,iy) = squeeze(max(abs(s1(ix,iy,t_i:t_f))));
                t_image_data_2(iz,ix,iy) = squeeze(max(abs(s2(ix,iy,t_i:t_f))));
            end
        end
    end
    

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % These slice points will serve as marking the edges of the ASIC

    % Search for slice points - in Y

    % Finding the 'left' edge
    %%%%%%%%% First cryocycle %%%%%%%%%
    sides = [];
    for ix=1:1:x_dim;
        for iy=1:1:y_dim;
            if t_image_data_1(1,ix,iy) > 0.45;
                sides(end+1) = iy;
                break
            end
        end
    end
    
    % remove largest value to improve 'true' mean value
    sides(sides==max(sides)) = [];
    
    % calculate mean of values, round to nearest int
    mu = int16(mean(sides));
    
    %%%%%%%% Second cryocycle %%%%%%%%%
    sides2 = [];
    %t_image_data_1(1,:,:)
    for ix=1:1:x_dim;
        for iy=1:1:y_dim;
            if t_image_data_2(1,ix,iy) > 0.45;
                sides2(end+1) = iy;
                break
            end
        end
    end
    
    sides2(sides2==max(sides2)) = [];
    mu2 = int16(mean(sides2));

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    % mu and mu2 are the slice 'region' for a slice in dim-Y
    % need to perform the same for X
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Search for slice point - in X
    
    % Finding the 'top' edge
    %%%%%%%%% First cryocycle %%%%%%%%%
    sidesX = [];
    for iy=1:1:y_dim;
        for ix=1:1:x_dim;
            if t_image_data_1(1,ix,iy) > 0.45;
                sidesX(end+1) = ix;
                break
            end
        end
    end
    
    % remove largest value to improve 'true' mean value
    sidesX(sidesX==max(sidesX)) = [];
    
    % calculate mean of values, round to nearest int
    muX = int16(mean(sidesX));
    
    %%%%%%%% Second cryocycle %%%%%%%%%
    sides2X = [];
    %t_image_data_1(1,:,:)
    for iy=1:1:y_dim;
        for ix=1:1:x_dim;
            if t_image_data_2(1,ix,iy) > 0.45;
                sides2X(end+1) = ix;
                break
            end
        end
    end
    
    sides2X(sides2X==max(sides2X)) = [];
    mu2X = int16(mean(sides2X));


    % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
    % Align the waveforms in time to eliminate any artificial %
    % anticorrelations due to differences in the ASIC heights %
    % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %

    % We will use the zero-crossing of the waveform to align the 
    % front surface of each ASIC (point where amplitude crosses the y-axis)
    % (see A-scan image for reference). This may have to be changed
    % depending on the qualities of the electronics being scanned.

    % load in properly shifted (in space) data
    s1_t = squeeze(t_Data_1(datachannel).rawdata((x_i_1+muX):(x_i_1+muX+102),(y_i_1+mu):(y_i_1+mu+102),45:55));
    s2_t = squeeze(t_Data_2(datachannel).rawdata((x_i_2+mu2X):(x_i_2+mu2X+102),(y_i_2+mu2):(y_i_2+mu2+102),45:55));
    % where the time window 45:55 is optimized to search for the
    % zero-crossing. Produce an A-scan and analyze the waveforms to see
    % which time window is ideal for identifying the zero-crossing.

    zero_points_1 = [];
    zero_points_2 = [];
    for iz=1:1:1;
        for ii=1:1:103; 
            for ij=1:1:103;
                min_value_1 = min(abs((s1_t(ii,ij,:))));
                min_value_2 = min(abs((s2_t(ii,ij,:))));
                % search for value of the zero-point crossing
                
                % now that we know the minimum value -- find it in time
                for itt=1:1:11;   % only 1:11 since our time window is 45:55
                    if abs(s1_t(ii,ij,itt)) == min_value_1;
                        zero_points_1(end+1) = 44+itt;  % must add 44 to get the actual time value in the t-data array
                    end
                    if abs(s2_t(ii,ij,itt)) == min_value_2;
                        zero_points_2(end+1) = 44+itt;
                    end
                end
            end
        end
    end

    zp_1 = int16(mean(zero_points_1));   % take average of the zero-points
    zp_2 = int16(mean(zero_points_2));

    % how much "ahead" the zero-crossing is for the second dataset
    allignT = (zp_2-zp_1);


    % % % % % % % % % % % % % % % % % % % % %
    % Step 4:  Perform correlation analysis %
    % % % % % % % % % % % % % % % % % % % % %
    
    for iT=1:length(time_loop_Ni);  % Loop through time gates

        % Plot labels
        XLabels = 1:960;
        CustomXLabels = string(XLabels);
        CustomXLabels(mod(XLabels,5) ~= 0) = " ";
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
        % Specify time window:
    
        ti_new=time_loop_Ni(iT); 
        tf_new=time_loop_Nf(iT);

        disp(strcat('t', num2str(ti_new), '-', num2str(tf_new)));
    
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
        % perform allignment by using shift from difference in means
         
        s1_new = squeeze(t_Data_1(datachannel).rawdata((x_i_1+muX):(x_i_1+muX+102),(y_i_1+mu):(y_i_1+mu+102),ti_new:tf_new));
        s2_new = squeeze(t_Data_2(datachannel).rawdata((x_i_2+mu2X):(x_i_2+mu2X+102),(y_i_2+mu2):(y_i_2+mu2+102),ti_new+allignT:tf_new+allignT));
    
        % The 102 value will need to be changed depending on the size of the ASIC
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    
        % We want to produce an image of *just* the ASIC - i.e. no pins
        % so that when we analyze the image in python, the AI doesn't look for
        % the pin anti-correlation regions.
        % Each ASIC is 103 pixels x 103 pixels from the edge points. So we can
        % take the sides found above in x and y and crop the image accordingly.
    
        for iz=1:1:1;
            for ii=1:1:103; 
                for ij=1:1:103;     
                    % perform correlation - the actual shift is applied here in
                    % s1_new and s2_new
                    cross_corr(iz,ii,ij) =  xcorr(squeeze(s1_new(ii,ij,:)),squeeze(s2_new(ii,ij,:)),0,'coef');
                end
            end
        end
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
        % Step 5: Produce Figures - make sure to adjust the save name extension
    
        % Correlation Images
        f1=figure('Renderer', 'painters', 'Position', [10 10 1000 1000], 'visible', 'off');
        h1=heatmap(squeeze(cross_corr(1,:,:))');   % ' denotes the Transpose - the ASICs are mirrored in the SAM images
        
        % Normal SAM plot colors:
        colormap(gca,'jet');
        caxis([-1 1]);
        colorbar;
        path1=strcat('Correlation_Images/Correlation_Plots/',time_loop{iT},'/ASIC_',num2str(z),'_corr[',name_1,'][',name_2,']_t',num2str(ti_new),'_',num2str(tf_new));
        saveas(f1, path1, 'png');
        
        % Negative plot colors: (for Open CV analysis)
        % black/white:
        cc = gray(2);
        colormap(cc);
        grid off;      % turn grid off to help the AI identify shapes
        caxis([-1,1]);
        colorbar;
        path=strcat('Correlation_Images/Negative_Plots/',time_loop{iT},'/ASIC_',num2str(z),'_neg[',name_1,'][',name_2,']_t',num2str(ti_new),'_',num2str(tf_new));
        saveas(f1, path, 'png');
    
        %{
        % Higher Threshold (-0.5 anti-correlation threshold, instead of 0)
        map = [1 1 1;
        1 1 1;
        1 1 1;
        0 0 0];
        colormap(flipud(map));
        grid off;      % turn grid off to help the AI identify shapes
        caxis([-1,1]);
        colorbar;
        path=strcat('Correlation_Images/HT_Negative_Plots/',time_loop{iT},'ASIC_',num2str(z),'_HTneg[',name_1,'][',name_2,']_t',num2str(ti_new),'_',num2str(tf_new));
        saveas(f1, path, 'png');
        %}

        % Interior Amplitude Images (no correlations)
        for iz=1:1:1;
            for ix=1:1:103;
               for iy=1:1:103;
            
                   interior1(iz,ix,iy)=squeeze(max(abs(s1_new(ix,iy,:))));
                   interior2(iz,ix,iy)=squeeze(max(abs(s2_new(ix,iy,:))));
            
               end
            end
        end

        amp1=figure('Renderer', 'painters', 'Position', [10 10 1000 1000], 'visible', 'off');
        a1=heatmap(squeeze(interior1(1,:,:))');
        colormap(gca,'jet');
        caxis([0 0.5]);
        colorbar;
        path_amp1=strcat('Correlation_Images/Interior_Amplitude_Plots/',time_loop{iT},'/ASIC_',num2str(z),'_amp[',name_1,']_t',num2str(ti_new),'_',num2str(tf_new));
        saveas(a1, path_amp1, 'png');

        amp2=figure('Renderer', 'painters', 'Position', [10 10 1000 1000], 'visible', 'off');
        a2=heatmap(squeeze(interior2(1,:,:))');
        colormap(gca,'jet');
        caxis([0 0.5]);
        colorbar;
        path_amp2=strcat('Correlation_Images/Interior_Amplitude_Plots/',time_loop{iT},'/ASIC_',num2str(z),'_amp[',name_2,']_t',num2str(ti_new),'_',num2str(tf_new));
        saveas(a2, path_amp2, 'png');

        % A-Scan
        x_point = 50;    % these can be any points, really
        y_point = 50;
        as=figure('Renderer', 'painters', 'Position', [10 10 1000 1000], 'visible', 'off');
        ascan1=squeeze(s1_new(x_point,y_point,:));
        ascan2=squeeze(s2_new(x_point,y_point,:));
        plot(ascan1, 'color', 'black', linewidth = 2);
        hold on
        plot(ascan2, 'color', 'red', linewidth = 2);
        legend(name_1, name_2);
        path_ascan=strcat('Correlation_Images/A_Scans/',time_loop{iT},'/ASIC_',num2str(z),'_Ascan[',name_1,'][',name_2, ']_t',num2str(ti_new),'_',num2str(tf_new));
        title(strcat('A-Scan ASIC ', num2str(z), ' | (x,y) = (', num2str(x_point), ',', num2str(y_point), ')'));
        saveas(as, path_ascan, 'png');
            
    end
end

disp(' ')
disp('done');
disp(' ');
