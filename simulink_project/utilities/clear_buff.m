cd ..\simulink_code_gen

delete('*.c');
delete('*.cpp');
delete('*.h');
delete('*.hpp');

cd ..\simulink_project;

cd work\cache\;

delete('*.slxc')

try
    rmdir('slprj', 's')
catch
    disp('Error ignored no slprj.')
end
try
    rmdir('*ert_rtw', 's')
catch
    disp('Error ignored no _ert_rtw.')
end

cd ..\..\;

cd work\codegen;

delete('*.slxc')

try
    rmdir('slprj', 's')
catch
    disp('Error ignored no slprj.')
end
try
    rmdir('*ert_rtw', 's')
catch
    disp('Error ignored no _ert_rtw.')
end

cd ..\..\;