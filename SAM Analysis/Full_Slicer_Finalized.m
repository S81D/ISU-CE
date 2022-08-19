%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%        Correlation Analysis for SAM FE LArASIC data        %
% ---------------------------------------------------------- %
% -- 1. Reads in .sdt acoustic data for all cryocycles (CCs) %
% -- 2. Slices the data ASIC-wise for each CC                %
% -- 3. Crops data to exclude the pin region                 %
% -- 3. Performs allignment to minimize anti-correlation     %
% -- 4. Performs correlation analysis between the CC's       %
% -- 5. Produces heatmap showing regions of anti-correlation %
% -- 6. Outputs heatmap to .png file                         %
% -- 7. Repeats code for multiple different windows of time  %
% ---------------------------------------------------------- %
%                   Author: Steven Doran                     %
%        --> with correlation analysis section code          %
%                by: Navaneeth Poonthottathi                 %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;
pathname = '';

%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Load in fixture data. Data was taken using SAM at the ASC off campus

data_20 = {'[0]/20_49.sdt', '[5]/20_49_after_5.sdt', '[20]/20_49_after_20.sdt', '[100]/20_49_after_100.sdt'};
data_50 = {'[0]/50_79.sdt', '[5]/50_79_after_5.sdt', '[20]/50_79_after_20.sdt', '[100]/50_79_after_100.sdt'};
data_80 = {'[0]/80_109.sdt', '[5]/80_109_after_5.sdt', '[20]/80_109_after_20.sdt', '[100]/80_109_after_100.sdt'};
data_110 = {'[0]/110_119.sdt', '[5]/110_119_after_5.sdt', '[20]/110_119_after_20.sdt', '[100]/110_119_after_100.sdt'};

data_files = {data_20, data_50, data_80, data_110};
first_ASIC_number = [20 50 80 110];

% If you want all time gates
%time_gates_first = [1 100 150 200];
%time_gates_second = [100 150 200 300];

% For OpenCV analysis, we just use t100-150 to maximize the ACRs
time_gates_first = [100];
time_gates_second = [150];

