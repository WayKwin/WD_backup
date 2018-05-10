#include<iostream>
#include<string>
#include<vector>
using namespace::std;
class Screen
{
public :
	typedef  string::size_type pos;
	//���� mutalbe����
	void some_member() const;
	//using pos = string::size_type;
	//���캯��
	Screen() = default;
	Screen(pos hi, pos wi, char c) :height(hi), width(wi), contents(hi*wi, c){};//String����������ʼ��
	//��Ա����Ĭ�����������͵�
	char get(){ return contents[cursor]; }
	inline char get(pos hi, pos wd) const;
	Screen &move(pos r, pos c);
	//7.3.2��������
	Screen& set(char);
	Screen& set(pos, pos, char);
private:
	//�ɱ����ݳ�Ա��const�������� �������Ҳ���޸��� L40
	mutable size_t access_ctr;
	pos cursor = 0;
	pos height = 0, width = 0;
	string contents;
};
inline char Screen::get(pos r, pos c) const
{
	pos row = r*width;
	//ע�� ����const����, �Ǿ�̬��Ա���������޸�
	//contents = "abcd";
	return contents[row + c];
}
inline Screen &Screen::move(pos r, pos c)
{

	pos row = r*width;
	cursor = row + c;
	return *this;
}
void Screen::some_member() const
{
	access_ctr++;
}
class Window_mgr
{
private :
	//�����ݳ�Ա�ĳ�ʼֵ
	//һ��Screen����Vector�� Ĭ�ϳ�ʼֵ����һ���ض�Screen����;
	vector<Screen> Screens{ Screen(20, 80, ' ') };
};
inline Screen& Screen::set(char c)
{
	contents[cursor] = c;//���õ�ǰλ��ΪC
	return *this;
}
inline Screen& Screen::set(pos r, pos col, char ch)
{
	contents[r*width + col] = ch;
	return *this;
}
int main()
{
	Screen MyScreen;
	//���õ�������������ֵ��������,
	//����������һ�������Ͻ��еĲ���
	//��move����screen ��ôset��������screen���еĲ���
	MyScreen.move(4, 0).set('*');
}