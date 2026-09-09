#include <bits/stdc++.h>
//#include <windows.h>
using namespace std;

#define debug 

/*
	原作：https://www.rngdle.com/

	v1.1 更新日志
	- 修复了登录时自动创建新账户的问题，现在可手动选择注册 
	- 退出时双重验证防误触 
	- 登录后主页不再显示“（需登录） ” 
	- 将协议原文放入函数中，可使用“跳至函数”快速查找（虽然对实际游玩没啥影响） 
	- 修改了保存文件后缀，请将“_chenRNGdle.txt”修改为“.chenRNGdle” 
	- 加入成就系统（20个） 
	- 支持临时登录 
	- 防止重复登录 
	- 丰富了主页内容 
	
	v1.2 预告
	- 支持修改用户名，密码 
	- 更多成就
	- 彩色文本
	
	注：暂时只能判定10个成就
	
	[ 六位数 ] 6个数字
	[ 五位数 ] 5个数字
	[ 四位数 ] 4个数字
	[ 三位数 ] 3个数字
	[ 两位数 ] 2个数字
	[ 一位数 ] 1个数字
	[ 质数 ] 是个质数
	[ 回文数 ] 是个回文数
	[ 奇数 ] 是个奇数
	[ 偶数 ] 是个偶数
	
	------ 
	
	系统：windows
	软件：dev-c++ 5.11 (c++11,-std=c++11)
	
	意见/bug反馈：Github issue/洛谷私信 
	
	此游戏已同步上传至仓库chen-games(MIT协议)
	可修改，可二创，需标注“原作者chen_14514(洛谷uid1760537)” 
	
	MIT协议原文见底（依协议要求，原文（英文版）不可删除） 
*/ 

//全局变量
string user_name="";
string user_password="";
int user_xp=0;//总经验 
int user_cnt=0;//抽奖计数
int user_coin=0;//金币数 
const int ach_num=20;//成就数 
int ach_cnt=0;
string ach_name[ach_num+1]={};//成就名 
string ach_info[ach_num+1]={};//成就介绍 
int ach_got[ach_num+1]={};//成就获得次数 

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
	#ifdef debug
		cout<<"# 调试模式"<<endl<<endl; 
	#endif
	cout<<"============ chen RNGdle ============"<<endl;
	cout<<endl;
	cout<<"当前用户："<<(user_name==""?"未登录":user_name)<<endl; 
	cout<<endl;
	cout<<"> 1.抽数字"<<(user_name==""?"（需登录）":"")<<endl;
	cout<<"> 2.登录/注册"<<endl;
	cout<<"> 3.个人主页"<<(user_name==""?"（需登录）":"")<<endl;
	cout<<"> 4.保存"<<(user_name==""?"（需登录）":"")<<endl; 
	cout<<"> 5.临时登录（数据不保存，无需注册）"<<endl; 
	cout<<"> 6.退出"<<endl;
	cout<<endl;
	cout<<"数字选择（1~6）："; 
}

//成就初始化
void initach(){
	ach_cnt=0;
	ach_name[++ach_cnt]="六位数";
	ach_info[ach_cnt]="6个数字"; 
	ach_name[++ach_cnt]="五位数";
	ach_info[ach_cnt]="5个数字"; 
	ach_name[++ach_cnt]="四位数";
	ach_info[ach_cnt]="4个数字"; 
	ach_name[++ach_cnt]="三位数";
	ach_info[ach_cnt]="3个数字"; 
	ach_name[++ach_cnt]="两位数";
	ach_info[ach_cnt]="2个数字"; 
	ach_name[++ach_cnt]="一位数";
	ach_info[ach_cnt]="1个数字"; 
	ach_name[++ach_cnt]="质数";
	ach_info[ach_cnt]="是个质数"; 
	ach_name[++ach_cnt]="回文数";
	ach_info[ach_cnt]="是个回文数"; 
	ach_name[++ach_cnt]="奇数";
	ach_info[ach_cnt]="是个奇数"; 
	ach_name[++ach_cnt]="偶数";
	ach_info[ach_cnt]="是个偶数"; 
	ach_name[++ach_cnt]="坡";
	ach_info[ach_cnt]="数字单调上升/下降"; 
	ach_name[++ach_cnt]="凸（山）";
	ach_info[ach_cnt]="最大数处于中间"; 
	ach_name[++ach_cnt]="凹（谷）";
	ach_info[ach_cnt]="最小数处于中间"; 
	ach_name[++ach_cnt]="67";
	ach_info[ach_cnt]="包含67"; 
	ach_name[++ach_cnt]="114514";
	ach_info[ach_cnt]="数字刚好为114514"; 
	ach_name[++ach_cnt]="幸运7";
	ach_info[ach_cnt]="包含7"; 
	ach_name[++ach_cnt]="666";
	ach_info[ach_cnt]="包含666"; 
	ach_name[++ach_cnt]="平方数";
	ach_info[ach_cnt]="是个平方数"; 
	ach_name[++ach_cnt]="洞";
	ach_info[ach_cnt]="包含0"; 
	ach_name[++ach_cnt]="顺子";
	ach_info[ach_cnt]="数字连续"; 
} 

//一堆成就触发条件
bool isprime(int n){
	if (n<2) return false;
	for (int i=2;i*i<=n;i++){
		if (n%i==0){
			return false; 
		}
	}
	return true;
} 

