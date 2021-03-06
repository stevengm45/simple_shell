#include "holberton.h"

/**
* verify_access - shell function
* @full_path: absolute path to the executable command
* @buffer: additional arguments
* @argv: arguments we pass to the program
* @count: count of lines
* Description: Verify if the executable command exists in
* the full path
* Return: 1 if command has founded in some of the directories of
* PATH. Otherwise returns 0
*/

int verify_access(char *full_path, char **buffer, char **argv, int count)
{
	int verify_access, access_flag, status;
	pid_t id_child = 0;
	(void)argv;
	(void) count;

	access_flag = 0;
	verify_access = access(full_path, F_OK);

	if (verify_access == 0)
	{
		id_child = fork();
		if (id_child == 0)
			execute_function(full_path, buffer);
		else if (id_child > 0)
			wait(&status);
		else
			perror("Could not create process");
	}
		else
		{
			access_flag = -1;
		}

	return (access_flag);
}
/**
* print_err - print error in non-interactive mode
* @count: number of line
* @argv: name of the file
* @buffer: command we pass to the program
*/
void print_err(int count, char **argv, char **buffer)
{
	int verify = 0;

	verify = verify_access(*buffer, buffer, argv, count);
	if (verify != 0)
	{
		_puts(argv[0]);
		_puts(separator);
		putchar_func(count + '0');
		_puts(separator);
		_puts(*buffer);
		_puts(": not found");
		_puts("\n");
		exit(127);
	}
}
