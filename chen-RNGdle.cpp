#include <bits/stdc++.h>
//#include <windows.h>
using namespace std;

/*
	原作：https://www.rngdle.com/ （不太稳定，然后就写了一个代码） 

	v1.0 更新日志
	- 加入登录，抽数字等基本内容 
	
	v1.1 预告
	- 加入成就系统
	- 支持修改用户名，密码 
	
	------ 
	
	系统：windows
	软件：dev-c++ 
	
	意见/bug反馈：github issue/洛谷私信 
	
	此游戏已同步上传至仓库chen-games(MIT协议)
	可修改，可二创，需标注“原作者chen_14514(洛谷uid1760537)” 
*/ 

//全局变量
string user_name="";
string user_password="";
int user_cnt=0;//抽奖计数 

//清屏 
void clean(){
	system("cls");
} 

//生成0~999999随机数 
int number(){
	int high=rand()%1000;
	int low=rand()%1000;
	return high*1000+low;
} 

//菜单 
void menu(){
	clean();
	cout<<"============ chen RNGdle ============"<<endl;
	cout<<endl;
	cout<<"当前用户："<<(user_name==""?"未登录":user_name)<<endl; 
	cout<<endl;
	cout<<"> 1.抽数字"<<endl;
	cout<<"> 2.登录/注册"<<endl;
	cout<<"> 3.个人主页（需登录）"<<endl;
	cout<<"> 4.保存（需登录）"<<endl; 
	cout<<"> 5.退出"<<endl;
	cout<<endl;
	cout<<"数字选择（1~5）："; 
}

void save(){
	string filename=user_name+"_chenRNGdle.txt";
	ofstream file(filename);
	if (file.is_open()){
		file<<user_name<<endl;
		file<<user_password<<endl;
		file<<user_cnt<<endl;
		file.close();
		cout<<"成功保存到："<<filename<<endl;
	}
	else{
		cout<<"保存失败！"<<endl;
	}
}

void load(string name,string password){
	string filename=name+"_chenRNGdle.txt";
	ifstream file(filename);
	if (file.is_open()){
		string load_name,load_password;
		file>>load_name;
		file>>load_password;
		if (password==load_password){
			user_name=load_name;
			user_password=load_password;
			file>>user_cnt;
			file.close();
			cout<<"成功加载："<<filename<<endl;
		}
		else{
			file.close();
			cout<<"用户名或密码错误！"<<endl;
		}
	}
	else{
		user_name=name;
		user_password=password;
		user_cnt=0;
		cout<<"已自动创建："<<filename<<endl;
		save();
	}
}

int main()
{
	srand((unsigned)time(0));
	while (true){
		menu();
		string op;
		cin>>op;
		cout<<endl;
		if (op=="1"){//抽数字
			if (user_name==""){
				cout<<"请先登录！"<<endl;
			} 
			else{
					user_cnt++;
					cout<<"当前数字："<<number()<<endl;
					cout<<"抽取次数："<<user_cnt<<endl;
				}
			}
		else if (op=="2"){//登录/注册
			string name,password;
			cout<<"输入用户名：";
			cin>>name;
			cout<<"输入密码：";
			cin>>password; 
			load(name,password);
		}
		else if (op=="3"){//个人主页（需登录）
			if (user_name==""){
				cout<<"请先登录！"<<endl;
			} 
			else{
				cout<<"用户名："<<user_name<<endl;
				cout<<"抽取次数："<<user_cnt<<endl;
			}
		}
		else if (op=="4"){//保存（需登录）
			if (user_name==""){
				cout<<"请先登录！"<<endl;
			} 
			else{
				save(); 
			}
		}
		else if (op=="5"){//退出
			if (user_name!=""){
				save();
				cout<<"已自动保存！"<<endl; 
			}
			return 0;
		}
		else{
			cout<<"无效选择！"<<endl;
		}
		cout<<"按回车键继续" <<endl;
		cin.ignore(1000,'\n');
        cin.get(); 
	}
	return 0;
}
