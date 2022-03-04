#include<stdio.h>
#define arrlen 15

void print_board(int *board, int n, int m){
    int a = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(*(board + a) == 1){
                printf("o");
            }
            else if(*(board + a) == 0){
                printf("_");
            }
            a++;
        }
        printf("\n");
    }
}

int check_valid_board(int *board, int n, int m, int *row_block_number, int *column_block_number, int *row_cells, int *column_cells){
    for(int i = 0; i < n; i++){
        int blocks_sum = 0;
        int cells_sum = 0;
        int b = arrlen * i;
        int index = 0;
        for(int j = 0; j < m; j++){
            if(*(board + (m * i + j)) == 1 && index == 0){
                blocks_sum++;
                cells_sum++;
                index = 1;
                if(j == m - 1){
                    if(cells_sum != *(row_cells + b)){
                        return 0;
                    }
                }
            }
            else if(*(board + (m * i + j)) == 1 && index == 1){
                cells_sum++;
                if(j == m - 1){
                    if(cells_sum != *(row_cells + b)){
                        return 0;
                    }
                }
            }
            else if(*(board + (m * i + j)) == 0 && index == 1){
                if(cells_sum != *(row_cells + b)){
                    return 0;
                }
                else{
                    b++;
                    index = 0;
                    cells_sum = 0;
                }
            }
        }
        if(blocks_sum != *(row_block_number + i)){
            return 0;
        }
    }
    for(int i = 0; i < m; i++){
        int blocks_sum = 0;
        int cells_sum = 0;
        int b = arrlen * i;
        int index = 0;
        for(int j = 0; j < n; j++){
            if(*(board + (i + m * j)) == 1 && index == 0){
                blocks_sum++;
                cells_sum++;
                index = 1;
                if(j == n- 1){
                    if(cells_sum != *(column_cells + b)){
                        return 0;
                    }
                }
            }
            else if(*(board + (i + m * j)) == 1 && index == 1){
                cells_sum++;
                if(j == n - 1){
                    if(cells_sum != *(column_cells + b)){
                        return 0;
                    }
                }
            }
            else if(*(board + (i + m * j)) == 0 && index == 1){
                if(cells_sum != *(column_cells + b)){
                    return 0;
                }
                else{
                    b++;
                    index = 0;
                    cells_sum = 0;
                }
            }
        }
        if(blocks_sum != *(column_block_number + i)){
            return 0;
        }
    }
    return 1;
}

void paint_board(int *board, int *position, int color){
    if(color == 1){
        *(board + *position) = 1;
        *position += 1;
    }
    else if(color == 0){
        *(board + *position) = 0;
        *position += 1;
    }
    else if(color == -1){
        *(board + *position) = -1;
    }
}

int recursion(int *board, int n, int m, int *row_block_number, int *column_block_number, int *row_cells, int *column_cells, int *position){
    if(*(board + n * m - 1) != -1){
        if(check_valid_board(board, n, m, row_block_number, column_block_number, row_cells, column_cells)){
            print_board(board, n, m);
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        paint_board(board, position, 1);
        int succeed = recursion(board, n, m, row_block_number, column_block_number, row_cells, column_cells, position);
        if(succeed){
            return 1;
        }
        else{
            *position -= 1;
        }
        paint_board(board, position, 0);
        succeed = recursion(board, n, m, row_block_number, column_block_number, row_cells, column_cells, position);
        if(succeed){
            return 1;
        }
        else{
            *position -= 1;
        }
        paint_board(board, position, -1);
        return 0;
    }
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    int row_block_number[n];
    int column_block_number[m];
    int row_cells[n][arrlen];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < arrlen; j++){
           row_cells[i][j] = 0; 
        }
    }
    int column_cells[m][arrlen];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < arrlen; j++){
           column_cells[i][j] = 0; 
        }
    }
    for(int i = 0; i < n; i++){
        scanf("%d", &row_block_number[i]);
        for(int j = 0; j < row_block_number[i]; j++){
            scanf("%d", &row_cells[i][j]);
        }
    }
    for(int i = 0; i < m; i++){
        scanf("%d", &column_block_number[i]);
        for(int j = 0; j < column_block_number[i]; j++){
            scanf("%d", &column_cells[i][j]);
        }
    }

    int board[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            board[i][j] = -1;        //-1 = empty, 1 = black, 0 = white
        }
    }

    int position = 0;

    recursion(&board[0][0], n, m, &row_block_number[0], &column_block_number[0], &row_cells[0][0], &column_cells[0][0], &position);
    
    return 0;
}