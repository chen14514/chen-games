#include <bits/stdc++.h>
//#include <windows.h>
using namespace std;

#define iakioihashkiller_webbuilder_debug_mode

/*
	v0.4 更新日志
	- 可进入下一天，收益计算 
	
	v0.5 预告
	- 完善内容 
	
	------ 
	
	系统：windows
	软件：dev-c++ 5.11 (-std=c++11)
	
	意见/bug反馈：Github issue/洛谷私信 
	
	此游戏已同步上传至仓库chen-games(MIT协议)
	
	Copyright (c) 2026 chen_14514 
*/ 

struct player{
	string name="";
	string password="";
	string webadd="";
	string webfwq="";
	long long money=0;
	int weblv=0; 
	int webh=0;
	int webg=0;
	int lastday=0;
	int days=0;
	int ll=0;
	int maxll=0;
	int sr=0;
}; player p;

bool returnflag=false;

//成就系统变量暂存 
const int ach_num=0; 
int f_ach=ach_num;//保存时的成就数 
int ach_cnt=0;
string ach_name[ach_num+1]={};//成就名 
string ach_info[ach_num+1]={};//成就介绍 
bool ach_got[ach_num+1]={};//成就获得

void clean(){
	system("cls");
} 

int high_rand(){
	int high=rand()%1000;
	int low=rand()%1000;
	return high*1000+low;
} 

void menu(){
	clean();
	#ifdef iakioihashkiller_webbuilder_debug_mode
		cout<<"# 调试模式"<<endl; 
	#endif
	cout<<"# 测试版"<<endl; 
	cout<<endl;
	cout<<"============ web builder ============"<<endl;
	cout<<endl;
	cout<<"用户名："<<(p.name==""?"未登录":p.name)<<"   金钱：￥"<<p.money/100<<"."<<p.money/10%10<<p.money%10<<endl; 
	cout<<endl;
	cout<<"> 1.网页数据"<<(p.name==""?"（需登录）":"")<<endl;
	cout<<"> 2.登录/注册"<<endl;
	cout<<"> 3.个人主页"<<(p.name==""?"（需登录）":"")<<endl;
	cout<<"> 4.保存"<<(p.name==""?"（需登录）":"")<<endl; 
	cout<<"> 5.临时登录（数据不保存，无需注册）"<<endl; 
	cout<<"> 6.退出"<<endl;
	cout<<endl;
	cout<<"数字选择（1~6）："; 
	
}

void web_yh(){
	while (true){
		clean();
		#ifdef iakioihashkiller_webbuilder_debug_mode
			cout<<"# 调试模式"<<endl; 
		#endif
		cout<<"# 测试版"<<endl; 
		cout<<endl;
		cout<<"============ 网页优化 ============"<<endl;
		cout<<endl;
		cout<<"余额："<<p.money/100<<"."<<p.money/10%10<<p.money%10<<endl;
		cout<<"流量："<<p.ll<<endl;
		cout<<"配置："<<p.webfwq<<endl; 
		cout<<endl;
		cout<<"> 1.网站升级（￥"<<100*(p.weblv+1)<<"，等级+1）"<<endl;
		cout<<"> 2.占位"<<endl;
		cout<<"> 3.占位"<<endl;
		cout<<"> 4.占位"<<endl;
		cout<<"> 5.占位"<<endl;
		cout<<"> 6.返回"<<endl;
		cout<<endl;
		cout<<"数字选择（1~6）：";
		string op;
		cin>>op;
		cout<<endl;
		if (op=="1"){
			if (p.money>=10000*(p.weblv+1)){
				p.money-=10000*(p.weblv+1);
				p.weblv++;
				cout<<"升级成功！当前等级："<<p.weblv<<endl;
			}
			else{
				cout<<"余额不足"<<endl; 
			}
		}
		else if (op=="2"){
			cout<<"不可选择"<<endl;
		} 
		else if (op=="3"){
			cout<<"不可选择"<<endl;
		}
		else if (op=="4"){
			cout<<"不可选择"<<endl;
		}
		else if (op=="5"){
			cout<<"不可选择"<<endl;
		}
		else if (op=="6"){
			return;
		}
		else{
			cout<<"无效选择！"<<endl;
		}
		cout<<endl; 
		cout<<"按回车键继续..." <<endl;
		cin.ignore(1000,'\n');
        cin.get(); 
	}
	
} 

