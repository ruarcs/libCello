
#include "Cello.h"

/*
** This example shows dynamic creation of a Type on the heap.
** As the functions must be static there is some limitation,
** but with creative thinking could become a powerful tool.
*/

local var Hello;

data {
  var type;
  int hello_val;
} HelloData;

local var Hello_New(var self, va_list* args) {
  HelloData* hd = cast(self, Hello);
  hd->hello_val = va_arg(*args, int);
  return self;
}

local var Hello_Delete(var self) {
  return self;
}

local var Hello_Eq(var self, var obj) {
  HelloData* lhs = cast(self, Hello);
  HelloData* rhs = cast(obj, Hello);
  if (lhs->hello_val == rhs->hello_val) {
    return True;
  } else {
    return False;
  }
}

int main(int argc, char** argv) {
  
  New hello_new_instance = { sizeof(HelloData), Hello_New, Hello_Delete };
  Eq hello_eq_instance = { Hello_Eq };
  
  Hello = new(Type, "Hello", 2, 
    (var[]){ &hello_new_instance, &hello_eq_instance }, 
    (const char*[]){ "New", "Eq" } );
  
  print("%s is a %s!\n", Hello, type_of(Hello));

  var hello_obj1 = new(Hello, 1);
  var hello_obj2 = new(Hello, 2);

  print("Equal? %d\n", eq(hello_obj1, hello_obj2));
  
  delete(hello_obj1);
  delete(hello_obj2);
  
  delete(Hello);
  
  return 0;
}

