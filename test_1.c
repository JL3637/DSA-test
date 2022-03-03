#include<stdio.h>
#include<string.h>
#define ARRAYSIZE 1000

int comparator_big(int bigint_1[ARRAYSIZE], int bigint_2[ARRAYSIZE],int strlen_a, int strlen_b){
    if(strlen_a != strlen_b){
        if(strlen_a > strlen_b){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        int a = strlen_a;
        while(bigint_1[a] == bigint_2[a]){
            a--;
        }
        if(bigint_1[a] > bigint_2[a]){
            return 1;
        }
        else{
            return 0;
        }
    }
}

void subtraction(int bigint_big[ARRAYSIZE], int bigint_small[ARRAYSIZE], int bigint_result[ARRAYSIZE], int *strlen_big, int *strlen_small){
    for(int i = 0; i < ARRAYSIZE; i++){
        if(bigint_big[i] - bigint_small[i] >= 0){
            bigint_result[i] = bigint_big[i] - bigint_small[i];
        }
        else{
            bigint_result[i] = 10 + bigint_big[i] - bigint_small[i];
            bigint_big[i+1]--;
        }
    }
    while(bigint_result[*strlen_big-1] == 0){
        *strlen_big-=1;
    }
}

void binary_division(int bigint[ARRAYSIZE], int bigint_result[ARRAYSIZE], int *strlen){
    for(int i = 0; i < *strlen; i++){
        if(bigint[i+1] % 2 == 0){
            bigint_result[i] = bigint[i] / 2;
        }
        else{
            bigint_result[i] = (bigint[i] + 10) / 2;
            bigint[i+1]--;
        }
    }
    if(bigint_result[*strlen-1] == 0){
        *strlen-=1;
    }
}

void binary_multiplication(int bigint[ARRAYSIZE], int bigint_result[ARRAYSIZE], int k, int *strlen){
    for(int j = 0; j < *strlen; j++){
        bigint_result[j] = bigint[j];
    }
    for(int i = 0; i < k; i++){
        for(int j = 0; j < *strlen; j++){
            bigint_result[j] = bigint_result[j] * 2;
        }
        for(int j = 0; j < *strlen; j++){
            if(bigint_result[j] > 9){
                bigint_result[j] =  bigint_result[j] -10;
                bigint_result[j+1]++;
            }
        }
        if(bigint_result[*strlen] != 0){
            *strlen+=1;
        }
    }
}

int not_zero_array_judge(int array[ARRAYSIZE]){
    for(int i = 0; i < ARRAYSIZE; i++){
        if(array[i] != 0){
            return 1;
        }
    }
    return 0;
}

int main(){
    int bigints[2][ARRAYSIZE] = {{0}};
    char str[2][ARRAYSIZE];
    int bigint_len_m = 0;
    int bigint_len_n = 0;
    int a = 0;
    while(scanf("%s", &str[a]) != EOF){
        for(int i = 0, j = strlen(str[a]) - 1; i < strlen(str[a]); i++ , j--){
            bigints[a][i] = str[a][j] - '0';
        }
        a++;
    }

    int m[ARRAYSIZE] = {0};
    int n[ARRAYSIZE] = {0};
    bigint_len_m = 0;
    bigint_len_n = 0;

    if(comparator_big(bigints[0], bigints[1], strlen(str[0]), strlen(str[1]))){
        for(int i = 0; i < ARRAYSIZE; i++){
            m[i] = bigints[0][i];
            n[i] = bigints[1][i];
        }
        bigint_len_m = strlen(str[0]);
        bigint_len_n = strlen(str[1]);
    }
    else{
        for(int i = 0; i < ARRAYSIZE; i++){
            m[i] = bigints[1][i];
            n[i] = bigints[0][i];
        }
        bigint_len_m = strlen(str[1]);
        bigint_len_n = strlen(str[0]);
    }

    int k = 0;
    int bigint_ans[ARRAYSIZE] = {0};

    while(not_zero_array_judge(n) && not_zero_array_judge(m)){
        if(n[0] % 2 == 0 && m[0] % 2 == 0){
            k++;
            binary_division(n, n, &bigint_len_n);
            binary_division(m, m, &bigint_len_m);
            continue;
        }
        else if(n[0] % 2 == 0){
            binary_division(n, n, &bigint_len_n);
            continue;
        }
        else if(m[0] % 2 == 0){
            binary_division(m, m, &bigint_len_m);
            continue;
        }
        if(comparator_big(n, m, bigint_len_n, bigint_len_m)){
            for(int i = 0; i < ARRAYSIZE; i++){
                int temp = m[i];
                m[i] = n[i];
                n[i] = temp;
            }
            int temp  = bigint_len_m;
            bigint_len_m = bigint_len_n;
            bigint_len_n = temp;
        }
        subtraction(m, n, m, &bigint_len_m, &bigint_len_n);
    }

    binary_multiplication(n, bigint_ans, k, &bigint_len_n);

    for(int i = bigint_len_n - 1; i >= 0; i--){
        printf("%d", bigint_ans[i]);
    }

    return 0;
}