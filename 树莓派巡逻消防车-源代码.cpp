#include <wiringPi.h>
#include <softPwm.h>
int fire = 0;  //光（火）源位置标记
#define ON 1     //使能LED
#define OFF 0    //禁止LED
//定义引脚
int LED_R = 3;  //LED_R接在Raspberry上的wiringPi编码3口
int LED_G = 2;  //LED_G接在Raspberry上的wiringPi编码2口
int LED_B = 5;  //LED_B接在Raspberry上的wiringPi编码5口
int buzzer = 10; //设置控制蜂鸣器引脚未wiringPi编码10口
//LED灯编码
int Left_motor_go = 28;       //左电机前进AIN2连接Raspberry的wiringPi编码28口
int Left_motor_back = 29;     //左电机后退AIN1连接Raspberry的wiringPi编码29口
int Right_motor_go = 24;      //右电机前进BIN2连接Raspberry的wiringPi编码24口
int Right_motor_back = 25;    //右电机后退BIN1连接Raspberry的wiringPi编码25口
int Left_motor_pwm = 27;      //左电机控速PWMA连接Raspberry的wiringPi编码27口
int Right_motor_pwm = 23;     //右电机控速PWMB连接Raspberry的wiringPi编码23口
int key = 10;                 //定义按键为Raspberry的wiringPi编码10口
const int LdrSensorLeft = 11;   //定义左边光敏电阻引脚为wiringPi编码11口
const int LdrSensorRight = 22;   //定义右边光敏电阻引脚为wiringPi编码22口
int LdrSersorLeftValue;         //定义变量来保存光敏电阻采集的数据大小
int LdrSersorRightValue;
int TrackSensorLeftPin1 = 9;   //定义左边第一个循迹红外传感器引脚为wiringPi编码9口
const int TracikSensorLeftPin2 = 21;  //定义左边第二个循迹红外传感器引脚为wiringPi编码21口
const int TrackSensorRightPin1 = 7;   //定义右边第一个循迹红外传感器引脚为wiringPi编码7口
const int TrackSensorRightPin2 = 1;   //定义右边第二个循迹红外传感器引脚为wiringPi编码1口
int TrackSensorLeftValue1;   //寻迹传感器1
int TrackSensorLeftValue2;   //寻迹传感器2
int TrackSensorRightValue1;  //寻迹传感器3
int TrackSensorRightValue2;  //寻迹传感器4
int OutfirePin = 8;      //设置灭火电机引脚为wiringPi编码8口
void run(int left_speed, int right_speed)  //小车前进
{
    //左电机前进
    digitalWrite(Left_motor_go, HIGH);   //左电机前进使能
    digitalWrite(Left_motor_back, LOW);  //左电机后退禁止
    softPwmWrite(Left_motor_pwm, left_speed);
    //右电机前进
    digitalWrite(Right_motor_go, HIGH);  //右电机前进使能
    digitalWrite(Right_motor_back, LOW); //右电机后退禁止
    softPwmWrite(Right_motor_pwm, right_speed);
}
void brake(int time)  //小车刹车
{
    digitalWrite(Left_motor_go, LOW);
    digitalWrite(Left_motor_back, LOW);
    digitalWrite(Right_motor_go, LOW);
    digitalWrite(Right_motor_back, LOW);
    delay(time * 100);
}
void stop()
{
    digitalWrite(Left_motor_go, LOW);
    digitalWrite(Left_motor_back, LOW);
    digitalWrite(Right_motor_go, LOW);
    digitalWrite(Right_motor_back, LOW);
}
void left(int left_speed, int right_speed) //小车左转(左轮不动，右轮前进)
{
    //左电机停止
    digitalWrite(Left_motor_go, LOW);    //左电机前进禁止
    digitalWrite(Left_motor_back, LOW);  //左电机后退禁止
    softPwmWrite(Left_motor_pwm, left_speed);
    //右电机前进
    digitalWrite(Right_motor_go, HIGH);  //右电机前进使能
    digitalWrite(Right_motor_back, LOW); //右电机后退禁止
    softPwmWrite(Right_motor_pwm, right_speed);
}
void right(int left_speed, int right_speed)  //小车右转(右轮不动，左轮前进)
{
    //左电机前进
    digitalWrite(Left_motor_go, HIGH);   //左电机前进使能
    digitalWrite(Left_motor_back, LOW);  //左电机后退禁止
    softPwmWrite(Left_motor_pwm, left_speed);
    //右电机停止
    digitalWrite(Right_motor_go, LOW);   //右电机前进禁止
    digitalWrite(Right_motor_back, LOW); //右电机后退禁止
    softPwmWrite(Right_motor_pwm, right_speed);
}
void spin_left(int left_speed, int right_speed) //寻迹左转
{
    //左电机后退
    digitalWrite(Left_motor_go, LOW);     //左电机前进禁止
    digitalWrite(Left_motor_back, HIGH);  //左电机后退使能
    softPwmWrite(Left_motor_pwm, left_speed);
    //右电机前进
    digitalWrite(Right_motor_go, HIGH);  //右电机前进使能
    digitalWrite(Right_motor_back, LOW); //右电机后退禁止
    softPwmWrite(Right_motor_pwm, right_speed);
}
void spin_right(int left_speed, int right_speed)    //寻迹右转
{
    //左电机前进
    digitalWrite(Left_motor_go, HIGH);    //左电机前进使能
    digitalWrite(Left_motor_back, LOW);   //左电机后退禁止
    softPwmWrite(Left_motor_pwm, left_speed);
   //右电机后退
    digitalWrite(Right_motor_go, LOW);    //右电机前进禁止
    digitalWrite(Right_motor_back, HIGH); //右电机后退使能
    softPwmWrite(Right_motor_pwm, right_speed);
}
void spin_right2(int left_speed, int right_speed)    //寻迹右转
{
    //左电机前进
    digitalWrite(Left_motor_go, HIGH);    //左电机前进使能
    digitalWrite(Left_motor_back, LOW);   //左电机后退禁止
    softPwmWrite(Left_motor_pwm, left_speed);
   //右电机后退
    digitalWrite(Right_motor_go, LOW);    //右电机前进禁止
    digitalWrite(Right_motor_back, HIGH); //右电机后退使能
    softPwmWrite(Right_motor_pwm, right_speed);
    delay(50);
}
void back(int time)  //小车后退
{
    //左电机后退
    digitalWrite(Left_motor_go, LOW);     //左电机前进禁止
    digitalWrite(Left_motor_back, HIGH);  //左电机后退使能
    softPwmWrite(Left_motor_pwm, 40);
    //右电机后退
    digitalWrite(Right_motor_go, LOW);    //右电机前进禁止
    digitalWrite(Right_motor_back, HIGH); //右电机后退使能
    softPwmWrite(Right_motor_pwm, 40);
    delay(time);
}
void key_scan()  //按键检测(包含软件按键去抖)
{
    while (digitalRead(key));       //当按键没有被按下一直循环
    while (!digitalRead(key))       //当按键被按下时
    {
        delay(10);                      //延时10ms
        if (digitalRead(key) == LOW)//第二次判断按键是否被按下
        {
            delay(100);
            while (!digitalRead(key));  //判断按键是否被松开
        }
    }
}
void color_led(int v_iRed, int v_iGreen, int v_iBlue)  //先调用按键扫描函数，接着寻光模式开启
{
    //红色LED
    v_iRed == ON ? digitalWrite(LED_R, HIGH) : digitalWrite(LED_R, LOW);

    //绿色LED
    v_iGreen == ON ? digitalWrite(LED_G, HIGH) : digitalWrite(LED_G, LOW);

    //蓝色LED
    v_iBlue == ON ? digitalWrite(LED_B, HIGH) : digitalWrite(LED_B, LOW);
}
void outfire()    //判光吹风
{
    LdrSersorLeftValue = digitalRead(LdrSensorLeft);
    LdrSersorRightValue = digitalRead(LdrSensorRight);
    while (1)
    {

        if (LdrSersorRightValue == HIGH || LdrSersorLeftValue == HIGH)
        {
            if (LdrSersorRightValue == HIGH && LdrSersorLeftValue == HIGH)
            {
                stop();
                digitalWrite(buzzer, LOW);
                color_led(ON, OFF, OFF);
                delay(1000);
                digitalWrite(buzzer, HIGH);
                digitalWrite(OutfirePin, LOW);
                while (LdrSersorLeftValue == HIGH || LdrSersorRightValue == HIGH)
                {
                    LdrSersorLeftValue = digitalRead(LdrSensorLeft);
                    LdrSersorRightValue = digitalRead(LdrSensorRight);
                }
                digitalWrite(OutfirePin, HIGH);
            }
            else if (LdrSersorLeftValue == HIGH && LdrSersorRightValue == LOW)
            {
                spin_left(100, 100);
                fire = 1;
            }
            else if (LdrSersorLeftValue == LOW && LdrSersorRightValue == HIGH)
            {
                spin_right(100, 100);
                fire = 2;
            }
        }
        if (LdrSersorLeftValue == LOW && LdrSersorRightValue == LOW)
        {
            if (fire == 1)
            {
                digitalWrite(OutfirePin, HIGH);
                TrackSensorLeftValue1 = digitalRead(TrackSensorLeftPin1);
                TrackSensorLeftValue2 = digitalRead(TrackSensorLeftPin2);
                TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
                TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
                while (!(TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW && TrackSensorRightValue2 == HIGH))
                {
                    spin_right(100, 100);
                    TrackSensorLeftValue1 = digitalRead(TrackSensorLeftPin1);
                    TrackSensorLeftValue2 = digitalRead(TrackSensorLeftPin2);
                    TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
                    TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
                }
                stop();
                fire = 0;
            }
            if (fire == 2)
            {
                digitalWrite(OutfirePin, HIGH);
                TrackSensorLeftValue1 = digitalRead(TrackSensorLeftPin1);
                TrackSensorLeftValue2 = digitalRead(TrackSensorLeftPin2);
                TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
                TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
                while (!(TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW && TrackSensorRightValue2 == HIGH))
                {
                    spin_left(100, 100);
                    TrackSensorLeftValue1 = digitalRead(TrackSensorLeftPin1);
                    TrackSensorLeftValue2 = digitalRead(TrackSensorLeftPin2);
                    TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
                    TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
                }
                stop();
                fire = 0;
            }
            if (fire == 0)
            {
                break;
            }
            else break;
        }
        LdrSersorLeftValue = digitalRead(LdrSensorLeft);
        LdrSersorRightValue = digitalRead(LdrSensorRight);
    }
}
void main()
{
    wiringPiSetup();//wiringPi初始化
    pinMode(Left_motor_go, OUTPUT);//初始化电机驱动IO口为输出方式
    pinMode(Left_motor_back, OUTPUT);
    pinMode(Right_motor_go, OUTPUT);
    pinMode(Right_motor_back, OUTPUT);
    pinMode(OutfirePin, OUTPUT);//定义灭火IO口为输出模式并初始化
    pinMode(LED_R, OUTPUT);//RGB引脚模式设置为输出模式
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(buzzer, OUTPUT);//鸣笛引脚设置为输出模式
    softPwmCreate(Left_motor_pwm, 0, 255);//创建两个软件控制的PWM脚
    softPwmCreate(Right_motor_pwm, 0, 255);
    pinMode(key, INPUT);//定义按键接口为输入接口
    pinMode(LdrSensorLeft, INPUT);//定义左右光敏电阻传感器为输入接口
    pinMode(LdrSensorRight, INPUT);
    pinMode(TrackSensorLeftPin1, INPUT);//定义四路循迹红外传感器为输入接口
    pinMode(TrackSensorLeftPin2, INPUT);
    pinMode(TrackSensorRightPin1, INPUT);
    pinMode(TrackSensorRightPin2, INPUT);
    key_scan();//调用按键扫描函数
    while (1)
    {
        //检测到黑线时循迹模块相应的指示灯亮，端口电平为LOW
        //未检测到黑线时循迹模块相应的指示灯灭，端口电平为HIGH
        TrackSensorLeftValue1 = digitalRead(TrackSensorLeftPin1);
        TrackSensorLeftValue2 = digitalRead(TrackSensorLeftPin2);
        TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
        TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
        //遇到光线,寻光模块的指示灯灭,端口电平为HIGH
        //未遇光线,寻光模块的指示灯亮,端口电平为LOW
        LdrSersorRightValue = digitalRead(LdrSensorRight);
        LdrSersorLeftValue = digitalRead(LdrSensorLeft);
        outfire();//判断是否有光，开风扇
        if (OutfirePin != LOW)
        {
            if (TrackSensorLeftValue1 == LOW && TrackSensorRightValue1 == LOW && TrackSensorRightValue2 == LOW && TrackSensorLeftValue2 == LOW)
            {//停止然后进行转向
                delay(30);
                TrackSensorLeftValue1 = digitalRead(TrackSensorLeftPin1);
                TrackSensorLeftValue2 = digitalRead(TrackSensorLeftPin2);
                TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
                TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
                if (TrackSensorLeftValue1 == LOW && TrackSensorRightValue1 == LOW && TrackSensorRightValue2 == LOW && TrackSensorLeftValue2 == LOW)
                {
                    spin_right2(250, 250);
                    delay(400);
                    TrackSensorLeftValue1 = digitalRead(TrackSensorLeftPin1);
                    TrackSensorLeftValue2 = digitalRead(TrackSensorLeftPin2);
                    TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
                    TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
                    while (!(TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW && TrackSensorRightValue2 == HIGH))
                    {
                        spin_right(170, 170);
                        TrackSensorLeftValue1 = digitalRead(TrackSensorLeftPin1);
                        TrackSensorLeftValue2 = digitalRead(TrackSensorLeftPin2);
                        TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
                        TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
                    }
                }
            }
            //处理右锐角和右直角的转动
            else if ((TrackSensorLeftValue1 == LOW || TrackSensorLeftValue2 == LOW) && TrackSensorRightValue2 == LOW)
            {
                brake(1);
                spin_right(120, 120);
                delay(80);
            }
            //处理左锐角和左直角的转动
            else if (TrackSensorLeftValue1 == LOW && (TrackSensorRightValue1 == LOW || TrackSensorRightValue2 == LOW))
            {
                brake(1);
                spin_left(120, 120);
                delay(80);
            }
            //最左边检测到
            else if (TrackSensorLeftValue1 == LOW)
                spin_left(120, 120);
            //最右边检测到
            else if (TrackSensorRightValue2 == LOW)
                spin_right(120, 120);
            //处理左小弯
            else if (TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == HIGH)
                left(0, 120);
            //处理右小弯
            else if (TrackSensorLeftValue2 == HIGH && TrackSensorRightValue1 == LOW)
                right(150, 0);
            //处理直线
            else if (TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW)
                run(110, 110);
            //当为1 1 1 1时小车保持上一个小车运行状态
        }
    }
    return;
}
