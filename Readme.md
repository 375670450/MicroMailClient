# MicroMailClient
�ʼ��ͻ���(MVC + QT + Material Design)

#��Ҫ����:
- ʹ��MVC���ģʽ�������ʼ�����ͻ���(QT + Material Design, ��Ʋο�Gmail�ƶ��ͻ���)
- �û������ڿͻ�����ʹ�ó��õ��ʼ�ϵͳ(ͨ��SMTP/POP3)�������ṩ���ʼ�ϵͳMicroMail
- ���Խ����ʼ����������շ�, �鿴��

#��Ҫģ��:
1. View(��ͼ)(2��):
	- ��½
	- ע��/�������(��ʹ��MicroMailʱ)
	- �ռ���
	- �����ʼ�
	- �鿴�ʼ�
	- �ϴ�, ���ظ���
	
2. Controller(������)(1��):
	View��Model(��ǰ�˺ͺ��)ͨ�Ų��ֳ����ʵ��

3. Model(ģ��)(2��):
	�ͻ��˵�¼���շ��ʼ�, �鿴�ʼ�, �������صȵĳ���ʵ��

4. ����ܹ����ӿ�, ���ݿ����(1��)

5. MicroMail�������������ʵ��(1��)

6. ͨ��(Utils)ģ��(1��)

7. ��������ĵ�(1��)


#�ֹ�:

- ��ͼ+����ܹ�+����������

- ��ͼ+������

- ģ��

- �����ĵ� + ����ģ��(���粿��)

#P.S. 

1. ʹ��git��Ϊ�汾������, [�̳�������](http://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000)

2. ȫ��ʹ��C++11�����Կ���, ʹ������ָ��(shared_ptr, weak_ptr, unique_ptr, ������auto_ptr), ������������ʹ��new/delete�Լ������ڴ�; ʹ��static_cast<>����(Type)������ת��.

3. ������ѭ[Google��Դ��Ŀ��C++���](http://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/), ������ͷ�ļ���ʹ�úͽ�ֹȫ�ֱ���. 

4. ���������Ϳ��:Qt Creator + Qt 5.6(MinGW4.9), [���ص�ַ](http://download.qt.io/official_releases/qt/5.6/5.6.0/qt-opensource-windows-x86-android-5.6.0.exe)
��װʱ��ѡTools/MinGW4.9

5. ��������Ҫʹ��POCO C++ Libraryʵ��, [�ٷ��ĵ�](http://pocoproject.org/docs/Poco.Net.MailMessage.html)

6. ǰ����Ҫʹ��qml-material��չģ��ʵ��, [�ٷ��ĵ�](http://papyros.io/qml-material/)

	���ص�ַ: box��ȡ�� material

	����˵��: http://www.heilqt.com/topic/56b010459e5a7aac4bc63b42

7. ���ݿ����[MongoDB](https://www.mongodb.com/)

---------