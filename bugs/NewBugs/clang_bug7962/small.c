int &f();

//Not a bug

void a(long *lngPtr, int number2) {
  *lngPtr = 2
  ++f();
}

void b(long *lngPtr, int number2) {
  *lngPtr = 2++
  f();
}
