@echo off
rem 这是一个用于代码提交的bat文件

git add .

git commit -m "%date%"

git push origin master

echo commit successfully

pause