/*
	BSD 3-Clause License

	Translated to C++ by James T. Meech in 2024 from Python code originally authored by Lech A. Grzelak in 2018.

	Copyright (c) 2024, Physical Computation Laboratory, University of Cambridge, Department of Engineering

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
	int T = 1;
	double r = 0.05;
	double sigma = 0.4;
	double sigma2 = pow(sigma,2);
	int S_0 = 100;
	double dt = (double)T / NoOfSteps;
	double rootdt = pow(dt, 0.5);
	
	std::random_device rd{};
	std::mt19937 gen{rd()};
	std::normal_distribution<> d2{0.4, 1.0};
	
	double Sigma[NoOfPaths][NoOfSteps];
	double Z[NoOfPaths][NoOfSteps];
	double X[NoOfPaths][NoOfSteps+1];
	
	for(int j = 0 ; j < NoOfPaths; j++)
	{
		X[j][0] = log(S_0);
	}
	
	for(int j = 0 ; j < NoOfPaths ; j++)
	{
    		for(int i = 0 ; i < NoOfSteps ; i++)
    		{ 
			std::normal_distribution<> d0{0.0, d2(gen)};
			std::normal_distribution<> dm1{0.0, d0(gen)}; 
			Sigma[j][i] = dm1(gen);
			std::normal_distribution<> d1{0.0, Sigma[j][i]}; 
			Z[j][i] = d1(gen);
			X[j][i+1] = X[j][i] + (r - 0.5 * pow(Sigma[j][i],2) ) * dt + Sigma[j][i] * rootdt*Z[j][i];
		}
	}
	return 0;
}
