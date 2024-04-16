#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<set>
#include <iomanip>
using namespace std;
	// (a)小題
	void solution_of_a(){
		int x1, x2, x3, x4; //primary input signals
		bool a, b, c, z; //output signals of logic gates
		cout << setw(2) << "x1" << " ";
		cout << setw(2) << "x2" << " ";
		cout << setw(2) << "x3" << " ";
		cout << setw(2) << "x4" << " ";
		cout << setw(2) << "a" << " ";
		cout << setw(2) << "b" << " ";
		cout << setw(2) << "c" << " ";
		cout << setw(2) << "z" << endl;
		for (x1 = 0; x1 <= 1; x1++) {
			for (x2 = 0; x2 <= 1; x2++) {
				for (x3 = 0; x3 <= 1; x3++) {
					for (x4 = 0; x4 <= 1; x4++) {
						a = x1 & x2;
						b = !(x2 || x3);
						c = !x4;
						z = a || b || c;
						cout << setw(2) << x1 << " ";
						cout << setw(2) << x2 << " ";
						cout << setw(2) << x3 << " ";
						cout << setw(2) << x4 << " ";
						cout << setw(2) << a << " ";
						cout << setw(2) << b << " ";
						cout << setw(2) << c << " ";
						cout << setw(2) << z << endl;
					}
				}
			}
		}
	}
	/////
	/////
	////(b)小題
	vector<string>intersection(vector<string> a, vector<string>b) {
		vector<string>ans;
		unordered_map<string,int>mp;
		for (int i = 0; i < a.size(); i++) { 
				mp[a[i]]=1;
		}
		for (int i = 0; i < b.size(); i++) {
			if (mp.find(b[i])!=mp.end()) {
				ans.push_back(b[i]);
				mp.erase(b[i]);
			}
		}
		return ans;
	}
	vector<string>my_union(vector<string>a, vector<string>b) {
		vector<string>ans;
		unordered_map<string,int>mp;
		for (int i = 0; i < a.size(); i++) {
			mp[a[i]] = 1;
		}
		for (int i = 0; i < b.size(); i++) {
			if (mp.find(b[i]) == mp.end()) {//只把沒登入的加入近來
				mp[b[i]] = 1;
			}
		}
		for (unordered_map<string, int>::iterator it = mp.begin(); it != mp.end(); it++) {
			ans.push_back(it->first);
		}
		return ans;
	}
	vector<string>my_difference(vector<string>a, vector<string>b) { //b是有prime的集合
		vector<string>ans;
		unordered_map<string, int>mp;
		for (int i = 0; i < a.size(); i++) { 
			mp[a[i]] = 1;
		}
		vector<string> tempo=intersection(a, b);
		for (int i = 0; i < tempo.size(); i++) { //把交集的元素刪掉
			if (mp.find(tempo[i]) != mp.end()) {
				mp.erase(tempo[i]);
			}
		}
		for (unordered_map<string, int>::iterator it = mp.begin(); it != mp.end(); it++) {
			ans.push_back(it->first);
		}
		return ans;
	
	}
	void solution_of_b() {
		int x1, x2, x3, x4; //primary input signals
		bool a, b, c, z; //output signals of logic gates
		int y21, y22; 
		cout << setw(2) << "x1" << " ";
		cout << setw(2) << "x2" << " ";
		cout << setw(2) << "x3" << " ";
		cout << setw(2) << "x4" << " ";
		cout << setw(2) << "detected_fault" << endl;
		//cout << setw(2) << "detected_fault_number" << endl;
		for (x1 = 0; x1 <= 1; x1++) {
			for (x2 = 0; x2 <= 1; x2++) {
				for (x3 = 0; x3 <= 1; x3++) {
					for (x4 = 0; x4 <= 1; x4++) {
						vector<string>Lx1, Lx2, Lx3, Lx4, La, Lb, Lc, Lz, Ly21, Ly22;
						a = x1 & x2;
						b = !(x2 || x3);
						c = !x4;
						z = a || b || c;
						y21 = x2;
						y22 = x2;
						cout << setw(2) << x1 << " ";
						cout << setw(2) << x2 << " ";
						cout << setw(2) << x3 << " ";
						cout << setw(2) << x4 << " ";
						//跟input值相反就是我的stack at fault;
						Lx1.push_back(x1 == 0 ? "x1/1" : "x1/0");
						Lx2.push_back(x2 == 0 ? "x2/1" : "x2/0");
						Lx3.push_back(x3 == 0 ? "x3/1" : "x3/0");
						Lx4.push_back(x4 == 0 ? "x4/1" : "x4/0");
						//處理分支 
						if (x2 == 0 && y21 == 0) {
							Ly21.push_back("x2/1");
							Ly21.push_back("y21/1");
						}
						else if (x2 == 1 && y21 == 1) {
							Ly21.push_back("x2/0");
							Ly21.push_back("y21/0");
						}
						if (x2 == 0 && y22 == 0) {
							Ly22.push_back("x2/1");
							Ly22.push_back("y22/1");
						}
						else if (x2 == 1 && y22 == 1) {
							Ly22.push_back("x2/0");
							Ly22.push_back("y22/0");
						}
						 //////////開始處理and-gate
						if (x1 == 1 && y21 == 1) {
							//La={a/0}+Lx1 U Ly21
							La.push_back("a/0");
							vector<string> tmp= my_union(Lx1, Ly21);
							for (int i = 0; i < tmp.size(); i++) {
								La.push_back(tmp[i]);
							}
						}
						else if(x1==0&&y21==0) {
							//La={a/1}+Lx1∩Ly21
							La.push_back("a/1");
							vector<string> tmp = intersection(Lx1, Ly21);
							for (int i = 0; i < tmp.size(); i++) {
								La.push_back(tmp[i]);
							}
						}
						else if (x1 == 0 && y21 == 1) {
							//La={a/1}+Lx1∩(Ly21)'
							La.push_back("a/1");
							vector<string>tmp = my_difference(Lx1, Ly21);
							for (int i = 0; i < tmp.size(); i++) {
								La.push_back(tmp[i]);
							}
						}
						else if (x1 == 1 && y21 == 0) {
							//La={a/1}+Lx1'∩Ly21
							La.push_back("a/1");
							vector<string>tmp = my_difference(Ly21, Lx1);
							for (int i = 0; i < tmp.size(); i++) {
								La.push_back(tmp[i]);
							}
						}
						/////////////處理完and gate
						
						////////////開始處理NOT gate
						if (x4 == 0) {
							//Lc={c/0}+{x4/0};
							Lc.push_back("c/0");
							Lc.push_back("x4/1");
						}
						else if(x4 == 1) {
							//Lc={c/1}+{x4/1}
							Lc.push_back("c/1");
							Lc.push_back("x4/0");
						}
						////////處理完NOT gate

						////////開始處理NOR gate
						if (y22 == 0 && x3 == 0) {
							//Lb={b/0}+Ly22+Lx3;
							Lb.push_back("b/0");
							vector<string> tmp = my_union(Ly22, Lx3);
							for (int i = 0; i < tmp.size(); i++) {
								Lb.push_back(tmp[i]);
							}
						}
						else if(y22==0&&x3==1){
							//Lb={b/1}+Ly22'∩Lx3
							Lb.push_back("b/1");
							vector<string> tmp = my_difference(Lx3, Ly22);
							for (int i = 0; i < tmp.size(); i++) {
								Lb.push_back(tmp[i]);
							}
						}
						else if (y22 == 1 && x3 == 0) {
							//Lb={b/1}+Ly22∩Lx3'
							Lb.push_back("b/1");
							vector<string> tmp = my_difference(Ly22, Lx3);
							for (int i = 0; i < tmp.size(); i++) {
								Lb.push_back(tmp[i]);
							}
						}
						else if (y22 == 1 && x3 == 1) {
							//Lb={b/1}+Ly22∩Lx3
							Lb.push_back("b/1");
							vector<string> tmp = intersection(Ly22, Lx3);
							for (int i = 0; i < tmp.size(); i++) {
								Lb.push_back(tmp[i]);
							}
						}
						//////處理完NOR gate
						
						/////開始處理3-input OR gate
						if (a == false && b == false && c == false) {
							//Lz={z/1}+La+Lb+Lc;
							Lz.push_back("z/1");
							vector<string> tmp1 = my_union(La, Lb);
							vector<string> tmp2 = my_union(tmp1,Lc);
							for (int i = 0; i < tmp2.size(); i++) {
								Lz.push_back(tmp2[i]);
							}
						}
						else if (a == false && b == false && c == true) {
							//Lz={z/0}+La'∩Lb'∩Lc
							Lz.push_back("z/0");
							vector<string> tmp1 = my_difference(Lc, La);
							vector<string> tmp2 = my_difference(tmp1, Lb);
							for (int i = 0; i < tmp2.size(); i++) {
								Lz.push_back(tmp2[i]);
							}
						}
						else if (a == false && b == true && c == false) {
							//Lz={z/0}+La'∩Lb∩Lc'
							Lz.push_back("z/0");
							vector<string> tmp1 = my_difference(Lb, La);
							vector<string> tmp2 = my_difference(tmp1, Lc);
							for (int i = 0; i < tmp2.size(); i++) {
								Lz.push_back(tmp2[i]);
							}
						}
						else if (a== false &&b== true &&c== true) {
							//Lz={z/0}+La'∩Lb∩Lc
							Lz.push_back("z/0");
							vector<string> tmp1 = my_difference(Lb, La);
							vector<string> tmp2 = intersection(tmp1, Lc);
							for (int i = 0; i < tmp2.size(); i++) {
								Lz.push_back(tmp2[i]);
							}
						}
						else if (a == true && b == false && c == false) {
							//Lz={z/0}+La∩Lb'∩Lc'
							Lz.push_back("z/0");
							vector<string> tmp1 =my_difference(La, Lb);
							vector<string> tmp2 = my_difference(tmp1, Lc);
							for (int i = 0; i < tmp2.size(); i++) {
								Lz.push_back(tmp2[i]);
							}
						}
						else if (a == 1 && b == false && c == true) {
							//Lz={z/0}+La∩Lb'∩Lc
							Lz.push_back("z/0");
							vector<string> tmp1 = my_difference(La, Lb);
							vector<string> tmp2 = intersection(tmp1, Lc);
							for (int i = 0; i < tmp2.size(); i++) {
								Lz.push_back(tmp2[i]);
							}
						}
						else if (a == true && b == true && c == false) {
							//Lz={z/0}+La∩Lb∩Lc'
							Lz.push_back("z/0");
							vector<string> tmp1 = my_difference(La, Lc);
							vector<string> tmp2 = intersection(tmp1, Lb);
							for (int i = 0; i < tmp2.size(); i++) {
								Lz.push_back(tmp2[i]);
							}
						}
						else if (a == true && b == true && c == true) {
							//Lz={z/0}+La∩Lb∩Lc
							Lz.push_back("z/0");
							vector<string> tmp1 = intersection(La, Lb);
							vector<string> tmp2 = intersection(tmp1, Lc);
							for (int i = 0; i < tmp2.size(); i++) {
								Lz.push_back(tmp2[i]);
							}
						}
						///處理完3-input OR gate
						for (int i = 0; i < Lz.size(); i++) {
							cout << setw(2) << Lz[i] << " ";
						}
						printf("\n");
						//cout << setw(2)<< Lz.size() << endl;
						

					}
				}
			}
		}
	}
int main() {
	cout << "第(a)小題:" << endl;
	solution_of_a();
	cout << "第(b)小題:" << endl;
	solution_of_b();
	return 0;
}