/************************************************
 * newmain.c
 * Tetsuya Kaku
 * =============================================
 * 白金薄膜温度センサメインファイル
 * =============================================
 * ・ver1.00 一版 2016/01/14 Tetsuya Kaku
 * 白金薄膜温度センサ
 * =============================================
 * PIC16F877A
 * MPLAB X IDE(v3.10/Win)
 * XC8 (v1.35/Win)
************************************************/

#include <xc.h>
#include <pic16f877a.h>
#include <stdio.h>
#include "pic_clock.h"
#include "uart_serial.h"
#include "AD_value.h"
#include "plati_temp.h"

//コンフィグ設定
#pragma config FOSC = HS, WDTE = OFF, PWRTE = ON,  BOREN = ON,  LVP = OFF
#pragma config CPD = OFF, WRT = OFF, CP = OFF

/****************************************************************************
* main()
****************************************************************************/
int main(){

    TRISDbits.TRISD4 = 0;   // LEDを使用するピン設定(RA4)
    PORTDbits.RD4 =0;       // LEDを使用するピン設定(RA4)
    uart_init();            //「調歩同期式シリアル通信」の設定を行う関数
    ad_con_init();          // AD変換の初期設定
    printf("Start_Temp!\r\n");
    
    // 無限ループ
    while(1){
        RD4 = 1;    // LED点灯
        printf("T = %.2f[℃]\r\n", get_temp());  // 温度データ取得＆表示
        RD4 = 0;    // LED消灯
    }
}
