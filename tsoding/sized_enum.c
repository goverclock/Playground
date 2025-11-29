// https://www.youtube.com/watch?v=IA-QzNmn_i8
// 54:05

#include <stdio.h>

#define TYPED_ENUM(type, name)                                                 \
  type name;                                                                   \
  enum

typedef TYPED_ENUM(char, my_enum){
    my_enum_foo,
    my_enum_bar,
};

int main() {
  my_enum x = my_enum_foo;
  printf("%zu", sizeof(my_enum));

  return 0;
}
