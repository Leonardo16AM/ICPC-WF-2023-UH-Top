Int norm_mod(Int a,Int p){
	a%=p;
	if(a<0)a+=p;
	return a;
}
//p: odd (not necessarily prime)
//10^18 
Int jacobi(Int a,Int p){
	a=norm_mod(a,p);
	auto neg=[](Int x){return x%2?-1:1;};
	if(a==0) return p==1;
	else if(a%2) return neg(((p-1)&(a-1))>>1)*jacobi(p%a,a);
	else return neg(((p&15)*(p&15)-1)/8)*jacobi(a/2,p);
}
//yosupo sqrt mod (work without define int ll)
//LOJ 150
//p: prime
//0<=a<p
//returns minimum solution
 
template<class T>
T rnd(T l,T r){	//[l,r)
	using D = uniform_int_distribution<T>;
	static random_device rd;
	static mt19937 gen(rd());
	return D(l,r-1)(gen);
}
template<class T>
T rnd(T n){	//[0,n)
	return rnd(T(0),n);
}
Int sqrt_mod(Int a,Int p){
	if(p==2)return a%2;
	if(a==0)return 0;
	if(jacobi(a,p)==-1)return -1;
	Int b,c;
	do{
		b=rnd<ll>(p);
		c=norm_mod(b*b-a,p);
	}while(jacobi(c,p)!=-1);
	auto mul=[&](pair<Int,Int> x,pair<Int,Int> y){
		return pair<Int,Int>(norm_mod(x.fs*y.fs+x.sc*y.sc%p*c,p),norm_mod(x.fs*y.sc+x.sc*y.fs,p));
	};
	pair<Int,Int> x(b,1),cur(1,0);
	Int n=(p+1)/2;
	while(n){
		if(n&1)cur=mul(cur,x);
		x=mul(x,x);
		n>>=1;
	}
	return min(cur.fs,p-cur.fs);
}