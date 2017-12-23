#define FOR(i,bg,ed) for(int i=(bg);i<(ed);i++)
#define REP(i,n) FOR(i,0,n)

typedef double D;
#define REP4(i,n) for(int i=0;i<n;i+=4)

constexpr int S = 128;
struct M{
    D v[S][S];
    D& operator()(int i,int j){
        return v[i][j];
    }
}mat[32];

void mat_mul(M &a,M& b,M &c){
    REP(i,S)REP(j,S)c(i,j)=0;
    D sum[4],tmp;
    REP(k,S){
        REP4(i,S){
            sum[0]=a(i,k);
            sum[1]=a(i+1,k);
            sum[2]=a(i+2,k);
            sum[3]=a(i+3,k);
            REP(j,S){
                tmp=b(k,j);
                c(i,j)+=sum[0]*tmp;
                c(i+1,j)+=sum[1]*tmp;
                c(i+2,j)+=sum[2]*tmp;
                c(i+3,j)+=sum[3]*tmp;
            }
        }
    }
}
