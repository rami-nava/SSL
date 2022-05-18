#include <assert.h>
#include "Conversion.h"
#include <stdio.h>

int main (void) {

assert (casiIgual (GetCelsFromFahr (20),-6.6667));
assert (casiIgual (GetCelsFromFahr (115),46.1111));
assert (casiIgual (GetCelsFromFahr (190),87.7778));
assert (casiIgual (GetCelsFromFahr (220),104.444));
assert (casiIgual (GetFahrFromCels (37),98.6));
assert (casiIgual (GetFahrFromCels (134),273.2));
assert (casiIgual (GetFahrFromCels (200),392.0));
assert (casiIgual (GetFahrFromCels (290),554.0));
printf("NO HAY ERRORES EN LOS TESTS\n");
}
