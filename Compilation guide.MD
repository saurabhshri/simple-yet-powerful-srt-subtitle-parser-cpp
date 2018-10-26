<h1>Build with GUI(Windows)</h1>
<ul>
<li>Download the latest CMake from <a href="http://www.cmake.org/">http://www.cmake.org/</a> and install it</li>
<li>Run CMake GUI (at the time of this writing, its called cmake-gui.exe
 on Windows and appears in the start menu after installation)</li>
<li>Point it to the location of the assimp source code. The UI should now look like the screenshot above</li>
<li>Also point it to the folder where you want the binaries to be placed in.</li>
<li>Lines marked in red mark settings you haven't confirmed yet, so 
check if everything is fine and press "Configure" again (if you rebuild 
assimp later, only changed or newly added settings will appear in red 
since the last build settings are cached by CMake!)</li>
<li>Press "Generate" and pick a suitable output build system</li>
<li>Open the generated solution/project files and have fun</li>
</ul>
<h1><a class="anchor" id="cmake_howto_other"></a>
Build without GUI (Other)</h1>
<ul>
<li>Install CMake through the package manager of your choice, or grab a copy from <a href="http://www.cmake.org/">http://www.cmake.org/</a></li>
<li>Navigate to the folder where assimp's top level <em>CMakeLists.txt</em> resides</li>
<li>Use <pre class="fragment">cmake -DNAME_OF_SETTING=VALUE </pre> to configure the build (see the CMake file for a list of all configurable settings.</li>
<li>Use <pre class="fragment">cmake -G 'Unix Makefiles' </pre> to generate build files (GNU make in this case, for a full list of targets see the CMake docs).</li>
<li>Press "Generate" and pick a suitable output build system (i.e. vc version)</li>
<li>Build</li>
</ul>
