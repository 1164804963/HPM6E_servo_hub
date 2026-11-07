function hLib = crl_table_sinfcn


hLib = RTW.TflTable;
%---------- entry: cos ----------- 
hEnt = createCRLEntry(hLib, ...
    'single y1 = cos( single u1 )', ...
    'single y1 = yuanhub_cos_f32( single u1 )');
hEnt.setTflCFunctionEntryParameters( ...
          'Priority', 100, ...
          'ImplementationHeaderFile', 'yuanhub_math.h');

hEnt.EntryInfo.Algorithm = 'RTW_UNSPECIFIED';


hLib.addEntry( hEnt ); 

%---------- entry: sin ----------- 
hEnt = createCRLEntry(hLib, ...
    'single y1 = sin( single u1 )', ...
    'single y1 = yuanhub_sin_f32( single u1 )');
hEnt.setTflCFunctionEntryParameters( ...
          'Priority', 100, ...
          'ImplementationHeaderFile', 'yuanhub_math.h');

hEnt.EntryInfo.Algorithm = 'RTW_UNSPECIFIED';


hLib.addEntry( hEnt ); 

%---------- entry: sqrt ----------- 
hEnt = createCRLEntry(hLib, ...
    'single y1 = sqrt( single u1 )', ...
    'single y1 = yuanhub_sqrt_f32( single u1 )');
hEnt.setTflCFunctionEntryParameters( ...
          'Priority', 100, ...
          'ImplementationHeaderFile', 'yuanhub_math.h');



hLib.addEntry( hEnt ); 

