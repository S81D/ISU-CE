function [data]=ReadSDTFileIW(filename)
%L. Koester, 12/2015
%This function imports data from an SDT file. It has not been thoroughly
%tested. Resulting data will contain fields pertaining to the range of the
%data, the timebase (if a waveform) and the raw data stored in an indexed
%structure datatype.
%Access individual datasets if there are more than one with the following
%syntax:
%   k-dataset (ie CScan data, TOF data, etc), takes k= 1, 2, 3...)
%  EXAMPLES OF USE
%  data(k).axes.range{1,b) for the RANGE of axis b (b= 1, 2)
%  data(k).axes.units{1,b) for the UNITS of axis b (b= 1, 2)
%  data(k).timebase        for the time base of the waveforms (will fail if
%                           no timebase (CScan data)
%  data(k).rawdata(n,m,:)  for an individual waveform at nxm.
%
%NOT tested for datasets with more than 2 scanning axes. Might fail with
%one (FIXED).
%Let me know if there are any problems with it.

fid=fopen(filename,'rb','ieee-le.l64');


header_info=textscan(fid,'%s %s',5,'Delimiter',':');

scan_axes=str2double(header_info{1,2}{4,1});
scan_subsets=str2double(header_info{1,2}{5,1});

%Get Scanning Axes Information and separate into values/units
for ii=1:1:scan_axes
    %Ignore '--- Nth Axis ---'
    [~]=textscan(fid,'%s%s%s%s%s%s',1);
    %Get Raw Strings
    scan_axes_info{ii,1}=textscan(fid,'%s %s',1,'Delimiter',':');
    scan_axes_info{ii,2}=textscan(fid,'%s %s',1,'Delimiter',':');
    scan_axes_info{ii,3}=textscan(fid,'%s %s',1,'Delimiter',':');
    scan_axes_info{ii,1}{1,3}='none';
    %Extract Values for minimum
    tempval1=sscanf(scan_axes_info{ii,2}{1,2}{:},'%f',1);
    %Extract Units for minimum
    tempunit1=sscanf(scan_axes_info{ii,2}{1,2}{:},'%*s %s',1);
    scan_axes_info{ii,2}{1,2}=tempval1;
    scan_axes_info{ii,2}{1,3}=tempunit1;
    %Extract Values for resolution
    tempval1=sscanf(scan_axes_info{ii,3}{1,2}{:},'%f',1);
    %Extract Units for resolution
    tempunit1=sscanf(scan_axes_info{ii,3}{1,2}{:},'%*s %s',1);
    scan_axes_info{ii,3}{1,2}=tempval1;
    scan_axes_info{ii,3}{1,3}=tempunit1;
    %Extract Values for length
    tempval1=sscanf(scan_axes_info{ii,1}{1,2}{:},'%f',1);
    scan_axes_info{ii,1}{1,2}=tempval1;
    
end

%Get Data Subset Information and Split
for ii=1:1:scan_subsets
    %Ignore '--- Data Subset N ---'
    [~]=textscan(fid,'%s%s%s%s%s%s',1);
    %Get Raw Strings
    %Subset Label
    data_subset_info{ii,1}=textscan(fid,'%s %s',1,'Delimiter',':');
    %Element Size(bytes)
    data_subset_info{ii,2}=textscan(fid,'%s %s',1,'Delimiter',':');
    %Element Representation
    data_subset_info{ii,3}=textscan(fid,'%s %s',1,'Delimiter',':');
    %Number of Sample Points
    data_subset_info{ii,4}=textscan(fid,'%s %f',1,'Delimiter',':');
    %Minimum Sample Position
    data_subset_info{ii,5}=textscan(fid,'%s %s',1,'Delimiter',':');
    %Sample Resolution
    data_subset_info{ii,6}=textscan(fid,'%s %s',1,'Delimiter',':');
    %Measurement Range
    data_subset_info{ii,7}=textscan(fid,'%s %s %*s %f %f %s',1);
    %Binary Offset Amount
    data_subset_info{ii,8}=textscan(fid,'%s %s',1,'Delimiter',':');
    %Undefineds Permitted
    data_subset_info{ii,9}=textscan(fid,'%s %s',1,'Delimiter',':');
    %Undefined Elements
    data_subset_info{ii,10}=textscan(fid,'%s %s',1,'Delimiter',':');
    %Assign 'none' for fields with no units
    %     for ij=[1,3,4,5,7,8,9]
    %         data_subset_info{ii,ij}{1,3}='none';
    %     end
    %check that its not an image (ie sample points ~=1, extract minimum for
    %timebase
    if data_subset_info{ii,4}{1,2}~=1
        %if so, separate minimum, resolution into values / units
        tempval1=sscanf(data_subset_info{ii,5}{1,2}{1},'%f %*s');
        tempunit1=sscanf(data_subset_info{ii,5}{1,2}{1},'%*s %s');
        data_subset_info{ii,5}{1,2}=tempval1;
        data_subset_info{ii,5}{1,3}=tempunit1;
        %resolution
        tempval1=sscanf(data_subset_info{ii,6}{1,2}{1},'%f %*s');
        tempunit1=sscanf(data_subset_info{ii,6}{1,2}{1},'%*s %s');
        data_subset_info{ii,6}{1,2}=tempval1;
        data_subset_info{ii,6}{1,3}=tempunit1;
        
    end
    %Extract Units for number of sample points, ensure not image data
    data_subset_info{ii,2}{1,2}=tempval1;
    %     data_subset_info{ii,2}{1,3}=tempunit1;
end

%Write final data to cells
for ii=1:1:scan_subsets
    %pull label from subset info
    data(ii).type=data_subset_info{ii,1}{1,2};
    %loop and calculate axes ranges based on # of scan axes
    for ij=1:1:scan_axes
        data(ii).axes.range{ij}=linspace(0,scan_axes_info{ij,3}{1,2}*(scan_axes_info{ij,1}{1,2}-1),scan_axes_info{ij,1}{1,2});
%         data(ii).axes.range{ij}=data(ii).axes.range{ij}-scan_axes_info{ij,3}{1,2}*(scan_axes_info{ij,1}{1,2}-1)/2;  %Zero centered
        data(ii).axes.units{ij}=scan_axes_info{ij,2}{1,3};
    end
    %check for a timebase (ie waveform data)
    if data_subset_info{ii,4}{1,2}~=1
        data(ii).timebase=linspace(0,data_subset_info{ii,6}{1,2}*(data_subset_info{ii,4}{1,2}-1),data_subset_info{ii,4}{1,2})+data_subset_info{ii,5}{1,2};
    end
    data(ii).min_amp{1}=data_subset_info{ii,7}{3};
    data(ii).max_amp{1}=data_subset_info{ii,7}{3}+data_subset_info{ii,7}{4};
    
end

[time_collection]=textscan(fid,'%s %s',1,'Delimiter',':');
%Skip instrument information
fcurr=ftell(fid);
fseek(fid,fcurr,-1);
data_start=0;
while ~data_start
    %     fgetl(fid)
    temp_char=textscan(fid,'%c',1);
    if temp_char{1}=='|'
        temp_string2=textscan(fid,'%s',1,'delimiter','|');
        if length(char(temp_string2{:}))==length('^Data Set^')
            if char(temp_string2{:})=='^Data Set^'
                last_chars=textscan(fid,'%u',3);
                data_start=1;
            end
        end
    end
end

% Determine data storage format, ie int8, char, etc.

for ii=1:1:scan_subsets
    format_type=sscanf(data_subset_info{ii,3}{1,2}{1},'%s %*s');
    format_bits{ii}=num2str(sscanf(data_subset_info{ii,3}{1,2}{1},'%*s %s'));
    if regexp(format_type,'INT')
        format_string{ii}=strcat(['int' format_bits{ii}]);
    elseif regexp(format_type,'CHAR')
        format_string{ii}='int8';
        format_bits{ii}='8';
    else
        error(strcat('Unknown datatype :', strcat(format_type,format_bits{ii})))
    end

end

%Import the data fields
for ii=1:1:scan_subsets
    %check if it is image data
    if data_subset_info{ii,4}{1,2}==1
        %import lxm points
        if size(scan_axes_info,1)==1
        data(ii).rawdata=fread(fid,scan_axes_info{1,1}{1,2},format_string{ii});
        %reshape to lxm matrix
        data(ii).rawdata=reshape(data(ii).rawdata,scan_axes_info{1,1}{1,2},1);
        %scale the data according to 16 bit values based on the ranges
        data(ii).rawdata=(data_subset_info{ii,7}{1,4}).*data(ii).rawdata./(2^str2num(format_bits{ii})-1);
        else
        data(ii).rawdata=fread(fid,scan_axes_info{1,1}{1,2}*scan_axes_info{2,1}{1,2},format_string{ii});
        %reshape to lxm matrix
        data(ii).rawdata=reshape(data(ii).rawdata,scan_axes_info{1,1}{1,2},scan_axes_info{2,1}{1,2});
        %scale the data according to 16 bit values based on the ranges
        data(ii).rawdata=(data_subset_info{ii,7}{1,4}).*data(ii).rawdata./(2^str2num(format_bits{ii})-1);
        end
    else %must be waveform data
        %import the data, l time points by nxm scan points gets lxmxn total
        %points check if its a 1d scan, else, assume 2d.
        if scan_axes==1
            data(ii).rawdata=fread(fid,scan_axes_info{1,1}{1,2}*data_subset_info{ii,4}{1,2},format_string{ii});
            %reshape to lxmxn matrix
            data(ii).rawdata=reshape(data(ii).rawdata,data_subset_info{ii,4}{1,2},scan_axes_info{1,1}{1,2},1);
            %permute to access such that its data(scan_axis1,scan_axis2,time)
            data(ii).rawdata=permute(data(ii).rawdata,[2,3,1]);
            %scale the data according to 8 bit values based on the ranges
            data(ii).rawdata=(data_subset_info{ii,7}{1,4}).*data(ii).rawdata./(2^str2num(format_bits{ii})-1);
        else
            
            data(ii).rawdata=fread(fid,scan_axes_info{1,1}{1,2}*scan_axes_info{2,1}{1,2}*data_subset_info{ii,4}{1,2},format_string{ii});
            %reshape to lxmxn matrix
            data(ii).rawdata=reshape(data(ii).rawdata,data_subset_info{ii,4}{1,2},scan_axes_info{1,1}{1,2},scan_axes_info{2,1}{1,2});
            %permute to access such that its data(scan_axis1,scan_axis2,time)
            data(ii).rawdata=permute(data(ii).rawdata,[2,3,1]);
            %3D array, use squeeze(data(x).rawdata(n,m,:)) to plot individual
            %waveforms
            %scale the data according to 16 bit values based on the ranges
            data(ii).rawdata=(data_subset_info{ii,7}{1,4}).*data(ii).rawdata./(2^str2num(format_bits{ii})-1);
            
        end
    end
    [pathstr, filename2, extension]=fileparts(filename);
    data(ii).fileinfo.path=pathstr;
    data(ii).fileinfo.filename=filename2;
    data(ii).fileinfo.extension=extension;
    data(ii).shiftvals=[];
    
end



fclose(fid)
end