for k=1:length(data_files);   % Loop through each ASIC dataset (20-49, 50-79, etc..)
    for l=1:(length(data_20)-1);  % Loop through each cryocycle
        for m=1:length(time_gates_first);  % Loop through time gates


            % Plot labels
            XLabels = 1:960;
            CustomXLabels = string(XLabels);
            CustomXLabels(mod(XLabels,5) ~= 0) = " ";
            
            t_1 =  data_files{k}{l};
            t_2 = data_files{k}{l+1}; 
            
            t_Data_1 = ReadSDTFileIW(fullfile(pathname,t_1));
            t_Data_2 = ReadSDTFileIW(fullfile(pathname,t_2));
            datachannel =2;
            
            % initializing
            row = 1;
            column = 1;
            
            %%%%% Parameterization Input 1 %%%%%
            
            % specify the first ASIC number in the fixture data
            first_ASIC = first_ASIC_number(k);
            
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%     

            for z=1:1:30;   
            
                % Front wall timegate - easy to analyze the edge as the slice point
                t_i = 1;
                t_f=100;
            
                % optimized to loop through the plastic fixture containing 30 ASICs per
                % measurement (6 columns per row, 5 rows in total)
                if column == 7;
                    column = 1;
                    row = row + 1;
                end
                
                
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                %%%%% Parameterization Input 2 %%%%%
            
                % Total length in x = 960 pixels  (960/6 = 160)
                % Total length in y = 780 pixels  (780/5 = 156)
            
                % Requires some trial and error - measurements are misalligned in X and
                % Y, so a shift is automatically enacted later. However, the shift can
                % sometimes be large - so we must optimize the 'slicing' of the
                % individual ASIC from the bulk dataset and have that 'window' in x and
                % y be able to account for that shift. This parameterization primarily
                % deals with this - slicing individual ASIC data from the bulk dataset,
                % but making sure to jump forward in x and y (the next row/column) in
                % precisely the right amount, and allowing for the shift to take place.

                % Many of the datasets have unique initial configurations,
                % but some datasets share similar settings

                % measurements beginning with [0] ==> (l==1)
                % measurements beginning with [5] ==> (l==2)
                % measurements beginning with [0] ==> (l==3)


                % All [0]_[5], [5]_[20]_20-49,50-79, [20]_[100]_20-49
                if (l == 1) || ((k == 1 || k == 2) && (l == 2)) || ((k == 1) && (l == 3));
                
                    % denote cell dimensions
                    x_dim = 120;
                    y_dim = 115;
                
                    % update the cell region - also to keep the images as alligned as
                    % possible with one another, try and skip some of the plastic middle
                    % fixture
                    x_i=8 + x_dim*(column-1) + 45*(column-1);
                    y_i=13 + y_dim*(row-1) + 45*(row-1);
                    
                    x_f=8 + x_dim + x_dim*(column-1) + 45*(column-1);
                    y_f=13 + y_dim + y_dim*(row-1) + 45*(row-1);
                
                end


                % [5]_[20]_80-109, [20]_[100]_80-109,110-119
                if (k == 3 && l == 2) || (k == 3 && l == 3) || (k == 4 && l == 3);
                
                    % denote cell dimensions
                    x_dim = 120;
                    y_dim = 145;
                
                    % update the cell region - also to keep the images as alligned as
                    % possible with one another, try and skip some of the plastic middle
                    % fixture
                    x_i=8 + x_dim*(column-1) + 45*(column-1);
                    y_i=3 + y_dim*(row-1) + 13*(row-1);
                    
                    x_f=8 + x_dim + x_dim*(column-1) + 45*(column-1);
                    y_f=3 + y_dim + y_dim*(row-1) + 13*(row-1);
                
                end
            

                % [5]_[20]_110-119
                if k == 4 && l == 2;
                
                    % denote cell dimensions
                    x_dim = 120;
                    y_dim = 125;
                
                    % update the cell region - also to keep the images as alligned as
                    % possible with one another, try and skip some of the plastic middle
                    % fixture
                    x_i=8 + x_dim*(column-1) + 45*(column-1);
                    y_i=13 + y_dim*(row-1) + 40*(row-1);
                    
                    x_f=8 + x_dim + x_dim*(column-1) + 45*(column-1);
                    y_f=13 + y_dim + y_dim*(row-1) + 40*(row-1);
                
                end

        
                % [20]_[100]_50-79
                if k == 2 && l == 3;
                
                    % denote cell dimensions
                    x_dim = 120;
                    y_dim = 120;
                
                    % update the cell region - also to keep the images as alligned as
                    % possible with one another, try and skip some of the plastic middle
                    % fixture
                    x_i=8 + x_dim*(column-1) + 45*(column-1);
                    y_i=5 + y_dim*(row-1) + 40*(row-1);
                    
                    x_f=8 + x_dim + x_dim*(column-1) + 45*(column-1);
                    y_f=5 + y_dim + y_dim*(row-1) + 40*(row-1);
                
                end

                % % % % % % % % % % % % % % % % % % % % % % % % % % % %

                s1 = squeeze(t_Data_1(datachannel).rawdata(x_i:x_f,y_i:y_f,t_i:t_f));
                s2 = squeeze(t_Data_2(datachannel).rawdata(x_i:x_f,y_i:y_f,t_i:t_f));

                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%       
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
            
            
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                % Reload single ASIC data with appropriate shifts - perform allignment
                % no need to load in entire fixture again
                
                % Allignment - difference in slice coordinates to ensure the cryocycles are alligned in X & Y       
                allignY = mu - mu2;
                allignX = muX - mu2X;
                
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                
                %%%%% Parameterization Input 3 %%%%%%%%%
                
                % change TOF for correlation analysis (TOF 100-150 optimizes ACRs)
                % Specify time region of interest:
                ti_new=time_gates_first(m); 
                tf_new=time_gates_second(m);
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            
                % perform allignment by using shift from difference in means
                 
                s1_new = squeeze(t_Data_1(datachannel).rawdata((x_i+muX):(x_i+muX+102),(y_i+mu):(y_i+mu+102),ti_new:tf_new));
                s2_new = squeeze(t_Data_2(datachannel).rawdata((x_i+mu2X):(x_i+mu2X+102),(y_i+mu2):(y_i+mu2+102),ti_new:tf_new));
            
            
                %%%%% Fix misplaced ASICs %%%%%
            
                % Some ASICs are placed rotated WRT initial measurements (human error)
                % Here is an if statement to rotate the arrays by either 90 or 180
                % degrees if an ASIC is incorrectly placed in one of the measurements
            
                % cannot perform on s1 or s2 directly (data is squeezed = concatenated), so we
                % must do it on the tdata array. We will re-load s1_new and s2_new with
                % the rotated data

                % measurements beginning with [0] ==> (l==1)
                % measurements beginning with [5] ==> (l==2)
                % measurements beginning with [0] ==> (l==3)

                % ASICs 20-49   ==> k = 1
                % ASICs 50-79   ==> k = 2
                % ASICs 80-109  ==> k = 3
                % ASICs 110-119 ==> k = 4
                
                %%%%%%%%%%%% errors in [0] measurement %%%%%%%%%%%%%%
                % ASIC 77, 81, 83 rotated 180 degrees
                % in the fixture, they are in positions [i = row, j = column],[z #]:
                % 77 = [5,4],[28]   81 = [1,2],[2]   83 = [1,4],[4]

                if (l == 1 && k == 3);
                    if (z == 2 || z == 4);
                        a = t_Data_1(datachannel).rawdata((x_i+muX):(x_i+muX+102),(y_i+mu):(y_i+mu+102),ti_new:tf_new);
                        b = rot90(a);
                        c = rot90(b);
                        s1_new = squeeze(c);
                    end
                end

                if (l == 1 && k == 2);
                    if z == 28;
                        a = t_Data_1(datachannel).rawdata((x_i+muX):(x_i+muX+102),(y_i+mu):(y_i+mu+102),ti_new:tf_new);
                        b = rot90(a);
                        c = rot90(b);
                        s1_new = squeeze(c);
                    end
                end
                
                %%%%%%%%%%%% errors in [5] measurement %%%%%%%%%%%%%%
                % ASIC 109 rotated 180 degrees
                % 109 = [30]

                % [0]_[5]
                if (l == 1 && k == 3);
                    if z == 30;
                        a = t_Data_2(datachannel).rawdata((x_i+mu2X):(x_i+mu2X+102),(y_i+mu2):(y_i+mu2+102),ti_new:tf_new);
                        b = rot90(a);
                        c = rot90(b);
                        s2_new = squeeze(c);
                    end
                end

                % [5]_[20]
                if (l == 2 && k == 3);
                    if z == 30;
                        a = t_Data_1(datachannel).rawdata((x_i+muX):(x_i+muX+102),(y_i+mu):(y_i+mu+102),ti_new:tf_new);
                        b = rot90(a);
                        c = rot90(b);
                        s1_new = squeeze(c);
                    end
                end
                
                %%%%%%%%%%%% errors in [20] measurement %%%%%%%%%%%%%%
                % ASIC 113,114,115,117 rotated 180 degrees
                % ASIC 118 rotated by -90 degrees (requires rotation of 270)
                % 113 = [4]; 114 = [5]; 115 = [6]; 117 = [8]; 118 = [9]
                
                % [5]_[20]
                if (l == 2 && k == 4);
                    if (z == 4 || z == 5 || z == 6 || z == 8);
                        a = t_Data_2(datachannel).rawdata((x_i+mu2X):(x_i+mu2X+102),(y_i+mu2):(y_i+mu2+102),ti_new:tf_new);
                        b = rot90(a);
                        c = rot90(b);
                        s2_new = squeeze(c);
                    end
                
                    if z == 9;
                        a = t_Data_2(datachannel).rawdata((x_i+mu2X):(x_i+mu2X+102),(y_i+mu2):(y_i+mu2+102),ti_new:tf_new);
                        b = rot90(a);
                        s2_new = squeeze(b);
                    end
                end

                % [20]_[100]
                if (l == 3 && k == 4);
                    if (z == 4 || z == 5 || z == 6 || z == 8);
                        a = t_Data_1(datachannel).rawdata((x_i+muX):(x_i+muX+102),(y_i+mu):(y_i+mu+102),ti_new:tf_new);
                        b = rot90(a);
                        c = rot90(b);
                        s1_new = squeeze(c);
                    end
                
                    if z == 9;
                        a = t_Data_1(datachannel).rawdata((x_i+muX):(x_i+muX+102),(y_i+mu):(y_i+mu+102),ti_new:tf_new);
                        b = rot90(a);
                        s1_new = squeeze(b);
                    end
                end
                
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
            
                % Produce Figures - make sure to adjust the save name extension

                CC1 = [0 5 20];
                CC2 = [5 20 100];

                if z == 1;
                    disp(strcat('[', num2str(CC1(l)), ']_[', num2str(CC2(l)),']_t', num2str(ti_new), '-', num2str(tf_new)))
                end
                
                disp(strcat('ASIC_', num2str(first_ASIC + (z-1))))
            
                % Correlation Image
                f1=figure('Renderer', 'painters', 'Position', [10 10 1000 1000], 'visible', 'off');
                h1=heatmap(squeeze(cross_corr(1,:,:))');   % ' denotes the Transpose - the ASICs are mirrored in the SAM images
                
                %{
                % Normal SAM plot colors:
                colormap(gca,'jet');
                caxis([-1 1]);
                colorbar;
                path1=strcat('Automated_Images/Corr/[', num2str(CC1(l)), ']_[', num2str(CC2(l)), ']/t', num2str(ti_new), '-', num2str(tf_new), '/ASIC_', num2str((z-1) + first_ASIC), '_corr[', num2str(CC1(l)), '][', num2str(CC2(l)), ']_t', num2str(ti_new), '_', num2str(tf_new));
                saveas(f1, path1, 'png');
                %}
                
                %{
                % Negative plot colors: (for Open CV analysis)
                % black/white:
                cc = gray(2);
                colormap(cc);
                grid off;      % turn grid off to help the AI identify shapes
                caxis([-1,1]);
                colorbar;
                path=strcat('Automated_Images/Neg/[', num2str(CC1(l)), ']_[', num2str(CC2(l)), ']/t', num2str(ti_new), '-', num2str(tf_new), '/ASIC_', num2str((z-1) + first_ASIC), '_neg[', num2str(CC1(l)), '][', num2str(CC2(l)), ']_t', num2str(ti_new), '_', num2str(tf_new));
                saveas(f1, path, 'png');
                %}

                % Higher Threshold (-0.5)
                map = [1 1 1;
                1 1 1;
                1 1 1;
                0 0 0];
                colormap(flipud(map));
                grid off;      % turn grid off to help the AI identify shapes
                caxis([-1,1]);
                colorbar;
                path=strcat('Automated_Images/High_Neg/[', num2str(CC1(l)), ']_[', num2str(CC2(l)), ']/t', num2str(ti_new), '-', num2str(tf_new), '/ASIC_', num2str((z-1) + first_ASIC), '_HTneg[', num2str(CC1(l)), '][', num2str(CC2(l)), ']_t', num2str(ti_new), '_', num2str(tf_new));
                saveas(f1, path, 'png');
           
            
                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                % Data 110-119 only contains 10 ASICs -- must break 30 loop
                if (k == 4 && z == 10);
                    break
                end
                
                % onto the next ASIC
                column = column + 1;
            
            
            end
        end
    end
end

disp('done')