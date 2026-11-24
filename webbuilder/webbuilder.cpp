#include <bits/stdc++.h>
//#include <windows.h>
using namespace std;

/*
	v1.0 更新日志
	- 添加域名过期时间 
	- 添加离线收益以及相关技能升级 
	
	v1.1 预告
	- 完善内容
	- 平衡性调整 
	
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
	long long money=0;//单位 分 
	int weblv=0; 
	int webh=0;//核 
	int webg=0;//G 
	int lastday=0;//上次结算时刻 
	int days=0;//运营天数 
	int ll=0;//流量 
	int maxll=0;
	int sr=0;//收入 
	int fwqdel=0;
	int adddel=0; 
	int lllv=0;//流量等级
	int srlv=0;//收入等级
	int lklv=0;//幸运等级 
	int leave=0;//离线时间 
	int lvtm=0;//离线时间等级 
	int lvsr=0;//离线收入等级 
}; player p;

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
		cout<<endl;
		cout<<"============ 网页优化 ============"<<endl;
		cout<<endl;
		cout<<"余额："<<p.money/100<<"."<<p.money/10%10<<p.money%10<<endl;
		cout<<"流量："<<p.ll<<endl;
		cout<<"配置："<<p.webfwq<<endl; 
		cout<<endl;
		cout<<"> 1.[ lv."<<p.weblv<<" ] 网站升级（￥"<<50*(p.weblv+1)<<"，等级+1）"<<endl;
		cout<<"> 2.[ lv."<<p.lklv<<" ] 幸运加成（￥"<<50*(p.lklv+1)<<"，+2%）"<<endl;
		cout<<"> 3.[ lv."<<p.lllv<<" ] 流量加成（￥"<<20*(p.lllv+1)<<"，+2%）"<<endl;
		cout<<"> 4.[ lv."<<p.srlv<<" ] 收益加成（￥"<<20*(p.srlv+1)<<"，+2%）"<<endl;
		cout<<"> 5.[ lv."<<p.lvtm<<" ] 离线时间加成（￥"<<50*(p.lvtm+1)<<"，+10min）"<<endl; 
		cout<<"> 6.[ lv."<<p.lvsr<<" ] 离线收益加成（￥"<<50*(p.lvsr+1)<<"，+1分）"<<endl;
		cout<<"> 7.返回"<<endl;
		cout<<endl;
		cout<<"数字选择（1~7）：";
		string op;
		cin>>op;
		cout<<endl;
		if (op=="1"){
			if (p.money>=5000*(p.weblv+1)){
				p.money-=5000*(p.weblv+1);
				p.weblv++;
				cout<<"升级成功！当前等级："<<p.weblv<<endl;
			}
			else{
				cout<<"余额不足"<<endl; 
			}
		}
		else if (op=="2"){
			if (p.money>=5000*(p.lklv+1)){
				p.money-=5000*(p.lklv+1);
				p.lklv++;
				cout<<"升级成功！当前等级："<<p.lklv<<endl;
			}
			else{
				cout<<"余额不足"<<endl;
			}
		} 
		else if (op=="3"){
			if (p.money>=2000*(p.lllv+1)){
				p.money-=2000*(p.lllv+1);
				p.lllv++;
				cout<<"升级成功！当前等级："<<p.lllv<<endl;
			}
			else{
				cout<<"余额不足"<<endl; 
			}
		}
		else if (op=="4"){
			if (p.money>=2000*(p.srlv+1)){
				p.money-=2000*(p.srlv+1);
				p.srlv++;
				cout<<"升级成功！当前等级："<<p.srlv<<endl;
			}
			else{
				cout<<"余额不足"<<endl; 
			}
		}
		else if (op=="5"){
			if (p.money>=5000*(p.lvtm+1)){
				p.money-=5000*(p.lvtm+1);
				p.lvtm++;
				cout<<"升级成功！当前等级："<<p.lvtm<<endl;
			}
			else{
				cout<<"余额不足"<<endl; 
			}
		}
		else if (op=="6"){
			if (p.money>=5000*(p.lvsr+1)){
				p.money-=5000*(p.lvsr+1);
				p.lvsr++;
				cout<<"升级成功！当前等级："<<p.lvsr<<endl;
			}
			else{
				cout<<"余额不足"<<endl; 
			}
		}
		else if (op=="7"){
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
	cout<<endl;
	cout<<"============ 服务器购买 ============"<<endl;
	cout<<endl;
	cout<<"当前服务器："<<p.webfwq<<endl;
	cout<<"还有 "<<p.fwqdel<<" 天过期"<<endl;
	cout<<"余额："<<p.money/100<<"."<<p.money/10%10<<p.money%10<<endl;
	cout<<endl;
	cout<<"> 1.[ ￥0/月 ][ 1核1G ] 旧电脑（流量上限 600）"<<endl;
	cout<<"> 2.[ ￥5/月 ][ 1核2G ] 小主机（流量上限 1,200）"<<endl;
	cout<<"> 3.[ ￥15/月 ][ 2核2G ] 新手小服务器（流量上限 1,500）"<<endl;
	cout<<"> 4.[ ￥30/月 ][ 2核4G ] 入门小服务器（流量上限 2,500）"<<endl;
	cout<<"> 5.[ ￥100/月 ][ 4核8G ] 标准服务器（流量上限 6,000）"<<endl;
	cout<<"> 6.[ ￥200/月 ][ 4核12G ] 进阶服务器（流量上限 9,000）"<<endl;
	cout<<"> 7.[ ￥300/月 ][ 4核16G ] 高端服务器（流量上限 15,000）"<<endl;
	cout<<"> 8.[ ￥1,200/月 ][ 8核32G ] 企业级服务器（流量上限 50,000）"<<endl;
	cout<<"> 9.[ ￥5,000/月 ][ 16核64G ] 独立服务器（流量上限 100,000）"<<endl;
	cout<<"> 10.[ ￥50,000/月 ][ 64核256G ] 全球多节点服务器（流量上限 700,000）"<<endl;
	cout<<"> 11.定制服务器"<<endl;
	cout<<"> 12.返回"<<endl;
	cout<<endl;
	cout<<"数字选择（1~12）：";
	string op;
	cin>>op;
	cout<<endl;
	if (op=="1"){
		p.webfwq="1核1G-旧电脑";
		p.webh=1;
		p.webg=1; 
		p.maxll=600;
		p.fwqdel=30;
		cout<<"获得 "<<p.webfwq<<" 成功！"<<endl; 
	}
	else if (op=="2"){
		if (p.money>=500){
			p.money-=500;
			p.webfwq="1核2G-小主机";
			p.webh=1;
			p.webg=2; 
			p.maxll=1200;
			p.fwqdel=30;
			cout<<"获得 "<<p.webfwq<<" 成功！"<<endl; 
		}
		else{
			cout<<"余额不足！"<<endl;
		}
	} 
	else if (op=="3"){
		if (p.money>=1500){
			p.money-=1500;
			p.webfwq="2核2G-新手小服务器";
			p.webh=2;
			p.webg=2; 
			p.maxll=1500;
			p.fwqdel=30;
			cout<<"获得 "<<p.webfwq<<" 成功！"<<endl; 
		}
		else{
			cout<<"余额不足！"<<endl;
		}
	}
	else if (op=="4"){
		if (p.money>=3000){
			p.money-=3000;
			p.webfwq="2核4G-入门小服务器";
			p.webh=2;
			p.webg=4; 
			p.maxll=2500;
			p.fwqdel=30;
			cout<<"获得 "<<p.webfwq<<" 成功！"<<endl; 
		}
		else{
			cout<<"余额不足！"<<endl;
		}
	}
	else if (op=="5"){
		if (p.money>=10000){
			p.money-=10000;
			p.webfwq="4核8G-标准服务器";
			p.webh=4;
			p.webg=8; 
			p.maxll=6000;
			p.fwqdel=30;
			cout<<"获得 "<<p.webfwq<<" 成功！"<<endl; 
		}
		else{
			cout<<"余额不足！"<<endl;
		}
	}
	else if (op=="6"){
		if (p.money>=20000){
			p.money-=20000;
			p.webfwq="4核12G-进阶服务器";
			p.webh=4;
			p.webg=12; 
			p.maxll=9000;
			p.fwqdel=30;
			cout<<"获得 "<<p.webfwq<<" 成功！"<<endl; 
		}
		else{
			cout<<"余额不足！"<<endl;
		}
	}
	else if (op=="7"){
		if (p.money>=30000){
			p.money-=30000;
			p.webfwq="4核16G-高端服务器";
			p.webh=4;
			p.webg=16; 
			p.maxll=15000;
			p.fwqdel=30;
			cout<<"获得 "<<p.webfwq<<" 成功！"<<endl; 
		}
		else{
			cout<<"余额不足！"<<endl;
		}
	}
	else if (op=="8"){
		if (p.money>=120000){
			p.money-=120000;
			p.webfwq="8核32G-企业级服务器";
			p.webh=8;
			p.webg=32; 
			p.maxll=50000;
			p.fwqdel=30;
			cout<<"获得 "<<p.webfwq<<" 成功！"<<endl; 
		}
		else{
			cout<<"余额不足！"<<endl;
		}
	}
	else if (op=="9"){
		if (p.money>=500000){
			p.money-=500000;
			p.webfwq="16核64G-独立服务器";
			p.webh=16;
			p.webg=64; 
			p.maxll=100000;
			p.fwqdel=30;
			cout<<"获得 "<<p.webfwq<<" 成功！"<<endl; 
		}
		else{
			cout<<"余额不足！"<<endl;
		}
	}
	else if (op=="10"){
		if (p.money>=5000000){
			p.money-=5000000;
			p.webfwq="64核256G-全球多节点服务器";
			p.webh=64;
			p.webg=256; 
			p.maxll=700000;
			p.fwqdel=30;
			cout<<"获得 "<<p.webfwq<<" 成功！"<<endl; 
		}
		else{
			cout<<"余额不足！"<<endl;
		}
	}
	else if (op=="11"){
		long long h,g;
		cout<<"输入服务器核，G（空格隔开）：";
		cin>>h>>g;
		if (h<1||h>256||g<1||g>1024){
		    cout<<"超出范围！核 1~256，G 1~1024"<<endl;
		    return;
		}
		long long price=(long long)h*h*200+(long long)g*g*100;
		if (p.money<price){
			cout<<"余额不足！需要￥"<<price/100.0<<endl;
			return;
		}
		cout<<"预计最大流量："<<h*h*100+g*500<<"，价钱："<<price/100.0<<"，确认支付？（Y/N）";
		string zf;
		cin>>zf;
		if (zf=="Y"||zf=="y"){
			p.money-=price;
			p.webfwq=to_string(h)+"核"+to_string(g)+"G-定制服务器";
			p.webh=h;
			p.webg=g;
			p.maxll=(long long)h*h*100+(long long)g*500;
			p.fwqdel=30;
			cout<<"获得 "<<p.webfwq<<" 成功！"<<endl;
		} 
		else{
			cout<<"已取消！"<<endl;
		}
	} 
	else if (op=="12"){
		return;
	}
	else{
		cout<<"无效选择！"<<endl;
	}
}

void web_ym(){
	clean();
	#ifdef iakioihashkiller_webbuilder_debug_mode
		cout<<"# 调试模式"<<endl; 
	#endif
	cout<<endl;
	cout<<"============ 域名购买 ============"<<endl;
	cout<<endl;
	cout<<"当前域名："<<p.webadd<<endl;
	cout<<"还有 "<<p.adddel<<" 天过期"<<endl; 
	cout<<"余额：￥"<<p.money/100<<"."<<p.money/10%10<<p.money%10<<endl;
	cout<<endl;
	cout<<"> 1.[ ￥0/月 ] IP地址：111.111.111.111"<<endl;
	cout<<"> 2.[ ￥5/月 ] ___.cc"<<endl;
	cout<<"> 3.[ ￥20/月 ] ___.com"<<endl;
	cout<<"> 4.[ ￥50/月 ] ___.cn"<<endl;
	cout<<"> 5.[ ￥100/月 ] ___.io"<<endl;
	cout<<"> 6.[ ￥250/月 ] ___.org"<<endl;
	cout<<"> 7.[ ￥500/月 ] ___.xyz"<<endl;
	cout<<"> 8.[ ￥750/月 ] ___.top"<<endl;
	cout<<"> 9.[ ￥1000/月 ] ___.ai"<<endl;
	cout<<"> 10.返回"<<endl;
	cout<<endl;
	cout<<"数字选择（1~10）：";
	string op;
	cin>>op;
	cout<<endl;
	if (op=="1"){
		p.webadd="111.111.111.111";
		p.adddel=30;
		cout<<"获得 "<<p.webadd<<" 成功！"<<endl; 
	}
	else if (op=="2"){
		if (p.money<500){
			cout<<"余额不足！"<<endl;
		}
		else{
			string ym;
			cout<<"输入域名："<<endl;
			cin>>ym; 
			p.webadd=ym+".cc";
			p.adddel=30;
			p.money-=500;
			cout<<"获得 "<<p.webadd<<" 成功！"<<endl;
		}
	}
	else if (op=="3"){
		if (p.money<2000){
			cout<<"余额不足！"<<endl;
		}
		else{
			string ym;
			cout<<"输入域名："<<endl;
			cin>>ym; 
			p.webadd=ym+".com";
			p.adddel=30;
			p.money-=2000;
			cout<<"获得 "<<p.webadd<<" 成功！"<<endl;
		}
	}
	else if (op=="4"){
		if (p.money<5000){
			cout<<"余额不足！"<<endl;
		}
		else{
			string ym;
			cout<<"输入域名："<<endl;
			cin>>ym; 
			p.webadd=ym+".cn";
			p.adddel=30;
			p.money-=5000;
			cout<<"获得 "<<p.webadd<<" 成功！"<<endl;
		}
	}
	else if (op=="5"){
		if (p.money<10000){
			cout<<"余额不足！"<<endl;
		}
		else{
			string ym;
			cout<<"输入域名："<<endl;
			cin>>ym; 
			p.webadd=ym+".io";
			p.adddel=30;
			p.money-=10000;
			cout<<"获得 "<<p.webadd<<" 成功！"<<endl;
		}
	}
	else if (op=="6"){
		if (p.money<25000){
			cout<<"余额不足！"<<endl;
		}
		else{
			string ym;
			cout<<"输入域名："<<endl;
			cin>>ym; 
			p.webadd=ym+".org";
			p.adddel=30;
			p.money-=25000;
			cout<<"获得 "<<p.webadd<<" 成功！"<<endl;
		}
	}
	else if (op=="7"){
		if (p.money<50000){
			cout<<"余额不足！"<<endl;
		}
		else{
			string ym;
			cout<<"输入域名："<<endl;
			cin>>ym; 
			p.webadd=ym+".xyz";
			p.adddel=30;
			p.money-=50000;
			cout<<"获得 "<<p.webadd<<" 成功！"<<endl;
		}
	}
	else if (op=="8"){
		if (p.money<75000){
			cout<<"余额不足！"<<endl;
		}
		else{
			string ym;
			cout<<"输入域名："<<endl;
			cin>>ym; 
			p.webadd=ym+".top";
			p.adddel=30;
			p.money-=75000;
			cout<<"获得 "<<p.webadd<<" 成功！"<<endl;
		}
	}
	else if (op=="9"){
		if (p.money<100000){
			cout<<"余额不足！"<<endl;
		}
		else{
			string ym;
			cout<<"输入域名："<<endl;
			cin>>ym; 
			p.webadd=ym+".ai";
			p.adddel=30;
			p.money-=100000;
			cout<<"获得 "<<p.webadd<<" 成功！"<<endl;
		}
	}
	else if (op=="10"){
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
	if (p.fwqdel<=0){
		cout<<"服务器已过期！"<<endl;
		p.webfwq+=(p.fwqdel==0?"[已过期]":""); 
		p.fwqdel=-1;
	} 
	if (p.adddel<=0){
		cout<<"域名已过期！"<<endl;
		p.webadd+=(p.adddel==0?"[已过期]":"");
		p.adddel=-1;
	}
	if (p.adddel>0&&p.fwqdel>0){
		if (p.days==0){
			p.ll=0;
			p.sr=0;
		}
		else{
			p.ll=((p.weblv*100+p.webh*50+p.webg*200)*(50+high_rand()%100+p.lklv*2)/100)*(1+p.lllv*0.02); 
			if (p.ll<=p.maxll){
				p.sr=p.ll*(1+p.srlv*0.02);
				p.money+=p.sr;
			}
			else{
				p.sr=(p.maxll*0.5+(p.ll-p.maxll)*0.01)*(1+p.srlv*0.02);
				p.money+=p.sr;
				cout<<"流量超限，服务器过载 "<<(p.ll-p.maxll)*100/p.maxll<<"% ！"<<endl;
			}
		}
		p.days++;
		p.fwqdel--;
		p.adddel--; 
		p.lastday=time(0);
		cout<<"进入下一天，已运营 "<<p.days<<" 天（服务器还有 "<<p.fwqdel<<" 天过期，域名还有 "<<p.adddel<<" 天过期）"<<endl;
	}
	
}
 
void user_page(){
	clean();
	#ifdef iakioihashkiller_webbuilder_debug_mode
		cout<<"# 调试模式"<<endl; 
	#endif
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
		file<<p.name<<endl<<p.password<<endl;
		file<<p.money<<endl<<p.webadd<<endl;
		file<<p.weblv<<endl<<p.webfwq<<endl;
		file<<p.webh<<endl<<p.webg<<endl; 
		file<<p.days<<endl<<p.lastday<<endl;
		file<<p.maxll<<endl<<p.ll<<endl;
		file<<p.sr<<endl<<p.fwqdel<<endl;
		file<<p.adddel<<endl<<p.lllv<<endl;
		file<<p.srlv<<endl<<p.lklv<<endl;
		file<<p.leave<<endl<<p.lvtm<<endl;
		file<<p.lvsr<<endl;
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
		file>>load_name>>load_password;
		if (password==load_password){
			p.name=load_name;
			p.password=load_password;
			file>>p.money>>p.webadd>>p.weblv>>p.webfwq;
			file>>p.webh>>p.webg>>p.days>>p.lastday;
			file>>p.maxll>>p.ll>>p.sr>>p.fwqdel;
			file>>p.adddel>>p.lllv>>p.srlv>>p.lklv; 
			file>>p.leave>>p.lvtm>>p.lvsr; 
			file.close();
			cout<<"成功加载："<<filename<<endl;
			if (p.leave!=0){
				long long now=min(14400+(long long)p.lvtm*600,(long long)time(0)-(long long)p.leave);
				p.money+=now*(1+p.lvsr);
				cout<<"离线时间(s)："<<now<<"  上限(s)："<<14400+p.lvtm*600<<"  离线收入："<<now*(1+p.lvsr)/100.0<<endl;
				p.leave=time(0);
				save();
			} 
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

void web(){
	while (true){
		clean();
		#ifdef iakioihashkiller_webbuilder_debug_mode
			cout<<"# 调试模式"<<endl; 
		#endif
		cout<<endl;
		cout<<"============ 网页信息 ============"<<endl;
		cout<<endl;
		cout<<"域名："<<p.webadd<<"  过期时间："<<p.adddel<<" 天后"<<endl; 
		cout<<"服务器："<<p.webfwq<<"   过期时间："<<p.fwqdel<<" 天后"<<endl;
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
		cout<<"> 3.域名购买"<<endl;
		cout<<"> 4.下一天（结算）"<<endl; 
		cout<<"> 5.保存并返回"<<endl;
		cout<<endl;
		cout<<"数字选择（1~5）：";
		string op;
		cin>>op;
		cout<<endl;
		if (op=="1"){//网页优化 
			web_yh();
		}
		else if (op=="2"){//服务器购买 
			web_fwq();
		}
		else if (op=="3"){//域名购买 
			web_ym();
		}
		else if (op=="4"){//下一天 
			#ifdef iakioihashkiller_webbuilder_debug_mode
				nextday();
			#else
				if (time(0)-p.lastday<10){
					cout<<"还需 "<<10-(time(0)-p.lastday)<<" 秒"<<endl; 
				}
				else{
					nextday(); 
				}
			#endif 
		}
		else if (op=="5"){//返回
			p.leave=time(0);
			save();
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

int main()
{
	system("title webbuilder");
	srand((unsigned)time(0));
	while (true){
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
					p.leave=time(0); 
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