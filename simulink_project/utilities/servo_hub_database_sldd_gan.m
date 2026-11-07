%清除基础工作区
clear

% 获取脚本所在目录
scriptDir = fileparts(mfilename('fullpath'));

% 获取工作目录
workDir = fileparts(scriptDir);

% 获取当前工作目录
currentDir = pwd;

% 如果不同，则切换到脚本目录
if ~strcmp(workDir, currentDir)
    cd(workDir);
end
disp(['当前工作目录：', pwd()]);

% 文件和系统路径
sldd_path = "./data/servo_hub_database.sldd";
filepath = '../tools/database_generate';
filename = 'servo_hub_database_all.csv';

%关闭所有打开的字典
eval('Simulink.data.dictionary.closeAll'); %#ok<*EVLCS>

%simulink总线代码生成头文件(数据库的结构体变量类型定义)
simulink_bus_header = "servo_hub_database_type.h";

%simulink信号代码生成头文件&源文件(.c文件：数据库结构体变量实例化, h文件：extern变量)
simulink_signal_header = "servo_hub_database_define.h";
simulink_signal_source = "servo_hub_database_define.c";

%打开当前目录选择excl文件
% [filename,filepath] = uigetfile('*.csv','选择文件');

%读取csv文件
raw = readtable(fullfile(filepath, filename));

% 创建列名到列号的映射
header_map = containers.Map();
for i = 1:length(raw.Properties.VariableNames)
    header_map(raw.Properties.VariableNames{i}) = i;
end

VariableNameContent = {};
NameZhContent = {};
CategoryContent = {};
DataTypeContent = {};
DefaultValueContent = {};
ArraySizeContent = {};

index = 1;

for i = 1:size(raw,1)
    if raw{i, header_map("GodeGen")} ~= 1
        continue;
    end

    VariableNameContent{index} = string(raw{i,header_map("VariableName")});
    VariableNameContent{index} = VariableNameContent{index}{1};

    NameZhContent{index} = string(raw{i,header_map("NameZh")});
    NameZhContent{index} = NameZhContent{index}{1};

    CategoryContent{index} = string(raw{i,header_map("Category")});
    CategoryContent{index} = CategoryContent{index}{1};

    DataTypeContent{index} = string(raw{i,header_map("DataType")});
    DataTypeContent{index} = DataTypeContent{index}{1};

    ArraySizeContent{index} = string(raw{i,header_map("Dimension")});
    ArraySizeContent{index} = ArraySizeContent{index}{1};

    DefaultValueContent{index} = string(raw{i,header_map("DefaultValue")});
    DefaultValueContent{index}(ismissing(DefaultValueContent{index})) = "0";
    DefaultValueContent{index} = DefaultValueContent{index}{1};

    index = index + 1;

end

clear index currentDir scriptDir workDir;

%将DefaultValueContent中的空字符串替换为0(未指定默认值的变量默认值为0)
for i = 1:size(DefaultValueContent,2)
    if isempty(DefaultValueContent{i})
        DefaultValueContent{i} = 0;
    end
end

%将提取出的信息合并成一个raw_content
raw_content = [ CategoryContent;
                VariableNameContent;
                DataTypeContent;
                NameZhContent;
                DefaultValueContent;
                ArraySizeContent
                ];

%将raw_content转置，方便后续处理，可以通过disp(raw_content)查看转置后的内容
raw_content = raw_content';

%提取raw_content中的第一列(StructObject结构体名)
StructObject = raw_content(:,1);

%StructObject转换为字符串数组(需要转成字符串数组,否则会报错)
StructObject = string(StructObject);

%去除StructObject中的重复元素(去除重复的结构体名)
StructObject = unique(StructObject);

%删除StructObject中的空元素(防止csv文件中有空内容)
StructObject = StructObject(StructObject ~= "");

%根据StructObject元素创建simulink.Bus,并修改属性
for i = 1:size(StructObject,1)
    evalc([StructObject{i},' = Simulink.Bus;']); %创建simulink.Bus
    evalc([StructObject{i},'.DataScope = "Exported"']);%修改代码生成属性，将结构体类型定义导出到头文件(simulink_bus_header)
    evalc([StructObject{i},'.HeaderFile = simulink_bus_header;']);
end

