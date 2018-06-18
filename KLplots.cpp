#include <iostream>
#include <vector>
#include <gsl/gsl_poly.h>

using namespace std;

bool EvenFlipTest(vector<int> const &word, vector<int> const &cumulative_sign, vector<int> const &signs);
bool ShiftTest(vector<int> const &word, vector<int> const &cumulative_sign);

vector<vector<int> > PossibleWords(int m, int n);
vector<vector<int> > PossibleSigns(int m);
vector<int> CumulativeSigns(vector<int> const &word, vector<int> const &sign);
vector<int> ConsturctCoeffs(vector<int> const &word, vector<int> const &cumulative_sign, vector<int> const &signs);
vector<double> GetRootsByTypeBySign(int m, int n, vector<int> sign);
vector<double> GetRootsByType(int m, int n);

bool EvenFlipTest(vector<int> const &word, vector<int> const &cumulative_sign, vector<int> const &signs) {
	int n = word.size() - 1;
	return cumulative_sign[n] * signs[word[n]] == 1;
}

bool ShiftTest(vector<int> const &word, vector<int> const &cumulative_sign) {
	vector<int> w1 = word;
	for (int i = 0; i < word.size(); i++) {
		w1.insert(w1.begin(), w1.back());
		w1.pop_back();

		int pos, order;
		for (pos = 0; pos < word.size(); pos++) {
			if (word[pos] != w1[pos]) break;
		}
		if (pos < word.size()) {
			if (word[pos] < w1[pos]) order = 1;
			else order = -1;
			int csign = cumulative_sign[pos];
			if (csign == order) {
				return false;
			}
		}
	}
	return true;
}

void PossibleWordsHelper(vector<vector<int> > &results, vector<int> temp, int m, int n) {
	if (temp.size() == n) {
		results.push_back(vector<int>(temp));
		return;
	}

	for (int i = 0; i < m; i++) {
		temp.push_back(i);
		PossibleWordsHelper(results, temp, m, n);
		temp.pop_back();
	}
}

vector<vector<int> > PossibleWords(int m, int n) {
	vector<vector<int> > results;
	vector<int> start;
	start.push_back(m-1);
	PossibleWordsHelper(results, start, m, n);
	return results;
}

void PossibleSignsHelper(vector<vector<int> > &possible_signs, vector<int> temp, int m) {
	if (temp.size() == m) {
		possible_signs.push_back(vector<int>(temp));
		return;
	}

	temp.push_back(-1);
	PossibleSignsHelper(possible_signs, temp, m);
	temp.pop_back();

	temp.push_back(1);
	PossibleSignsHelper(possible_signs, temp, m);
	temp.pop_back();

}

vector<vector<int> > PossibleSigns(int m) {
	vector<vector<int> > possible_signs;
	vector<int> start;
	PossibleSignsHelper(possible_signs, start, m);
	return possible_signs;
}

vector<int> CumulativeSigns(vector<int> const &word, vector<int> const &signs) {
	vector<int> c;
	c.push_back(1);
	for (int i = 0; i < word.size()-1; i++) {
		c.push_back(signs[word[i]] * c.back());
	}
	return c;
}

vector<int> ConsturctCoeffs(vector<int> const &word, vector<int> const &cumulative_sign, vector<int> const &signs) {
	vector<int> coeffs;
	for (int i = word.size()-1; i >= 0; i--) {
		coeffs.push_back(0 - cumulative_sign[i] * (word[i] + (1-signs[word[i]]) / 2));
	}
	coeffs[0]--;
	coeffs.push_back(1);
	return coeffs;
}

vector<double> GetRootsByTypeBySign(int m, int n, vector<int> signs) {
	vector<double> roots;
	vector<vector<int> > possible_words = PossibleWords(m, n);
	for (int i = 0; i < possible_words.size(); i++) {
		vector<int> word = possible_words[i];
		vector<int> cumulative_sign = CumulativeSigns(word, signs);
		if (EvenFlipTest(word, cumulative_sign, signs) && ShiftTest(word, cumulative_sign)) {
			vector<int> coeffs = ConsturctCoeffs(word, cumulative_sign, signs);
			double poly[n+1];
			double ans[2*n];
			for (int pos = 0; pos <= n; pos++) {
				poly[pos] = double(coeffs[pos]);
			}

			gsl_poly_complex_workspace *workspace = gsl_poly_complex_workspace_alloc(n+1);
			gsl_poly_complex_solve(poly, n+1, workspace, ans);
			gsl_poly_complex_workspace_free(workspace);

			for (int j = 0; j < 2*n; j++) {
				roots.push_back(ans[j]);
			}
		}
	}
	return roots;
}

vector<double> GetRootsByType(int m, int n) {
	vector<double> roots;
	vector<vector<int> > possible_signs = PossibleSigns(m);
	for (int i = 0; i < possible_signs.size(); i++) {
		vector<int> signs = possible_signs[i];
		vector<vector<int> > possible_words = PossibleWords(m, n);
		for (int j = 0; j < possible_words.size(); j++) {
			vector<int> word = possible_words[j];
			vector<int> cumulative_sign = CumulativeSigns(word, signs);
			if (EvenFlipTest(word, cumulative_sign, signs) && ShiftTest(word, cumulative_sign)) {
				vector<int> coeffs = ConsturctCoeffs(word, cumulative_sign, signs);
				double poly[n+1];
				double ans[2*n];
				for (int pos = 0; pos <= n; pos++) {
					poly[pos] = double(coeffs[pos]);
				}

				gsl_poly_complex_workspace *workspace = gsl_poly_complex_workspace_alloc(n+1);
				gsl_poly_complex_solve(poly, n+1, workspace, ans);
				gsl_poly_complex_workspace_free(workspace);

				for (int j = 0; j < 2*n; j++) {
					roots.push_back(ans[j]);
				}
			}
		}
	}
	return roots;
}


int main() {
	vector<double> results = GetRootsByType(2, 20);
	// for (vector<double>::iterator it = results.begin(); it != results.end(); ++it) {
	// 		cout << ' ' << *it;
	// 	}
	// 	cout << '\n';

	FILE *gnuplotPipe,*tempDataFile;
	char *tempDataFileName;
  	double x,y;
  	tempDataFileName = "graph.txt";     //this will store all of the point external file. Change the name if necessary
  	gnuplotPipe = popen("gnuplot","w");
  	if (gnuplotPipe) {
    	fprintf(gnuplotPipe,"set terminal svg \n");
    	fprintf(gnuplotPipe,"set output 'plot.svg' \n");
      fprintf(gnuplotPipe,"plot \"%s\" lt rgb \"blue\" \n",tempDataFileName); //change the color of the points here
      fflush(gnuplotPipe);
      tempDataFile = fopen(tempDataFileName,"w");
      for (int i = 0; i < results.size(); i=i+2) {
          x = results[i];
          y = results[i+1];
          fprintf(tempDataFile,"%lf %lf\n",x,y);
      }
      fprintf(gnuplotPipe,"set out \n");
      fclose(tempDataFile);
  } else {
      printf("gnuplot not found...");
  }

	// for (vector<vector<int> >::iterator it = results.begin(); it != results.end(); ++it) {
	// 	for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2) {
	// 		cout << ' ' << *it2;
	// 	}
	// 	cout << '\n';
	// }
	return 0;
}