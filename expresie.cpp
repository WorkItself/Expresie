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

int main()
{
	string s = "(2+(4-6/2*3+1)+(2-4/(2-1)+1)-1)";// cin >> s;
	if(s[0] != '(') {
		s.insert(0, "(");
		s += ")";
	}
	vector<char> ordine; stack<char> operatii;
	for(int i = 0; i < s.length(); i++)
	{
		if(isdigit(s[i])) ordine.push_back(s[i]);
		else if(s[i] >= 42 && s[i] <= 47) {
			unsigned current = prioritate(s[i]);
			while(prioritate(operatii.top()) <= current && operatii.top() != '(')
			{
				ordine.push_back(operatii.top());
				operatii.pop();
			}
			operatii.push(s[i]);
		}
		else if(s[i] == ')') {
			while(operatii.top() != '(')
			{
				ordine.push_back(operatii.top());
				operatii.pop();
			}
			operatii.pop();
		}
		else operatii.push(s[i]);
	}
	stack<int> rezultate;
	for(int i = 0; i < ordine.size(); i++)
	{
		if(isdigit(ordine[i])) rezultate.push(ordine[i] - '0');
		else {
			int nr1 = rezultate.top();
			rezultate.pop();
			int nr2 = rezultate.top();
			rezultate.pop();
			switch(ordine[i])
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
