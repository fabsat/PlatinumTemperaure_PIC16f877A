# PlatinumTemperaure_PIC16f877A

PIC16F877Aを使用.
白金薄膜温度センサを使用.

PICのADコンバータを使って5.0Vを2.4kΩで分圧し、
白金薄膜温度センサの電圧を取得して、温度に変換する.

AD読み取りピンはRA0で行い、Vref+はRA3ピンを使用、Vref-に関してはVss.