void web_fwq(){
	clean();
	#ifdef iakioihashkiller_webbuilder_debug_mode
		cout<<"# 调试模式"<<endl; 
	#endif
	cout<<"# 测试版"<<endl; 
	cout<<endl;
	cout<<"============ 服务器购买 ============"<<endl;
	cout<<endl;
	cout<<"余额："<<p.money/100<<"."<<p.money/10%10<<p.money%10<<endl;
	cout<<endl;
	cout<<"> 1.[ 免费 ][ 1核1G ] 旧电脑（流量上限 50）"<<endl;
	cout<<"> 2.[ 缺货 ][ ￥50/月 ][ 1核2G ] 小主机（流量上限 200）"<<endl;
	cout<<"> 3.[ 缺货 ][ ￥100/月 ][ 2核2G ] 新手小服务器（流量上限 450）"<<endl;
	cout<<"> 4.[ 缺货 ][ ￥200/月 ][ 2核4G ] 入门小服务器（流量上限 1,000）"<<endl;
	cout<<"> 5.[ 缺货 ][ ￥500/月 ][ 4核8G ] 标准服务器（流量上限 3,500）"<<endl;
	cout<<"> 6.[ 缺货 ][ ￥1000/月 ][ 4核12G ] 进阶服务器（流量上限 9,000）"<<endl;
	cout<<"> 7.[ 缺货 ][ ￥2000/月 ][ 4核16G ] 高端服务器（流量上限 20,000）"<<endl;
	cout<<"> 8.[ 缺货 ][ ￥5000/月 ][ 8核32G ] 企业级服务器（流量上限 7,5000）"<<endl;
	cout<<"> 9.[ 缺货 ][ ￥15000/月 ][ 16核64G ] 独立服务器（流量上限 250,000）"<<endl;
	cout<<"> 10.[ 缺货 ][ ￥50000/月 ][ 64核256G ] 全球多节点服务器（流量上限 1,000,000）"<<endl;
	cout<<"> 11.返回"<<endl;
	cout<<endl;
	cout<<"数字选择（1~11）：";
	string op;
	cin>>op;
	cout<<endl;
	if (op=="1"){
		p.webfwq="1核1G 旧电脑";
		p.webh=1;
		p.webg=1; 
		p.maxll=50;
		cout<<"获得 "<<p.webfwq<<" 成功！"<<endl; 
	}
	else if (op=="2"){
		cout<<"服务器缺货"<<endl;
	} 
	else if (op=="3"){
		cout<<"服务器缺货"<<endl;
	}
	else if (op=="4"){
		cout<<"服务器缺货"<<endl;
	}
	else if (op=="5"){
		cout<<"服务器缺货"<<endl;
	}
	else if (op=="6"){
		cout<<"服务器缺货"<<endl;
	}
	else if (op=="7"){
		cout<<"服务器缺货"<<endl;
	}
	else if (op=="8"){
		cout<<"服务器缺货"<<endl;
	}
	else if (op=="9"){
		cout<<"服务器缺货"<<endl;
	}
	else if (op=="10"){
		cout<<"服务器缺货"<<endl;
	}
	else if (op=="11"){
		return;
	}
	else{
		cout<<"无效选择！"<<endl;
	}
}

