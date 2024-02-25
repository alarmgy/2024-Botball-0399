#include <kipr/wombat.h>

const int CLAW_CLOSED = 20;

void drive(int time, int direction)
{
    mav(2, 500 * direction);
    mav(3, 500 * direction);
    msleep(time);
    mav(3, 0);
    mav(2, 0);
}

void drive_fast(int time, int direction)
{
    mav(2, 1000 * direction);
    mav(3, 1000 * direction);
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

void turn_arm(int target, int direction)
{
    mav(0, 400 * direction);
    while(abs(get_motor_position_counter(0) - target) > 15 && get_motor_position_counter(0) > target)
    {
        msleep(50);
    }
    freeze(0);
}

void turn(int time, int direction) // 1 is right, -1 is left
{
    mav(2, 500 * direction);
    mav(3, -500 * direction);
    msleep(time);
    mav(3, 0);
    mav(2, 0);
}

void init()
{
    enable_servo(0);
    enable_servo(1);
    
    set_servo_position(0, CLAW_CLOSED);
    set_servo_position(1, 0);
    
    
    mav(0, 500);
    msleep(3000);
    freeze(0);
    
}

void square_up(int direction)
{
    drive_fast(5000, -1);
    
    msleep(500);
    
    if(direction == 1)
    {
        drive(1300, 1);
    }
    else
    {
        drive(1100, 1);
    }
    
    turn(1950, direction);
    
    drive(2000, 1);
    
    msleep(1000);
}

void move_arm(int target)
{
    int direction;
    if(target - get_servo_position(1) > 0)
    {
        direction = 1;
    }
    else
    {
        direction = -1;
    }
    while(abs(get_servo_position(1) - target) > 20)
    {
        set_servo_position(1, get_servo_position(1) + direction * 30);
        msleep(30);
    }
}

void grab_poms()
{
    move_arm(1530);
    msleep(500);
    set_servo_position(0, 300);
    msleep(500);
    set_servo_position(1, 1750);
    msleep(500);
    set_servo_position(0, CLAW_CLOSED);
    msleep(1000);
    move_arm(0);
    msleep(500);
    
    turn_arm(-1050, -1);
    move_arm(800);
    msleep(500);
    set_servo_position(0, 400);
    msleep(1000);
    move_arm(0);
    set_servo_position(0, CLAW_CLOSED);
    mav(0, 500);
    msleep(5000);
    freeze(0);
    clear_motor_position_counter(0);
}

void grab_light_poms(int pos)
{
    clear_motor_position_counter(0);
    set_servo_position(0, CLAW_CLOSED);
    turn_arm(pos, -1);
    set_servo_position(0, 450);
    msleep(1000);
    move_arm(1720);
    msleep(500);
    set_servo_position(0, CLAW_CLOSED);
    msleep(500);
    move_arm(0);
    
    turn_arm(-1050, -1);
    move_arm(800);
    msleep(500);
    set_servo_position(0, 400);
    msleep(1000);
    move_arm(0);
    set_servo_position(0, CLAW_CLOSED);
    mav(0, 500);
    msleep(5000);
    freeze(0);
    clear_motor_position_counter(0);
}

void get_poms1()
{
    clear_motor_position_counter(0);
    
    square_up(1);
    
    msleep(500);
    
    grab_poms();
    /*
    msleep(500);
    grab_poms();
    */
    
    
    msleep(1000);
    grab_light_poms(-200);
	grab_light_poms(-300);
    
}

void get_poms2()
{
	square_up(-1);
    
    msleep(500);
    clear_motor_position_counter(0);
    turn_arm(-380, -1);
    msleep(500);
    grab_poms();
    msleep(500);
    /*
    turn_arm(-370, -1);
    grab_poms();
    */
}


int main()
{
    init();

    msleep(500);
    get_poms1();
    
    msleep(500);
    drive(1000, -1);
    turn(2000, -1);
    
    drive_fast(2000, -1);
    msleep(500);
    drive_fast(3500, 1);
    turn(2000, -1);
    
    get_poms2();
    
    
    return 0;
}
