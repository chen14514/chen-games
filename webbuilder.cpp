#include <bits/stdc++.h>
//#include <windows.h>
using namespace std;

/*
	v0.1 更新日志
	- 基础框架，无实际功能 
	
	v0.2 预告
	- 完善内容 
	
	------ 
	
	系统：windows
	软件：dev-c++ 5.11 (-std=c++11)
	
	意见/bug反馈：Github issue/洛谷私信 
	
	此游戏已同步上传至仓库chen-games(MIT协议)
	可修改，可二创，需标注“原作者chen_14514(洛谷uid1760537)” 
	
	MIT协议原文见底（依协议要求，原文（英文版）不可删除） 
*/ 

//全局变量
string user_name="";
string user_password="";
string user_webadd="";
int user_money=0;
int user_weblv=0; 

const int ach_num=0; 
int f_ach=ach_num;//保存时的成就数 
int ach_cnt=0;
string ach_name[ach_num+1]={};//成就名 
string ach_info[ach_num+1]={};//成就介绍 
bool ach_got[ach_num+1]={};//成就获得

//清屏 
void clean(){
	system("cls");
} 

//菜单 
void menu(){
	clean();
	#ifdef iakioihashkiller_webbuilder_debug_mode
		cout<<"# 调试模式"<<endl<<endl; 
	#endif
	cout<<"============ web builder ============"<<endl;
	cout<<endl;
	cout<<"用户名："<<(user_name==""?"未登录":user_name)<<"   金钱数："<<user_money<<endl; 
	cout<<endl;
	cout<<"> 1.网页数据"<<(user_name==""?"（需登录）":"")<<endl;
	cout<<"> 2.登录/注册"<<endl;
	cout<<"> 3.个人主页"<<(user_name==""?"（需登录）":"")<<endl;
	cout<<"> 4.保存"<<(user_name==""?"（需登录）":"")<<endl; 
	cout<<"> 5.临时登录（数据不保存，无需注册）"<<endl; 
	cout<<"> 6.退出"<<endl;
	cout<<endl;
	cout<<"数字选择（1~6）："; 
}

void web(){
	clean();
	cout<<"============ 网页信息 ============"<<endl;
	cout<<endl;
	cout<<"网址："<<user_webadd<<endl; 
	cout<<"等级："<<user_weblv<<endl;
	cout<<endl;
	cout<<"=================================="<<endl;
	cout<<endl;
	cout<<"> 1.网页优化"<<endl;
	cout<<"> 2.服务器购买"<<endl;
	cout<<"> 3.技能升级"<<endl;
	cout<<"> 4.退出"<<endl;
	cout<<endl;
	cout<<"数字选择（1~4）："; 
} 

//保存 
void save(){
	#ifdef iakioihashkiller_webbuilder_debug_mode
		string filename="iakioihashkiller_webbuilder_debug_mode_"+user_name+".webbuilder";
	#else
		string filename=user_name+".webbuilder";
	#endif
	ofstream file(filename.c_str());
	if (file.is_open()){
		file<<user_name<<endl;
		file<<user_password<<endl;
		file<<user_money<<endl;
		file<<user_webadd<<endl;
		file<<user_weblv<<endl;
		file.close();
		cout<<"成功保存到："<<filename<<endl;
	}
	else{
		cout<<"保存失败，请检查存档文件"<<endl;
	}
}

