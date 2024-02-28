files="src/lexer.cpp src/main.cpp src/SMachine.cpp"
out="bin/app.exe"
libs="-ltinyxml2"

g++ $files -o $out $libs

echo $files
