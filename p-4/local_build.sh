sudo apt install g++-10 cmake

cmake -D CMAKE_CXX_COMPILER=/usr/bin/g++-10 -S . -B build

cmake --build build -v
cp BookstoreInventory.dat ./build/BookstoreInventory.dat && mv "Open Library Database-Large.dat" "./build/Open Library Database-Large.dat"

cd build && ls && ./testing

if test -f ../sample_input.txt; then
  ls && ./executable < ../sample_input.txt
else
  ls && ./executable
fi
