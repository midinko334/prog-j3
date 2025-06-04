#include <stdio.h>

int main() {
    // 長方形Pの左下と右上の座標
    int LP1, LP2, RP1, RP2;
    // 長方形Qの左下と右上の座標
    int LQ1, LQ2, RQ1, RQ2;

    // 座標の入力
    printf("長方形Pの左下と右上の座標を入力 (LP1 LP2 RP1 RP2): ");
    scanf("%d %d %d %d", &LP1, &LP2, &RP1, &RP2);

    printf("長方形Qの左下と右上の座標を入力 (LQ1 LQ2 RQ1 RQ2): ");
    scanf("%d %d %d %d", &LQ1, &LQ2, &RQ1, &RQ2);

    // 重なりの左下の座標 (重なり領域の左端と下端)
    int overlap_left   = ((LP1) > (LQ1) ? (LP1) : (LQ1));
    int overlap_bottom = ((LP2) > (LQ2) ? (LP2) : (LQ2));
    // 重なりの右上の座標 (重なり領域の右端と上端)
    int overlap_right  = ((RP1) < (RQ1) ? (RP1) : (RQ1));
    int overlap_top    = ((RP2) < (RQ2) ? (RP2) : (RQ2));

    // 重なり領域の幅と高さを計算
    int overlap_width  = overlap_right - overlap_left;
    int overlap_height = overlap_top - overlap_bottom;

    int area = 0;

    // 幅と高さがともに正である場合のみ重なりが存在
    if (overlap_width > 0 && overlap_height > 0) {
        area = overlap_width * overlap_height;
    }

    // 結果の出力
    printf("重なっている部分の面積は: %d\n", area);

    return 0;
}