void web_jn(){
	while (true){
		clean();
		#ifdef iakioihashkiller_webbuilder_debug_mode
			cout<<"# 调试模式"<<endl; 
		#endif
		cout<<"# 测试版"<<endl; 
		cout<<endl;
		cout<<"============ 技能升级 ============"<<endl;
		cout<<endl;
		cout<<"余额：￥"<<p.money/100<<"."<<p.money/10%10<<p.money%10<<endl;
		cout<<endl;
		cout<<"> 1.[ 幸运 ] 幸运值+0.1"<<endl;
		cout<<"> 2.[ 流量 ] 流量 +1%"<<endl;
		cout<<"> 3.[ 收益 ] 收益 +1%"<<endl;
		cout<<"> 4.返回"<<endl;
		cout<<endl;
		cout<<"数字选择（1~4）：";
		string op;
		cin>>op;
		cout<<endl;
		if (op=="1"){
			cout<<"不可升级"<<endl;
		}
		else if (op=="2"){
			cout<<"不可升级"<<endl;
		}
		else if (op=="3"){
			cout<<"不可升级"<<endl;
		}
		else if (op=="4"){
			return;
		}
		else{
			cout<<"无效选择！"<<endl;
		}
		cout<<endl; 
		cout<<"按回车键继续..." <<endl;
		cin.ignore(1000,'\n');
        cin.get(); 
	}
}

void web_ym(){
	clean();
	#ifdef iakioihashkiller_webbuilder_debug_mode
		cout<<"# 调试模式"<<endl; 
	#endif
	cout<<"# 测试版"<<endl; 
	cout<<endl;
	cout<<"============ 域名购买 ============"<<endl;
	cout<<endl;
	cout<<"余额：￥"<<p.money/100<<"."<<p.money/10%10<<p.money%10<<endl;
	cout<<endl;
	cout<<"> 1.[ 免费 ] IP地址：111.111.111.111"<<endl;
	cout<<"> 2.[ 缺货 ] ___.cc"<<endl;
	cout<<"> 3.[ 缺货 ] ___.com"<<endl;
	cout<<"> 4.[ 缺货 ] ___.cn"<<endl;
	cout<<"> 5.[ 缺货 ] ___.io"<<endl;
	cout<<"> 6.[ 缺货 ] ___.org"<<endl;
	cout<<"> 7.[ 缺货 ] ___.xyz"<<endl;
	cout<<"> 8.[ 缺货 ] ___.top"<<endl;
	cout<<"> 9.[ 缺货 ] ___.ai"<<endl;
	cout<<"> 10.[ 缺货 ] ___.__"<<endl;
	cout<<"> 11.返回"<<endl;
	cout<<endl;
	cout<<"数字选择（1~11）：";
	string op;
	cin>>op;
	cout<<endl;
	if (op=="1"){
		p.webadd="111.111.111.111";
		cout<<"获得 "<<p.webadd<<" 成功！"<<endl; 
	}
	else if (op=="2"){
		cout<<"域名缺货"<<endl;
	}
	else if (op=="3"){
		cout<<"域名缺货"<<endl;
	}
	else if (op=="4"){
		cout<<"域名缺货"<<endl;
	}
	else if (op=="5"){
		cout<<"域名缺货"<<endl;
	}
	else if (op=="6"){
		cout<<"域名缺货"<<endl;
	}
	else if (op=="7"){
		cout<<"域名缺货"<<endl;
	}
	else if (op=="8"){
		cout<<"域名缺货"<<endl;
	}
	else if (op=="9"){
		cout<<"域名缺货"<<endl;
	}
	else if (op=="10"){
		cout<<"域名缺货"<<endl;
	}
	else if (op=="11"){
		return;
	}
	else{
		cout<<"无效选择！"<<endl;
	}
}

void nextday(){
	if (p.webfwq==""||p.webadd==""){
		cout<<"暂无域名 / 服务器，请先购买"<<endl;
	} 
	else{
		if (p.days==0){
			p.ll=0;
			p.sr=0;
		}
		else{
			p.ll=(p.weblv*10+p.webh*5+p.webg*5)*(50+high_rand()%100)/100; 
			p.sr=p.ll;
			p.money+=p.sr;
		}
		p.days++;
		p.lastday=time(0);
		cout<<"进入下一天，已运营 "<<p.days<<" 天"<<endl;
	}
}
 
void user_page(){
	clean();
	#ifdef iakioihashkiller_webbuilder_debug_mode
		cout<<"# 调试模式"<<endl; 
	#endif
	cout<<"# 测试版"<<endl; 
	cout<<endl;
	cout<<"============ 个人主页 ============"<<endl;
	cout<<endl;
	cout<<"用户名："<<p.name<<endl;
	cout<<"金钱：￥"<<p.money/100<<"."<<p.money/10%10<<p.money%10<<endl;
	cout<<"网页域名："<<p.webadd<<endl;
	cout<<"服务器："<<p.webfwq<<endl;
	cout<<"网站等级："<<p.weblv<<endl;
	cout<<"运营天数："<<p.days<<endl;
} 

