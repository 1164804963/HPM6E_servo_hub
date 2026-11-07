function sl_customization(cm)
% Change the order of libraries in the Simulink Library Browser. 
cm.LibraryBrowserCustomizer.applyOrder({'ServoHub Library',-2});
end