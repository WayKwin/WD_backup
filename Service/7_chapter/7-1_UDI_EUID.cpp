#include<unistd.h>
#include<stdio.h>
static bool switch_to_user(uid_t user_id,gid_t usr_gid)
{
  //不能切换为roo用户
  if(user_id == 0 && usr_gid == 0)
  {
    return false;
  }
  gid_t gid = getgid();
  uid_t uid = getuid();
  //当前用户必须是 root 或者目的用户

}
int main()
{
  //权限S 改密码  特权位
  uid_t uid = getuid();
  uid_t euid = geteuid();
  printf("userid is %d,effective userid is : %d \n",uid,euid);
  return 0;
}
