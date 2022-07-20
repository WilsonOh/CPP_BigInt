#include <BigInt.hpp>

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
  auto a = "8005"_bn;
  auto b = "35"_bn;
  std::cout << a / b << '\n';
}
