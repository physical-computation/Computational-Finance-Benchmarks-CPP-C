/*
	BSD 3-Clause License

	Translated to C by James T. Meech in 2024 from Python code originally authored by Lech A. Grzelak.

	Copyright (c) 2024, Physical Computation Laboratory, University of Cambridge, Department of Engineering

	Original Python code copyright (c) 2024, leszek

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice,
	this list of conditions and the following disclaimer in the documentation
	and/or other materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its
	contributors may be used to endorse or promote products derived from
	this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int
main()
{
	int NoOfPaths = 25;
	int NoOfSteps = 500;
	int T = 5;
	int xiP = 1;
	double muJ = 0;
	double sigmaJ = 0.7;
	double muPath = 0;
	double sigmaPath = 1.0;
	double sigma = 0.2;
	double S0 = 100;
	double log_S0 = log(S0);
	double r=0.05;	
	double dt = T / (double) NoOfSteps;
	double muPoisson = xiP*dt;
	
	double sigmaRootDt = sigma*sqrt(dt);

	double X[NoOfPaths][NoOfSteps+1];
	double ZPois[NoOfPaths][NoOfSteps];
	double Z[NoOfSteps][NoOfSteps];
	double J[NoOfSteps][NoOfSteps];
                
	double EeJ = exp(muJ + 0.5*sigmaJ*sigmaJ);
	double const1 = (r - xiP*(EeJ-1) - 0.5*sigma*sigma)*dt;

	const gsl_rng_type * RNG;
	gsl_rng * R;
	gsl_rng_env_setup();
	RNG = gsl_rng_default;
	R = gsl_rng_alloc (RNG);

	for(int j = 0 ; j < NoOfPaths ; j++)
	{
		X[j][0] = log_S0;
		for(int i = 0 ; i < NoOfSteps ; i++)
		{
			ZPois[j][i] = gsl_ran_poisson(R, muPoisson);
			Z[j][i] = gsl_ran_gaussian(R, sigmaPath) + muPath;
			J[j][i] = gsl_ran_gaussian(R, sigmaJ) + muJ;
			X[j][i+1]  = X[j][i] + const1 + sigmaRootDt * Z[j][i] + J[j][i] * ZPois[j][i];
		}
	}

	gsl_rng_free (R);

	return 0;
}
