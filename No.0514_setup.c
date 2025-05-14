#include <stdlib.h>

int main(){
  system("echo \" \" >> .bashrc");
  system("echo \"function GPIO(){\" >> .bashrc");
  system("echo \"  if [ \\$2 = 0 ]; then\" >> .bashrc");
  system("echo \"    pinctrl -e set \\$1 op dl\" >> .bashrc");
  system("echo \"  else\" >> .bashrc");
  system("echo \"    pinctrl -e set \\$1 op dh\" >> .bashrc");
  system("echo \"  fi\" >> .bashrc");
  system("echo \"}\" >> .bashrc");
  system("echo \" \" >> .bashrc");
  system("echo \"function ce(){\" >> .bashrc");
  system("echo \"  gcc -Wall -pthread \\$1 -lpigpiod_if2 -lrt\" >> .bashrc");
  system("echo \"}\" >> .bashrc");
}
