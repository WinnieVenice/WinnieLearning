void getPrime(bool p[],int n){
    for(int i=2;i<=n;i++)
        p[i]=true;
    p[1]=false;
    for(int i=2;i<=n;i++){
        if(p[i]){
            for(int j=i+i;j<=n;j+=i)
                p[j]=false;
        }
    }
}