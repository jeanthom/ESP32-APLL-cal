#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* ESP32's Xtal frequency */
const double fXtal = 40000000.0;

/* Target frequency */
const double fTarget = 24576000.0;

/* ESP32 chip revision */
const enum {
	REV0,
	REV1
} rev = REV1;

int main(int argc, char *argv[]) {
	double fOut, temp;
	double bestDelta = 1.0/0.0; /* +INF */
	int sdm0 = 0, sdm1 = 0, sdm2 = 0, odiv = 0;
	int bestSdm0 = 0, bestSdm1 = 0, bestSdm2 = 0, bestOdiv = 0;

	if (rev == REV0) {
		for (sdm2 = 0; sdm2 <= 63; sdm2++) {
			/* Checking for frequency range of the numerator */
			temp = fXtal * (sdm2 + 4);
			if (temp > 500000000.0 || temp < 350000000.0) {
				continue;
			}
			
			for (odiv = 0; odiv <= 31; odiv++) {
				fOut = temp/(double)(2*(odiv+2));
				if (fabs(fOut-fTarget) < bestDelta) {
					bestDelta = fabs(fOut-fTarget);
					bestSdm2 = sdm2;
					bestOdiv = odiv;
				}
			}
		}
	} else if (rev == REV1) {
		for (sdm0 = 0; sdm0 <= 255; sdm0++) {
			for (sdm1 = 0; sdm1 <= 255; sdm1++) {
				for (sdm2 = 0; sdm2 <= 63; sdm2++) {
					/* Checking for frequency range of the numerator */
					temp = fXtal * (sdm2 + (double)sdm1/256.0 + (double)sdm0/65536.0 + 4);
					if (temp > 500000000.0 || temp < 350000000.0) {
						continue;
					}

					for (odiv = 0; odiv <= 31; odiv++) {
						fOut = temp/(double)(2*(odiv+2));

						if (fabs(fOut-fTarget) < bestDelta) {
							bestDelta = fabs(fOut-fTarget);
							bestSdm0 = sdm0;
							bestSdm1 = sdm1;
							bestSdm2 = sdm2;
							bestOdiv = odiv;
						}
					}
				}
			}
		}
	}

	fOut = fXtal * (bestSdm2 + bestSdm1/256.0 + bestSdm0/65536.0 + 4) / (double)(2*(bestOdiv+2));
	printf("f= %.01f Hz, ∆f=%.01f Hz (relative: %.04f%%)\n", fOut, fabs(fOut-fTarget), 100*fabs(fOut-fTarget)/fTarget);
	printf("sdm0=%d, sdm1=%d, sdm2=%d, odiv=%d\n", bestSdm0, bestSdm1, bestSdm2, bestOdiv);

	return EXIT_SUCCESS;
}