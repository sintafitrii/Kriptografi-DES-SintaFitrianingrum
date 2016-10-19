#include<bits/stdc++.h>
#define nl "\n" 
using namespace std;
//Declaration
int plain_text[65],Cipher_text[65];
int key[65],C[29],D[29];
int IP_Tab[65], Ex_Tab[49],Per_Tab[33], inv_Tab[65];
int s1t[64],s2t[64],s3t[64],s4t[64],s5t[64],s6t[64],s7t[64],s8t[64];
int PC1_tab[57],PC2_tab[49];
int IP[65], Lprev[33],Rprev[33],Lnext[33],Rnext[33], Exp[49],Sbox[49],SboxOut[33],Permutation[33];
int PC1[57],saveC[17][29],saveD[17][29],PC2[49];
int s1[7],s2[7],s3[7],s4[7],s5[7],s6[7],s7[7],s8[7]; 
int tempp=1;

void makeTable(){
	//plain
	std::fstream filep("plain.txt",std::ios_base::in);
	int indeks;
	for(int i=1;i<65;i++){
		filep>>plain_text[i];
	}
	
	//key
	std::fstream filek("key.txt",std::ios_base::in);
	for(int i=1;i<65;i++){
		filek>>key[i];
	}
	
	//table IP
	std::fstream file("IP.txt",std::ios_base::in);
	for(int i=1;i<65;i++){
		file>>IP_Tab[i];
	}
	
	//table expand
	std::fstream file2("Exp.txt",std::ios_base::in);
	for(int i=1;i<49;i++){
		file2>>Ex_Tab[i];
	}
	
	//table permutation
	std::fstream file3("permutation.txt",std::ios_base::in);
	for(int i=1;i<33;i++){
		file3>>Per_Tab[i];
	}
	
	//PC1
	std::fstream file4("PC1.txt",std::ios_base::in);
	for(int i=1;i<57;i++){
		file4>>PC1_tab[i];
	}	
	
	//PC2
	std::fstream file5("PC2.txt",std::ios_base::in);
	for(int i=1;i<49;i++){
		file5>>PC2_tab[i];
	}
	
	//inv IP
	std::fstream file6("inv_IP.txt",std::ios_base::in);
	for(int i=1;i<65;i++){
		file6>>inv_Tab[i];
	}
	
	//s-box table
	std::fstream file11("s1.txt",std::ios_base::in);
	for(int i=0;i<64;i++){
		file11>>s1t[i];
	}
	std::fstream file12("s2.txt",std::ios_base::in);
	for(int i=0;i<64;i++){
		file12>>s2t[i];
	}
	std::fstream file13("s3.txt",std::ios_base::in);
	for(int i=0;i<64;i++){
		file13>>s3t[i];
	}
	std::fstream file14("s4.txt",std::ios_base::in);
	for(int i=0;i<64;i++){
		file14>>s4t[i];
	}
	std::fstream file15("s5.txt",std::ios_base::in);
	for(int i=0;i<64;i++){
		file15>>s5t[i];
	}
	std::fstream file16("s6.txt",std::ios_base::in);
	for(int i=0;i<64;i++){
		file16>>s6t[i];
	}
	std::fstream file17("s7.txt",std::ios_base::in);
	for(int i=0;i<64;i++){
		file17>>s7t[i];
	}
	std::fstream file18("s8.txt",std::ios_base::in);
	for(int i=0;i<64;i++){
		file18>>s8t[i];
	}
	
}

void display(int m[]){
	int tempo=9;
	for(int indeks=1;indeks<65;indeks++){			
		if(indeks==tempo){
			cout<<nl<<m[indeks]<<" ";
			tempo+=8;
		}else{
			cout<<m[indeks]<<" ";
		}
	}
}

void gen_bit(int plain_text[],string plain){
	int tempor=1;
	int arr_biner[8],dec;
	int sisa,dapet;
	for(int i=0;i<plain.size();i++){
		dec=(int)plain[i];
		for(int i=7;i>=0;i--){
			sisa=dec%2;
			arr_biner[i]=sisa;
			dec/=2;
		}
		for(int i=0;i<8;i++){
			plain_text[tempor]=arr_biner[i];
			tempor++;
		}
	}
}

void initial_permutation(int IP[],int plain_text[]){
	int indeks;
	for(int i=1;i<65;i++){
		indeks=IP_Tab[i];
		IP[i]=plain_text[indeks];
	}	
}

void setLRprev(int Lprev[],int Rprev[], int IP[]){
	int temp=1;
	for(int i=1;i<33;i++){
		Lprev[i]=IP[i];
	}
	
	for(int j=33;j<65;j++){
		Rprev[temp]=IP[j];
		temp++;
	}	
}

void Permuted_Choice1(int PC1[],int key[]){
	int indeks;
	for(int i=1;i<57;i++){
		indeks=PC1_tab[i];
		PC1[i]=key[indeks];
	}
}

