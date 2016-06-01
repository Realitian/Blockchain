 #define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <functional>
#include <chrono>
#include <deque>
using std::vector;
using std::cin;

std::random_device rd;
std::mt19937 gen(rd());

const long double alpha = 0.85;
const long double convergence = 0.000000001;



int main()
{
	std::freopen("test.in", "r", stdin);
	int N;
	std::cin >> N;

	auto start = std::chrono::high_resolution_clock::now();

	std::freopen("test.out", "w", stdout);


	std::deque<std::deque<int> > in_degree(N, std::deque<int>());
	std::deque<std::deque<int> > out_degree(N, std::deque<int>());
	//
	// std::uniform_int_distribution<int> rand_Link(N-1,3*N);
	// std::function<int()> f = std::bind(rand_Link, std::ref(gen));
	//
	// std::uniform_int_distribution<int> rand_Node(0,N-1);
	// std::function<int()> f2 = std::bind(rand_Node, std::ref(gen));
	//
	// int M =f();
	int i(0), j(0);
	// while(i < M)
	// {
	// 	int a = f2();
	// 	int b = f2();
	// 	if (a == b)
	// 		break;
	// 	in_degree.at(b).push_back(a);
	// 	out_degree.at(a).push_back(b);
	// 	i++;
	// }
	int M;
	cin >> M;
	for (int i(0); i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		in_degree.at(b).push_back(a);
		out_degree.at(a).push_back(b);
	}
	long double coeff2 = (1 - alpha) / N;

	std::deque < std::deque<long double>> H(N, std::deque<long double>(N, coeff2));

	i = 0;

	for (const auto &x : in_degree)
	{
		for (const auto &y : x)
		{
			H.at(i).at(y) += alpha*static_cast<long double>(1 / static_cast<long double>(out_degree.at(y).size()));
		}
		i++;
	}

	i = 0;
	for (const auto&x : out_degree)
	{
		if (!x.size())
			for (j = 0; j < N; j++)
				H.at(j).at(i) += alpha / static_cast<double>(N);
		i++;
	}
	std::deque<long double> PR(N, 1 / static_cast<double>(N)); // The final PageRank

	std::deque<long double> buffer(N, 0); //
	double res(0);
	bool stop = false;
	int nombre_iteration = 0;
	while (!stop)
	{
		nombre_iteration++;
		j = 0;

		for (const auto& x : H)
		{
			res = 0; i = 0;
			for (const auto& y : x)
			{
				res += PR.at(i++)*y;
			}
			buffer.at(j++) = res;
		}

		i = 0;
		for (const auto& x : buffer)
		{
			if (std::abs(x - PR.at(i++)) > convergence)
			{
				PR = buffer;
				break;
			}

			if (i == N)
			{
				stop = true;
			}
		}
	}
	i = 1;
	auto fin = std::chrono::high_resolution_clock::now();
	std::cout << "Time in second :" << std::chrono::duration_cast<std::chrono::milliseconds>(fin - start).count() << std::endl;
	std::cout << "Number of iterations :" << nombre_iteration << std::endl;
	for (const auto & x : buffer)
	{
		std::cout << "PageRank " << i++ << "  : " << x << std::endl;
	}


	system("pause");
	system("pause");
	system("pause");

	return 0;
}
