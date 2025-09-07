/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baelgadi <baelgadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 00:29:47 by baelgadi          #+#    #+#             */
/*   Updated: 2025/09/08 01:06:40 by baelgadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_bit_ack;

static int	print_error_and_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

static void	server_ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_bit_ack = 1;
	if (sig == SIGUSR2)
		ft_putstr_fd("\033[34m Delivered.\n \033[0m", 1);
}

static void	transmit_char(pid_t server_pid, unsigned char c)
{
	int	i;
	int	signal;

	i = 8;
	while (i > 0)
	{
		i--;
		g_bit_ack = 0;
		if (((c >> i) & 1) == 1)
			signal = SIGUSR2;
		else
			signal = SIGUSR1;
		if (kill(server_pid, signal) == -1)
			print_error_and_exit("Error: Failed to send signal.\n");
		while (g_bit_ack == 0)
			usleep(100);
	}
}

static void	transmit_msg(pid_t server_pid, const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		transmit_char(server_pid, str[i++]);
	transmit_char(server_pid, '\0');
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	pid_t				server_pid;

	if (ac != 3 || !av[2][0])
		print_error_and_exit("Error: Use ./client <server_PID> \"message\".\n");
	server_pid = ft_atoi(av[1]);
	if (server_pid <= 0 || kill(server_pid, 0) == -1)
		print_error_and_exit("Error: PID is invalid.\n> pgrep server.\n");
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &server_ack_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		print_error_and_exit("Error: Failed to set up the SIGUSR1 handler.\n");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		print_error_and_exit("Error: Failed to set up the SIGUSR2 handler.\n");
	transmit_msg(server_pid, av[2]);
	ft_putstr_bin_fd(av[2], 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
