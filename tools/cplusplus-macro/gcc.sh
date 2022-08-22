
# author        Oliver Blaser
# date          24.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

g++ --version | grep g++

std=98
echo "$(g++ -dM -E -std=c++$std -x c++ /dev/null | grep -F __cplusplus)  C++$std"

std="03"
echo "$(g++ -dM -E -std=c++$std -x c++ /dev/null | grep -F __cplusplus)  C++$std"

std=11
echo "$(g++ -dM -E -std=c++$std -x c++ /dev/null | grep -F __cplusplus)  C++$std"

std=14
echo "$(g++ -dM -E -std=c++$std -x c++ /dev/null | grep -F __cplusplus)  C++$std"

std=17
echo "$(g++ -dM -E -std=c++$std -x c++ /dev/null | grep -F __cplusplus)  C++$std"

std="2a"
echo "$(g++ -dM -E -std=c++$std -x c++ /dev/null | grep -F __cplusplus)  C++$std"

std=20
echo "$(g++ -dM -E -std=c++$std -x c++ /dev/null | grep -F __cplusplus)  C++$std"

std=23
echo "$(g++ -dM -E -std=c++$std -x c++ /dev/null | grep -F __cplusplus)  C++$std"
