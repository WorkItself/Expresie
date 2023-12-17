#include <iostream>
#include <stack>
#include <vector>

using namespace std;

unsigned prioritate(char op)
{
	if(op == '(' || op == ')') return 0;
	else if(op == '*' || op == '/') return 1;
	else return 2;
}

int conv(string s)
{
	int rez = 0;
	for(int i = 0; i < s.length(); i++)
		rez = rez * 10 + s[i] - '0';
	return rez;
}

int main()
{
	string s = "(2+(4-6/2*3+1)+(2-4/(2-1)+1)-1)";// cin >> s;
	s = "(" + s + ")";
	vector<string> ordine; stack<char> operatii;
	for(int i = 0; i < s.length(); i++)
	{
		if(isdigit(s[i])) {
			string str = "";
			str += s[i];
			ordine.push_back(str);
			while(isdigit(s[i+1]))
			{
				ordine[ordine.size()-1] += s[i+1];
				i++;
			}
		}
		else if(s[i] >= 42 && s[i] <= 47) {
			unsigned current = prioritate(s[i]);
			while(prioritate(operatii.top()) <= current && operatii.top() != '(')
			{
				ordine.push_back("" + operatii.top());
				operatii.pop();
			}
			operatii.push(s[i]);
		}
		else if(s[i] == ')') {
			while(operatii.top() != '(')
			{
				string str = "";
				str += operatii.top();
				ordine.push_back(str);
				operatii.pop();
			}
			operatii.pop();
		}
		else operatii.push(s[i]);
	}
	stack<double> rezultate;
	for(int i = 0; i < ordine.size(); i++)
	{
		if(isdigit(ordine[i][0])) rezultate.push(conv(ordine[i]));
		else {
			int nr1 = rezultate.top();
			rezultate.pop();
			double nr2 = rezultate.top();
			rezultate.pop();
			switch(ordine[i][0])
			{
				case '+': nr2+=nr1; break;
				case '-': nr2-=nr1; break;
				case '*': nr2*=nr1; break;
				case '/': nr2/=nr1; break;
			}
			rezultate.push(nr2);
		}
	}
	cout << rezultate.top();
	return 0;
}
