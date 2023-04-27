echo "post build script execution starting..."

if [ -f "build/bin/libMoltenVK.dylib" ] ; then
    rm "build/bin/libMoltenVK.dylib"
fi

if [ -f "build/bin/libvulkan.1.dylib" ] ; then
    rm "build/bin/libvulkan.1.dylib"
fi

echo "post build script execution Ended!"