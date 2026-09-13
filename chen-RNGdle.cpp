#include <bits/stdc++.h>
//#include <windows.h>
using namespace std;

/*
	原作：https://www.rngdle.com/

	v1.1 更新日志
	- 修复了登录时自动创建新账户的问题，现在可手动选择注册 
	- 退出时双重验证防误触 
	- 登录后主页不再显示“（需登录） ” 
	- 将协议原文放入函数中，可使用“跳至函数”快速查找（虽然对实际游玩没啥影响） 
	- 修改了保存文件后缀，请将“_chenRNGdle.txt”修改为“.chenRNGdle” 
	- 加入成就系统（22个） 
	- 支持临时登录 
	- 防止重复登录 
	- 丰富了主页内容 
	- 记录了EP最大值及最佳数字 
	
	v1.2 预告
	- 支持修改用户名，密码 
	- 更多成就
	- 彩色文本
	
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
int user_maxep=-1;//单次最高EP
int user_bestnum=-1;//最佳数字 
int user_lastfree=0;//上次免费抽奖时间 
const int ach_num=22;//成就数 
int f_ach=ach_num;//保存时的成就数 
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
	cout<<"用户名："<<(user_name==""?"未登录":user_name)<<"   金币数："<<user_coin; 
	cout<<endl;
	cout<<"> 1.抽数字（1000金币，每日免费一次）"<<(user_name==""?"（需登录）":"")<<endl;
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
	ach_info[ach_cnt]="6个数字"; //1
	ach_name[++ach_cnt]="五位数";
	ach_info[ach_cnt]="5个数字"; //2
	ach_name[++ach_cnt]="四位数";
	ach_info[ach_cnt]="4个数字"; //3
	ach_name[++ach_cnt]="三位数";
	ach_info[ach_cnt]="3个数字"; //4
	ach_name[++ach_cnt]="两位数";
	ach_info[ach_cnt]="2个数字"; //5
	ach_name[++ach_cnt]="一位数";
	ach_info[ach_cnt]="1个数字"; //6
	ach_name[++ach_cnt]="质数";
	ach_info[ach_cnt]="是个质数"; //7
	ach_name[++ach_cnt]="回文数";
	ach_info[ach_cnt]="是个回文数"; //8
	ach_name[++ach_cnt]="奇数";
	ach_info[ach_cnt]="是个奇数"; //9
	ach_name[++ach_cnt]="偶数";
	ach_info[ach_cnt]="是个偶数"; //10
	ach_name[++ach_cnt]="坡";
	ach_info[ach_cnt]="数字单调上升/下降"; //11
	ach_name[++ach_cnt]="山";
	ach_info[ach_cnt]="中间某一点比左右大"; //12
	ach_name[++ach_cnt]="谷";
	ach_info[ach_cnt]="中间某一点比左右小"; //13
	ach_name[++ach_cnt]="67";
	ach_info[ach_cnt]="包含67"; //14
	ach_name[++ach_cnt]="114514";
	ach_info[ach_cnt]="数字刚好为114514"; //15
	ach_name[++ach_cnt]="幸运7";
	ach_info[ach_cnt]="包含7"; //16
	ach_name[++ach_cnt]="666";
	ach_info[ach_cnt]="包含666"; //17
	ach_name[++ach_cnt]="平方数";
	ach_info[ach_cnt]="是个平方数"; //18
	ach_name[++ach_cnt]="洞";
	ach_info[ach_cnt]="包含0"; //19
	ach_name[++ach_cnt]="顺子";
	ach_info[ach_cnt]="数字连续"; //20
	ach_name[++ach_cnt]="凸";
	ach_info[ach_cnt]="中间只有一点比左右大"; //21
	ach_name[++ach_cnt]="凹";
	ach_info[ach_cnt]="中间只有一点比左右小"; //22
} 

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
		ep+=5000; 
		rate+=0.01;
		cout<<"[ "<<ach_name[3]<<" ] "<<ach_info[3]<<" +5,000EP"<<endl;
	}
	if (len==3){
		ach_got[4]++;
		ep+=10000; 
		rate+=0.05;
		cout<<"[ "<<ach_name[4]<<" ] "<<ach_info[4]<<" +10,000EP"<<endl;
	}
	if (len==2){
		ach_got[5]++;
		ep+=50000; 
		rate+=0.1;
		cout<<"[ "<<ach_name[5]<<" ] "<<ach_info[5]<<" +50,000EP"<<endl;
	}
	if (len==1){
		ach_got[6]++;
		ep+=100000; 
		rate+=0.5;
		cout<<"[ "<<ach_name[6]<<" ] "<<ach_info[6]<<" +100,000EP"<<endl;
	}
	if (isprime(num)){
		ach_got[7]++;
		ep+=1500;
		rate+=0.03;
		cout<<"[ "<<ach_name[7]<<" ] "<<ach_info[7]<<" +1,500EP"<<endl;
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
		ep+=200; 
		rate+=0.002;
		cout<<"[ "<<ach_name[9]<<" ] "<<ach_info[9]<<" +200EP"<<endl;
	} 
	if (num%2==0){
		ach_got[10]++;
		ep+=200; 
		rate+=0.002;
		cout<<"[ "<<ach_name[10]<<" ] "<<ach_info[10]<<" +200EP"<<endl;
	} 
	bool up=true,down=true;
	for (int i=0;i<len-1;i++){
		if (s_num[i]<s_num[i+1]){
			down=false;
		}
		if (s_num[i]>s_num[i+1]){
			up=false;
		} 
	}
	if (up||down){
		ach_got[11]++;
		ep+=7000; 
		rate+=0.05;
		cout<<"[ "<<ach_name[11]<<" ] "<<ach_info[11]<<" +7,000EP"<<endl;
	}
	if (len>=3){
		int high=0,low=0;
		for (int i=1;i<len-1;i++){
			if (s_num[i]>s_num[i-1]&&s_num[i]>s_num[i+1]){
				high++;
			}
			if (s_num[i]<s_num[i-1]&&s_num[i]<s_num[i+1]){
				low++;
			}
		}
		if (high==1){
			ach_got[21]++;
			ep+=5000; 
			rate+=0.01;
			cout<<"[ "<<ach_name[21]<<" ] "<<ach_info[21]<<" +5,000EP"<<endl;
		} 
		if (low==1){
			ach_got[22]++;
			ep+=5000; 
			rate+=0.01;
			cout<<"[ "<<ach_name[22]<<" ] "<<ach_info[22]<<" +5,000EP"<<endl;
		}
		if (high>1){
			ach_got[12]++;
			ep+=2000; 
			rate+=0.007;
			cout<<"[ "<<ach_name[12]<<" ] "<<ach_info[12]<<" +2,000EP"<<endl;
		}
		if (low>1){
			ach_got[13]++;
			ep+=2000; 
			rate+=0.007;
			cout<<"[ "<<ach_name[13]<<" ] "<<ach_info[13]<<" +2,000EP"<<endl;
		}
	}
	if (s_num.find("67")!=string::npos){
		ach_got[14]++;
		ep+=6767; 
		rate+=0.067;
		cout<<"[ "<<ach_name[14]<<" ] "<<ach_info[14]<<" +6,767EP"<<endl;
	}
	if (num==114514){
		ach_got[15]++;
		ep+=114514; 
		rate+=0.8;
		cout<<"[ "<<ach_name[15]<<" ] "<<ach_info[15]<<" +114,514EP"<<endl;
	}
	if (s_num.find("7")!=string::npos){
		ach_got[16]++;
		ep+=777; 
		rate+=0.003;
		cout<<"[ "<<ach_name[16]<<" ] "<<ach_info[16]<<" +777EP"<<endl;
	}
	if (s_num.find("666")!=string::npos){
		ach_got[17]++;
		ep+=6666; 
		rate+=0.066;
		cout<<"[ "<<ach_name[17]<<" ] "<<ach_info[17]<<" +6,666EP"<<endl;
	}
	int root=sqrt(num);
	if (root*root==num){
		ach_got[18]++;
		ep+=7000; 
		rate+=0.05;
		cout<<"[ "<<ach_name[18]<<" ] "<<ach_info[18]<<" +7,000EP"<<endl;
	}
	if (s_num.find("0")!=string::npos){
		ach_got[19]++;
		ep+=500; 
		rate+=0.003;
		cout<<"[ "<<ach_name[19]<<" ] "<<ach_info[19]<<" +500EP"<<endl;
	}
	up=down=true;
	for (int i=1;i<len;i++){
		if (s_num[i]-s_num[i-1]!=1){
			up=false;
		}
		if (s_num[i-1]-s_num[i]!=1){
			down=false;
		}
	}
	if (up||down){
		ach_got[20]++;
		ep+=10000; 
		rate+=0.3;
		cout<<"[ "<<ach_name[20]<<" ] "<<ach_info[20]<<" +10,000EP"<<endl;
	}
	cout<<endl;
	cout<<"基础总分 EP："<<ep<<"   倍率："<<rate<<endl;
	ep*=rate; 
	ep=floor(ep);
	cout<<"实际评分（下取整）："<<ep<<endl;
	cout<<"累计总评分 XP："<<user_xp<<"+"<<ep<<"="<<user_xp+ep<<endl;
	user_xp+=ep;
	cout<<"获得金币："<<floor(ep*0.3)<<endl;
	user_coin+=floor(ep*0.3);
	if (ep>user_maxep){
		cout<<"单次最高EP提升："<<(user_maxep!=-1?user_maxep:0)<<"->"<<ep<<endl;
		user_maxep=ep;
		user_bestnum=num; 
	} 
} 

//保存 
void save(){
	#ifdef debug
		string filename="iakioihashkiller_chenRNGdle_debug_mode_"+user_name+".chenRNGdle";
	#else
		string filename=user_name+".chenRNGdle";
	#endif
	ofstream file(filename.c_str());
	if (file.is_open()){
		file<<user_name<<endl;
		file<<user_password<<endl;
		file<<user_cnt<<endl;
		file<<user_xp<<endl;
		file<<ach_num<<endl; 
		for (int i=1;i<=ach_num;i++){
            file<<ach_got[i]<<" ";
        } 
        file<<endl;
        file<<user_maxep<<endl;
        file<<user_bestnum<<endl;
        file<<user_coin<<endl;
        file<<user_lastfree<<endl;
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
		string filename="iakioihashkiller_chenRNGdle_debug_mode_"+name+".chenRNGdle";
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
			file>>f_ach;
			for (int i=1;i<=f_ach;i++){
	            file>>ach_got[i];
	        } 
	        file>>user_maxep;
       		file>>user_bestnum;
       		file>>user_coin;
       		file>>user_lastfree;
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
	cout<<"成就初始化，请稍后..."<<endl; 
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
				if (time(0)-user_lastfree>=86400){
					clean();
					user_lastfree=time(0);
					cout<<"每日免费抽取"<<endl<<endl; 
					user_cnt++;
					int now_number=number();
					cout<<"当前数字："<<now_number<<endl;
					cout<<"抽数次数："<<user_cnt<<endl;
					cout<<endl; 
					checkach(now_number);
				} 
				else{
					if (user_coin>=1000){
						clean();
						cout<<"下一次免费时间："<<max(0,86400-(int)(time(0)-user_lastfree))<<"s"<<endl; 
						cout<<"金币-1000"<<endl<<endl;
						user_cnt++;
						user_coin-=1000;
						int now_number=number();
						cout<<"当前数字："<<now_number<<endl;
						cout<<"抽数次数："<<user_cnt<<endl;
						cout<<endl; 
						checkach(now_number);
					}
					else{
						cout<<"金币不足！"<<endl; 
					}
				}
			}
			if (user_cnt%5==0&&user_password!=""){
				save();
				cout<<"已自动保存"<<endl;
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
				int unlocked = 0;
			        for (int i=1;i<=ach_cnt;i++) {
			            if (ach_got[i]>0){
			            	unlocked++;
						}
			        }
				cout<<"用户名："<<user_name<<endl;
				cout<<"金币数："<<user_coin<<"   抽取次数："<<user_cnt<<endl;
				cout<<"下一次免费时间："<<max(0,86400-(int)(time(0)-user_lastfree))<<"s"<<endl; 
				cout<<"累计总评分 XP："<<user_xp<<endl; 
				cout<<"单次最高EP："<<(user_maxep!=-1?to_string(user_maxep):"暂无")<<"   最佳数字："<<(user_bestnum!=-1?to_string(user_bestnum):"暂无")<<endl<<endl;
				cout<<"成就进度："<<unlocked<<"/"<<ach_cnt<<endl;
				for (int i=1;i<=ach_cnt;i++) {
		            if (ach_got[i]==0){
		            	cout<<"[ ??? ] ??? x0"<<endl;
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
				cout<<"数 "<<num<<" 获得成就："<<endl;
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