void setCDprev(int C[],int D[],int PC1[]){
	for(int i=1;i<29;i++){
		C[i]=PC1[i];
	}
	int tem=29;
	for(int i=1;i<29;i++){
		D[i]=PC1[tem];
		tem++;
	}	
}

void left_shift(int ronde,int C[],int D[]){
	int c1=C[1],d1=D[1];
	if(ronde==1 || ronde==2 || ronde==9 || ronde==16){
		for(int i=1;i<28;i++){
			C[i]=C[i+1];
			D[i]=D[i+1];
		}
		C[28]=c1;
		D[28]=d1;
	}else{
		for(int j=1;j<=2;j++){
			c1=C[1],d1=D[1];
			for(int i=1;i<28;i++){
				C[i]=C[i+1];
				D[i]=D[i+1];
			}
			C[28]=c1;
			D[28]=d1;
		}
	}
}

void saveKey(int saveC[17][29],int saveD[17][29],int C[],int D[],int ronde){
	for(int i=1;i<29;i++){
		saveC[ronde][i]=C[i];
		saveD[ronde][i]=D[i];
	}
}

void Expansion(int Exp[],int Rprev[]){
	int indeks;
	for(int i=1;i<49;i++){
		indeks=Ex_Tab[i];
		Exp[i]=Rprev[indeks];
	}	
}

void Permuted_Choice2(int PC2[],int C[],int D[]){
	int key_shift[57],indeks;
	for(int i=1;i<29;i++){
		key_shift[i]=C[i];
	}
	int tem=29;
	for(int i=1;i<29;i++){
		key_shift[tem]=D[i];
		tem++;
	}
		
	for(int i=1;i<49;i++){
		indeks=PC2_tab[i];
		PC2[i]=key_shift[indeks];
	}
}

void XOR(int m1[],int m2[],int m3[]){
	for(int i=1;i<49;i++){
		if(m1[i]!=m2[i]){
			m3[i]=1;
		}else{
			m3[i]=0;
		}
	}
}

int getSboxtable(int biner[7]){		
	int rrow[3],rcol[5],rowdec=0,coldec=0,indeks;
	
	rrow[1] = biner[1];
	rrow[2] = biner[6];
	for(int i=1;i<=4;i++){
		rcol[i]=biner[i+1];
	}
	
	for(int i=1;i<=2;i++){
		rowdec=rowdec+rrow[i]*pow(2,2-i);
	}
	
	for(int i=1;i<=4;i++){					
		coldec=coldec+rcol[i]*pow(2,4-i);
	}
	indeks=rowdec*16+coldec;
	return indeks;
}

void dec_bin(int D, int SboxOut[]){
				
	int dec=D, arr_biner[5];
	int sisa,dapet;
	for(int i=4;i>=1;i--){
		sisa=dec%2;
		arr_biner[i]=sisa;
		dec/=2;
	}
	for(int i=1;i<=4;i++){
		SboxOut[tempp]=arr_biner[i];
		tempp++;
	}
}

void sbox(int Sbox[],int SboxOUt[]){
	int s1[7],s2[7],s3[7],s4[7],s5[7],s6[7],s7[7],s8[7];
	int tem;
	for(int i=1;i<7;i++){
		s1[i]=Sbox[i];
	}	
	tem=7;
	for(int i=1;i<7;i++){
		s2[i]=Sbox[tem];
		tem++;
	}
	for(int i=1;i<7;i++){
		s3[i]=Sbox[tem];
		tem++;
	}
	for(int i=1;i<7;i++){
		s4[i]=Sbox[tem];
		tem++;
	}
	for(int i=1;i<7;i++){
		s5[i]=Sbox[tem];
		tem++;
	}
	for(int i=1;i<7;i++){
		s6[i]=Sbox[tem];
		tem++;
	}
	for(int i=1;i<7;i++){
		s7[i]=Sbox[tem];
		tem++;
	}
	for(int i=1;i<7;i++){
		s8[i]=Sbox[tem];
		tem++;
	}
	
	int dec1;int l1=getSboxtable(s1);
	dec1=s1t[l1];
	dec_bin(dec1,SboxOUt);
	
	int dec2;int l2=getSboxtable(s2);
	dec2=s2t[l2];
	dec_bin(dec2,SboxOUt);
	
	int dec3;int l3=getSboxtable(s3);
	dec3=s3t[l3];
	dec_bin(dec3,SboxOUt);

	int dec4;int l4=getSboxtable(s4);
	dec4=s4t[l4];
	dec_bin(dec4,SboxOUt);

	int dec5;int l5=getSboxtable(s5);
	dec5=s5t[l5];
	dec_bin(dec5,SboxOUt);

	int dec6;int l6=getSboxtable(s6);
	dec6=s6t[l6];
	dec_bin(dec6,SboxOUt);

	int dec7;int l7=getSboxtable(s7);
	dec7=s7t[l7];
	dec_bin(dec7,SboxOUt);

	int dec8;int l8=getSboxtable(s8);
	dec8=s8t[l8];
	dec_bin(dec8,SboxOUt);					
}

