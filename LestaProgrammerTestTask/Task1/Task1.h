/*
	�������� ������� ����������� �������� �����.
	�����: ������� ����������(� ���)
	������: ���������� � ��������� � ���� �������, �� ���������� ��������� �������� ������� �������

*/
inline bool isEven(int value) 
{ 
	return value % 2 == 0; 
}
/*
	������� 1. ������� ����������� �������� �����
	��� ����������� �������� ������������ ��������� � � ������,
	����� ���������� ��������� ��� �����
	�����: ������� �������� ���� ������� 
	��-�� �������� ������
*/
inline bool isEven2(int value)
{
	return !(value & 0x00000001);
}

