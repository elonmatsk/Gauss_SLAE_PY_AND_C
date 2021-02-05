#include <iostream>
#include <ios>
#include <climits>
#include <string>
#include <algorithm>

class Gauss_method {
private:
	int equations, unknowns, rang_little = 0, rang_big = 0;
	struct Eq_parameters {
		double **eq;
		double **unk;
		double **ans;
	} item;
	struct L_parameters {
		double **eq;
	} L;
	struct U_parameters {
		double **eq;
	} U;


public:
	Gauss_method(int eq, int uk) {
		equations = eq;
		unknowns = uk;
		Define_equation();
	}

	void Enter_elements() {
		for (size_t i = 0; i < equations; i++) {
			for (size_t j = 0; j < unknowns; j++) {
				std::cin >> item.eq[i][j];
			}
			std::cin >> item.ans[i][0];
			item.unk[i][0] = -10000000000000000000000000000000000000000000000000000000000.;
		}
	}

	std::string Find_solution() {
		return IsSolvable() ? Solve_equation() : "NO";
	}

	void Get_unknown() {							
		for (size_t i = 0; i < rang_big; i++) {
			std::cout << item.unk[i][0] << " ";
		}
	}

	/*void Get_L() {
		for (size_t i = 0; i < equations; i++) {
			for (size_t j = 0; j < unknowns; j++) {
				std::cout << L.eq[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void Get_U() {
		for (size_t i = 0; i < equations; i++) {
			for (size_t j = 0; j < unknowns; j++) {
				std::cout << U.eq[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}*/


private:
	void Define_equation() {
		L.eq = new double *[equations];
		U.eq = new double *[equations];
		item.eq = new double *[equations];
		item.unk = new double *[equations];
		item.ans = new double *[equations];
		for (std::size_t i = 0; i < equations; i++) {
			item.eq[i] = new double[unknowns];
			L.eq[i] = new double[unknowns];
			U.eq[i] = new double[unknowns];
			item.unk[i] = new double[1];
			item.ans[i] = new double[1];
		}
	}

	bool IsSolvable() {
		Find_rangs();
		return (rang_little == rang_big) ? true : false;
	}

	void Find_rangs() {															
		for (size_t i = 0; i < equations; i++) {							
			for (size_t j = 0; j < i; j++) {
				U.eq[i][j] = 0;
			}
			for (size_t j = i; j < unknowns; j++) {
				L.eq[i][j] = (i == j) ? 1 : 0;
			}
		}
		for (size_t i = 0; i < std::min(unknowns, equations); i++) {			
			double min = 10000000000000000000000000000000000000000000000000000000000.;
			int index = -1;
			for (size_t j = i; j < equations; j++) {							
				if ((item.eq[j][i] < min) && (item.eq[j][i] != 0)) {
					min = item.eq[j][i];
					index = j;
				}
			}
			if ((index != i) && (index != -1)) {								
				std::swap(item.eq[i], item.eq[index]);
				std::swap(item.ans[i], item.ans[index]);
			}
			for (size_t j = i; j < unknowns; j++) {								
				U.eq[i][j] = item.eq[i][j];
			}
			for (size_t j = i + 1; j < equations; j++) {						
				double sub = 0;
				if (item.eq[j][i] == 0) sub = 0;
				else sub = item.eq[j][i] / item.eq[i][i];
				L.eq[j][i] = sub;
				for (size_t k = i; k < unknowns; k++) {
					item.eq[j][k] -= sub * item.eq[i][k];
				}
				item.ans[j][0] -= sub * item.ans[i][0];
			}
		}
		for (size_t i = 0; i < equations; i++) {								
			int zeroes = 0;
			for (size_t j = i; j < unknowns; j++) {
				if (item.eq[i][j] == 0) {
					zeroes++;
				}
				else {
					rang_little++;
					break;
				}
			}
			if (zeroes == unknowns - i) break;
		}
		rang_big = rang_little;
		for (size_t i = rang_little; i < equations; i++) {						
			if (item.ans[i][0] == 0) {
				break;
			}
			else rang_big++;
		}	
	}

	std::string Solve_equation() {
		if(rang_big < unknowns) return "INF";

		for (int i = rang_big - 1; i >= 0; i--) {
			double sum = 0;
			int count = 0;
			for (int j = unknowns - 1; j > i; j--) {
				sum += U.eq[i][j] * item.unk[rang_big - 1 - count++][0];
			}
			item.unk[i][0] = (item.ans[i][0] - sum) / U.eq[i][i];
		}

		return "YES";
	}

};



int main() {
	std::ios_base::sync_with_stdio(false);
	int equations, unknowns;
	std::cin >> equations >> unknowns;

	Gauss_method *equation = new Gauss_method(equations, unknowns);
	equation->Enter_elements();
	std::string solution = equation->Find_solution();
	if ((solution == "NO") || (solution == "INF")) {
		std::cout << solution << std::endl;
	}
	else {
		std::cout << solution << std::endl;
		equation->Get_unknown();
	}

	//system("pause");
	return 0;
}