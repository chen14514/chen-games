#include <bits/stdc++.h>
using namespace std;

//原价11￥现0￥ （原游戏《6-7》https://store.steampowered.com/app/1436640/67/） 

int main()
{
	srand(time(0));
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
	int cnt=1;
	while (true){
		if (cnt==14){
			cout<<"恭喜！猜对了";
			return 0;
		}
		cout<<"当前轮数："<<cnt<<endl;
		cin>>s; 
		if (s=="6"){
			if (num[cnt]==6){
				cout<<"对"<<endl;
				cnt++;
			}
			else{
				cout<<"错误！答案：";
				for (int i=1;i<=13;i++){
					cout<<num[i]<<" ";
				}
				return 0; 
			}
		}
		else if (s=="7"){
			if (num[cnt]==7){
				cout<<"对"<<endl;
				cnt++;
			}
			else{
				cout<<"错误！答案：";
				for (int i=1;i<=13;i++){
					cout<<num[i]<<" ";
				}
				return 0; 
			}
		}
		else{
			cout<<"无效输入！"<<endl; 
		}
	}
	return 0;
}

