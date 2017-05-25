@ECHO OFF
SortingDemo.exe -algo both -loop 3 -size 100 > summary.txt
SortingDemo.exe -algo both -loop 3 -size 500 >> summary.txt
SortingDemo.exe -algo both -loop 3 -size 1000 >> summary.txt
echo Saved results to summary.txt
pause