%根据StructObject元素创建simulink.BusElement(创建结构体成员变量,例:CmdValue.controlword)
temp_string = "NONE";
for j = 1:size(StructObject,1)
    for i = 1:size(raw_content,1)
        if strcmp(raw_content{i,1},StructObject{j})
            if strcmp(raw_content{i,1},temp_string)
                num = num + 1;
            else
                num = 1;
                temp_string = StructObject{j};
            end
            eval([StructObject{j},'_elems(',num2str(num),') = Simulink.BusElement;']);
            eval([StructObject{j},'_elems(',num2str(num),').Name = raw_content{i,2};']);
            eval([StructObject{j},'_elems(',num2str(num),').DataType = raw_content{i,3};']);
            eval([StructObject{j},'_elems(',num2str(num),').Description = raw_content{i,4};']);
            eval([StructObject{j},'_elems(',num2str(num),').Dimensions = raw_content{i,6};']);
            eval([StructObject{j},'.Elements = ',StructObject{j},'_elems;']);
        end
    end
end

%写入simulink.BusElement
% for i = 1:size(StructObject,1)
%     eval([StructObject{i},'.Elements = ',StructObject{i},'_elems;']);
%     %创建simulink.Signal
%     eval(['k',StructObject{i},' = Simulink.Signal;']);
%     eval(['k',StructObject{i},'.DataType = "Bus: ',StructObject{i},'";']);
%     eval(['k',StructObject{i},'.Dimensions = 1;']);
%     eval(['k',StructObject{i},'.DimensionsMode = "Fixed";']);
%     eval(['k',StructObject{i},'.Complexity = "real";']);
%     eval(['k',StructObject{i},'.CoderInfo.StorageClass = "Custom";']);
%     eval(['k',StructObject{i},'.CoderInfo.CustomStorageClass = "ExportToFile";']);
%     eval(['k',StructObject{i},'.CoderInfo.CustomAttributes.HeaderFile = simulink_signal_header;']);
%     eval(['k',StructObject{i},'.CoderInfo.CustomAttributes.DefinitionFile = simulink_signal_source;']);
% end

%创建Axis的simulink.Bus
Axis = Simulink.Bus;
Axis.HeaderFile = simulink_bus_header;
Axis.DataScope = "Exported";

%所有StructObject字符串大小写驼峰格式改成小写加下划线格式，赋值给StructObjectName
for i = 1:size(StructObject,1)
    StructObjectName{i} = regexprep(StructObject{i},'(?<=[a-z])([A-Z])','_$1'); %#ok<SAGROW>
    StructObjectName{i} = lower(StructObjectName{i}); %#ok<SAGROW>
end

%创建ParamDataBase的simulink.BusElement
for i = 1:size(StructObject,1)
    eval(['Axis_elems(',num2str(i),') = Simulink.BusElement;']);
    eval(['Axis_elems(',num2str(i),').Name = StructObjectName{i};'])
    eval(['Axis_elems(',num2str(i),').DataType = StructObject{i};']);
end

Axis.Elements = Axis_elems;

%创建ParamDataBase的simulink.Signal
kAxis = Simulink.Signal;
kAxis.DataType = "Bus: Axis";
kAxis.Dimensions = 1;
kAxis.DimensionsMode = "Fixed";
kAxis.Complexity = "real";
kAxis.CoderInfo.StorageClass = "Custom";
kAxis.CoderInfo.CustomStorageClass = "ExportToFile";
kAxis.CoderInfo.CustomAttributes.HeaderFile = simulink_signal_header;
kAxis.CoderInfo.CustomAttributes.DefinitionFile = simulink_signal_source;



%清除StructObject{i}_elems的基础工作区临时变量
for i = 1:size(StructObject,1)
    eval(['clear ',StructObject{i},'_elems']);
end

%清除基础工作区临时变量
clear i j k temp_string array_temp array_size first_index second_index num filename filepath raw raw_content raw_DefaultValue simulink_signal_source simulink_signal_header simulink_bus_header DataBaseTypedef
clear StructObject StructObjectName CategoryContent VariableNameContent DataTypeContent NameZhContent DefaultValueContent ArraySizeContent
clear ParamDataBase_elems
clear str

%如果'external_database.sldd'存在，删除
if exist(sldd_path,'file')
    delete(sldd_path);
end

%打开sldd文件
myDictionaryObj = Simulink.data.dictionary.create(sldd_path);
%将当前工作区变量导入sldd
clear sldd_path
importFromBaseWorkspace(myDictionaryObj);
saveChanges(myDictionaryObj)

% %清除基础工作区
clear