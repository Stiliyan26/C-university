#include <stdio.h>
#include <string.h>

int br = 6;
int coins = { 50, 20, 10, 5, 2, 1};

void main() {
  for (int i = 0; i < br; i++ ) {
    printf("%d ", coins[i]);
  }
}