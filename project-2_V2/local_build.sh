sudo apt install g++-10 cmake

cmake -D CMAKE_CXX_COMPILER=/usr/bin/g++-10 -S . -B build

cmake --build build -v

cd build && ls && ./testing

ls && ./executable < ../sample_input.txt
