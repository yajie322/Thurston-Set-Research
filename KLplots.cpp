#include <iostream>
#include <vector>

using namespace std;

bool EvenFlipTest(vector<int> const &word, vector<int> const &cumulative_sign, vector<int> const &signs);
bool ShiftTest(vector<int> const &word, vector<int> const &cumulative_sign);

vector<vector<int> > PossibleWords(int m, int n);
vector<int> PossibleSigns(int m);
vector<int> CumulativeSigns(vector<int> word, vector<int> sign);
vector<int> GetRootsByTypeBySign(int m, int n, vector<int> sign);
vector<int> GetRootsByType(int m, int n);

bool EvenFlipTest(vector<int> const &word, vector<int> const &cumulative_sign, vector<int> const &signs) {
	int n = word.size() - 1;
	return cumulative_sign[n] * signs[word[n]] == 1

}

bool ShiftTest(vector<int> const &word, vector<int> const &cumulative_sign) {
	vector<int> w1 = word;
	for (int i = 0, i < word.size(); i++) {
		w1.insert(w1.begin(), w1.pop_back());

		int pos, order;
		for (pos = 0; pos < word.size(); pos++) {
			if (word[pos] != w1[pos]) {
				if (word[pos] < w1[pos]) order = 1;
				else order = -1;
				
				csign = cumulative_sign[pos];
				if (csign == order) return false;
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

vector<int> CumulativeSigns(vector<int> word, vector<int> signs) {
	vector<int> c;
	c.push_back(1);
	for (int i = 0; i < word.size(); i++) {
		c.push_back(signs[word[i]] * c.back());
	}
	return c;
}

vector<int> GetRootsByTypeBySign(int m, int n, vector<int> signs) {
	vector<vector<int> > possible_words = PossibleWords(m, n);
	for (int i = 0; i < possible_words.size(); i++) {
		vector<int> word = possible_words[i];
		vector<int> cumulative_sign = CumulativeSigns(word, signs);
		if (EvenFlipTest(word, cumulative_sign, signs) && ShiftTest(word, cumulative_sign)) {
			// Consturct polynomial and solve it 
		}
	}
}

// TO DO
vector<int> GetRootsByType(int m, int n) {
	vector<vector<int> > possible_signs = PossibleSigns(m);
	for (int i = 0; i < possible_signs.size(); i++) {
		vector<int> sign = possible_signs[i];

		// call GetRootsByTypeBySign
	}
}


int main() {
	vector<vector<int> > results = PossibleWords(2, 19);

	for (vector<vector<int> >::iterator it = results.begin(); it != results.end(); ++it) {
		for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2) {
			cout << ' ' << *it2;
		}
		cout << '\n';
	}
	return 0;
}