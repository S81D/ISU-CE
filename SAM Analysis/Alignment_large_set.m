close all
clear all
pathname = '';


start_time_index=1; 
end_time_index=100;

%start_time_index=start_time_index_LN+56; % shifting the waveform for aligment as data were taken different time
%end_time_index=end_time_index_LN+56; % shifting the waveform for aligment  as data were taken different time


XLabels = 1:960;
CustomXLabels = string(XLabels);
CustomXLabels(mod(XLabels,5) ~= 0) = " ";


t_1=  '[0]/50_79.sdt';
t_2 = '[5]/50_79_after_5.sdt'; 
%t_2 = 'Scans_for_CT20/80_109_after20_CT.sdt';



t_Data_1 = ReadSDTFileIW(fullfile(pathname,t_1));
t_Data_2 = ReadSDTFileIW(fullfile(pathname,t_2));
datachannel =2;

%s11 = squeeze(max(abs(t_Data_1(datachannel).rawdata(28:148,30:150,start_time_index:end_time_index))));



           

       %s1 = squeeze(t_Data_1(datachannel).rawdata(319:478,624:764,start_time_index:end_time_index));
       %s2 = squeeze(t_Data_2(datachannel).rawdata(320:479,640:780,start_time_index:end_time_index));
       
       s1 = squeeze(t_Data_1(datachannel).rawdata(1:959,1:779,start_time_index:end_time_index));
       s2 = squeeze(t_Data_2(datachannel).rawdata(1:959,1:779,start_time_index:end_time_index));
       
for iz=1:1:1;
   for ii=1:1:959; %159
       for ij=1:1:779; %140
           % input the vectors (s1,s2 ..) to compute the correlation   
           
           
        t_image_data_1(iz,ii,ij)=squeeze(max(abs(t_Data_1(datachannel).rawdata(ii,ij,start_time_index:end_time_index))));
        t_image_data_2(iz,ii,ij)=squeeze(max(abs(t_Data_2(datachannel).rawdata(ii,ij,start_time_index:end_time_index))));
        
        cross_corr_1(iz,ii,ij) =  xcorr(squeeze(s1(ii,ij,:)),squeeze(s2(ii,ij,:)),0,'coef');
        

       end
   end
end


tested_1=figure('Renderer', 'painters', 'Position', [10 10 1600 1600], 'visible', 'off');
%heatmap(squeeze(t_image_data_1(1,300:600,600:780)));
heatmap(squeeze(t_image_data_1(1,:,:))');
colormap(gca,'jet')
caxis([0.0 0.5])
colorbar;
saveas(tested_1,sprintf('CC0.png'));
%saveas(tested_1,sprintf('/Users/pnav/Desktop/For_ME/DUNE_CNDE/FullBoardScans/UTData/Images_RT0_CT5/RT0_2D_80_84_220_320.png'));

tested_2=figure('Renderer', 'painters', 'Position', [10 10 1600 1600], 'visible', 'off');
%heatmap(squeeze(t_image_data_2(1,300:600,600:780)));
heatmap(squeeze(t_image_data_2(1,:,:))');
colormap(gca,'jet')
caxis([0.0 0.5])
colorbar;
saveas(tested_2,sprintf('CC5.png'));
%saveas(tested_2,sprintf('/Users/pnav/Desktop/For_ME/DUNE_CNDE/FullBoardScans/UTData/Images_RT0_CT5/CT20_2D_80_84_220_320.png'));

%{
f1=figure('Renderer', 'painters', 'Position', [10 10 1600 350])
%f1=figure('Name','FE_1','NumberTitle','off')
%h1=heatmap(squeeze(cross_corr_1(iz,300:600,600:780))) %make an image of the data
h1=heatmap(squeeze(cross_corr_1(1,:,:)))
%contourf(squeeze(cross_corr_1(iz,:,:))')
colormap(gca,'jet')
caxis([-1 1])
colorbar
%h1.XDisplayLabels = CustomXLabels;
%h1.YDisplayLabels = CustomXLabels;

%Y_1 = squeeze(t_Data_2(2).rawdata(75,65,1:575));
%Y_2 = squeeze(LN_Data_2(2).rawdata(75,65,1:575));


%Y_1 = squeeze(t_Data_1(2).rawdata(78,63,1:575));
%Y_2 = squeeze(t_Data_2(2).rawdata(78,63,1:575));
%saveas(f1,sprintf('/Users/pnav/Desktop/For_ME/DUNE_CNDE/FullBoardScans/UTData/Images_RT0_CT5/Corr_80_84_220_320.png'));
%}









%f1=figure('Renderer', 'painters', 'Position', [10 10 1600 350])
%f1=figure('Name','FE_1','NumberTitle','off')
%h1=heatmap(squeeze(cross_corr_1(iz,300:600,600:780))) %make an image of the data
%%h1=heatmap(squeeze(cross_corr_1(1,1:160,:)))
%contourf(squeeze(cross_corr_1(iz,:,:))')
%%colormap(gca,'jet')
%%caxis([-1 1])
%%colorbar
%h1.XDisplayLabels = CustomXLabels;
%h1.YDisplayLabels = CustomXLabels;

%Y_1 = squeeze(t_Data_2(2).rawdata(75,65,1:575));
%Y_2 = squeeze(LN_Data_2(2).rawdata(75,65,1:575));


%Y_1 = squeeze(t_Data_1(2).rawdata(78,63,1:575));
%Y_2 = squeeze(t_Data_2(2).rawdata(78,63,1:575));
%saveas(f1,sprintf('/Users/pnav/Desktop/For_ME/DUNE_CNDE/FullBoardScans/UTData/Images_RT0_CT20/Corr_20_24_220_320.png'));


%%saveas(tested_2,sprintf('/Users/pnav/Desktop/large_scan_images/2_63_CT[5].png'));
%saveas(f1,sprintf('/Users/pnav/Desktop/large_scan_images/Corr_2_63_CT[5].png'));
