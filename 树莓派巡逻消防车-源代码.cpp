#include <wiringPi.h>
#include <softPwm.h>
int fire = 0;  //�⣨��Դλ�ñ��
#define ON 1     //ʹ��LED
#define OFF 0    //��ֹLED
//��������
int LED_R = 3;  //LED_R����Raspberry�ϵ�wiringPi����3��
int LED_G = 2;  //LED_G����Raspberry�ϵ�wiringPi����2��
int LED_B = 5;  //LED_B����Raspberry�ϵ�wiringPi����5��
int buzzer = 10; //���ÿ��Ʒ���������δwiringPi����10��
//LED�Ʊ���
int Left_motor_go = 28;       //����ǰ��AIN2����Raspberry��wiringPi����28��
int Left_motor_back = 29;     //��������AIN1����Raspberry��wiringPi����29��
int Right_motor_go = 24;      //�ҵ��ǰ��BIN2����Raspberry��wiringPi����24��
int Right_motor_back = 25;    //�ҵ������BIN1����Raspberry��wiringPi����25��
int Left_motor_pwm = 27;      //��������PWMA����Raspberry��wiringPi����27��
int Right_motor_pwm = 23;     //�ҵ������PWMB����Raspberry��wiringPi����23��
int key = 10;                 //���尴��ΪRaspberry��wiringPi����10��
const int LdrSensorLeft = 11;   //������߹�����������ΪwiringPi����11��
const int LdrSensorRight = 22;   //�����ұ߹�����������ΪwiringPi����22��
int LdrSersorLeftValue;         //��������������������ɼ������ݴ�С
int LdrSersorRightValue;
int TrackSensorLeftPin1 = 9;   //������ߵ�һ��ѭ�����⴫��������ΪwiringPi����9��
const int TracikSensorLeftPin2 = 21;  //������ߵڶ���ѭ�����⴫��������ΪwiringPi����21��
const int TrackSensorRightPin1 = 7;   //�����ұߵ�һ��ѭ�����⴫��������ΪwiringPi����7��
const int TrackSensorRightPin2 = 1;   //�����ұߵڶ���ѭ�����⴫��������ΪwiringPi����1��
int TrackSensorLeftValue1;   //Ѱ��������1
int TrackSensorLeftValue2;   //Ѱ��������2
int TrackSensorRightValue1;  //Ѱ��������3
int TrackSensorRightValue2;  //Ѱ��������4
int OutfirePin = 8;      //�������������ΪwiringPi����8��
void run(int left_speed, int right_speed)  //С��ǰ��
{
    //����ǰ��
    digitalWrite(Left_motor_go, HIGH);   //����ǰ��ʹ��
    digitalWrite(Left_motor_back, LOW);  //�������˽�ֹ
    softPwmWrite(Left_motor_pwm, left_speed);
    //�ҵ��ǰ��
    digitalWrite(Right_motor_go, HIGH);  //�ҵ��ǰ��ʹ��
    digitalWrite(Right_motor_back, LOW); //�ҵ�����˽�ֹ
    softPwmWrite(Right_motor_pwm, right_speed);
}
void brake(int time)  //С��ɲ��
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
void left(int left_speed, int right_speed) //С����ת(���ֲ���������ǰ��)
{
    //����ֹͣ
    digitalWrite(Left_motor_go, LOW);    //����ǰ����ֹ
    digitalWrite(Left_motor_back, LOW);  //�������˽�ֹ
    softPwmWrite(Left_motor_pwm, left_speed);
    //�ҵ��ǰ��
    digitalWrite(Right_motor_go, HIGH);  //�ҵ��ǰ��ʹ��
    digitalWrite(Right_motor_back, LOW); //�ҵ�����˽�ֹ
    softPwmWrite(Right_motor_pwm, right_speed);
}
void right(int left_speed, int right_speed)  //С����ת(���ֲ���������ǰ��)
{
    //����ǰ��
    digitalWrite(Left_motor_go, HIGH);   //����ǰ��ʹ��
    digitalWrite(Left_motor_back, LOW);  //�������˽�ֹ
    softPwmWrite(Left_motor_pwm, left_speed);
    //�ҵ��ֹͣ
    digitalWrite(Right_motor_go, LOW);   //�ҵ��ǰ����ֹ
    digitalWrite(Right_motor_back, LOW); //�ҵ�����˽�ֹ
    softPwmWrite(Right_motor_pwm, right_speed);
}
void spin_left(int left_speed, int right_speed) //Ѱ����ת
{
    //��������
    digitalWrite(Left_motor_go, LOW);     //����ǰ����ֹ
    digitalWrite(Left_motor_back, HIGH);  //��������ʹ��
    softPwmWrite(Left_motor_pwm, left_speed);
    //�ҵ��ǰ��
    digitalWrite(Right_motor_go, HIGH);  //�ҵ��ǰ��ʹ��
    digitalWrite(Right_motor_back, LOW); //�ҵ�����˽�ֹ
    softPwmWrite(Right_motor_pwm, right_speed);
}
void spin_right(int left_speed, int right_speed)    //Ѱ����ת
{
    //����ǰ��
    digitalWrite(Left_motor_go, HIGH);    //����ǰ��ʹ��
    digitalWrite(Left_motor_back, LOW);   //�������˽�ֹ
    softPwmWrite(Left_motor_pwm, left_speed);
   //�ҵ������
    digitalWrite(Right_motor_go, LOW);    //�ҵ��ǰ����ֹ
    digitalWrite(Right_motor_back, HIGH); //�ҵ������ʹ��
    softPwmWrite(Right_motor_pwm, right_speed);
}
void spin_right2(int left_speed, int right_speed)    //Ѱ����ת
{
    //����ǰ��
    digitalWrite(Left_motor_go, HIGH);    //����ǰ��ʹ��
    digitalWrite(Left_motor_back, LOW);   //�������˽�ֹ
    softPwmWrite(Left_motor_pwm, left_speed);
   //�ҵ������
    digitalWrite(Right_motor_go, LOW);    //�ҵ��ǰ����ֹ
    digitalWrite(Right_motor_back, HIGH); //�ҵ������ʹ��
    softPwmWrite(Right_motor_pwm, right_speed);
    delay(50);
}
void back(int time)  //С������
{
    //��������
    digitalWrite(Left_motor_go, LOW);     //����ǰ����ֹ
    digitalWrite(Left_motor_back, HIGH);  //��������ʹ��
    softPwmWrite(Left_motor_pwm, 40);
    //�ҵ������
    digitalWrite(Right_motor_go, LOW);    //�ҵ��ǰ����ֹ
    digitalWrite(Right_motor_back, HIGH); //�ҵ������ʹ��
    softPwmWrite(Right_motor_pwm, 40);
    delay(time);
}
void key_scan()  //�������(�����������ȥ��)
{
    while (digitalRead(key));       //������û�б�����һֱѭ��
    while (!digitalRead(key))       //������������ʱ
    {
        delay(10);                      //��ʱ10ms
        if (digitalRead(key) == LOW)//�ڶ����жϰ����Ƿ񱻰���
        {
            delay(100);
            while (!digitalRead(key));  //�жϰ����Ƿ��ɿ�
        }
    }
}
void color_led(int v_iRed, int v_iGreen, int v_iBlue)  //�ȵ��ð���ɨ�躯��������Ѱ��ģʽ����
{
    //��ɫLED
    v_iRed == ON ? digitalWrite(LED_R, HIGH) : digitalWrite(LED_R, LOW);

    //��ɫLED
    v_iGreen == ON ? digitalWrite(LED_G, HIGH) : digitalWrite(LED_G, LOW);

    //��ɫLED
    v_iBlue == ON ? digitalWrite(LED_B, HIGH) : digitalWrite(LED_B, LOW);
}
void outfire()    //�йⴵ��
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
    wiringPiSetup();//wiringPi��ʼ��
    pinMode(Left_motor_go, OUTPUT);//��ʼ���������IO��Ϊ�����ʽ
    pinMode(Left_motor_back, OUTPUT);
    pinMode(Right_motor_go, OUTPUT);
    pinMode(Right_motor_back, OUTPUT);
    pinMode(OutfirePin, OUTPUT);//�������IO��Ϊ���ģʽ����ʼ��
    pinMode(LED_R, OUTPUT);//RGB����ģʽ����Ϊ���ģʽ
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(buzzer, OUTPUT);//������������Ϊ���ģʽ
    softPwmCreate(Left_motor_pwm, 0, 255);//��������������Ƶ�PWM��
    softPwmCreate(Right_motor_pwm, 0, 255);
    pinMode(key, INPUT);//���尴���ӿ�Ϊ����ӿ�
    pinMode(LdrSensorLeft, INPUT);//�������ҹ������贫����Ϊ����ӿ�
    pinMode(LdrSensorRight, INPUT);
    pinMode(TrackSensorLeftPin1, INPUT);//������·ѭ�����⴫����Ϊ����ӿ�
    pinMode(TrackSensorLeftPin2, INPUT);
    pinMode(TrackSensorRightPin1, INPUT);
    pinMode(TrackSensorRightPin2, INPUT);
    key_scan();//���ð���ɨ�躯��
    while (1)
    {
        //��⵽����ʱѭ��ģ����Ӧ��ָʾ�������˿ڵ�ƽΪLOW
        //δ��⵽����ʱѭ��ģ����Ӧ��ָʾ���𣬶˿ڵ�ƽΪHIGH
        TrackSensorLeftValue1 = digitalRead(TrackSensorLeftPin1);
        TrackSensorLeftValue2 = digitalRead(TrackSensorLeftPin2);
        TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
        TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
        //��������,Ѱ��ģ���ָʾ����,�˿ڵ�ƽΪHIGH
        //δ������,Ѱ��ģ���ָʾ����,�˿ڵ�ƽΪLOW
        LdrSersorRightValue = digitalRead(LdrSensorRight);
        LdrSersorLeftValue = digitalRead(LdrSensorLeft);
        outfire();//�ж��Ƿ��й⣬������
        if (OutfirePin != LOW)
        {
            if (TrackSensorLeftValue1 == LOW && TrackSensorRightValue1 == LOW && TrackSensorRightValue2 == LOW && TrackSensorLeftValue2 == LOW)
            {//ֹͣȻ�����ת��
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
            //��������Ǻ���ֱ�ǵ�ת��
            else if ((TrackSensorLeftValue1 == LOW || TrackSensorLeftValue2 == LOW) && TrackSensorRightValue2 == LOW)
            {
                brake(1);
                spin_right(120, 120);
                delay(80);
            }
            //��������Ǻ���ֱ�ǵ�ת��
            else if (TrackSensorLeftValue1 == LOW && (TrackSensorRightValue1 == LOW || TrackSensorRightValue2 == LOW))
            {
                brake(1);
                spin_left(120, 120);
                delay(80);
            }
            //����߼�⵽
            else if (TrackSensorLeftValue1 == LOW)
                spin_left(120, 120);
            //���ұ߼�⵽
            else if (TrackSensorRightValue2 == LOW)
                spin_right(120, 120);
            //������С��
            else if (TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == HIGH)
                left(0, 120);
            //������С��
            else if (TrackSensorLeftValue2 == HIGH && TrackSensorRightValue1 == LOW)
                right(150, 0);
            //����ֱ��
            else if (TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW)
                run(110, 110);
            //��Ϊ1 1 1 1ʱС��������һ��С������״̬
        }
    }
    return;
}
