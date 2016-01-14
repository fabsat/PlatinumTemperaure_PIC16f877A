/************************************************
 * AD_value.h
 * Tetsuya Kaku
 * =============================================
 * AD変換ヘッダファイル
 * =============================================
 * ・ver1.00 一版 2016/01/14 Tetsuya Kaku
 * AD変換する
 * =============================================
 * PIC16F877A
 * MPLAB X IDE(v3.10/Win)
 * XC8 (v1.35/Win)
************************************************/
#ifndef AD_VALUE_H
#define	AD_VALUE_H

void ad_con_init(void);                                    // AD変換初期設定
static int bit_shift(char my_adres_h, char my_adres_l);    // ビットシフト関数
double get_adcon(void);                                    // AD変換値取得関数

#endif	/* AD_VALUE_H */

