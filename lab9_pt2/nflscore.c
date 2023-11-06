#include <stdio.h>
#include <stdlib.h>

// Template for Printing Combinations
void combo_print(int twopt_touchdown, int fg_touchdown, int touchdown, int three_point, int safety) {
    printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", twopt_touchdown, fg_touchdown, touchdown, three_point, safety);
}

// Adds Combinations
void add_combination(int combos[][5], int* num_combos, int twopt_touchdown, int fg_touchdown, int touchdown, int three_point, int safety) {
    for (int i = 0; i < *num_combos; i++) {
        if (combos[i][0] == twopt_touchdown && combos[i][1] == fg_touchdown && combos[i][2] == touchdown && combos[i][3] == three_point && combos[i][4] == safety) {
            return;
        }
    }
    combos[*num_combos][0] = twopt_touchdown;
    combos[*num_combos][1] = fg_touchdown;
    combos[*num_combos][2] = touchdown;
    combos[*num_combos][3] = three_point;
    combos[*num_combos][4] = safety;
    (*num_combos)++;
}

// Finds Combinations
void find_combinations(int score, int current, int twopt_touchdown, int fg_touchdown, int touchdown, int three_point, int safety,
                       int combos[][5], int* num_combos) {
    if (current == score) {
        add_combination(combos, num_combos, twopt_touchdown, fg_touchdown, touchdown, three_point, safety);
        return;
    }

    if (current + 2 <= score) {
        find_combinations(score, current + 2, twopt_touchdown, fg_touchdown, touchdown, three_point, safety + 1, combos, num_combos);
    }
    if (current + 3 <= score) {
        find_combinations(score, current + 3, twopt_touchdown, fg_touchdown, touchdown, three_point + 1, safety, combos, num_combos);
    }
    if (current + 6 <= score) {
        find_combinations(score, current + 6, twopt_touchdown, fg_touchdown, touchdown + 1, three_point, safety, combos, num_combos);
    }
    if (current + 7 <= score) {
        find_combinations(score, current + 7, twopt_touchdown, fg_touchdown + 1, touchdown, three_point, safety, combos, num_combos);
    }
    if (current + 8 <= score) {
        find_combinations(score, current + 8, twopt_touchdown + 1, fg_touchdown, touchdown, three_point, safety, combos, num_combos);
    }
}

// Orders Combinations by Ascending Order
int combo_comp(const void *a, const void *b) {
    int *combo_one = (int *)a;
    int *combo_two = (int *)b;

    // Compare Based on Priority: TD + 2pt, TD + FG, TD, 3pt FG, Safety
    if (combo_one[0] != combo_two[0]) {
        return combo_one[0] - combo_two[0];
    } else if (combo_one[1] != combo_two[1]) {
        return combo_one[1] - combo_two[1];
    } else if (combo_one[2] != combo_two[2]) {
        return combo_one[2] - combo_two[2];
    } else if (combo_one[3] != combo_two[3]) {
        return combo_one[3] - combo_two[3];
    } else {
        return combo_one[4] - combo_two[4];
    }
}

int main() {
    int score;

    while (1) {
        printf("Enter 0 or 1 to STOP\n");
        printf("Enter the NFL score: ");
        scanf("%d", &score);

        if (score <= 1) {
            break;
        }

        printf("Possible combinations of scoring plays:\n");

        int combos[100][5];
        int num_combos = 0;

        find_combinations(score, 0, 0, 0, 0, 0, 0, combos, &num_combos);

        qsort(combos, num_combos, sizeof(int[5]), combo_comp);

        for (int i = 0; i < num_combos; i++) {
            combo_print(combos[i][0], combos[i][1], combos[i][2], combos[i][3], combos[i][4]);
        }
    }

    return 0;
}
