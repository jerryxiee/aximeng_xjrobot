//////////////////////////////////////////////////////////////////////////
//zt_motor_master_driver.h 
//������ �������
//�ײ��������� �ṩ�����ʼ�����ٶȿ��ƣ�λ�ÿ��ƽӿ�
//�����ڲ���һ���Զ����ٶȿ��Ƹ��º������ú�����ÿ��tickʱ������һ��
//////////////////////////////////////////////////////////////////////////
#ifndef _ZT_MOTOR_MASTER_DRIVER_H_
#define _ZT_MOTOR_MASTER_DRIVER_H_

#define GET_SLAVE_WHEEL_CODE()  GetTimerCodeVal(TIM4)
#define  SLAVE_WHEEL_CODE_SCALE         2400		//���̻������ϵ��


/************************************************* 
*Function:		zt_motor_master_driver_init
*Input:			
*OUTPUT:		void
*Return:		
*DESCRIPTION:  �����ֵ����ʼ��
*************************************************/
void zt_motor_master_driver_init(void);

/*************************************************
*Input:			
*OUTPUT:		void
*Return:		ʵ�����õ��ٶ�
*DESCRIPTION:  ���� �����ֵ�����ٶ�
*************************************************/
s16 zt_motor_master_driver_set_speed(s16 speed,u16 code_run);

/************************************************* 
*Function:		zt_motor_master_driver_set_accl
*Input:			
*OUTPUT:		void
*Return:		ʵ�����õ� ���ٶ�
*DESCRIPTION:  ���� �����ֵ���ļ��ٶ�  ���ٶ�ֵΪ���Ƶ���ٶȱ仯ʱ��
*           ��������θ���ʱ���仯���ٶ��� �ٶ�ֵΪ 0.00��100.00 
*           Ϊ�˿��� �ͼ��㾫�� ���ٶ�ֵ ��λΪ0.01
*************************************************/
u16 zt_motor_master_driver_set_accl(u16 accl);


//////////////////////////////////////////////////////////////////////////
//��λ���� ��Ҫ�����ֿ��Ʋ��� �� float ת��Ϊ int ����
//����ٶȣ�������ֵ ���ڲ����ƶ��� int����

typedef struct
{
    u8      cur_dir;    //��ǰ�ķ���  ����ķ���0 ��ʾ����  �������Ƿ�ת
    u8      set_dir;    //���õķ���
    u16     n_accl;     //��ǰ�ļ��ٶ�
    u16     n_del_accl;     //��ǰ�ļ��ٶ�
    u16     set_speed;    //���õ��ٶ� Ŀ���ٶ�
    u16     cur_speed;    //��ǰ���ٶ� ��ֵΪ �ٶȵ�100�� ������Щβ��
    u16     left_code;    //���Ƶ���˶� ʣ�µ������� ���ﵽ��Щ������ʱ����Ҫ���ֹͣ
    
    s16   real_out_speed; 

    //limit_speed ��ͬ������� ���ٲ�ͬ ��ѹ��̫С ���� ̫��ʱ ����Ҫ��Щ
    //�������Ҫ�������٣���Ҫ��������ֵΪ 101*100
    u16     limit_speed ;  
    u16     limit_speed_time ; //���ٳ���ʱ��

    u16     ys_running_time;  //2017-04-06 ��ˢ��������ڼ���������Ƿ��쳣������������Ҫֹͣ���һ��ʱ��
    u16     ys_stop_in_running_time; //���й����� ֹͣ��ʱ�䳤��
    u16     ys_need_stop_time_err; //��ˢ����쳣ʱ����Ҫ��Ϣ��ʱ��
    
    bool	motor_master_wheel_slippage_state;	//�����ִ�״̬��־

	   
	
}MotorDriverCtrlType;

extern MotorDriverCtrlType gMstMt;

/************************************************* 
*Return:	void
*DESCRIPTION:  �������ٶ�ʵ�ʿ����ٶȷ��������¹���
*************************************************/
void zt_motor_master_driver_update(void);


/*************************************************
*Input:			
*OUTPUT:		void
*Return:		
*DESCRIPTION:  �ж��������Ƿ��
*************************************************/
void zt_motor_master_wheel_slippage(void);


#endif