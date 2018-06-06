#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > PossibleWords(int m, int n);
vector<int> CumulativeSigns(vector<int> word, vector<int> sign);
vector<int> GetRootsByTypeBySign(int m, int n, vector<int> sign);

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
		vector<int> s = CumulativeSigns(word, signs);
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