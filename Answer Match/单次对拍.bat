@echo off

rand.exe  %random% > data.in
std.exe < data.in > std.out
my.exe < data.in > my.out

fc std.out my.out
pause