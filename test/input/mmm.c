

int main(int argc, char ** argv) {

long A[50][50];
long B[50][50];
long C[50][50];
int x1, x2, x3;
#pragma scop
for ( x1 = 0 ; x1 <= 49 ; x1++) {
  for (x2 = 0 ; x2 <= 49 ;  x2++) {
     for (x3 = 0 ; x3 <= 49 ; x3++) {
         C[x1][x2] = C[x1][x2] + A[x1][x3]*B[x3][x2];
     }
  }
}
#pragma endscop
}