void Permut(int Permutation[],int SboxOut[]){
	int indeks;
	for(int i=1;i<33;i++){
		indeks=Per_Tab[i];
		Permutation[i]=SboxOut[indeks];
	}
}

void setLRnext(int Lprev[],int Rprev[],int Lnext[],int Rnext[]){
	for(int i=1;i<33;i++){
		Lnext[i]=Rprev[i];
	}

	for(int i=1;i<33;i++){
		Rprev[i]=Rnext[i];
		Lprev[i]=Lnext[i];
	}
}

void inv_IP(int Cipher_text[],int Lnext[],int Rnext[]){
	int dummy[65],tem=1,indeks;
	for(int i=1;i<33;i++){
		dummy[tem]=Rnext[i];
		tem++;
	}
	for(int i=1;i<33;i++){
		dummy[tem]=Lnext[i];
		tem++;
	}

	for(int i=1;i<65;i++){
		indeks=inv_Tab[i];
		Cipher_text[i]=dummy[indeks];
	}	
}

void useKey(int ronde,int C[],int D[],int saveC[17][29],int saveD[17][29]){
	for(int i=1;i<29;i++){
		C[i]=saveC[ronde][i];
		D[i]=saveD[ronde][i];
	}
}

void DES_encrypt(string plain){
	gen_bit(plain_text,plain);
	cout<<"Plaintext"<<nl;
	display(plain_text);cout<<nl<<nl;
	
	initial_permutation(IP,plain_text);
	setLRprev(Lprev,Rprev,IP);
	Permuted_Choice1(PC1,key);
	setCDprev(C,D,PC1);
	
	cout<<"key awal : "<<nl;
	cout<<"C : ";
	for(int i=1;i<29;i++){
			cout<<C[i]<<" ";
	}cout<<nl;
	cout<<"D : ";
	for(int i=1;i<29;i++){
		cout<<D[i]<<" ";
	}cout<<nl<<nl;
	int round=1;
	
	while(round<=16){
		left_shift(round,C,D);
		saveKey(saveC,saveD,C,D,round);
		cout<<"Round-"<<round<<nl;
		cout<<"Lprev : ";
		for(int i=1;i<33;i++){
			cout<<Lprev[i]<<" ";
		}cout<<nl;
		cout<<"Rprev : ";
		for(int i=1;i<33;i++){
			cout<<Rprev[i]<<" ";
		}cout<<nl;
		cout<<"C : ";
		for(int i=1;i<29;i++){
			cout<<C[i]<<" ";
		}cout<<nl;
		cout<<"D : ";
		for(int i=1;i<29;i++){
			cout<<D[i]<<" ";
		}cout<<nl;
		
		Expansion(Exp,Rprev);		Permuted_Choice2(PC2,C,D);
		XOR(Exp,PC2,Sbox);
		sbox(Sbox,SboxOut);
		Permut(Permutation,SboxOut);
		XOR(Lprev,Permutation,Rnext);
		setLRnext(Lprev,Rprev,Lnext,Rnext);			
		round++;
	}
	inv_IP(Cipher_text,Lnext,Rnext);
	cout<<"Ciphertext"<<nl;
	display(Cipher_text);cout<<nl<<nl;
}

void DES_decrypt(int Cipher_text[]){
	initial_permutation(IP,Cipher_text);
	setLRprev(Lprev,Rprev,IP);
	int round=16;
	
	while(round>0){
		useKey(round,C,D,saveC,saveD);
		
		cout<<"Round-"<<round<<nl;
		cout<<"Lprev : ";
		for(int i=1;i<33;i++){
			cout<<Lprev[i]<<" ";
		}cout<<nl;
		cout<<"Rprev : ";
		for(int i=1;i<33;i++){
			cout<<Rprev[i]<<" ";
		}cout<<nl;
		cout<<"C : ";
		for(int i=1;i<29;i++){
			cout<<C[i]<<" ";
		}cout<<nl;
		cout<<"D : ";
		for(int i=1;i<29;i++){
			cout<<D[i]<<" ";
		}cout<<nl;
		
		Expansion(Exp,Rprev);		Permuted_Choice2(PC2,C,D);
		XOR(Exp,PC2,Sbox);
		sbox(Sbox,SboxOut);
		Permut(Permutation,SboxOut);
		XOR(Lprev,Permutation,Rnext);
		setLRnext(Lprev,Rprev,Lnext,Rnext);	
		round--;
	}
	inv_IP(Cipher_text,Lnext,Rnext);
	cout<<"Plaintext Decryption"<<nl;
	display(Cipher_text);
}

int main(){
	makeTable(); 
	string plain;
	cout<<"masukkan plaintext = ";cin>>plain;cout<<endl;
	cout<<"Key : ";
	for(int i=1;i<65;i++){
		cout<<key[i];
	}cout<<nl;
	
	DES_encrypt(plain);
	DES_decrypt(Cipher_text);
	
}
