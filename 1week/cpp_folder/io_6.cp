#include <iostream>
#include <cstdio>
int main(){
    int n, m, i;
    scanf ("%d", &n);
    int a[n];
    for (int i=0; i<n; i++)
        std::cin>>a[i];
    scanf ("%d", &m);
    int k[m];
    for (i=0; i<m; i++)
        std::cin>>k[i];
    int min_, max_;
    int len[n];
    for (int y = 0; y < m; y++)
    {
        for (i=0; i < n; i++)
            len[i]=0;
        for (i=0; i<n-1; i++){
            min_ = (a[i] >= a[i+1])? a[i+1]: a[i];
            max_ = (a[i] >= a[i+1])? a[i]: a[i+1];
            for (int t=i; t<n ; t++){
                max_ = (max_>=a[t])? max_:a[t];
                min_ = (min_<= a[t])? min_:a[t];
                if (max_ - min_ <= k[y])
                    len[i]++;
                else
                    break;
            }
        }
        int max = -1, beg = -1;
        for (i = 0; i<n; i++){
            if (len[i]>max) {
                beg = i;
                max = len[i];
            }
        }
        max = (max>1)?--max:max;
        beg++;
        printf("%d %d\n",beg, beg+max);
    };
    return 0;
}

