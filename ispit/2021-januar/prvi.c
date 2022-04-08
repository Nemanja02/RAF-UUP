#include <stdio.h>

int main() {
    int n = 5, m = 6;
    int mat[5][6] = {
        {1,3,1,4,3,1},
        {2,1,3,4,9,7},
        {1,4,7,1,2,1},
        {2,7,7,1,1,1},
        {2,3,4,5,1,2}
    };


    // Prolazak kroz sve elemente

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            // Svaki element se proverava da li moze da bude vrh trougla po dimenzijama
            // Dimenzije mogu biti od 1 do m
            // Dimenzija je visina i sirina trougla na dnu (Polovina kvadratne matrice)

            for (int dim = 2; dim < m; dim++) {

                // Ukoliko su dimenzije trougla prevelike za pocetnu matricu preci na sledeci element

                if (i + dim > n || j + dim > m) break;

                int brParnih = 0, brNeparnih = 0;

                for (int x = i; x < i+dim; x++) {
                    for (int y = j; y < j+dim; y++) {


                        // provera da li su elementi ispod ili na glavnoj dijagonali
                        if (x-i >= y-j) {
                            if (mat[x][y] % 2 == 0) brParnih++;
                            else brNeparnih++;
                        }

                    }
                }
                if (brParnih >= brNeparnih) {
                    printf("(%d,%d) - %d\n", i+dim-1, j, dim);
                }
            }
        

        }
    }
    return 0;
}