//加载 
void load(string name,string password){
	#ifdef iakioihashkiller_webbuilder_debug_mode
		string filename="iakioihashkiller_webbuilder_debug_mode_"+name+".webbuilder";
	#else
		string filename=name+".webbuilder";
	#endif
	ifstream file(filename.c_str());
	if (file.is_open()){
		string load_name,load_password;
		file>>load_name;
		file>>load_password;
		if (password==load_password){
			user_name=load_name;
			user_password=load_password;
			file>>user_money;
			file>>user_webadd;
			file>>user_weblv;
			file.close();
			cout<<"成功加载："<<filename<<endl;
		}
		else{
			file.close();
			cout<<"用户名或密码错误！"<<endl;
		}
	}
	else{
		cout<<"是否注册？（Y/N）";
		string zc;
		cin>>zc;
		if (zc=="Y"||zc=="y"){
			user_name=name;
			user_password=password;
			cout<<endl<<"已创建："<<filename<<endl;
			save();
		}
		else{
			cout<<endl<<"已取消注册"<<endl; 
		}
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
		if (op=="1"){//网页数据（需登录）
			if (user_name==""){
				cout<<"请先登录！"<<endl;
			} 
			else{
				web(); 
			}
		}
		else if (op=="2"){//登录/注册
			if (user_name!="") {
				cout<<"已登录！"<<endl;
			}
			else{
				string name,password;
				cout<<"输入用户名：";
				cin>>name;
				cout<<"输入密码：";
				cin>>password; 
				load(name,password);
			}
		}
		else if (op=="3"){//个人主页（需登录）
			if (user_name==""){
				cout<<"请先登录！"<<endl;
			} 
			else{
				clean();
				cout<<"用户名："<<user_name<<endl;
			}
		}
		else if (op=="4"){//保存（需登录）
			if (user_password==""){
				cout<<"请先登录！"<<endl;
			} 
			else{
				save(); 
			}
		}
		else if (op=="5"){//临时登录 
			if (user_name!=""){
				cout<<"已登录！"<<endl; 
			}
			else{
				cout<<"确定临时登录？（Y/N）";
				string lsdl;
				cin>>lsdl;
				if (lsdl=="Y"||lsdl=="y"){
					user_name="访客_"+to_string(time(0));
					user_password="";
					user_money=100;
					cout<<endl<<"临时登录成功！"<<endl; 
				}
				else{
					cout<<endl<<"已取消！"<<endl;
				}
			}
			
		}
		else if (op=="6"){//退出
			cout<<"确定退出？（Y/N）";
			string tc;
			cin>>tc;
			if (tc=="Y"||tc=="y"){
				if (user_password!=""){
					cout<<endl<<"已自动保存！"<<endl; 
					save();
				}
				return 0;
			}
			else{
				cout<<"已取消！"<<endl;
			}
		}
		else{
			cout<<"无效选择！"<<endl;
		}
		#ifdef iakioihashkiller_webbuilder_debug_mode
			if (op=="/-save"){
				save();
				cout<<"已强制保存！"<<endl;
			}
			else if (op=="/-money"){
				int money;
				cin>>money;
				user_money=money;
				cout<<"金钱已修改："<<user_money<<endl; 
			}
			else if (op=="/-return"){
				cout<<"已强制退出！"<<endl;
				return 0;
			}
		#endif
		cout<<endl; 
		cout<<"按回车键继续..." <<endl;
		cin.ignore(1000,'\n');
        cin.get(); 
	}
	return 0;
}

void MIT(){
	/*
	MIT License
	
	Copyright (c) 2026 chen_14514
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
	
	翻译（deepseek）
	MIT 许可协议
	
	版权所有 (c) 2026 chen_14514
	
	特此授予任何人免费获得本软件及相关文档文件（“软件”）副本的许可，允许其无限制地
	处理本软件，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售本软件
	副本的权利，并允许本软件的接收者享有上述权利，但须遵守以下条件：
	
	上述版权声明和本许可声明应包含在本软件的所有副本或实质性部分中。
	
	本软件按“原样”提供，不提供任何形式的明示或暗示保证，包括但不限于适销性、特定用途
	适用性和非侵权性的保证。在任何情况下，作者或版权持有人均不对任何索赔、损害或其他责
	任负责，无论是在合同诉讼、侵权诉讼或其他诉讼中，由本软件或本软件的使用或其他交易引
	起的、由本软件引起的或与本软件有关的。 
	*/
} 