void save(){
	#ifdef iakioihashkiller_webbuilder_debug_mode
		string filename="debug_"+p.name+".webbuilder";
	#else
		string filename=p.name+".webbuilder";
	#endif
	ofstream file(filename.c_str());
	if (file.is_open()){
		file<<p.name<<endl;
		file<<p.password<<endl;
		file<<p.money<<endl;
		file<<p.webadd<<endl;
		file<<p.weblv<<endl;
		file<<p.webfwq<<endl;
		file<<p.webh<<endl;
		file<<p.webg<<endl; 
		file<<p.days<<endl;
		file<<p.lastday<<endl;
		file<<p.maxll<<endl;
		file<<p.ll<<endl;
		file<<p.sr<<endl;
		file.close();
		cout<<"成功保存到："<<filename<<endl;
	}
	else{
		cout<<"保存失败，请检查存档文件"<<endl;
	}
}

void load(string name,string password){
	#ifdef iakioihashkiller_webbuilder_debug_mode
		string filename="debug_"+name+".webbuilder";
	#else
		string filename=name+".webbuilder";
	#endif
	ifstream file(filename.c_str());
	if (file.is_open()){
		string load_name,load_password;
		file>>load_name;
		file>>load_password;
		if (password==load_password){
			p.name=load_name;
			p.password=load_password;
			file>>p.money;
			file>>p.webadd;
			file>>p.weblv;
			file>>p.webfwq;
			file>>p.webh;
			file>>p.webg;
			file>>p.days;
			file>>p.lastday;
			file>>p.maxll;
			file>>p.ll;
			file>>p.sr;
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
			p.name=name;
			p.password=password;
			p.money=5000; 
			cout<<endl<<"已创建："<<filename<<endl;
			save();
		}
		else{
			cout<<endl<<"已取消注册"<<endl; 
		}
	}
}

void webbuilder(){
	if (p.name=="chen_14514"){
		ifstream file("admin_password.webbuilder");
		if (file.is_open()){
			string password;
			file>>password;
			file.close();
			if (p.password==password){
				while (true){
					clean();
					cout<<"# 调试模式"<<endl; 
					cout<<"# 测试版"<<endl; 
					cout<<endl;
					cout<<"======== web builder 后台 ========"<<endl;
					cout<<endl;
					cout<<"用户名："<<p.name<<endl; 
					cout<<"余额：￥"<<p.money/100<<"."<<p.money/10%10<<p.money%10<<endl;
					cout<<"运营天数："<<p.days<<endl;
					cout<<"昨日收入：￥"<<p.sr/100<<"."<<p.sr/10%10<<p.sr%10<<endl;
					cout<<"昨日流量："<<p.ll<<endl; 
					cout<<endl;
					cout<<"=================================="<<endl;
					cout<<endl;
					cout<<"> ";
					string op;
					cin>>op;
					cout<<endl;
					if (op=="/-back"){
						return; 
					}
					else if (op=="/-save"){
						save();
						cout<<"已强制保存！"<<endl;
					}
					else if (op=="/-money"){
						long long money;
						cin>>money;
						p.money=money*100;
						cout<<"金钱已修改：￥"<<p.money/100<<"."<<p.money/10%10<<p.money%10<<endl; 
					}
					else if (op=="/-return"){
						returnflag=true;
						save();
						return;
					}
					else if (op=="/-nextday"){
						nextday();
						cout<<"已强制下一天！"<<endl;
					}
					else if (op=="/-weblv"){
						cin>>p.weblv;
						cout<<"网站等级已修改："<<p.weblv;
					}
					else{
						cout<<"无效选择！"<<endl;
					}
					cout<<endl; 
					cout<<"按回车键继续..." <<endl;
					cin.ignore(1000,'\n');
			        cin.get(); 
				}
			}
		}
	}
	cout<<"无权限！"<<endl;
	return;
}

