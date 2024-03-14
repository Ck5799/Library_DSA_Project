sudo apt install g++-10 cmake

cmake -D CMAKE_CXX_COMPILER=/usr/bin/g++-10 -S . -B build

cmake --build build -v

cd build && ls && ./testing

cp -u Sample_Book_Database.dat ./build/Sample_Book_Database.dat

if test -f ../sample_input.txt; then
  ls && ./executable < ../sample_input.txt
else
  ls && ./executable 238.48
fi