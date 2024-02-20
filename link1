#include <kipr/wombat.h>

const int CLAW_CLOSED = 100;

void drive(int time, int direction)
{
    mav(2, 500 * direction);
    mav(3, 500 * direction);
    msleep(time);
    mav(3, 0);
    mav(2, 0);
}

void drive_left(int time, int direction)
{
    mav(2, 500 * direction);
    msleep(time);
    mav(2, 0);
}

void drive_right(int time, int direction)
{
    mav(3, 500 * direction);
    msleep(time);
    mav(3, 0);
}

void turn(int time, int direction) // 1 is right, -1 is left
{
    mav(2, 500 * direction);
    mav(3, -500 * direction);
    msleep(time);
    mav(3, 0);
    mav(2, 0);
}

void init_servos()
{
    enable_servo(0);
    enable_servo(1);
    
    set_servo_position(0, CLAW_CLOSED);
    set_servo_position(1, 0);
}

void square_up(int direction)
{
    drive(5000, -1);
    
    msleep(500);
    
    drive(1200, 1);
    
    turn(1950, direction);
    
    drive(2000, 1);
    
    msleep(1000);
}

void move_arm(int target)
{
    int direction = (target - get_servo_position(1)) > 0;
    while(abs(get_servo_position(1) - target) > 15)
    {
        set_servo_position(1, get_servo_position(1) + direction * 10);
        msleep(30);
    }
}

void grab_poms()
{
    drive_right(200, -1);
    move_arm(1600);
    msleep(1000);
    set_servo_position(0, 300);
    msleep(1000);
    set_servo_position(1, 1800);
    msleep(1000);
    set_servo_position(0, CLAW_CLOSED);
    msleep(1000);
    set_servo_position(1, 0);
    msleep(1000);
}

void get_poms1()
{
    square_up(1);
    
    msleep(500);
    
    grab_poms();
}

void get_poms2()
{
    square_up(-1);
    
    msleep(500);
    
    grab_poms();
}

int main()
{
    init_servos();

    msleep(500);
    
    get_poms1(1);
    
    return 0;
}
