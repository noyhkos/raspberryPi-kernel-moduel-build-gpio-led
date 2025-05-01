# raspberryPi-kernel-moduel-build-gpio-led

```project_root/
├── mydev1_driver/ 
│   ├── src/ 
│   │   ├── mydev1_driver.c
│   │   └── Makefile
│   ├── module/
│   │   ├── gpio_module.c
│   │   ├── gpio_module.h
│   │   ├── led_module.c
│   │   ├── led_module.h
│   │   └── Makefile
│   ├── build.sh 
│   └── clean.sh 
│
└── app/
    ├── app.c
    ├── Makefile
    ├── run.sh
    └── clean.sh
```

## HOW TO USE
1. /mydev1_driver
    1. 드라이버 개발
        - 메인 드라이버:
            LED = crate_led(pin num);
            destroy_led(LED);
        - led_module:
            GPIO = create_gpio(pin num);
            destroy_gpio(GPIO);
    2. 드라이버 설치
        - build.sh 실행

2. /app
    1. app 개발
    2. 드라이버 설치
    3. run.sh 실행
