files="src/lexer.cpp src/main.cpp src/SMachine.cpp"
out="bin/app.exe"

g++ $files -o $out

echo $files
