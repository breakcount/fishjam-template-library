package com.fishjam.android.study;
import android.test.AndroidTestCase;

/**************************************************************************************************************************************
 * Thread -- ʵ�� Runnable �ӿ�֧�ֶ��̣߳�  new Thread(Runable).start();
 *   while(!Thread.currentThread().isInterrupted()) { ... } 
 *   
 *   AsyncTask<byte[], String, String> -- �첽�����ࣿ����Ϊģ����ʽ? ������������첽����ͼƬ ?
 *     doInBackground(byte[]...params) -- �̳�������Ҫ���صľ��幤������ 
 *     execute(����) -- ���ÿ�ʼ�첽ִ��
 *     
 *  
**************************************************************************************************************************************/

public class ThreadTester extends AndroidTestCase{

	public void ThreadDemo(){
		//�̺߳�ִ̨�У�ǰ̨��ʾ���ȶԻ���
		/**************************************************************************************************************************************
		 m_myDialog = ProgressDialog.show(EX03_18.this,strDialogTitle,strDialogBody, true);
		 new Thread()
		  {
		    public void run()
		    {
		      try
		      {
		        sleep(3000); //��̨���еĳ���Ƭ�Σ��˴�����ͣ3����Ϊʾ��
		      }
		      catch(Exception e)
		      {
		        e.printStackTrace();
		      }
		      finally
		      {
		         myDialog.dismiss(); //ж����������m_myDialog����
		      }
		    }
		  }.start();//��ʼ�����߳�
		//**************************************************************************************************************************************/
	}
}