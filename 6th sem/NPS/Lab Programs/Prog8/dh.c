#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main()
{
	long long int p,g;
	long long int a, b;	// a - Alice's private Key, b - Bob's private Key.
	long long int A, B;	// A - Alice's Public Key, B - Bob's Public Key
	printf("Enter the prime no(p) :");
	scanf("%lld",&p);
	printf("\nEnter the primitive root of p(g) :");
	scanf("%lld",&g);
	printf("\nEnter the alice private key (a) :");
	scanf("%lld",&a);
	printf("\nEnter the Bob private key (b) :");
	scanf("%lld",&b);
	
	A = (long long int) pow(g,a)%p;
	B = (long long int) pow(g,b)%p;

	long long int keyA = (long long int) pow(B,a)%p;
	long long int keyB = (long long int) pow(A,b)%p;

	printf("\nAlice's Secret Key is %lld\nBob's Secret Key is %lld\n\n", keyA, keyB);

	return 0;
}
