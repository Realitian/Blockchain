#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <functional> 
#include <chrono>
#include <algorithm>
#include <deque>
using std::vector;
using std::cin;

std::random_device rd;
std::mt19937 gen(rd());

const long double alpha = 0.85;
const long double convergence = 0.001;




int main()
{
	std::freopen("test", "r", stdin);
	int N;
	std::cout << "Nombre de noeuds pour le graphe" << std::endl;
	std::cin >> N;

	auto start = std::chrono::high_resolution_clock::now();
	//
	std::freopen("test.out", "w", stdout);
	//
	//
	std::deque<std::deque<int> > in_degree(N, std::deque<int>());
	std::deque<std::deque<int> > out_degree(N, std::deque<int>());
	//
	std::uniform_int_distribution<int> rand_Link(N - 1, 3 * N);
	std::function<int()> f = std::bind(rand_Link, std::ref(gen));
	
	std::uniform_int_distribution<int> rand_Node(0, N - 1);
	std::function<int()> f2 = std::bind(rand_Node, std::ref(gen));
	
	int M = f();
	int i(0), j(0);
	int M;
	// cin >> M;
	while (i < M)
	{
		int a, b;
		a = f2();
		b = f2();
		//	cin >> a >> b;
		//	std::cerr << a << b;
		//	a--; b--;
		in_degree.at(b).push_back(a);
		out_degree.at(a).push_back(b);
		i++;
	}

	vector<int> outgoing_link_null;
	for (int i(0); i < N; i++)
	{
		if (out_degree.at(i).size() == 0)
			outgoing_link_null.push_back(i);
	}

	long double coeff2 = (1 - alpha) / N;


	i = 0;



	std::deque<long double> PR(N, 1 / static_cast<float>(N)); // The final PageRank

	std::deque<long double> buffer(N, 0); // 
	double res(0);
	bool stop = false;
	int nombre_iteration = 0;

	while (!stop)
	{
		nombre_iteration++;
		j = 0;
		float sum2 = 0;
		std::for_each(PR.begin(), PR.end(), [&sum2](auto& n) {
			sum2 += n;
		});
		for (i = 0; i < N; i++)
		{
			res = 0;
			for (const auto& x : in_degree.at(i))
			{
				res += alpha*(1 / static_cast<float>(out_degree.at(x).size()))* PR.at(x);
			}
			for (const auto& x : outgoing_link_null)
			{
				res += (alpha / static_cast<float>(N))*PR.at(x);
			}
			res += sum2*coeff2;
			buffer.at(i) = res;
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
				stop = true;
		}
	}
	i = 1;
	auto fin = std::chrono::high_resolution_clock::now();
	std::cout << "Time in second :" << std::chrono::duration_cast<std::chrono::seconds>(fin - start).count() << std::endl;
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
