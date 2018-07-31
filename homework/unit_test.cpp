#include"maze.h"
#define HEAD \
    do{  \
     printf("\n----------------%s----------------\n",__FUNCTION__); \
    }while(0)

void test_without_semicolon(){
  HEAD;
  cout << "expect : " << ErrorString[Maze::number_format_error] <<endl;
  vector<string> input(2);
  input[0] = "3,3";
  input[1] = "0,0 0,1, 0,0 0,2";
  Maze m(input);
  m.Input = input;
  Maze::ret_code ret = m.input_check();
  if(ret != Maze::sucess)
  cout<<"actual : " <<  ErrorString[ret] <<endl;
}
void test_nonnumber()
{
  HEAD;
  cout << "expect : " << ErrorString[Maze::invalid_input] <<endl;
  vector<string> input(2);
  input[0] = "3,3";
  input[1] = "0,0 a,1;0,0 0,2";
  Maze m(input);
  m.Input = input;
  Maze::ret_code ret = m.input_check();
  m.Print_Input();
  if(ret != Maze::sucess)
  cout<<"actual : " <<  ErrorString[ret] <<endl;

}

void test_empty_input()
{
  HEAD;
  cout << "expect : " << ErrorString[Maze::number_format_error] <<endl;
  vector<string> input(2);
  input[0] = "3,3";
  input[1] = "";
  Maze m(input);
  m.Input = input;
  Maze::ret_code ret = m.input_check();
  m.Print_Input();
  if(ret != Maze::sucess)
  cout<<"actual : " <<  ErrorString[ret] <<endl;


}
void test_negative_input()
{
  HEAD;
  cout << "expect : " << ErrorString[Maze::number_range] <<endl;
  vector<string> input(2);
  input[0] = "3,3";
  input[1] = "0,1 0,-1;0,1 0,0";
  Maze m(input);
  m.Input = input;
  Maze::ret_code ret = m.input_check();
  m.Print_Input();
  if(ret != Maze::sucess)
  cout<<"actual : " <<  ErrorString[ret] <<endl;

}
void test_out_of_range_input()
{
  HEAD;
  cout << "expect : " << ErrorString[Maze::number_range] <<endl;
  vector<string> input(2);
  input[0] = "3,3";
  input[1] = "0,1 0,3;0,1 0,0";
  pair<int,int> s = {3,3};
  Maze m(input);
  Maze::ret_code ret = m.input_check();
  m.Print_Input();
  if(ret != Maze::sucess)
  cout<<"actual : " <<  ErrorString[ret] <<endl;

}
void test_incompleted_input()
{
  HEAD;
  cout << "expect : " << ErrorString[Maze::number_format_error] <<endl;
  vector<string> input(2);
  input[0] = "3,3";
  input[1] = "0,1 0,";
  Maze m(input);
  m.Input = input;
  Maze::ret_code ret = m.input_check();
  m.Print_Input();
  if(ret != Maze::sucess)
  cout<<"actual : " <<  ErrorString[ret] <<endl;

}
void test_input()
{

  //test_without_semicolon();
  //test_nonnumber();
  //test_empty_input();
  //test_negative_input();
  //test_out_of_range_input();
  //test_incompleted_input();
}
void test_print()
{
  HEAD;
  //cout << "expect : " << ErrorString[Maze::number_format_error] <<endl;
  vector<string> input(2);
  input[0] = "3,3";
  input[1] = "0,1 0,2;0,0 1,0;0,1 1,1;0,2 1,2;1,0 1,1;1,1 1,2;1,1 2,1;1,2 2,2;2,0 2,1";
  Maze m(input);
  m.connecte();
  m.Print();

}
void test_row_print()
{
  HEAD;
  vector<string> input(2);
  input[0] = "3,3";
  input[1] = "0,0 0,1";
  pair<int,int> s = {3,3};
  Maze m(input);
  m.connecte();
  m.Print();

}
void test_col_print()
{
  HEAD;
  vector<string> input(2);
  input[0] = "3,3";
  input[1] = "0,0 1,0";
  Maze m(input);
  m.connecte();
  m.Print();
}

void test_adjacent_print()
{
  HEAD;
  vector<string> input(2);
  input[0] = "3,3";
  input[1] = "0,0 2,2";
  Maze m(input);
  m.connecte();
  m.Print();

}
int main()
{
  //test_print();
  vector<string> input(2);
  int count = 0;
  while(getline(cin,input[count++]))
  {
    if(count >= 2)
    break;
  }
  Maze m(input);
  m.connecte();
  m.Print();


  //test_print();
  //test_row_print();
  //test_col_print();
  //test_adjacent_print();
}
