#include <bits/stdc++.h>

using namespace std;

int lps[100];
char pattern[100];
int plen;
char str[10000];

void populate() {
    int j = 0;
     int i = 1;
     while(pattern[i] != '\0') {
        if(pattern[i] == pattern[j]) {
            lps[i] = j+1;
            i++;j++;
        }

        else if(j == 0) {
            lps[i] = 0;
            i++;
        }

        else {
            j = lps[j-1];
        }
     }

     plen = i-1;

     for(i=0;pattern[i]!='\0';i++) cout<<lps[i]<<" ";
     cout<<endl;
}

void KMP() {
   int i,j;
   i=j=0;

   while(str[i] != '\0') {
    if(str[i] == pattern[j]) {

        if(j == plen) {
            cout<<i-plen<<" ";
            j = lps[j];
            i++;
        }

        else {i++;j++;}
    }
    else if(j == 0){
        i++;
    }
    else{
        j = lps[j-1];
    }

   }

}

int main() {
     cin>>pattern;
     populate();

     cin>>str;

     KMP();

     return 0;
}
