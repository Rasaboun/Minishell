#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <term.h>
#include <curses.h>
#include<signal.h>

void sig_handler(int signum){

  //Return type of the handler function should be void
  write(1,"CONTROL C",10);
}


int main()
{

	while(1)
	{
		signal(SIGINT,sig_handler);
		printf("%s\n",readline("\x1b[36m❯ \x1b[35m(Minishell)\x1b[37m "));
		
	}


}