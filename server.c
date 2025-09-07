/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baelgadi <baelgadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 00:29:35 by baelgadi          #+#    #+#             */
/*   Updated: 2025/09/08 01:06:35 by baelgadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

static void	handle_char(unsigned char character, pid_t pid)
{
	if (character == '\0')
	{
		ft_putchar_fd('\n', 1);
		if (kill(pid, SIGUSR2) == -1)
			ft_putstr_fd("Error: Failed to acknowledge client.\n", 2);
	}
	else
		ft_putchar_fd(character, 1);
}

static void	client_sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	received_char;
	static int				bits_received;
	static pid_t			s_client_pid;

	(void)ucontext;
	if (s_client_pid != info->si_pid)
	{
		s_client_pid = info->si_pid;
		received_char = 0;
		bits_received = 0;
		ft_putchar_fd('\n', 1);
	}
	received_char = (received_char << 1) | (sig == SIGUSR2);
	bits_received++;
	if (bits_received == 8)
	{
		handle_char(received_char, info->si_pid);
		bits_received = 0;
		received_char = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_putstr_fd("Error: Failed to acknowledge client.\n", 2);
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &client_sig_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		print_error("Error: Failed to set up SIGUSR1 handler.\n");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		print_error("Error: Failed to set up SIGUSR2 handler.\n");
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
}
