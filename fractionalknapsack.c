//FRACTIONAL_KNAPSACK
#include <stdio.h>
#define CAPACITY 13
#define MAX 50
typedef struct {
    int profit,weight;
    int item_no;
    float item_accepted;
}items;

void fractional_knapsack(items item[],float *current_profit, float *current_weight, int n,float accepted_array[]) {
    int i,j;
    items temp;
    for(i=1; i<n ; i++) {
        for(j=0 ; j < n-i ; j++){
            if((item[j].profit/item[j].weight) < (item[j+1].profit/item[j+1].weight)) {
                temp = item[j];
                item[j] = item[j+1];
                item[j+1] = temp;
            }
        }
    }

    for(i=0 ; i<n ; i++) {
        if(*current_weight + item[i].weight < CAPACITY) {
            accepted_array[item[i].item_no] = 1;
            item[i].item_accepted = 1;
            *current_profit = *current_profit + item[i].profit;
            *current_weight = *current_weight + item[i].weight;
        }
        else {
            accepted_array[item[i].item_no] = (CAPACITY - *current_weight) / item[i].weight;
            item[i].item_accepted = (CAPACITY - *current_weight) / item[i].weight;
            *current_profit = *current_profit + item[i].profit*item[i].item_accepted;
            *current_weight = CAPACITY;
            return;
        }
    }
}

void main() {
    items item[MAX];
    float current_profit = 0;
    float current_weight = 0;
    int i,n;
    float accepted_array[MAX];
    printf("\nEnter Total Items: ");
    scanf("%d",&n);
    printf("\nEnter in the form: Profit Weight\n");
    for(i = 0 ; i<n ; i++) {
        scanf("%d %d",&item[i].profit,&item[i].weight);
        item[i].item_no = i;
    }
    fractional_knapsack(item,&current_profit, &current_weight,n,accepted_array);
    printf("\nCurrent Profit = %f.",current_profit);
    printf("\nCurrent Weight = %f.",current_weight);
    printf("\nAccepted items\n:");
    for(i=0;i<n;i++){
        printf("% f",accepted_array[i]);
    }
}