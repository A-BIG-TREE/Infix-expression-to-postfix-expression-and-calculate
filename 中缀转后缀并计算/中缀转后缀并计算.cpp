#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool check(string& ch) {
	stack<char> br;
	int point = 0;
	for (int i = 0; i < ch.size(); i++) {
		//字符只能是0-9或+-*/或小数点
		if (!((ch[i] >= '0' && ch[i] <= '9') || ch[i] == '+' || ch[i] == '-' || ch[i] == '*' || ch[i] == '/' || ch[i] == '(' || ch[i] == ')' || ch[i] == '.'))
			return false;
		//数字后不能紧跟左括号
		if ((ch[i] >= '0' && ch[i] <= '9') && ch[i + 1] == '(')
			return false;
		//右括号后不能紧跟数字
		if (ch[i] == ')' && (ch[i + 1] >= '0' && ch[i + 1] <= '9'))
			return false;
		if (ch[i] == '+' || ch[i] == '-' || ch[i] == '*' || ch[i] == '/' || ch[i] == '.') {
			//开头不能是符号
			if (i == 0) return false;
			//末尾不能是符号
			else if (i + 1 == ch.size()) return false;
			//不能存在连续两个符号
			else if (ch[i + 1] == '+' || ch[i + 1] == '-' || ch[i + 1] == '*' || ch[i + 1] == '/')
				return false;
			//运算符的前后不能是括号
			else if (/*ch[i - 1] == '(' ||*/ ch[i + 1] == ')')
				return false;
		}
		//一个数字不能出现两个小数点
		if (ch[i] == '.') {
			point++;
			if (point >= 2)
				return false;
		}
		if (ch[i] == '+' || ch[i] == '-' || ch[i] == '*' || ch[i] == '/')
			point = 0;
		//不能出现空括号
		if (ch[i] == '(' && ch[i + 1] == ')')
			return false;
		//不能出现不成对的括号
		if (ch[i] == '(')
			br.push(ch[i]);
		if (ch[i] == ')') {
			//不能出现单独右括号
			if (br.empty())return false;
			else br.pop();
		}
	}
	//不能出现不成对的括号
	if (!br.empty())
		return false;
	return true;
}

string change(string& ch) {
	stack <char> sign;
	string str;
	for (int i = 0; i < ch.size(); i++) {
		//遇到数字直接输出
		while ((ch[i] >= '0' && ch[i] <= '9') || ch[i] == '.') {
			str.push_back(ch[i]);
			i++;
			if (!(ch[i] >= '0' && ch[i] <= '9' || ch[i] == '.')) {
				str.push_back(' ');
				break;
			}
		}
		//遇到加减号
		if (ch[i] == '+' || ch[i] == '-') {
			if (sign.empty())
				sign.push(ch[i]);
			else {
				while (!sign.empty()) {
					if (sign.top() == '(') {
						//sign.push(ch[i]);
						break;
					}
					else {
						str.push_back(sign.top());
						sign.pop();
					}
				}
				sign.push(ch[i]);
			}
		}
		//遇到乘除号
		else if (ch[i] == '*' || ch[i] == '/') {
			if ((!sign.empty())&&(sign.top() == '*' || sign.top() == '/')) {
				str.push_back(sign.top());
				sign.pop();
				sign.push(ch[i]);
			}
			else {
				sign.push(ch[i]);
			}
		}
		//遇到左括号
		else if (ch[i] == '(')
			sign.push(ch[i]);
		//遇到右括号
		else if (ch[i] == ')') {
			while (sign.top() != '(') {
				str.push_back(sign.top());
				sign.pop();
			}
			sign.pop();
		}
	}
	//剩下符号都输出
	while (!sign.empty()) {
		str.push_back(sign.top());
		sign.pop();
	}
	return str;
}

double calculate(string& str) {
	stack<double> re;
	string num;
	double a, b;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			b = re.top(); re.pop();
			a = re.top(); re.pop();
			switch (str[i]) {
			case '+':re.push(a + b); break;
			case '-':re.push(a - b); break;
			case '*':re.push(a * b); break;
			case '/':re.push(a / b); break;
			}
		}
		else {
			num.clear();
			for (; i < str.size(); i++) {
				if (str[i] == ' ')
					break;
				else num.push_back(str[i]);
			}
			re.push(stod(num));
		}	
	}
	return re.top();
}

int main() {
	string ch;
	while (1) {
		cout << "请输入中缀表达式（整数或小数和加减乘除符号）：" << endl;
		cin >> ch;
		if (!check(ch))
			cout << "输入格式错误" << endl;
		else break;
	}
	string str = change(ch);
	cout <<"转化为后缀表达式为："<<endl<< str << endl;
	double result = calculate(str);
	cout << "表达式的值为：" << endl << result << endl;
}