//成就触发
void checkach(int num){
	double rate=1.0;//积分翻倍倍率 
	double ep=0;//经验 
	string s_num=to_string(num);
	int len=s_num.size();
	if (len==6){
		ach_got[1]++;
		ep+=100; 
		rate+=0.001;
		cout<<"[ "<<ach_name[1]<<" ] "<<ach_info[1]<<" +100EP"<<endl;
	} 
	if (len==5){
		ach_got[2]++;
		ep+=1000; 
		rate+=0.005;
		cout<<"[ "<<ach_name[2]<<" ] "<<ach_info[2]<<" +1,000EP"<<endl;
	}
	if (len==4){
		ach_got[3]++;
		ep+=2000; 
		rate+=0.01;
		cout<<"[ "<<ach_name[3]<<" ] "<<ach_info[3]<<" +2,000EP"<<endl;
	}
	if (len==3){
		ach_got[4]++;
		ep+=5000; 
		rate+=0.05;
		cout<<"[ "<<ach_name[4]<<" ] "<<ach_info[4]<<" +5,000EP"<<endl;
	}
	if (len==2){
		ach_got[5]++;
		ep+=10000; 
		rate+=0.1;
		cout<<"[ "<<ach_name[5]<<" ] "<<ach_info[5]<<" +10,000EP"<<endl;
	}
	if (len==1){
		ach_got[6]++;
		ep+=50000; 
		rate+=0.5;
		cout<<"[ "<<ach_name[6]<<" ] "<<ach_info[6]<<" +50,000EP"<<endl;
	}
	if (isprime(num)){
		ach_got[7]++;
		ep+=3500;
		rate+=0.03;
		cout<<"[ "<<ach_name[7]<<" ] "<<ach_info[7]<<" +3,500EP"<<endl;
	}
	string rev=s_num;
	reverse(rev.begin(),rev.end());
	if (s_num==rev){
		ach_got[8]++;
		ep+=25000;
		rate+=0.3;
		cout<<"[ "<<ach_name[8]<<" ] "<<ach_info[8]<<" +25,000EP"<<endl;
	}
	if (num%2==1){
		ach_got[9]++;
		ep+=100; 
		rate+=0.001;
		cout<<"[ "<<ach_name[9]<<" ] "<<ach_info[9]<<" +100EP"<<endl;
	} 
	if (num%2==0){
		ach_got[10]++;
		ep+=100; 
		rate+=0.001;
		cout<<"[ "<<ach_name[10]<<" ] "<<ach_info[10]<<" +100EP"<<endl;
	} 
	
	cout<<endl;
	cout<<"基础总分 EP："<<ep<<"   倍率："<<rate<<endl;
	ep*=rate; 
	ep=floor(ep);
	cout<<"实际评分（下取整）："<<ep<<endl;
	cout<<"累计总评分 XP："<<user_xp<<"+"<<ep<<"="<<user_xp+ep<<endl;
	user_xp+=ep;
} 

//保存 
void save(){
	#ifdef debug
		string filename=user_name+".chenRNGdle.dev";
	#else
		string filename=user_name+".chenRNGdle";
	#endif
	ofstream file(filename.c_str());
	if (file.is_open()){
		file<<user_name<<endl;
		file<<user_password<<endl;
		file<<user_cnt<<endl;
		file<<user_xp<<endl;
		for (int i=1;i<=ach_cnt;i++){
            file<<ach_got[i]<<" ";
        } 
		file.close();
		cout<<"成功保存到："<<filename<<endl;
	}
	else{
		cout<<"保存失败，请检查存档文件"<<endl;
	}
}

//加载 
void load(string name,string password){
	#ifdef debug
		string filename=name+".chenRNGdle.dev";
	#else
		string filename=name+".chenRNGdle";
	#endif
	ifstream file(filename.c_str());
	if (file.is_open()){
		string load_name,load_password;
		file>>load_name;
		file>>load_password;
		if (password==load_password){
			user_name=load_name;
			user_password=load_password;
			file>>user_cnt;
			file>>user_xp; 
			for (int i=1;i<=ach_cnt;i++){
	            file>>ach_got[i];
	        } 
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
			user_cnt=0;
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
	initach();
	while (true){
		menu();
		string op;
		cin>>op;
		cout<<endl;
		if (op=="1"){//抽数字（需登录）
			if (user_name==""){
				cout<<"请先登录！"<<endl;
			} 
			else{
					user_cnt++;
					int now_number=number();
					cout<<"当前数字："<<now_number<<endl;
					cout<<"抽数次数："<<user_cnt<<endl;
					cout<<endl; 
					checkach(now_number);
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
				int unlocked = 0;
			        for (int i=1;i<=ach_cnt;i++) {
			            if (ach_got[i]>0){
			            	unlocked++;
						}
			        }
				cout<<"用户名："<<user_name<<endl;
				cout<<"金币数："<<user_coin<<endl; 
				cout<<"抽取次数："<<user_cnt<<endl;
				cout<<"累计总评分 XP："<<user_xp<<endl<<endl; 
				cout<<"成就进度："<<unlocked<<"/"<<ach_cnt<<endl;
				for (int i=1;i<=ach_cnt;i++) {
		            if (ach_got[i]==0){
		            	cout<<"[???] ??? x0"<<endl;
		        	}
					else{
						cout<<"[ "<<ach_name[i]<<" ] "<<ach_info[i]<<" x"<<ach_got[i]<<endl;
					}
		        } 
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
					user_cnt=0;
					user_coin=0;
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
		#ifdef debug
			if (op=="/-save"){// /-save
				save();
				cout<<"已强制保存！"<<endl;
			}
			else if (op=="/-coin"){// /-coin x
				int coin;
				cin>>coin;
				user_coin=coin;
				cout<<"金币已修改："<<user_coin<<endl; 
			}
			else if (op=="/-return"){// /-return
				cout<<"已强制退出！"<<endl;
				return 0;
			} 
			else if (op=="/-number"){// /-number x
				int num;
				cin>>num;
				cout<<"数："<<num<<endl;
				checkach(num); 
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
