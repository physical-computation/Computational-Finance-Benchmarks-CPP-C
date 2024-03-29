/*
	BSD 3-Clause License

	Translated to C++ by James T. Meech in 2024 from Python code originally authored by Lech A. Grzelak.

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
#include <random>

int
main()
{
	int NoOfPaths = 25;
	int NoOfSteps = 500;
	double T = 1.0;
	double rho = -0.9;
	double dt = T / float(NoOfSteps);
	double rootDt = pow(dt, 0.5);
	double oneMinusRhoSqauredRooted = sqrt(1.0 - pow(rho,2));
	
	double Z1[NoOfPaths][NoOfSteps];
	double Z2[NoOfPaths][NoOfSteps];
	
	double W1[NoOfPaths][NoOfSteps + 1];
	double W2[NoOfPaths][NoOfSteps + 1];
	
	std::random_device rd {};
	std::mt19937 gen {rd()};
	std::normal_distribution<> d {0.0, 1.0};
	
	for (int j = 0 ; j < NoOfPaths ; j++)
	{
		for (int i = 0 ; i < NoOfSteps ; i++)
		{
			Z1[j][i] = d(gen);
			Z2[j][i] = d(gen);
			Z2[j][i]= rho * Z1[j][i] + oneMinusRhoSqauredRooted * Z2[j][i];
			W1[j][i+1] = W1[j][i] + rootDt*Z1[j][i];
			W2[j][i+1] = W2[j][i] + rootDt*Z2[j][i];
		}
	}	
	return 0;
}
