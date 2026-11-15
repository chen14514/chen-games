#include <bits/stdc++.h>
using namespace std;

void sixseven(){
	bool three=true;
	int num[14]={0,6,6,6,6,6,6,7,7,7,7,7,7,7};
	while (three){
		for (int i=1;i<=12;i++){
			if (rand()%2==0){
				swap(num[i],num[i+1]);
			}
		}
		three=false;
		for (int i=3;i<=13;i++){
			if (num[i-2]==num[i-1]&&num[i-1]==num[i]){
				three=true;
				break;
			}
		}
	}
	cout<<"猜67（6个6，7个7，不会有三个连续数字重复）"<<endl; 
	string s;
	int cnt=1,six=6,seven=7;
	while (true){
		if (cnt==14){
			cout<<"恭喜！猜对了";
			return;
		}
		cout<<"当前轮数："<<cnt<<endl;
		cin>>s; 
		if (s=="6"){
			if (num[cnt]==6){
				six--;
				cout<<"对（6-7剩余："<<six<<"-"<<seven<<"）"<<endl;
				cnt++;
			}
			else{
				cout<<"错误！答案：";
				for (int i=1;i<=13;i++){
					cout<<num[i]<<" ";
				}
				return; 
			}
		}
		else if (s=="7"){
			if (num[cnt]==7){
				seven--;
				cout<<"对（6-7剩余："<<six<<"-"<<seven<<"）"<<endl;
				cnt++;
			}
			else{
				cout<<"错误！答案：";
				for (int i=1;i<=13;i++){
					cout<<num[i]<<" ";
				}
				return; 
			}
		}
		else{
			cout<<"无效输入！"<<endl; 
		}
	}
}

int main()
{
	srand(time(0));
	int play=0;
	while (true){
		cout<<"累计游玩："<<play<<endl; 
		sixseven();
		play++;
		cout<<endl<<"继续（Y/N）：";
		string s;
		cin>>s;
		if (s=="Y"||s=="y"){
			system("cls");
			continue;
		}
		else if (s=="N"||s=="n"){
			return 0;
		}
		system("cls");
	}
	return 0;
}

