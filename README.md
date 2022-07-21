# Big Integer library written in C++

## Dependencies
- `CMake` 3.23.2 and above
- `C++17` and above

## CMake Integration
In your `CMakeLists.txt` file, add the following code:
```cmake
include(FetchContent)

cmake_minimum_required(VERSION 3.23.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(<Your Project Name> CXX)

FetchContent_Declare(
  bigint
  GIT_REPOSITORY https://github.com/WilsonOh/CPP_BigInt.git
  GIT_TAG main
)

FetchContent_MakeAvailable(HttpClient)

add_executable(${PROJECT_NAME} <Your Source Files>...)

target_link_libraries(${PROJECT_NAME} PRIVATE bigint)
```

If you're building the project within the source directory, you can run:
```console
cmake -S . -B build 
```
to build the files, or you can include tests by passing the environment variable `ENABLE_TESTING=ON`:
```console
cmake -DENABLE_TESTING=ON -S . -B build
```
and then run the tests with:
```console
cd build && make
make test
```

## Usage
This BigInt library makes use of C++'s `user defined literals`.
The following code declares and initializes a `BigInt` object:
```cpp
auto a = 12345_bn;
```
All the appropriate operators are overloaded for `BigInt`, so you can use it like you would for an `int`.<br>
Negative values are also supported, and the sign of a `BigInt` can be flipped by calling the `negate` method, which returns a `BigInt` with a flipped sign.

## Examples
---
### Fiboncacci Sequence 
```cpp
#include <BigInt.hpp>
#include <iostream>

BigInt fib(int n) {
  if (n < 2) {
    return n;
  }
  auto a = 0_bn;
  auto b = 1_bn;
  auto c = a + b;
  for (int i = 0; i < n; ++i) {
    a = b;
    b = c;
    c = a + b;
  }
  return a;
}

int main(void) {
  std::cout << fib(10000) << '\n';
}

```
<details>
<summary>Output</summary>

3364476487643178326662161200510754331030214846068006390656476997468008144
2166662368155595513633734025582065332680836159373734790483865268263040892
4630564318873545443695598274916066020998841839338646527313000888302692356
7361313511757929743785441375213052050434770160226475831890652789085515436
6159582987279682987510631200575428783453215515103870818298969791613127856
2650331954871402142875326981879620469360978799003509623022910263681314931
9527563022783762844154036058440257211433496118002309120828704608892396232
8835461505776583271252546093591128203925285393434620904245248929403901706
2338889910858410651831733604374707379085526317643257339937128719375877468
9747992630583706574283016163740896917842637862421283525811282051637029808
9332099905707920064367426202389783111470054074998459250360633560933883831
9233867830561364353518921332797329081337326426526339897639227234078829281
7795358057099369104917547080893184105614632233821746563732124822638309210
3297701648054726243842374862411453093812206564914032751086643394517512161
5265453613331113140424368548051067658434935238369596534280717687753283482
3434555736671973139274627362910821067928078471803532913117677892465908993
8635459327894523777674406192240337638674004021330343297496902028328145933
4188268176838930720036347956231171031012919531697946076327375892535307725
5237594378843450406771555577905645044301664011946258097221672975861502696
8443146952034614932291105970676243268515992834709891284706740862008587135
0162603120719031720860940812983215810772820763531866246112782455372085323
6530577595643007251774431505153960090516860322034916322264088524885243315
8051534849622434848299380905070483482449327453732624567755879089187190803
6620580095947431500524025327097469953187707243768259074199396322659841474
9819360928522394503970716544315642132815768890805878318340491743455627052
0223564846495196112460268313970975069382648706613264507665074611512677522
7486215986425307112984411826226610571635150692600298617049454250474913781
1515413994155067125627119713325276363193960690289565028826860836224108205
0562430701794976171121233066073310059947366875

</details>
