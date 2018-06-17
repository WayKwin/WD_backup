-- 
select ename,sql,job from emp where(sal > 500 or job = 'MANAGER') and ename like 'J%';
-- 年薪降序排列
select ename,(sal*12 + ifnull(comm,0)) year_sal from emp order by year_sal desc;
-- 显示工资最高的员工的名字和工作岗位
select ename,job,sal from emp where sal  = select max(sal) from emp;
-- 显示工作最高的员工的名字
select ename,job,sal from emp where sal  = select avg(sal) from emp;
-- 显示每个部门的平均工资和最高工资
select avg(sal),max(sal),deptno from emp group by deptno;
-- 显示 平均工资定于2000的 部门号和它的平均工资
select avg(sal) as avg_sal,deptno from emp group by deptno having avg_sal < 2000;