void web(){
	while (true){
		clean();
		#ifdef iakioihashkiller_webbuilder_debug_mode
			cout<<"# 调试模式"<<endl; 
		#endif
		cout<<"# 测试版"<<endl; 
		cout<<endl;
		cout<<"============ 网页信息 ============"<<endl;
		cout<<endl;
		cout<<"域名："<<p.webadd<<endl; 
		cout<<"服务器："<<p.webfwq<<endl;
		cout<<"最大流量："<<p.maxll<<endl;
		cout<<"等级："<<p.weblv<<endl;
		cout<<"运营天数："<<p.days<<endl;
		cout<<"昨日收入：￥"<<p.sr/100<<"."<<p.sr/10%10<<p.sr%10<<endl;
		cout<<"昨日流量："<<p.ll<<endl; 
		cout<<endl;
		cout<<"=================================="<<endl;
		cout<<endl;
		cout<<"> 1.网页优化"<<endl;
		cout<<"> 2.服务器购买"<<endl;
		cout<<"> 3.技能升级"<<endl;
		cout<<"> 4.域名购买"<<endl;
		cout<<"> 5.下一天（结算）"<<endl; 
		cout<<"> 6.返回"<<endl;
		cout<<endl;
		cout<<"数字选择（1~6）：";
		string op;
		cin>>op;
		cout<<endl;
		if (op=="1"){//网页优化 
			web_yh();
		}
		else if (op=="2"){//服务器购买 
			web_fwq();
		}
		else if (op=="3"){//技能升级 
			web_jn();
		}
		else if (op=="4"){//域名购买 
			web_ym();
		}
		else if (op=="5"){//下一天 
			if (time(0)-p.lastday<60){
				cout<<"还需 "<<60-(time(0)-p.lastday)<<" 秒"<<endl; 
			}
			else{
				nextday(); 
			}
		}
		else if (op=="6"){//返回
			return;
		}
		#ifdef iakioihashkiller_webbuilder_debug_mode
		else if (op=="/-inwebbuilder"){
			webbuilder();
		}
		#endif
		else{
			cout<<"无效选择！"<<endl;
		}
		cout<<endl; 
		cout<<"按回车键继续..." <<endl;
		cin.ignore(1000,'\n');
        cin.get(); 
	}
}

int main()
{
	system("title webbuilder");
	srand((unsigned)time(0));
	while (true){
		if (returnflag){
			return 0;
		}
		menu();
		string op;
		cin>>op;
		cout<<endl;
		if (op=="1"){//网页数据（需登录）
			if (p.name==""){
				cout<<"请先登录！"<<endl;
			} 
			else{
				web();
			}
		}
		else if (op=="2"){//登录/注册
			if (p.name!="") {
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
			if (p.name==""){
				cout<<"请先登录！"<<endl;
			} 
			else{
				clean();
				user_page();
			}
		}
		else if (op=="4"){//保存（需登录）
			if (p.password==""){
				cout<<"请先登录！"<<endl;
			} 
			else{
				save(); 
			}
		}
		else if (op=="5"){//临时登录 
			if (p.name!=""){
				cout<<"已登录！"<<endl; 
			}
			else{
				cout<<"确定临时登录？（Y/N）";
				string lsdl;
				cin>>lsdl;
				if (lsdl=="Y"||lsdl=="y"){
					p.name="访客_"+to_string(time(0));//报错加 -std=c++11 
					p.password="";
					p.money=5000; 
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
				if (p.password!=""){
					cout<<endl<<"已自动保存！"<<endl; 
					save();
				}
				return 0;
			}
			else{
				cout<<"已取消！"<<endl;
			}
		}
		#ifdef iakioihashkiller_webbuilder_debug_mode
		else if (op=="/-inwebbuilder"){
			webbuilder();
		}
		#endif
		else{
			cout<<"无效选择！"<<endl;
		}
		cout<<endl; 
		cout<<"按回车键继续..." <<endl;
		cin.ignore(1000,'\n');
        cin.get(); 
	}
	return 0;
}

void MIT(){
	/*
	依协议要求，原文（英文版）不可删除
	
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
