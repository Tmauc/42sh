/*
** EPITECH PROJECT, 2018
** get_child_status.c
** File description:
** ...
*/

#include "my.h"

static exit_status fork_signals_msg[] = {
	{SIGHUP, "Hangup"},
	{SIGINT, "Interrupt"},
	{SIGQUIT, "Quit"},
	{SIGILL, "Illegal instruction"},
	{SIGTRAP, "Trace/BPT trap"},
	{SIGABRT, "Abort"},
	{SIGFPE, "Floating exception"},
	{SIGKILL, "Killed"},
	{SIGUSR1, "User signal 1"},
	{SIGUSR2, "User signal 2"},
	{SIGSEGV, "Segmentation fault"},
	{SIGBUS, "Bus error"},
	{SIGSYS, "Bad system call"},
	{SIGALRM, "Alarm clock"},
	{SIGTERM, "Terminated"},
	{SIGCHLD, "Child stopped or exited"},
	{SIGCHLD, "Child exited"},
	{SIGURG, "Urgent condition on I/O channel"},
	{SIGSTOP, "Suspended (signal)"},
	{SIGSTOP, "Stopped (signal)"},
	{SIGTSTP, "Suspended"},
	{SIGTSTP, "Stopped"},
	{SIGCONT, "Continued"},
	{SIGTTIN, "Suspended (tty input)"},
	{SIGTTIN, "Stopped (tty input)"},
	{SIGTTOU, "Suspended (tty output)"},
	{SIGTTOU, "Stopped (tty output)"},
	{SIGXCPU, "Cputime limit exceeded"},
	{SIGXFSZ, "Filesize limit exceeded"},
	{SIGPROF, "Profiling time alarm"},
	{SIGPOLL, "Pollable event occured"},
	{SIGVTALRM, "Virtual time alarm"},
	{SIGWINCH, "Window size changed"},
	{-84, "END"}
};

static int display_status_child(int status, int i)
{
	if (WTERMSIG(status) == fork_signals_msg[i].code) {
		printf("%s", fork_signals_msg[i].msg);
		if (WCOREDUMP(status))
			printf(" (core dumped)");
		printf("\n");
		status = (status < 30 && status > 4 ? status + 128 : status);
	}
	return (status);
}

int get_status_child(int pid)
{
	int status = 1;

	if (waitpid(pid, &status, WUNTRACED | WCONTINUED) == -1)
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		for (int i = 0; fork_signals_msg[i].code != -84; i++)
			status = display_status_child(status, i);
	return (status);
}
