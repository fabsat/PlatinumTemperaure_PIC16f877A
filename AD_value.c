/************************************************
 * AD_value.c
 * Tetsuya Kaku
 * =============================================
 * AD変換ソースファイル
 * =============================================
 * ・ver1.00 一版 2016/01/14 Tetsuya Kaku
 * AD変換する
 * =============================================
 * PIC16F877A
 * MPLAB X IDE(v3.10/Win)
 * XC8 (v1.35/Win)
************************************************/
#include <xc.h>
#include <pic16f877a.h>
#include <math.h>
#include "pic_clock.h"
#include "AD_value.h"


/*=====================================================
 * @breif
 *     ADコンバータ設定関数
 * @param
 *     なし
 * @return
 *     なし
 * @note
 *     ADコンバータするピンを要確認
 *===================================================*/
void ad_con_init(void){
    
    PORTAbits.RA0 = 0;
    PORTAbits.RA3 = 0;
    TRISAbits.TRISA0 = 1;   //RA0を入力ピンにしてVref＋読み取りピン
    TRISAbits.TRISA3 = 1;   //RA3を入力ピンにしてAD読み取りピン 
    ADCON1 = 0b00000001;
}


/*-----------------------------------------------------
 * @breif
 *     bitshiftの関数
 * @param
 *     my_adres_h:上位アドレス(ADRESH)
 *     my_adres_l:下位アドレス(ADRESL)
 * @return
 *     AD変換後の値
 * @note
 *     AD_value.c内で使用する関数なのでstatic関数
 *---------------------------------------------------*/
static int bit_shift(char my_adres_h, char my_adres_l){
    
    int i, j;
    int ad_value;
    
    char buf      = 0x00;
    char bit_mask = 0b10000000;

    /* get value from ADRESH */
    for(i = 0; i < 8; i++)
    {
        buf = my_adres_h & bit_mask;
        buf >>= 7;
        ad_value |= (int)buf;
        ad_value <<= 1;
        my_adres_h <<= 1;
    }
        
    /* get value from ADRESL */    
    for(j = 0; j < 2; j++)
    {      
        buf = my_adres_l & bit_mask;
        buf >>= 7;
        ad_value |= (int)buf;
    
        if (j < 1)
        {
            ad_value <<= 1; 
        }
        my_adres_l <<= 1;
    }
    /* return voltage value that is type of int */
    return ad_value;
}


/*=====================================================
 * @breif
 *     AD変換する関数
 * @param
 *     なし
 * @return
 *     AD変換した電圧値(V)
 * @note
 *     AD変換する関数
 *===================================================*/
double get_adcon(void)
{
    /* A/D con Range */
    const unsigned int range = 0x3ff;
    
    /* A/D value */
    int ad_value = 0b0000000000;
    double voltage_value;

    /* variables to recive binary from Register */
    long my_adres_h;
    long my_adres_l; 
        
    /* A/D Con Enable */
    ADCON0 = 0b10000001;
    ADCON0bits.GO_DONE = 1;

    /* waiting for finish of A/D */
    while(ADCON0bits.GO_DONE){;}

    /* get binary from Register */
    my_adres_h = ADRESH;
    my_adres_l = ADRESL;
    ad_value = bit_shift(my_adres_h, my_adres_l);

    /* calculate value of voltage */
    voltage_value = ad_value * 5.0 / range;
    
    return voltage_value;
}
