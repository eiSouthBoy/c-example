# dance partner

舞者匹配问题：在舞场有男、女若干人，需要让一男一女组成一个队伍，将舞场所有人进行组队后，剩下多个男士和女士为组队？

使用队列结构处理此类问题。

1、创建一个男士队列，将所有男士进行排队。另外创建一个女士队列，将所有女士进行排队。
2、若男士队列和女士队列不为空，则各自队列出一人进行组队，直到男士队列或女士队列为空


**编译和运行**

编译项目：

```bash
cd 001-dance-partner
mkdir -p build && cd build
cmake ..
make
```

运行可执行文件：

```bash
001-dance-partner/build$ ./dance_partner 
Please input numbers of dancer(numbers > 0):2

Please input dancer info(name and sex).
the input format is name \space sex.
name: max len is 10 characters.
sex: M is male, F is female. you can only input M or F.
The 1 dancer info:Zhangsan M
The 2 dancer info:Lisi F

1 dance team: [Zhangsan(M), Lisi(F)]
After male and female combine a team, numbers of surplus male: 0
After male and female combine a team, numbers of surplus female: 0
```