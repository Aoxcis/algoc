#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool isEven(int i) { return i%2==0; }



bool estParfait(int nombre){
	int somme = 0;
	for(int i = 1; i < nombre; i++){
		if(nombre % i == 0){
			somme += i;
		}
	}
	if(somme == nombre){
		return true;
	}
	else{
		return false;
	}
}

void nbParfaits(int n){
	for(int i = 1; i <= n; i++){
		if(estParfait(i)){
			printf("%i est parfait\n", i);
		}
	}
}
